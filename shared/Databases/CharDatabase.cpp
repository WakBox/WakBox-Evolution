#include "CharDatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_CHARACTERS_BY_ACCOUNT_ID, "SELECT * FROM characters WHERE account_id = ?");
    LoadQuery(SELECT_CHARACTER_BY_GUID, "SELECT * FROM characters WHERE guid = ?");
    LoadQuery(DELETE_CHARACTER_BY_GUID, "DELETE FROM characters WHERE guid = ?");
}
