#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_USERNAME, "SELECT * FROM account WHERE username = ?");
}
