#ifndef OS_IOS
	#ifndef _DLL
		#ifndef BUILD_STATICLIB
			#include "App.h"
		#endif
	#endif

using namespace Leadwerks;

void DebugErrorHook(char* c)
{
	Leadwerks::System::Print(c);
	//=========================================================================================
	//=========================================================================================

	exit(1);//<--------------------------- Add a breakpoint here to catch errors
	
	//=========================================================================================
	//=========================================================================================
}

#ifdef __APPLE__
	int main_(int argc,const char *argv[]) {
#else
	int main(int argc,const char *argv[]) {
#endif

	//Load saved settings
	std::string settingsfile = std::string(argv[0]);
	settingsfile = FileSystem::StripAll(settingsfile);
	if (String::Right(settingsfile, 6) == ".debug") settingsfile = String::Left(settingsfile, settingsfile.length() - 6);
	std::string settingsdir = FileSystem::GetAppDataPath();

#ifdef __linux__
	#ifndef __ANDROID__
		settingsdir = settingsdir + "/." + String::Lower(settingsfile);
	#else
		settingsdir = settingsdir + "/" + settingsfile;
	#endif
#else
	settingsdir = settingsdir + "/" + settingsfile;
#endif
	if (FileSystem::GetFileType(settingsdir) == 0) FileSystem::CreateDir(settingsdir);
	settingsfile = settingsdir + "/" + settingsfile + ".cfg";
	System::LoadSettings(settingsfile);

	//Load command-line parameters
	System::ParseCommandLine(argc, argv);

	//Add debug hook for catching errors
	Leadwerks::System::AddHook(System::DebugErrorHook,(void*)DebugErrorHook);
	
    //Load any zip files in main directory
    Leadwerks::Directory* dir = Leadwerks::FileSystem::LoadDir(".");
    if (dir)
    {
        for (unsigned i=0; i < dir->files.size(); i += 1)
        {
            std::string file = dir->files[i];
            if (Leadwerks::String::Lower(Leadwerks::FileSystem::ExtractExt(file))=="zip")
            {
                Leadwerks::Package::Load(file);
            }
        }
        delete dir;
    }
    
    #ifdef DEBUG
	std::string debuggerhostname = System::GetProperty("debuggerhostname");
	if (debuggerhostname!="")
	{
		//Connect to the debugger
		int debuggerport = String::Int(System::GetProperty("debuggerport"));		
		if (!Interpreter::Connect(debuggerhostname,debuggerport))
		{
			Print("Error: Failed to connect to debugger with hostname \""+debuggerhostname+"\" and port "+String(debuggerport)+".");
			return false;
		}
		Print("Successfully connected to debugger.");
		std::string breakpointsfile = System::GetProperty("breakpointsfile");
		if (breakpointsfile!="")
		{
			if (!Interpreter::LoadBreakpoints(breakpointsfile))
			{
				Print("Error: Failed to load breakpoints file \""+breakpointsfile+"\".");
			}
		}
	}
    else
    {
    //    Print("No debugger hostname supplied in command line.");
    }
#endif
	App* app = new App;
 	if (app->Start()) {
		while (app->Loop()) {
		
		}

#ifdef DEBUG
		Interpreter::Disconnect();
#endif
		//Save settings
		delete app;
		System::SaveSettings(settingsfile);
		System::Shutdown();
		return 0;
	}
	else {	
#ifdef DEBUG
		Interpreter::Disconnect();
#endif
		return 1;
	}
}
#endif
