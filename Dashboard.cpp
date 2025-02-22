// Dashboard.cpp
#include "Dashboard.h"
#include "Database.h"
#include "Client.h"
#include "FDclientDashboard.h"

void FrontDeskDashboard::displayMenu(Database& db) {
    
    int choice;
    do {
        std::cout << "\nFront Desk Dashboard:\n";
        std::cout << "1. Create New Client\n";
        std::cout << "2. Select Existing Client\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice:";
        std::cin >> choice;

        switch (choice) {
        case 1 :
            Client::createNewClient(db);
            break;
        case 2 :
            Client::displayClients(db);
            int cID;
            std::cout << "Enter Client ID: ";
            std::cin >> cID;
            {
                Client client = Client::selectClient(db, cID);
                
                client.showClientDashboard(db ,client); //  showFDClientDashboard()
            }
            break;
        case 3 :
            std::cout << "Exiting Front Desk DashBoard....\n";
            break;
        default:
            std::cout << "Invalid Choice.\n";

        }
    } while (choice != 3);
}

void SurveyorDashboard::displayMenu(Database& db) {
    std::cout << "\nSurveyor Dashboard:\n";
    std::cout << "1. Approve Proposals\n";
    std::cout << "2. Review Policies\n";
    std::cout << "3. Logout\n";
}

void UnderwriterDashboard::displayMenu(Database& db) {
    std::cout << "\nUnderwriter Dashboard:\n";
    std::cout << "1. Approve Policies\n";
    std::cout << "2. Risk Assessment\n";
    std::cout << "3. Logout\n";
}

void SuperManagerDashboard::displayMenu(Database& db) {
    std::cout << "\nSuper Manager Dashboard:\n";
    std::cout << "1. Manage Users\n";
    std::cout << "2. View Reports\n";
    std::cout << "3. Logout\n";
}