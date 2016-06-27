#pragma once
#include "DbQuery.hpp"

DbQuery::DbQuery(std::string _sqlQuery)
	: m_query(_sqlQuery) { }

DbQuery::~DbQuery(void) { }

void DbQuery::Set(const std::string& _query) { this->m_query = _query; }

const std::string DbQuery::Text(void) { return m_query; }