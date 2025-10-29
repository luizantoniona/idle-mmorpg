import { Injectable } from "@angular/core";
import { readDir, BaseDirectory } from "@tauri-apps/plugin-fs";

@Injectable({ providedIn: "root" })
export class FileSystemService {

    constructor() { }

    async readDirectory(path: string = "", base: BaseDirectory = BaseDirectory.Home) {
        try {
            const entries = await readDir(path, { baseDir: base });
            return entries;

        } catch (error) {
            console.error("Error", error);
            return [];
        }
    }
}
