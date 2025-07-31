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

## Development server

To start a local development server, run:

```bash
ng serve
```

Once the server is running, open your browser and navigate to `http://localhost:4200/`. The application will automatically reload whenever you modify any of the source files.

## Code scaffolding

Angular CLI includes powerful code scaffolding tools. To generate a new component, run:

```bash
ng generate component component-name
```

For a complete list of available schematics (such as `components`, `directives`, or `pipes`), run:

```bash
ng generate --help
```

## Building

To build the project run:

```bash
ng build
```

This will compile your project and store the build artifacts in the `dist/` directory. By default, the production build optimizes your application for performance and speed.

## Running unit tests

To execute unit tests with the [Karma](https://karma-runner.github.io) test runner, use the following command:

```bash
ng test
```

## Running end-to-end tests

For end-to-end (e2e) testing, run:

```bash
ng e2e
```

Angular CLI does not come with an end-to-end testing framework by default. You can choose one that suits your needs.

## Additional Resources

For more information on using the Angular CLI, including detailed command references, visit the [Angular CLI Overview and Command Reference](https://angular.dev/tools/cli) page.
