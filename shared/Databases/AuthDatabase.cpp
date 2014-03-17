#include "AuthDatabase.h"

void AuthDatabase::LoadQueries()
{
    LoadQuery(SELECT_ACCOUNT_BY_USERNAME, "SELECT * FROM account WHERE username = ?");
    LoadQuery(SELECT_WORLD_ID, "SELECT * FROM world_list WHERE world_id = ?");
}
