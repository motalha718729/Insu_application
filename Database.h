// Directory: /InsuApp/src/database/Database.h
 #ifndef DATABASE_H 
 #define DATABASE_H

#include <iostream>
#include <windows.h> 
#include <sqlext.h> 
#include <string>

class Database 
{ 
public: 
static SQLHANDLE ConnectToSQLServer(bool useWindowsAuth); 
static void RunQuery(SQLHANDLE sqlConnHandle, const std::string& query);
static void DisconnectFromSQLServer(SQLHANDLE sqlConnHandle);
};

#endif // DATABASE_H