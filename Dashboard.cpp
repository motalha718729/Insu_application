// Dashboard.cpp
#include "Dashboard.h"
#include "Database.h"
#include "Client.h"
#include "FDclientDashboard.h"
#include "Proposal.h"
#include <limits>

void FrontDeskDashboard::displayMenu(Database& db) {
    
    int choice;
    do {
        std::cout << "\nFront Desk Dashboard:\n";
        std::cout << "1. Create New Client\n";
        std::cout << "2. Select Existing Client\n";
        std::cout << "3. Logout\n";
        std::cout << "Enter your choice:";
        std::cin >> choice;
        system("cls");

        switch (choice) {
        case 1 :
            Client::createNewClient(db);
            break;
        case 2 :
            Client::displayClients(db);
            int cID;
            std::cout << "Enter Client ID: ";
            std::cin >> cID;
            try
            {
                Client client = Client::selectClient(db, cID);
                
                client.showClientDashboard(db ,client); //  showFDClientDashboard()
            }
            catch (const std::runtime_error& e) {
                std::cout << e.what() << "\n"; 
                return; 
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
    int choice;
    do {
        std::cout << "\nSurveyor Dashboard:\n";
        std::cout << "1. Approve Proposals\n";
        /*std::cout << "2. Review Policies\n";*/
        std::cout << "2. Logout\n";
        std::cout << "Enter Your Choice\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            int cd;
            std::cout << "Enter Client Id : \n";
            std::cin >> cd;

            if (Proposal::displayProposal(db, cd)) {
                int pID;
                std::cout << "Enter Proposal ID: ";
                std::cin >> pID;
                if (Proposal::isProposalBelongsToClient(db, pID, cd)) {

                    {
                        Proposal proposal = Proposal::selectProposal(db, pID);
                        proposal.showClientDashboard(db, proposal); //  showSUClientDashboard()

                    }
                }
                else {
                    std::cout << "The Proposal ID " << pID << " does not belong to the selected client (Client ID: " << cd << ").\n";
                }
            }
            break;
        case 2:
            std::cout << "Exiting Front Desk DashBoard....\n";
            break;
        }
    } while (choice != 2);
}

void UnderwriterDashboard::displayMenu(Database& db) {
    int choice;
    do {
        std::cout << "\nUnderwriter Dashboard:\n";
        std::cout << "1. Approve Policies\n";
       /* std::cout << "2. Risk Assessment\n";*/
        std::cout << "2. Logout\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            int cd;
            std::cout << "Enter Client Id : \n";
            std::cin >> cd;

            if (Proposal::displayPolicyUW(db, cd)) { // display all the proposal which are approved but form is proposal
                int pID;
                std::cout << "Enter Proposal ID: ";
                std::cin >> pID;
                if (Proposal::isProposalBelongsToClient(db, pID, cd)) {
                    {
                        Proposal proposal = Proposal::selectPolicy(db, pID); //need to make selectPolicy 
                        proposal.showClientDashboardUW(db, proposal);
                    }
                }
                else {
                    std::cout << "The Proposal ID " << pID << " does not belong to the selected client (Client ID: " << cd << ").\n";
                }
            }
            break;
        case 2:
            std::cout << "Exiting Front Desk DashBoard....\n";
            break;
        }
    } while (choice != 2);
}

void SuperManagerDashboard::displayMenu(Database& db) {
    int choice;
    do {
        std::cout << "\nSuper Manager Dashboard:\n";
        std::cout << "1. Manage Users\n";
        std::cout << "2. View Approvals Table\n"; // View Approvals Table
        std::cout << "3. View Payments Table\n";  // View Payments Table
        std::cout << "4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            manageUsers(db);  
            break;

        case 2:
            viewApprovalsTable(db);  
            break;

        case 3:
            viewPaymentsTable(db);  
            break;

        case 4:
            std::cout << "Logging out...\n";
            break;

        default:
            std::cout << "Invalid choice, please try again.\n";
            break;
        }
    } while (choice != 4);
}

void SuperManagerDashboard::manageUsers(Database& db) {
    int userChoice;
    do {
        std::cout << "\nManage Users:\n";
        std::cout << "1. Add New User\n";
        std::cout << "2. Update Existing User\n";
        std::cout << "3. Delete User\n";
        std::cout << "4. View All Users\n";
        std::cout << "5. Go Back\n";
        std::cout << "Enter your choice: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            addUser(db);  // Function to add a new user
            break;

        case 2:
            updateUser(db);  // Function to update an existing user
            break;

        case 3:
            deleteUser(db);  // Function to delete a user
            break;

        case 4:
            viewAllUsers(db);  // Function to view all users
            break;

        case 5:
            std::cout << "Returning to main menu...\n";
            break;

        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (userChoice != 5);
}

void SuperManagerDashboard::viewPaymentsTable(Database& db) {
    std::string query = "SELECT * FROM dbo.Payment";
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

    if (!results.empty()) {
        std::cout << "\nPayments Table:\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "PaymentID | ProposalID | AmountPaid | PaymentMode | PaymentDate | PaymentStatus\n";
        std::cout << "--------------------------------------------\n";

        for (const auto& row : results) {
            std::cout << row.at("PaymentID") << " | "
                << row.at("ProposalID") << " | "
                << row.at("AmountPaid") << " | "
                << row.at("PaymentMode") << " | "
                << row.at("PaymentDate") << " | "
                << row.at("PaymentStatus") << "\n";
        }
    }
    else {
        std::cout << "No records found in the Payments table.\n";
    }
}

void SuperManagerDashboard::viewApprovalsTable(Database& db) {
    std::string query = "SELECT * FROM dbo.Approvals";
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

    if (!results.empty()) {
        std::cout << "\nApprovals Table:\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "ApprovalID | ProposalID | ApprovedBy | ApprovalStatus | ApprovalDate\n";
        std::cout << "----------------------------------------------\n";

        for (const auto& row : results) {
            std::cout << row.at("ApprovalID") << " | "
                << row.at("ProposalID") << " | "
                << row.at("ApprovedBy") << " | "
                << row.at("ApprovalStatus") << " | "
                << row.at("ApprovalDate") << "\n";
        }
    }
    else {
        std::cout << "No records found in the Approvals table.\n";
    }
}

void SuperManagerDashboard::addUser(Database& db) {
    std::string username, password, role , email;

    std::cout << "Enter username: ";
    std::cin.ignore();
    std::getline(std::cin, username);  // Use std::getline() to read the full username with spaces

    std::cout << "Enter password: ";
    std::cin.ignore();
    std::getline(std::cin, password);   // Use std::getline() to read the full password with spaces

    std::cout << "Enter Email-ID: ";
    std::cin.ignore();
    std::getline(std::cin, email);

    std::cout << "Enter role (e.g., Admin, FrontDesk, Surveyor, etc.): ";
    std::cin.ignore();
    std::getline(std::cin, role);

    // Insert user data into the database
    std::string query = "INSERT INTO dbo.Users (Username, PasswordHash, Role , Email) VALUES ('" + username + "', '" + password + "', '" + role + "' , '" + email + "')";
    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "New user added successfully.\n";
}


void SuperManagerDashboard::updateUser(Database& db) {
    int userID;
    std::string newPassword, newRole;
    std::cout << "Enter user ID to update: ";
    std::cin >> userID;
    std::cout << "Enter new password: ";
    std::cin >> newPassword;
    std::cout << "Enter new role: ";
    std::cin >> newRole;

    // Update user details in the database
    std::string query = "UPDATE dbo.Users SET PasswordHash = '" + newPassword + "', Role = '" + newRole + "' WHERE UserID = " + std::to_string(userID);
    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "User updated successfully.\n";
}


void SuperManagerDashboard::deleteUser(Database& db) {
    int userID;
    std::cout << "Enter user ID to delete: ";
    std::cin >> userID;

    // Delete the user from the database
    std::string query = "DELETE FROM dbo.Users WHERE UserID = " + std::to_string(userID);
    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "User deleted successfully.\n";
}


void SuperManagerDashboard::viewAllUsers(Database& db) {
    std::string query = "SELECT * FROM dbo.Users";
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

    if (!results.empty()) {
        std::cout << "\nUsers Table:\n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "UserID | Username | Password | Role\n";
        std::cout << "-------------------------------------------------\n";

        for (const auto& row : results) {
            std::cout << row.at("UserID") << " | "
                << row.at("Username") << " | "
                << row.at("Password") << " | "
                << row.at("Role") << "\n";
        }
    }
    else {
        std::cout << "No users found in the database.\n";
    }
}
