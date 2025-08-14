# 📘 API Documentation

## GET /status

**Description:** Checks if the server is active.

Response:
```json
{
  "message": "Server Active"
}
```
---

## POST /login

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

## POST /logout

**Description:** Logs out the current session.

Request Header:
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

No Body:
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

## POST /sign

**Description:** Registers a new user. (Not yet implemented)

---

## POST /character

**Description:** Creates a new character.

Request Header:
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

Body:
```json
{
  "name": "Character Name"
}
```

Response:
```json
{
  "message": "Character created"
}
```

---

## GET /characters

**Description:** Lists all characters of the logged-in user.

Request Header:
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

No Body:
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
    ...
  }
]
```