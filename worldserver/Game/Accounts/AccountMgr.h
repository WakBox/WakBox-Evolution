#ifndef ACCOUNTMGR_H
#define ACCOUNTMGR_H

#include "Databases/Database.h"
#include "Utils/Singleton.h"

class AccountMgr : public Singleton<AccountMgr>
{
public:
    AccountMgr();
    ~AccountMgr();
private:

};

#endif // ACCOUNTMGR_H
