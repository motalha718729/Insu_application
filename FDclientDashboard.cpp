#include "FDclientDashboard.h"
#include <iostream>
#include "Database.h"
#include "Proposal.h"

void FDclientDashboard::ClientdisplayMenu(Database& db , Client cd) {
        //std::cout << "\nClient Dashboard:\n";
        //std::cout << "1. Create a Proposal\n";
        //std::cout << "2. Show Exisiting Policy\n";
        //std::cout << "3. Cancelation\n";
        //std::cout << "4. Exit\n";
        //std::cout << "Enter your choice:";
    int choice;
    do {
        std::cout << "\nClient Dashboard:\n";
        std::cout << "1. Create a Proposal\n";
        std::cout << "2. Show Exisiting Policy\n";
        std::cout << "3. Cancelation\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice:";
        std::cin >> choice;

        switch (choice) {
        case 1:
            Proposal::createNewPropsal(db,cd);
            break;
        case 2:
              Proposal::displayPolicy(db,cd);
        //    int cID;
        //    std::cout << "Enter Client ID: ";
        //    std::cin >> cID;
        //    {
        //        Client client = Client::selectClient(db, cID);
        //        /*client.showClientDashboard();*/  //  showFDClientDashboard()
        //    }
           break;
        case 3:
            std::cout << "Cancelling Policy\n";
            break;
        case 4:
            std::cout << "Exiting Client DashBoard....\n";
            break;
        default:
            std::cout << "Invalid Choice.\n";

        }
    } while (choice != 4);
}

//void SUclientDashboard::ClientdisplayMenu(Database& db) {
//    std::cout << "\nClient Dashboard:\n";
//    std::cout << "1. Review a Proposal\n";
//    std::cout << "2. Convert Proposal to Policy \n";
//    std::cout << "3. Exit\n";
//    std::cout << "Enter your choice:";
//}
//
//void UWclientDashboard::ClientdisplayMenu(Database& db) {
//    std::cout << "\nClient Dashboard:\n";
//    std::cout << "1. Review Policy\n";
//    std::cout << "2. Exit\n";
//    std::cout << "Enter your choice:";
//}
//void SMclientDashboard::ClientdisplayMenu(Database& db) {
//    std::cout << "\nClient Dashboard:\n";
//    std::cout << "1. Client Deletion\n";
//    std::cout << "2. Exit\n";
//    std::cout << "Enter your choice:";
//}




