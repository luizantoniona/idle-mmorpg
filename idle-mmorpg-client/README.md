# Idle RPG Client
TODO

```
idle-mmorpg-client
├── eslint.config.js
├── index.css
├── index.html
├── index.tsx
├── package-lock.json
├── package.json
├── README.md
├── tsconfig.app.json
├── tsconfig.json
├── tsconfig.node.json
├── vite.config.ts
└── src
    ├── App.css
    ├── App.tsx
    ├── vite-env.d.ts
    ├── components
    │   ├── atoms
    │   │   ├── index.ts
    │   │   ├── Button
    │   │   │   ├── Button.css
    │   │   │   └── Button.tsx
    │   │   ├── InputField
    │   │   │   ├── InputField.css
    │   │   │   └── InputField.tsx
    │   │   ├── Loading
    │   │   │   ├── Loading.css
    │   │   │   └── Loading.tsx
    │   │   ├── Panel
    │   │   │   ├── Panel.css
    │   │   │   ├── Panel.tsx
    │   │   │   ├── PanelHorizontal.tsx
    │   │   │   └── PanelVertical.tsx
    │   │   └── StatusCircle
    │   │       ├── StatusCircle.css
    │   │       └── StatusCircle.tsx
    │   ├── molecules
    │   │   ├── index.ts
    │   │   ├── Card
    │   │   │   ├── CharacterCard.css
    │   │   │   └── CharacterCard.tsx
    │   │   └── Form
    │   │       ├── LoginForm.css
    │   │       ├── LoginForm.tsx
    │   │       ├── ServerForm.css
    │   │       └── ServerForm.tsx
    │   ├── organisms
    │   │   ├── index.ts
    │   │   ├── List
    │   │   │   ├── CharacterList.css
    │   │   │   └── CharacterList.tsx
    │   │   └── Panel
    │   │       ├── CharacterActionPanel.tsx
    │   │       ├── CharacterAttributesPanel.tsx
    │   │       ├── CharacterEquipamentPanel.tsx
    │   │       ├── CharacterInventoryPanel.tsx
    │   │       ├── CharacterSkillsPanel.tsx
    │   │       ├── CharacterVitalsPanel.tsx
    │   │       ├── CharacterWalletPanel.tsx
    │   │       ├── ChatPanel.tsx
    │   │       ├── MapActionsPanel.tsx
    │   │       └── MapPanel.tsx
    │   └── pages
    │       ├── index.ts
    │       ├── Account
    │       │   ├── AccountPage.css
    │       │   └── AccountPage.tsx
    │       ├── Game
    │       │   ├── GamePage.css
    │       │   ├── GamePage.tsx
    │       │   └── GamePageHooks.ts
    │       └── Login
    │           ├── LoginPage.css
    │           └── LoginPage.tsx
    ├── contexts
    │   ├── AuthContext.tsx
    │   └── ServerContext.tsx
    ├── managers
    │   ├── AuthManager.ts
    │   ├── ServerManager.ts
    │   └── StorageManager.ts
    ├── models
    │   ├── index.ts
    │   ├── Character
    │   │   ├── Character.ts
    │   │   ├── CharacterAction.ts
    │   │   ├── CharacterAttributes.ts
    │   │   ├── CharacterEquipament.ts
    │   │   ├── CharacterInventory.ts
    │   │   ├── CharacterProgression.ts
    │   │   ├── CharacterSkill.ts
    │   │   ├── CharacterVitals.ts
    │   │   └── CharacterWallet.ts
    │   ├── Item
    │   │   └── Item.ts
    │   └── Map
    │       ├── Map.ts
    │       └── MapAction.ts
    └── services
        ├── APIService.ts
        └── WsService.ts
```