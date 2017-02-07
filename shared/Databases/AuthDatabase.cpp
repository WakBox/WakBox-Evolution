#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_USERNAME, "SELECT * FROM accounts WHERE username = ?");
    LoadQuery(SELECT_ACCOUNT_BY_TOKEN, "SELECT * FROM accounts WHERE session_token = ?");
    LoadQuery(SELECT_REALMS, "SELECT * FROM realms ORDER BY realm_id DESC");

    LoadQuery(UPDATE_SESSION_TOKEN, "UPDATE accounts SET session_token = ? WHERE account_id = ?");

    LoadQuery(INSERT_ACCOUNT, "INSERT INTO accounts (username, pseudo, hash_password) VALUES (?, ?, ?)");
}
