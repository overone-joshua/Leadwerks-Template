#pragma once
#include "ScriptController.hpp"
#include "../Utilities/Macros.hpp"

#include <squirrel/squirrel.h>
#include <sqrat.h>
#include <sqrat/sqext.h>

#include <iostream>
#include <string>

HSQUIRRELVM gSquirrelVm;
ScriptController::SquirrelTables ScriptController::tables;

bool ScriptController::Initialize(unsigned nStackSize)
{
	// < Create our squirrel VM.
	gSquirrelVm = sq_open(nStackSize);

	if (gSquirrelVm == nullptr) { return false; }

	// < Set our new squirrel VM as the default VM for sqrat.
	Sqrat::DefaultVM::Set(gSquirrelVm);

	Sqrat::RootTable().Func("print", &ScriptController::SqPrint);		 

	return true;
}

void ScriptController::Shutdown(void)
{	
	Dispose();
	sq_close(gSquirrelVm);
}

void ScriptController::SqPrint(SQChar* message)
{
	std::cout << message << std::endl;
}

Sqrat::Table* ScriptController::GetTable(const SQChar* tablename)
{	
	Sqrat::Table* table = nullptr;

	// < cast the SQChar* to a string in order to
	// * look for the table by value.
	std::string name = tablename;

	auto iter = tables.find(tablename);
	if (iter == tables.end())
	{
		tables.insert( std::make_pair(name, new Sqrat::Table()) );

		table = tables.at(tablename);
		Sqrat::RootTable().Bind(tablename, *table);
	}
	else
	{
		table = iter->second;
	}	

	return table;
}

void ScriptController::Dispose(void)
{
	auto iter = tables.begin();
	while (iter != tables.end())
	{
		SAFE_DELETE(iter->second);
		iter = tables.erase(iter);

		if (iter != tables.end()){ iter++; }
	}
	tables.clear();

}