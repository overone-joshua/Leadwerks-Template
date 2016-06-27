#ifndef _DBCONNECTION_STRING_HPP_
	#define _DBCONNECTION_STRING_HPP_

#pragma once

#include <string>

typedef struct DbConnectionString
{
	std::string cServer;
	std::string cDatabase;
	std::string cUserId;
	std::string cPassword;

    DbConnectionString(void) { Init(); }
    DbConnectionString(const std::string& _server, const std::string& _database, const std::string& _userId = "", const std::string& _password = "")
        : cServer(_server), cDatabase(_database), cUserId(_userId), cPassword(_password) { }

    ~DbConnectionString(void)
    {
        Init();
    }

private:

    void Init(void)
    {
        this->cServer = "";
        this->cDatabase = "";
        this->cUserId = "";
        this->cPassword = "";
    }

} DbConnectionString; // < end struct.

#endif _DBCONNECTION_STRING_HPP_