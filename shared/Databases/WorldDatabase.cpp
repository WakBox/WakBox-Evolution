#include "WorldDatabase.h"

void WorldDatabase::LoadQueries()
{
    LoadQuery(SELECT_CREATURES, "SELECT * FROM creatures");
    LoadQuery(SELECT_INTERACTIVE_ELEMENTS, "SELECT * FROM interactive_elements");
}
