#include "AccountMgr.h"

template<> AccountMgr*  Singleton<AccountMgr>::m_instance = 0;

/*
Account* ObjectFactory::GetAccount(int id)
{
    if(m_accounts.contains(id))
        return m_accounts.value(id);
    else
        return NULL;
}

Character* ObjectFactory::GetCharacter(int id)
{
    if(m_characters.contains(id))
        return m_characters.value(id);
    else
        return NULL;
}

Character* ObjectFactory::CreateCharacter(int account, QString name, int breed, int gender, int gfxId, char* color1, char* color2, char* color3)
{
    if(!m_accounts.contains(account))
        return NULL;

    Database::Char()->PQuery(INSERT_NEW_CHAR, account, name.toLatin1().data(), breed, gender, gfxId, color1, color2, color3);
    QList<Character*> charsCreated = LoadAccountCharacters(m_accounts.value(account));
    Database::Auth()->PQuery(AUTH_UPDATE_ACCOUNT_CHARS, account, ConfigMgr::Instance()->World()->GetInt("ServerId"), m_accounts.value(account)->GetCharacters()->count());
    if(charsCreated.isEmpty())
        return NULL;
    else
        return charsCreated.last();
}
*/
