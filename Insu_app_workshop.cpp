// Insu_app_workshop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <windows.h>
//#include <sqlext.h>
//#include <string>
//
//
//SQLHANDLE ConnectToSQLServer(bool useWindowsAuth);
//void RunQuery(SQLHANDLE sqlConnHandle, const std::string& query);
//void DisconnectFromSQLServer(SQLHANDLE sqlConnHandle);
//
//SQLHANDLE ConnectToSQLServer(bool useWindowsAuth) {
//    SQLHANDLE sqlEnvHandle, sqlConnHandle;
//    SQLRETURN retCode;
//    SQLCHAR connectionString[512];
//
//    if (useWindowsAuth) {
//        // Corrected string formatting
//        strcpy((char*)connectionString,
//            "DRIVER={ODBC Driver 17 for SQL Server};"
//            "SERVER=localhost;"
//            "DATABASE=master;"
//            "Trusted_Connection=Yes;");
//    }
//    else {
//        // Corrected string formatting
//        strcpy((char*)connectionString,
//            "DRIVER={ODBC Driver 17 for SQL Server};"
//            "SERVER=INLT3178\\SQLEXPRESS;"
//            "DATABASE=SQL_TRAINING;"
//            "UID=sa;"
//            "PWD=YourStrongPassword;");
//    }
//
//    // Allocate the environment handle
//    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
//        return NULL;
//
//    // Set ODBC version
//    SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
//
//    // Allocate the connection handle
//    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
//        return NULL;
//
//    // Attempt to connect using the connection string
//    retCode = SQLDriverConnect(sqlConnHandle, NULL, connectionString, SQL_NTS,
//        NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
//
//    if (SQL_SUCCESS == retCode || SQL_SUCCESS_WITH_INFO == retCode) {
//        std::cout << "Connected to SQL Server successfully!\n";
//        return sqlConnHandle;
//    }
//    else {
//        std::cerr << "Failed to connect to SQL Server.\n";
//        return NULL;
//    }
//}
//
//void RunQuery(SQLHANDLE sqlConnHandle, const std::string& query) {
//    SQLHANDLE sqlStmtHandle;
//    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);
//
//    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {
//        std::cerr << "Error executing query!\n";
//        return;
//    }
//
//    SQLCHAR columnData[256];
//    SQLLEN dataLen;
//
//    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//        SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, columnData, sizeof(columnData), &dataLen);
//        std::cout << "Result: " << columnData << "\n";
//    }
//
//    // Free the statement handle
//    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//}
//
//void DisconnectFromSQLServer(SQLHANDLE sqlConnHandle) {
//    // Disconnect and free the connection handle
//    SQLDisconnect(sqlConnHandle);
//    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
//    std::cout << "Disconnected from SQL Server.\n";
//}
//
//int main() {
//    bool useWindowsAuth;
//    std::cout << "Use Windows Authentication? (1 = Yes, 0 = No): ";
//    std::cin >> useWindowsAuth;
//    std::cin.ignore();  // Ignore the newline character left by std::cin
//
//    // Establish connection to SQL Server
//    SQLHANDLE sqlConnHandle = ConnectToSQLServer(useWindowsAuth);
//
//    if (sqlConnHandle) {
//        std::string query;
//        std::cout << "Enter SQL Query: ";
//        /*std::cin >> query;*/
//        std::getline(std::cin, query);
//        RunQuery(sqlConnHandle, query);
//        DisconnectFromSQLServer(sqlConnHandle);
//    }
//
//    return 0;
//}

#include <iostream>
#include "Database.h"
#include "login.h"
//
//int main() {
//    bool useWindowsAuth; std::cout << "Use Windows Authentication? (1 = Yes, 0 = No): ";
//    std::cin >> useWindowsAuth; 
//    std::cin.ignore(); // Ignore the newline character left by std::cin
//
//    // Establish connection to SQL Server
//    Database db;
//
//    SQLHANDLE sqlConnHandle = db.ConnectToSQLServer(useWindowsAuth);
//    if (sqlConnHandle) {
//        std::string query;
//        std::cout << "Enter SQL Query: ";
//        std::getline(std::cin, query);
//        db.RunQuery(sqlConnHandle,query);
//        db.DisconnectFromSQLServer(sqlConnHandle);
//    }
//
//    return 0;
//
//}

// main.cpp  
#include "Dashboard.h"

void launchDashboard(const std::string& role , Database& db) {
    Dashboard* dashboard = nullptr;
    if (role == "Front Desk") {
        dashboard = new FrontDeskDashboard();
        
    }
    else if (role == "Surveyor") {
        dashboard = new SurveyorDashboard();
    }
    else if (role == "Underwriter") {
        dashboard = new UnderwriterDashboard();
    }
    else if (role == "Super Manager") {
        dashboard = new SuperManagerDashboard();
    }
    else {
        std::cout << "Invalid role! Exiting...\n";
        return;
    }

    if (dashboard) {
        dashboard->displayMenu(db);
        delete dashboard;
    }
}
int main() {
    Database db;
    Login loginSystem(db);
    do {
        std::string username, password, role;
        std::cout << "Enter Username: ";
        std::cin >> username;
        std::cout << "Enter Password: ";
        std::cin >> password;
        system("cls");
        loginSystem.authenticateUser(username, password, role);

        if (!role.empty()) {
            std::cout << "Login successful! Role: " << role << "\n";
            launchDashboard(role, db);
        }
        else {
            std::cout << "Login failed. Invalid credentials.\n";
        }
        system("cls");
    } while (true);

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
