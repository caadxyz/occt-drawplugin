### Extending Test Harness with custom commands

How to extend Test Harness with custom commands and how to activate them using a plug-in mechanism?


```
static Standard_Integer myDrawCommand(Draw_Interpretor& di, Standard_Integer argc, char** argv)
{
...
}
```

Registration of commands in Test Harness
To become available in the Test Harness the custom command must be registered in it. This should be done as follows.

```
void MyDrawPlugin::CommonCommands(Draw_Interpretor& theCommands)
{
...
char* g = "myCommands";
theCommands.Add ( "myDrawCommand", "myDrawCommand Description",
                  __FILE__, myDrawCommand, g );
...
}
```

Creating a toolkit (library) as a plug-in
All custom commands are compiled and linked into a dynamic library (.dll on Windows, or .so on Unix/Linux). 
To make Test Harness recognize it as a plug-in it must respect certain conventions. Namely, it must export function PLUGINFACTORY() accepting the Test Harness interpreter object (Draw_Interpretor). This function will be called when the library is dynamically loaded during the Test Harness session.

This exported function PLUGINFACTORY() must be implemented only once per library.

For convenience the DPLUGIN macro (defined in the Draw_PluginMacro.hxx file) has been provided. It implements the PLUGINFACTORY() function as a call to the Package::Factory() method and accepts Package as an argument. Respectively, this Package::Factory() method must be implemented in the library and activate all implemented commands.

```
#include <Draw_PluginMacro.hxx>
void MyDrawPlugin::Factory(Draw_Interpretor& theDI)
{
...
//
MyDrawPlugin::CommonCommands(theDI);
...
}
// Declare entry point PLUGINFACTORY
DPLUGIN(MyDrawPlugin)
```

Creation of the plug-in resource file
As mentioned above, the plug-in resource file must be compliant with Open CASCADE Technology requirements (see Resource_Manager.hxx file for details). In particular, it should contain keys separated from their values by a colon (;:;). For every created plug-in there must be a key. For better readability and comprehension it is recommended to have some meaningful name. Thus, the resource file must contain a line mapping this name (key) to the library name. The latter should be without file extension (.dll on Windows, .so on Unix/Linux) and without the ;lib; prefix on Unix/Linux. For several plug-ins one resource file can be created. In such case, keys denoting plug-ins can be combined into groups, these groups – into their groups and so on (thereby creating some hierarchy). Any new parent key must have its value as a sequence of child keys separated by spaces, tabs or commas. Keys should form a tree without cyclic dependencies.

Examples (file MyDrawPlugin):

```
! Hierarchy of plug-ins
ALL                : ADVMODELING, MESHING
DEFAULT            : MESHING
ADVMODELING        : ADVSURF, ADVCURV
! Mapping from naming to toolkits (libraries)
ADVSURF            : TKMyAdvSurf
ADVCURV            : TKMyAdvCurv
MESHING            : TKMyMesh
```

For other examples of the plug-in resource file refer to the Plug-in resource file chapter above or to the $CASROOT/src/DrawPlugin file shipped with Open CASCADE Technology.

Dynamic loading and activation
Loading a plug-in and activating its commands is described in the Activation of the commands implemented in the plug-in chapter.

The procedure consists in defining the system variables and using the pload commands in the Test Harness session.


```
Draw[]> set env(CSF_MyDrawPluginDefaults) /users/test
Draw[]> pload -MyDrawPlugin ALL
```
