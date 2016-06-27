#ifndef _ISOLATION_LEVEL_HPP_
	#define _ISOLATION_LEVEL_HPP_

#pragma once

#include <string>

typedef enum
{
	ISOLATION_LEVEL_DEFERRED = 0,
	ISOLATION_LEVEL_IMMEDIATE= 1 << 0,
	ISOLATION_LEVEL_EXCLUSIVE = 1 << 1,

} IsolationLevel; // < end enum.

static inline std::string IsolationLevelToString(const IsolationLevel& _isolationLevel);

std::string IsolationLevelToString(const IsolationLevel& _isolationLevel)
{
	std::string res;

	switch (_isolationLevel)
	{
	case ISOLATION_LEVEL_DEFERRED: res = "DEFERRED"; break;
	case ISOLATION_LEVEL_IMMEDIATE: res = "IMMEDIATE"; break;
	case ISOLATION_LEVEL_EXCLUSIVE: res = "EXCLUSIVE"; break;
	default: throw "Invalid IsolationLevel!";
	}

	return res;
}

#endif _ISOLATION_LEVEL_HPP_