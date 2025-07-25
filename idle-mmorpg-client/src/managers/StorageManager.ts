export const StorageManager = {
    get<T>(key: string, storage: Storage = localStorage): T | null {
        const raw = storage.getItem(key);
        return raw ? JSON.parse(raw) : null;
    },

    set<T>(key: string, value: T, storage: Storage = localStorage) {
        storage.setItem(key, JSON.stringify(value));
    },

    remove(key: string, storage: Storage = localStorage) {
        storage.removeItem(key);
    },
};
