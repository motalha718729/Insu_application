// Client.cpp
#include "Client.h"
#include "Database.h"
#include "FDclientDashboard.h"
#include "vector"
#include "SUclientDashboard.h"

Client::Client(int id, std::string fName, std::string lName, std::string mail, std::string ph) : clientID(id), firstName(fName), lastName(lName), email(mail), phone(ph) {}
//Database db;
//SQLHANDLE sqlConnHandle = db.ConnectToSQLServer(true);
void Client::createNewClient(Database& db) {
    std::string ClientID, UserID, FirstName, LastName, DOB, Gender, Email, Mobile, SmokerStatus, AnnualIncome, Occupation;
    std::cout << "Enter Client ID: ";
    std::cin >> ClientID;

    std::cout << "Enter User ID: ";
    std::cin >> UserID;

    std::cout << "Enter First Name: ";
    std::cin >> FirstName;

    std::cout << "Enter Last Name: ";
    std::cin >> LastName;

    std::cout << "Enter Date of Birth (YYYY-MM-DD): ";
    std::cin >> DOB;

    std::cout << "Enter Gender: ";
    std::cin >> Gender;

    std::cout << "Enter Email: ";
    std::cin >> Email;

    std::cout << "Enter Mobile Number: ";
    std::cin >> Mobile;

    std::cout << "Enter Smoker Status (Yes/No): ";
    std::cin >> SmokerStatus;

    std::cout << "Enter Annual Income: ";
    std::cin >> AnnualIncome;

    std::cout << "Enter Occupation: ";
    std::cin >> Occupation;


    std::string query = "INSERT INTO dbo.Client (ClientID, UserID , FirstName , LastName , DOB , Gender , Email , Mobile , SmokerStatus , AnnualIncome , Occupation) VALUES ('" + ClientID + "', '" + UserID + "', '" + FirstName + "', '" + LastName + "', '" + DOB + "', '" + Gender + "', '" + Email + "', '" + Mobile + "', '" + SmokerStatus + "', '" + AnnualIncome + "', '" + Occupation + "')";
    
    db.RunQuery(db.ConnectToSQLServer(true),query);
    std::cout << "Client created successfully!\n";

}

void Client::displayClients(Database& db) { 
    std::string query = "SELECT ClientID, FirstName, LastName FROM dbo.Client";
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);
    std::cout << "Clients List: " << std::endl;

    // Loop through each row in the results vector
    for (const auto& row : results) {
        // Print ClientID, FirstName, and LastName for each client
        std::cout << "ClientID: " << row.at("ClientID")
            << ", FirstName: " << row.at("FirstName")
            << ", LastName: " << row.at("LastName") << std::endl;
    }
}
//void Client::displayClients(Database& db) {
//    std::string query = "SELECT ClientID, FirstName, LastName FROM dbo.Client";
//
//    // Execute the query and get the results
//    std::vector<std::vector<std::string>> result = db.RunQuery(db.ConnectToSQLServer(true), query);
//
//    // Check if results are empty
//    if (result.empty()) {
//        std::cout << "No clients found.\n";
//        return;
//    }
//
//    // Display the results (table format)
//    std::cout << "ClientID | FirstName | LastName\n";
//    std::cout << "---------------------------------\n";
//
//    for (const auto& row : result) {
//        std::cout << row[0] << " | " << row[1] << " | " << row[2] << "\n";
//    }
//}

Client Client::selectClient(Database& db, int clientID) {
    std::string query = "SELECT * FROM Client WHERE ClientID = " + std::to_string(clientID);
    db.RunQuery(db.ConnectToSQLServer(true), query);
    return Client(clientID, "", "", "", ""); 
}

void Client::showClientDashboard(Database& db , Client cd) { 
    //std::cout << "Client Dashboard\n";
    //std::cout << "1. Create New Proposal\n";
    //std::cout << "2. List Policies\n"; 
    //std::cout << "3. Cancel Policy\n";
    FDclientDashboard::ClientdisplayMenu(db , cd);
}
