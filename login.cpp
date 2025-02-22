// Login.cpp
#include "Login.h"
#include <iostream>

Login::Login(Database& db) : db(db) {}

bool Login::authenticateUser(const std::string& username, const std::string& password, std::string& role) {
    SQLHANDLE sqlConnHandle = db.ConnectToSQLServer(true);
    if (!sqlConnHandle) {
        std::cerr << "Database connection failed.\n";
        return false;
    }

    std::string query = "SELECT Role FROM [dbo].[Users] WHERE [Username] = '" + username + "' AND [PasswordHash] = '" + password + "'";
    SQLHANDLE sqlStmtHandle;
    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {
        std::cerr << "Error executing query!\n";
        std::cout << query << std::endl;
        return false;
    }

    SQLCHAR roleData[50];
    SQLLEN dataLen;
    if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
        SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, roleData, sizeof(roleData), &dataLen);
        role = std::string((char*)roleData);
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        db.DisconnectFromSQLServer(sqlConnHandle);
        return true;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    db.DisconnectFromSQLServer(sqlConnHandle);
    return false;
}