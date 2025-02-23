#include "FDclientDashboard.h"
#include <iostream>
#include "Database.h"
#include "Proposal.h"

void FDclientDashboard::ClientdisplayMenu(Database& db , Client cd) {

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
        premium = (premium- (premium * 0.10));  // 10% discount for Half-Yearly
        std::cout << "Applying 10% discount for Half-Yearly payment. Updated Premium: " << premium << "\n";
    }
    else if (pd.paymentmode == "Annual") {
        premium = (premium - (premium * 0.15));  // 15% discount for Annual
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
// 
void FDclientDashboard::ClientdisplayPolicy(Database& db, Proposal pd) {
   /* std::cout << "\nPlease choose an option:\n";
    std::cout << "1. Approve Proposal\n";
    std::cout << "2. Reject Proposal\n";
    std::cout << "Enter your choice (1 or 2): ";*/

    std::cout << "Proposal Status: " << pd.status<< "\n";

    if (pd.status == "Approved" && pd.form == "Proposal") {
        std::string option;
        std::cout << "Do you want to proceed to convert the proposal to a policy? (yes/no): ";
        std::cin >> option;

        if (option == "yes") {
            // Changing the proposal status to Policy and updating the form
            std::string query = "UPDATE dbo.Proposal SET  Form = 'Policy' WHERE ProposalID = " + std::to_string(pd.proposalID);
            db.RunQuery(db.ConnectToSQLServer(true), query);
            std::cout << "Proposal converted to Policy.\n";

            std::string approvalQuery = "INSERT INTO dbo.Approvals (ProposalID, ApprovedBy, ApprovalStatus, ApprovalDate) "
                "VALUES (" + std::to_string(pd.proposalID) + ", 'Mathew', 'Approved', GETDATE())";  // Replace 'Admin' with the actual person approving if needed
            db.RunQuery(db.ConnectToSQLServer(true), approvalQuery);
            std::cout << "Approval recorded in the system.\n";

            // Now, let's handle payment details
            std::string paymentOption;
            double amountToPay;
            if (pd.paymentmode == "HalfYr" ) {
                 amountToPay = std::stod(pd.premiumpermon)*6; // This should be the premium that needs to be paid
             }
            if (pd.paymentmode == "Annual") {
                 amountToPay = std::stod(pd.premiumpermon)*12; // This should be the premium that needs to be paid
            }
            // Displaying payment options
            std::cout << "Choose a preferred payment method:\n";
            std::cout << "1. Cash\n2. Credit Card\n3. Debit Card\n4. Net Banking\n5. UPI\n6. Paytm\n";
            std::cout << "Enter your choice (1-6): ";
            std::cin >> paymentOption;

            std::string paymentMethod;
            switch (std::stoi(paymentOption)) {
            case 1:
                paymentMethod = "Cash";
                break;
            case 2:
                paymentMethod = "Credit Card";
                break;
            case 3:
                paymentMethod = "Debit Card";
                break;
            case 4:
                paymentMethod = "Net Banking";
                break;
            case 5:
                paymentMethod = "UPI";
                break;
            case 6:
                paymentMethod = "Paytm";
                break;
            default:
                paymentMethod = "Unknown";
                break;
            }

            std::cout << "You selected " << paymentMethod << " for payment.\n";

            // Accept Terms and Conditions
            std::cout << "Please read and accept the terms and conditions before proceeding.\n";
            std::cout << "Do you accept the terms and conditions? (yes/no): ";
            std::string acceptTerms;
            std::cin >> acceptTerms;

            if (acceptTerms == "yes") {
                // Insert payment data into the Payment table
                std::string paymentQuery = "INSERT INTO dbo.Payment (ProposalID, AmountPaid, PaymentMode, PaymentDate, PaymentStatus) "
                    "VALUES (" + std::to_string(pd.proposalID) + ", " + std::to_string(amountToPay) + ", '"
                    + paymentMethod + "', GETDATE(), 'Completed')";
                db.RunQuery(db.ConnectToSQLServer(true), paymentQuery);

                std::cout << "Payment of " << amountToPay << " " << paymentMethod << " completed successfully.\n";
            }
            else {
                std::cout << "You must accept the terms and conditions to proceed.\n";
            }
        }
        else {
            std::cout << "You chose not to proceed with converting the proposal to a policy.\n";

            std::string rejectionQuery = "INSERT INTO dbo.Approvals (ProposalID, ApprovedBy, ApprovalStatus, ApprovalDate) "
                "VALUES (" + std::to_string(pd.proposalID) + ", 'Mathew', 'Rejected', GETDATE())";  // Replace 'Admin' with the actual person rejecting if needed
            db.RunQuery(db.ConnectToSQLServer(true), rejectionQuery);
            std::cout << "Proposal rejection recorded in the system.\n";
        }
    }
    else {
        std::cout << "The proposal is not yet approved or rejected. Please check again later.\n";
    }
}

//void SMclientDashboard::ClientdisplayMenu(Database& db) {
//    std::cout << "\nClient Dashboard:\n";
//    std::cout << "1. Client Deletion\n";
//    std::cout << "2. Exit\n";
//    std::cout << "Enter your choice:";
//}




