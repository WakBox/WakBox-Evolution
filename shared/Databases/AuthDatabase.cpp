#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_USERNAME, "SELECT * FROM account WHERE username = ?");
    LoadQuery(SELECT_REALMS, "SELECT * FROM realms ORDER BY realm_id DESC");
}
