import { Component, Input, inject, Output, EventEmitter } from "@angular/core";

import { ButtonComponent } from "../../../../../component/button/button.component";

import { Character } from "../../../../../model";
import { Denizen } from "../../../../../model";
import { Item } from "../../../../../model";

import { WebsocketService } from "../../../../../service/websocket.service";

type TradeSelection = {
    [itemId: string]: number;
};

@Component({
    selector: "app-trade-panel",
    templateUrl: "./trade.panel.html",
    styleUrls: ["./trade.panel.scss"],
    imports: [
        ButtonComponent
    ],
})

export class TradePanel {
    @Input() denizen: Denizen | null = null;
    @Input() character!: Character;
    @Output() close = new EventEmitter<true>();

    private websocketService = inject(WebsocketService);

    sendMessage(data: any): void {
        this.websocketService.send(data);
    }

    getSellableItems(): Item[] {
        if (!this.denizen?.trade?.buy || !this.character) return [];
        return this.denizen.trade.buy.filter(item => {
            const charItem = this.character.inventory.items.find(i => i.id === item.id);
            return charItem && charItem.amount > 0;
        });
    }

    buySelection: TradeSelection = {};
    sellSelection: TradeSelection = {};

    onPlusClicked(item: Item, type: 'buy' | 'sell') {
        const selection = type === 'buy' ? this.buySelection : this.sellSelection;

        if (type === 'sell' && this.character) {
            const charItem = this.character.inventory.items.find(i => i.id === item.id);
            const maxQuantity = charItem?.amount || 0;

            if ((selection[item.id] || 0) >= maxQuantity) {
                return;
            }
        }

        selection[item.id] = (selection[item.id] || 0) + 1;
        this.updateCoinBreakdown();
    }

    onMinusClicked(item: Item, type: 'buy' | 'sell') {
        const selection = type === 'buy' ? this.buySelection : this.sellSelection;
        if (selection[item.id]) {
            selection[item.id] = Math.max(selection[item.id] - 1, 0);
        }
        this.updateCoinBreakdown();
    }

    getQuantity(item: Item, type: 'buy' | 'sell') {
        const selection = type === 'buy' ? this.buySelection : this.sellSelection;
        return selection[item.id] || 0;
    }

    getTotal(): number {
        let total = 0;

        Object.entries(this.buySelection).forEach(([itemId, quantity]) => {
            const item = this.denizen?.trade?.sell.find(i => i.id === itemId);
            if (item) total -= item.value * quantity;
        });

        Object.entries(this.sellSelection).forEach(([itemId, quantity]) => {
            const item = this.character.inventory.items.find(i => i.id === itemId);
            if (item) total += item.value * quantity;
        });

        return total;

    }

    coinBreakdown = { copper: 0, silver: 0, gold: 0 };

    updateCoinBreakdown() {
        let total = this.getTotal();

        const sign = total < 0 ? -1 : 1;
        total = Math.abs(total);

        const gold = Math.floor(total / 1_000_000);
        total -= gold * 1_000_000;

        const silver = Math.floor(total / 1_000);
        total -= silver * 1_000;

        const copper = total;

        this.coinBreakdown = { copper: copper * sign, silver: silver * sign, gold: gold * sign };
    }

    get hasSelection(): boolean {
        const totalBuy = Object.values(this.buySelection).reduce((a, b) => a + b, 0);
        const totalSell = Object.values(this.sellSelection).reduce((a, b) => a + b, 0);
        return (totalBuy + totalSell) > 0;
    }

    onConfirm() {
        this.sendMessage({
            type: 'CHARACTER_TRADE_DENIZEN',
            payload: {
                buy: Object.entries(this.buySelection).map(([itemId, quantity]) => ({ itemId, quantity })),
                sell: Object.entries(this.sellSelection).map(([itemId, quantity]) => ({ itemId, quantity })),
                denizenId: this.denizen?.id,
            }
        });

        this.buySelection = {};
        this.sellSelection = {};
        this.close.emit();
    }

    onCancel() {
        this.close.emit();
    }
}
