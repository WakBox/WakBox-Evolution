#include "CharDatabase.h"

void CharDatabase::LoadQueries()
{
    LoadQuery(SELECT_CHARACTER_MAX_GUID, "SELECT MAX(guid) FROM characters");
    LoadQuery(SELECT_CHARACTERS_BY_ACCOUNT_ID, "SELECT * FROM characters WHERE account_id = ?");
    LoadQuery(SELECT_CHARACTER_BY_GUID, "SELECT * FROM characters WHERE guid = ?");
    LoadQuery(SELECT_CHARACTER_BY_GUID_AND_ACCOUNT, "SELECT * FROM characters WHERE guid = ? AND account_id = ?");
    LoadQuery(SELECT_CHARACTER_BY_NAME, "SELECT guid FROM characters WHERE name = ?");
    LoadQuery(DELETE_CHARACTER_BY_GUID, "DELETE FROM characters WHERE guid = ?");
    LoadQuery(INSERT_CHARACTER, "INSERT INTO characters VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
}
