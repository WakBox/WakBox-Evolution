#include "Object.h"
#include "Entities/Character/Character.h"

Object::Object()
{
    m_guid          = 0;
    m_typeId        = TYPEID_OBJECT;
    m_inWorld       = false;
}

Object::~Object()
{

}

void Object::SetInWorld(bool inWorld)
{
    m_inWorld = inWorld;

    // TMP?
    if (Character* character = ToCharacter())
    {
        if (inWorld)
            sWorld->AddCharacter(character->GetName(), character);
        else
        {
            character->SendActorDespawn();
            sWorld->RemoveCharacterByName(character->GetName());
        }
    }
}
