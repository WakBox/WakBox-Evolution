#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_USERNAME, "SELECT * FROM accounts WHERE username = ?");
    LoadQuery(SELECT_REALMS, "SELECT * FROM realms ORDER BY realm_id DESC");

    LoadQuery(UPDATE_SESSION_TOKEN, "UPDATE accounts SET session_token = ? WHERE account_id = ?");
}
