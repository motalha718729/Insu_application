// Directory: /InsuApp/src/database/Database.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Database.h"
#include "vector"

SQLHANDLE Database::ConnectToSQLServer(bool useWindowsAuth) {
    SQLHANDLE sqlEnvHandle, sqlConnHandle; 
    SQLRETURN retCode;
    SQLCHAR connectionString[512];

    if (useWindowsAuth) {
        strcpy((char*)connectionString, "DRIVER={ODBC Driver 17 for SQL Server}; SERVER=localhost; DATABASE=master;Trusted_Connection=Yes;");
    }
    else {
        strcpy((char*)connectionString, "DRIVER={ODBC Driver 17 for SQL Server};SERVER=INLT3178\\SQLEXPRESS;DATABASE=SQL_TRAINING;UID=sa;PWD=YourStrongPassword;");
    }

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) return NULL;
    SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)) return NULL;

    retCode = SQLDriverConnect(sqlConnHandle, NULL, connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCESS == retCode || SQL_SUCCESS_WITH_INFO == retCode) {
        std::cout << "Connected to SQL Server successfully!\n";
        return sqlConnHandle;
    }
    else {
        std::cerr << "Failed to connect to SQL Server.\n";
        return NULL;
    }

}

void Database::RunQuery(SQLHANDLE sqlConnHandle, const std::string& query) { 
    SQLHANDLE sqlStmtHandle; 
    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle); 
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {
        std::cerr << "Error executing query!\n";
        return; 
    } 
    SQLCHAR columnData1[256];
    SQLCHAR columnData2[256];
    SQLLEN dataLen;
    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
        SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &dataLen);
        SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &dataLen);
        std::cout << "Client ID: " << columnData1 << "::" <<"Name: " <<columnData2<< "\n";
    } 
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
}



std::vector<std::map<std::string, std::string>> Database::RunQuerydisplay(SQLHANDLE sqlConnHandle, const std::string& query) {
    SQLHANDLE sqlStmtHandle;
    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

    // Execute the query
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {
        std::cerr << "Error executing query!\n";
        return {}; // Return empty result if error occurs
    }

    std::vector<std::map<std::string, std::string>> result;  // This will store all rows as maps of column name -> value
    SQLCHAR columnData[256];
    SQLLEN dataLen;

    // Get the number of columns in the result
    SQLSMALLINT numColumns = 0;
    SQLNumResultCols(sqlStmtHandle, &numColumns);

    // Get column names dynamically and store them
    std::vector<std::string> columnNames(numColumns);
    for (SQLSMALLINT col = 0; col < numColumns; col++) {
        SQLCHAR colName[256];
        SQLSMALLINT colNameLen;
        SQLDescribeCol(sqlStmtHandle, col + 1, colName, sizeof(colName), &colNameLen, NULL, NULL, NULL, NULL);
        columnNames[col] = std::string(reinterpret_cast<char*>(colName), colNameLen);
    }

    // Fetch rows and store them in a map (column name -> value)
    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
        std::map<std::string, std::string> row;
        for (SQLSMALLINT col = 0; col < numColumns; col++) {
            SQLGetData(sqlStmtHandle, col + 1, SQL_C_CHAR, columnData, sizeof(columnData), &dataLen);
            row[columnNames[col]] = std::string(reinterpret_cast<char*>(columnData), dataLen);
        }
        result.push_back(row);  // Store the row in the result
    }

    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    return result;
}

//std::vector<std::vector<std::string>> RunQuery(SQLHANDLE sqlConnHandle, const std::string& query) {
//    SQLHANDLE sqlStmtHandle;
//    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);
//
//    std::vector<std::vector<std::string>> results;  // Table to hold the query result
//
//    // Execute the query
//    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query.c_str(), SQL_NTS)) {
//        std::cerr << "Error executing query!\n";
//        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//        return results;  // Return empty table in case of error
//    }
//
//    // Allocate buffers for column data (adjust size according to the expected data type)
//    SQLCHAR columnData1[256];
//    SQLCHAR columnData2[256];
//    SQLLEN dataLen;
//
//    // Fetch rows from the result set
//    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//        std::vector<std::string> row;
//
//        // Get data from the first column and store it in the row
//        SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, columnData1, sizeof(columnData1), &dataLen);
//        row.push_back(reinterpret_cast<char*>(columnData1));
//
//        // Get data from the second column and store it in the row
//        SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, columnData2, sizeof(columnData2), &dataLen);
//        row.push_back(reinterpret_cast<char*>(columnData2));
//
//        // Add the row to the results table
//        results.push_back(row);
//    }
//
//    // Free the statement handle
//    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//
//    return results;  // Return the populated table
//}

void Database::DisconnectFromSQLServer(SQLHANDLE sqlConnHandle) { 
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle); 
    std::cout << "Disconnected from SQL Server.\n";
}