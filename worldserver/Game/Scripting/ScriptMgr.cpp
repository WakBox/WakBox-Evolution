#include "ScriptMgr.h"
#include "ScriptLoader.h"
#include "Entities/ObjectMgr.h"
#include "Logs/Log.h"

template<class T>
class ScriptRegistry
{
public:
    typedef QMap<QString, T*> ScriptsMap;
    typedef typename ScriptsMap::Iterator ScriptsMapItr;
    static ScriptsMap ScriptsList;

    static void AddScript(const QString &name, T* const script)
    {
        ScriptsList[name] = script;
    }

    static T* GetScriptByName(const QString &name)
    {
        ScriptsMapItr itr = ScriptsList.find(name);
        if (itr != ScriptsList.end())
            return itr.value();

        return NULL;
    }
};

// Utility macros to refer to the script registry.
#define SCR_REG_MAP(T) ScriptRegistry<T>::ScriptsMap
#define SCR_REG_ITR(T) ScriptRegistry<T>::ScriptsMapItr
#define SCR_REG_LST(T) ScriptRegistry<T>::ScriptsList

// Utility macros for looping over scripts.
#define FOR_SCRIPTS(T, C, E) \
if (SCR_REG_LST(T).empty()) \
return; \
for (SCR_REG_ITR(T) C = SCR_REG_LST(T).begin(); \
C != SCR_REG_LST(T).end(); ++C)

#define FOR_SCRIPTS_RET(T, C, E, R) \
if (SCR_REG_LST(T).empty()) \
return R; \
for (SCR_REG_ITR(T) C = SCR_REG_LST(T).begin(); \
C != SCR_REG_LST(T).end(); ++C)

#define FOREACH_SCRIPT(T) \
FOR_SCRIPTS(T, itr, end) \
(*itr)

// Utility macros for finding specific scripts.
#define GET_SCRIPT(T, I, V) \
    T* V = ScriptRegistry<T>::GetScriptByName(I); \
    if (!V) \
        return;

template<> ScriptMgr*  Singleton<ScriptMgr>::m_instance = 0;

ScriptMgr::ScriptMgr() {}
ScriptMgr::~ScriptMgr() {}

void ScriptMgr::Initialize()
{
    // Load C++ scripts
    LoadScripts();

    // Hook
    ScriptMgr::Instance()->OnLoad();
}

void ScriptMgr::OnLoad()
{
    FOREACH_SCRIPT(ServerScript)->OnLoad();
}

void ScriptMgr::OnUpdate(quint64 diff)
{
    FOREACH_SCRIPT(ServerScript)->OnUpdate(diff);
}

void ScriptMgr::OnInteractiveElementActive(Character* character, quint32 interactiveElementId, InteractiveElementType type)
{
    QString scriptName = ObjectMgr::Instance()->GetInteractiveElementScriptNameById(interactiveElementId);

    if (!scriptName.isEmpty())
    {
        GET_SCRIPT(InteractiveElementScript, scriptName, tmpScript);
        tmpScript->OnActive(character, type);
    }
    else
        Log::Write(LOG_TYPE_NORMAL, "No script found for interactive element %u !", interactiveElementId);
}

ServerScript::ServerScript(const QString &name) : ScriptObject(name)
{
    ScriptRegistry<ServerScript>::AddScript(name, this);
}

InteractiveElementScript::InteractiveElementScript(const QString &name) : ServerScript(name)
{
    ScriptRegistry<InteractiveElementScript>::AddScript(name, this);
}

// Instantiate static members of ScriptRegistry.
template<class T> QMap<QString, T*> ScriptRegistry<T>::ScriptsList;

// Specialize for each script type class like so:
template class ScriptRegistry<ServerScript>;
template class ScriptRegistry<InteractiveElementScript>;

// Undefine utility macros.
#undef SCR_REG_LST
#undef SCR_REG_ITR
#undef SCR_REG_MAP
#undef FOREACH_SCRIPT
#undef FOR_SCRIPTS_RET
#undef FOR_SCRIPTS
#undef GET_SCRIPT
