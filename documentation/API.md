# 📘 API Documentation

This document lists the HTTP endpoints exposed by the **idle‑mmorpg** server. All routes are relative to the base URL (by default `http://localhost:8080`).

### ✋ Authentication
- Most endpoints require a valid session token in the `Authorization` header.
- The header format is: `X-Session <sessionId>` (e.g. `X-Session 5f5c...7a`).

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

## 📝 POST /sign

**Description:** Create a new user account and automatically log them in.

**Request body** *(application/json)*:
```json
{
  "username": "newplayer",
  "password": "securepwd"
}
```

**Responses:**
- *201 Created* with session details on success.
- *400 Bad Request* when required fields are missing or empty.
- *409 Conflict* if the username already exists.

**Success Example**:
```json
{
  "userID": 5,
  "username": "newplayer",
  "sessionID": "fa3d...01",
  "message": "User created successfully"
}
```

---

## 🧱 POST /character/create

**Description:** Create a new character for the authenticated user.

**Request headers:**
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

**Request body** *(application/json)*:
```json
{
  "name": "Character Name"
}
```

**Success Response** *(201 Created)*:
```json
{
  "message": "Character created",
  "idCharacter": 42
}
```

Errors:
- *400 Bad Request* if the payload is malformed or missing `name`.
- *401 Unauthorized* when the session is invalid.
- *500 Internal Server Error* on unexpected failures.

---

## 🗑️ POST /character/remove

**Description:** Delete one of the user's characters.

**Request headers:**
```json
{
  "Authorization": "X-Session 5f5c...7a"
}
```

**Request body** *(application/json)*:
```json
{
  "characterId": 42
}
```

**Success Response** *(200 OK)*:
```json
{
  "message": "Character removed"
}
```

Possible error codes include *400*, *401*, *403* (forbidden), and *500* as noted above.

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
