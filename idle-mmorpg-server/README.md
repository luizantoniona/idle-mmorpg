# ⚔️🛡️🏹🗡️ Idle RPG Server

Base URL: http://localhost:8080

## 📘 API Documentation

### GET /status

**Description:** Checks if the server is active.

Response:
```json
{
  "message": "Server Active"
}
```
---

### POST /login

**Description:** Authenticates a user and returns a sessionId.

Request Body:
```json
{
  "username": "teste",
  "password": "1234"
}
```

Response:
```json
{
  "userID": 1,
  "username": "teste",
  "sessionID": "5f5c...7a",
  "message": "Login successful"
}
```
---

### POST /logout

**Description:** Logs out the current session.

Request Header:
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

Request Body:
```json
{

}
```

Response:
```json
{
  "message": "Logout successful"
}
```

---

### POST /sign

**Description:** Registers a new user. (Not yet implemented)

---

### POST /adventurer

**Description:** Creates a new adventurer. (Not yet implemented)

---

### GET /adventurers

**Description:** Lists all adventurers of the logged-in user.

Request Header:
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

Request Body: TODO
```json
{
    
}
```

Response:
```json
[
  {
    "id": 1,
    "name": "Zeldar",
  }
]
```

---

### Webscoket


---

## Building:
```
git clone git@github.com:luizantoniona/idle-rpg-server.git
```