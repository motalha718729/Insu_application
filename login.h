#pragma once
// Login.h
#ifndef LOGIN_H 
#define LOGIN_H

#include <string>
#include "Database.h"

class Login {
public: 
	Login(Database &db);

	bool authenticateUser(const std::string& username, const std::string& password, std::string& role);

private: 
	Database& db;
};

#endif 
// LOGIN_H