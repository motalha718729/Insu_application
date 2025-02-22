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


void FDclientDashboard::ClientdisplayProposal(Database& db, Proposal pd) {

    double premium = std::stod(pd.premiumpermon);

    if (pd.paymentmode == "HalfYr") {
        premium = premium- (premium * 0.10);  // 10% discount for Half-Yearly
        std::cout << "Applying 10% discount for Half-Yearly payment. Updated Premium: " << premium << "\n";
    }
    else if (pd.paymentmode == "Annual") {
        premium = premium - (premium * 0.15);  // 15% discount for Annual
        std::cout << "Applying 15% discount for Annual payment. Updated Premium: " << premium << "\n";
    }

    std::cout << "\nPlease choose an option:\n";
    std::cout << "1. Approve Proposal\n";
    std::cout << "2. Reject Proposal\n";
    std::cout << "Enter your choice (1 or 2): ";

   

    int choice;
    std::cin >> choice;

    std::string status;
    if (choice == 1) {
        status = "Approved";  // Set status to Approved
        std::cout << "Proposal approved! Sending for Underwriting...\n";
    }
    else if (choice == 2) {
        status = "Rejected";  // Set status to Rejected
        std::cout << "Proposal rejected.\n";
    }
    else {
        std::cout << "Invalid choice. Please enter 1 or 2.\n";
        return;  // Exit the function if the user entered an invalid choice
    }

    // Update the proposal status in the database
    std::string query = "UPDATE dbo.Proposal SET Status = '" + status + "', PremiumPerMonth = " + std::to_string(premium) + " WHERE ProposalID = " + std::to_string(pd.proposalID);

    // Execute the query to update the status
    db.RunQuery(db.ConnectToSQLServer(true), query);


    // Optionally, you could display the updated status
    std::cout << "Proposal status updated to: " << status << "\n";
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




