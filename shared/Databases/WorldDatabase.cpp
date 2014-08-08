#include "WorldDatabase.h"

void WorldDatabase::LoadQueries()
{
    LoadQuery(SELECT_INTERACTIVE_ELEMENTS, "SELECT * FROM interactive_elements");
}
