#ifndef _DBCONNECTION_OPTIONS_HPP_
	#define _DBCONNECTION_OPTIONS_HPP_

#pragma once
typedef struct DbConnectionOptions
{
	unsigned long nConnectionTimeout;
    unsigned nRetryAttempts;

} DbConnectionOptions; // < end struct.

#endif _DBCONNECTION_OPTIONS_HPP_
