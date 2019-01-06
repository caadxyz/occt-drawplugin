#include <stdio.h>
#include <Standard.hxx>
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw_PluginMacro.hxx>

static Standard_Integer MyDrawCommand (Draw_Interpretor& theInterpretor,
                                         Standard_Integer  argc,
                                         const char**      argv)
{
  theInterpretor << "Test MyDrawCommand" << "\n";
  return 0;
}


class MyDrawPlugin
{
public:
  DEFINE_STANDARD_ALLOC
  Standard_EXPORT static void CommonCommands (Draw_Interpretor& DI);
  Standard_EXPORT static void Factory (Draw_Interpretor& DI);
};

void MyDrawPlugin::CommonCommands (Draw_Interpretor& theCommands)
{
  const char* group = "MyCommands";
  theCommands.Add ("MyDrawCommand",
                   "MyDrawCommand Description",
                   __FILE__,
                   MyDrawCommand,
                   group);
}

void MyDrawPlugin::Factory(Draw_Interpretor& theCommands)
{
  MyDrawPlugin::CommonCommands(theCommands);
}

// Declare entry point PLUGINFACTORY
DPLUGIN(MyDrawPlugin)
