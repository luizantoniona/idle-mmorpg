import { useState, useEffect } from "react";

interface InventoryItem {
    id: string;
    name: string;
    quantity: number;
}

interface Props {
    items?: InventoryItem[];
}

export function InventoryPanel({ items = [] }: Props) {
    const [inventory, setInventory] = useState<InventoryItem[]>(items);

    useEffect(() => {
        setInventory(items);
    }, [items]);

    return (
        <div>
            <h2>Inventory</h2>
            <ul>
                {inventory.map((item) => (
                    <li key={item.id}>
                        {item.name} x{item.quantity}
                    </li>
                ))}
            </ul>
        </div>
    );
}