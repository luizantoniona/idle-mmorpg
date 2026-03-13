## ⚔️ [`idle-mmorpg-client`](https://github.com/luizantoniona/idle-mmorpg/tree/main/idle-mmorpg-client)
- **Web Client**
  - Responsible for rendering the game UI, receiving real-time updates via WebSocket, and sending player updates to the server.
  - Built with **Angular** and **Typescript**.

### 📖 **Documentation**:  
Refer to the root `documentation/` folder for the HTTP API and WebSocket protocol:
- [`API.md`](../documentation/API.md)
- [`WebSocket.md`](../documentation/WebSocket.md)

### **GithubPages Deploy**
Use the scripts in package.json with npm
```
npm run build:prod
npm run deploy
```