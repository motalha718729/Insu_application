// Directory: /InsuApp/src/database/Database.h
 #ifndef DATABASE_H 
 #define DATABASE_H

#include <iostream>
#include <windows.h> 
#include <sqlext.h> 
#include <string>
#include "map"
#include "vector"

class Database 
{ 
public: 
static SQLHANDLE ConnectToSQLServer(bool useWindowsAuth); 
std::vector<std::map<std::string, std::string>> RunQuerydisplay(SQLHANDLE sqlConnHandle, const std::string& query);
static void RunQuery(SQLHANDLE sqlConnHandle, const std::string& query);
static void DisconnectFromSQLServer(SQLHANDLE sqlConnHandle);
};

#endif // DATABASE_H