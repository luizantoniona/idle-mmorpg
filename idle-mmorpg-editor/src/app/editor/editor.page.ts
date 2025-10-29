import { Component, OnInit } from "@angular/core";
import { CommonModule } from "@angular/common";
import { BaseDirectory } from "@tauri-apps/plugin-fs";

import { FileSystemService } from "../service/file-system.service";

import { FilePanelComponent } from "./component/file-panel.component";

@Component({
    selector: "app-editor-page",
    templateUrl: "./editor.page.html",
    styleUrls: ["./editor.page.scss"],
    imports: [
        CommonModule,
        FilePanelComponent,
    ],
})

export class EditorPage implements OnInit {

    constructor(private fsService: FileSystemService) { }

    async ngOnInit() {
        const files = await this.fsService.readDirectory("", BaseDirectory.Home);

        files.forEach(f => {
            console.log(f.name, f.isDirectory ? "(pasta)" : "(arquivo)");
        });
    }
}
