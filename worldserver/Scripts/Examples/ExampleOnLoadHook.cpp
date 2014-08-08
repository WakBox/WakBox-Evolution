#include "Game/Scripting/ScriptMgr.h"
#include "Logs/Log.h"

class ExampleOnLoadHook : ServerScript
{
public:
    ExampleOnLoadHook() : ServerScript("example_onloadhook")
    {
    }

    void OnLoad()
    {
        Log::Write(LOG_TYPE_NORMAL, "ScriptMgr:: Script ExampleOnLoadHook is loaded (hook OnLoad).");
    }
};

void AddScript_ExampleOnLoadHook()
{
    new ExampleOnLoadHook();
}
