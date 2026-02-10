export class StorageManager {
    static get<T>(key: string, storage: Storage = localStorage): T | null {
        const raw = storage.getItem(key);
        return raw ? JSON.parse(raw) : null;
    }

    static set<T>(key: string, value: T, storage: Storage = localStorage): void {
        storage.setItem(key, JSON.stringify(value));
    }

    static remove(key: string, storage: Storage = localStorage): void {
        storage.removeItem(key);
    }
}
