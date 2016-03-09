#ifndef _SCRIPT_CONTROLLER_HPP_
	#define _SCRIPT_CONTROLLER_HPP_

#pragma once

#include <squirrel/squirrel.h>
#include <sqrat.h>

#include <map>
#include <string>

class ScriptController
{	
public:
	typedef std::map<std::string, Sqrat::Table*> SquirrelTables;

	static bool Initialize(unsigned nStackSize = 1024);
	static void Shutdown(void);	

	static void SqPrint(SQChar* message);

	// < Gets or creates a squirrel table with the given tablename.
	static Sqrat::Table* GetTable(const SQChar* tablename);

protected:

	static void Dispose(void);

private:

	static SquirrelTables tables;	

}; // < end class.

extern HSQUIRRELVM gSquirrelVm;

#endif _SCRIPT_CONTROLLER_HPP_
