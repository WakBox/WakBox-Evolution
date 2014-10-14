#ifndef SCRIPTMGR_H
#define SCRIPTMGR_H

#include <QtCore>
#include "Utils/Singleton.h"
#include "Miscellaneous/SharedDefines.h"
#include "Define.h"
#include "Entities/Character/Character.h"

class Character;

class ScriptObject
{
    friend class ScriptMgr;

public:
    ScriptObject(const QString& name) : m_name(name) {}
    virtual ~ScriptObject() {}

    const QString& GetName() const { return m_name; }

private:
    const QString m_name;
};

class ServerScript : public ScriptObject
{
public:
    ServerScript(const QString& name);

    virtual void OnLoad() {}
    virtual void OnUpdate(quint64 /*diff*/) {}
};

class InteractiveElementScript : public ServerScript
{
public:
    InteractiveElementScript(const QString& name);

    virtual void OnActive(Character* /*character*/, InteractiveElementType /*type*/) {}
};

class ScriptMgr : public Singleton<ScriptMgr>
{
    friend class ScriptObject;

public:
    ScriptMgr();
    ~ScriptMgr();

    void Initialize();

    // ServerScript hooks
    void OnLoad();
    void OnUpdate(quint64 diff);

    // Interactive elements scripts
    void OnInteractiveElementActive(Character* character, quint32 interactiveElementId, InteractiveElementType type);

private:
};

#define sScriptMgr ScriptMgr::Instance()

#endif // SCRIPTMGR_H
