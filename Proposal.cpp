// Proposal.cpp

#include "Proposal.h"
#include "Database.h"
#include "Client.h"
#include "FDclientDashboard.h"
#include "SUclientDashboard.h"
#include <iomanip>


Proposal::Proposal(int pid, int cid, std::string InsuType, long lyfcvramt, std::string status, std::string form , std::string paymentmode , std::string premiumpermon ) : proposalID(pid), clientID(cid), InsuranceType(InsuType), LifecoverAmount(lyfcvramt), status(status), form(form) , paymentmode(paymentmode) , premiumpermon(premiumpermon) {}

void Proposal::createNewPropsal(Database& db , Client cd) {
    std::string propID,clientid, InsuType, SelectedTopUps, PaymentMode, Status, PolicyNumber,addRiders, Form;
    int  LifeCoverUpToAge, PaymentTenure;
    double LifeCoverAmount, PremiumPerMonth;
    std::string CreatedAt; // Assuming date will be entered as string in a specific format
    double riderPremium = 0.0;

    // Get input for the Proposal details
    std::cout << "Enter Proposal ID: ";
    std::cin >> propID;

    clientid = std::to_string(cd.clientID);
    std::cout << "Enter Insurance Type: ";
    std::cin.ignore(); // to clear the newline character left in the buffer
    std::getline(std::cin, InsuType);

    std::cout << "Enter Life Cover Amount: ";
    std::cin >> LifeCoverAmount;

    std::cout << "Enter Life Cover Up To Age: ";
    std::cin >> LifeCoverUpToAge;

    PremiumPerMonth = ((LifeCoverAmount * 0.115) / LifeCoverUpToAge) / 2;

    std::cout << "Premium per month for you is " << PremiumPerMonth << "\n";

    std::cout << "Do you want to add any Riders (Top-ups)? (Yes/No): \n";
    std::cin.ignore();
    std::getline(std::cin, addRiders);

    if (addRiders == "Yes" || addRiders == "yes") {
        std::cout << "Select Accident Death Benefit Coverage Amount (min 25K): ";
        double accidentDeathCoverage;
        std::cin >> accidentDeathCoverage;

        if (accidentDeathCoverage >= 25000) {
            double accidentDeathPremium = (accidentDeathCoverage / 50000) * 10;  // Rs.10 per 50K coverage
            riderPremium += accidentDeathPremium;
            std::cout << "Premium for Accident Death Benefit Rider: Rs. " << accidentDeathPremium << "\n";
        }

        std::cout << "Select Comprehensive Care Coverage Amount (min 2L): ";
        double comprehensiveCareCoverage;
        std::cin >> comprehensiveCareCoverage;

        if (comprehensiveCareCoverage >= 200000) {
            double comprehensiveCarePremium = (comprehensiveCareCoverage / 300000) * 400;  // Rs.400 per 3L coverage
            riderPremium += comprehensiveCarePremium;
            std::cout << "Premium for Comprehensive Care Rider: Rs. " << comprehensiveCarePremium << "\n";
        }

        // Update the total PremiumPerMonth based on riders
        PremiumPerMonth += riderPremium;
    }

    std::cout << "Your total monthly premium (with riders) is: Rs. " << PremiumPerMonth << "\n";

   /* std::cout << "Enter Premium Per Month: ";
    std::cin >> PremiumPerMonth;*/

    std::cout << "Enter Selected Top Ups: ";
    std::cin.ignore();
    std::getline(std::cin, SelectedTopUps);

    std::cout << "Enter Payment Tenure: ";
    std::cin >> PaymentTenure;

    std::cout << "Enter Payment Mode (e.g., Monthly, Quarterly): ";
    std::cin.ignore();
    std::getline(std::cin, PaymentMode);

    std::cout << "Enter Status (e.g., Pending, Active): ";
    std::getline(std::cin, Status);

    std::cout << "Enter Policy Number: ";
    std::getline(std::cin, PolicyNumber);

    std::cout << "Enter Form: ";
    std::getline(std::cin, Form);

    // You can also use the current date or prompt the user for the date as a string
   /* std::cout << "Enter CreatedAt (e.g., YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, CreatedAt);*/

    std::string query =  "INSERT INTO dbo.Proposal (ProposalID, ClientID, InsuranceType, LifeCoverAmount, LifeCoverUpToAge, PremiumPerMonth, SelectedTopUps, PaymentTenure, PaymentMode,  Status, PolicyNumber, Form, CreatedAt) VALUES ('" + propID + "','" + clientid + "', '" + InsuType + "', "+ std::to_string(LifeCoverAmount) + ", " + std::to_string(LifeCoverUpToAge) + ", " + std::to_string(PremiumPerMonth) + ", '" + SelectedTopUps + "', "
        + std::to_string(PaymentTenure) + ", '" + PaymentMode + "', '" + Status + "', '" + PolicyNumber + "', '"
        + Form + "',  GetDate() )";

    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "Proposal created successfully!\n";

   /* "INSERT INTO dbo.Proposal (ProposalID, ClientID, InsuranceType, LifeCoverAmount, LifeCoverUpToAge, PremiumPerMonth, SelectedTopUps, PaymentTenure, PaymentMode,  Status, PolicyNumber, Form, CreatedAt) VALUES ('" + propID + "','" + clientid + " ','  " + InsuType + "', " + std::to_string(LifeCoverAmount) + ", " + std::to_string(LifeCoverUpToAge) + ", " + std::to_string(PremiumPerMonth) + ", '" + SelectedTopUps + "', "
        + std::to_string(PaymentTenure) + ", '" + PaymentMode + "', '" + Status + "', '" + PolicyNumber + "', '"
        + Form + "', '" + CreatedAt + "')";*/

}

//void Proposal::displayPolicy(Database& db , Client cd) {
//    int clientid;
//    clientid = (cd.clientID);
//
//    std::string query = "SELECT * FROM dbo.Proposal WHERE ClientID = " + std::to_string(clientid);
//    db.RunQuery(db.ConnectToSQLServer(true), query);
//    std::cout << "display Policy";
//}

void Proposal::displayPolicy(Database& db, Client cd) {
    int clientid = cd.clientID;
std::string query = "SELECT p.ProposalID, p.InsuranceType, p.LifeCoverAmount, p.LifeCoverUpToAge, "
"c.SmokerStatus, c.AnnualIncome, p.PremiumPerMonth, p.SelectedTopUps, "
"p.PaymentTenure, p.PaymentMode, p.Status, p.PolicyNumber, p.Form, p.CreatedAt, "
"c.FirstName, c.LastName, c.Email, c.Mobile "
"FROM dbo.Proposal p "
"JOIN dbo.Client c ON p.ClientID = c.ClientID "
"WHERE p.ClientID = " + std::to_string(clientid);

// Run the query and get the results
std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

// Display the results
if (!results.empty()) {
    for (const auto& row : results) {
        std::cout << "\nProposal Details:\n";
        std::cout << "-------------------------------\n";
        std::cout << "ProposalID          : " << row.at("ProposalID") << "\n";
        std::cout << "Insurance Type      : " << row.at("InsuranceType") << "\n";
        std::cout << "Life Cover Amount   : " << std::fixed << std::setprecision(2) << std::stod(row.at("LifeCoverAmount")) << "\n";
        std::cout << "Life Cover Up To Age: " << row.at("LifeCoverUpToAge") << "\n";
        std::cout << "Tobacco Consumption : " << row.at("SmokerStatus") << "\n";
        std::cout << "Annual Income       : " << row.at("AnnualIncome") << "\n";
        std::cout << "Premium Per Month   : " << std::fixed << std::setprecision(2) << std::stod(row.at("PremiumPerMonth")) << "\n";
        std::cout << "Selected Top Ups    : " << row.at("SelectedTopUps") << "\n";
        std::cout << "Payment Tenure      : " << row.at("PaymentTenure") << "\n";
        std::cout << "Payment Mode        : " << row.at("PaymentMode") << "\n";
        std::cout << "Status              : " << row.at("Status") << "\n";
        std::cout << "Policy Number       : " << row.at("PolicyNumber") << "\n";
        std::cout << "Form                : " << row.at("Form") << "\n";
        std::cout << "Created At          : " << row.at("CreatedAt") << "\n";
        std::cout << "First Name          : " << row.at("FirstName") << "\n";
        std::cout << "Last Name           : " << row.at("LastName") << "\n";
        std::cout << "Email               : " << row.at("Email") << "\n";
        std::cout << "Mobile              : " << row.at("Mobile") << "\n";
        std::cout << "-------------------------------\n";
    }
}  
else {
    std::cout << "No results found.\n";
}
}


void Proposal::cancellation(Database& db, int proposalID) {
    std::cout << "Cancel policy"; 

}


void Proposal::displayProposal(Database& db, int clientID) {
    std::string query = "SELECT ProposalID , InsuranceType , Status , Form  FROM dbo.Proposal WHERE [Status] = 'Pending' AND ClientID = " + std::to_string(clientID);
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);
    if (!results.empty()) {
        // Print header
        std::cout << "ProposalID\tInsuranceType\tStatus\tForm\n";
        std::cout << "------------------------------------------------------\n";

        // Loop through each row (map)
        for (const auto& row : results) {
            // For each row, print each column (key-value pair) in the map
            std::cout << row.at("ProposalID") << "\t"
                << row.at("InsuranceType") << "\t"
                << row.at("Status") << "\t"
                << row.at("Form") << "\n";
        }
    }
    else {
        std::cout << "No results found.\n";
    }
}


int Proposal::displayPolicyUW(Database& db, int clientID) {
    std::string query = "SELECT ProposalID , InsuranceType , Status , Form  FROM dbo.Proposal WHERE [Status] = 'Approved' AND [Form] = 'Proposal' AND ClientID = " + std::to_string(clientID);
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);
    if (!results.empty()) {
        // Print header
        std::cout << "ProposalID\tInsuranceType\tStatus\tForm\n";
        std::cout << "------------------------------------------------------\n";

        // Loop through each row (map)
        for (const auto& row : results) {
            // For each row, print each column (key-value pair) in the map
            std::cout << row.at("ProposalID") << "\t"
                << row.at("InsuranceType") << "\t"
                << row.at("Status") << "\t"
                << row.at("Form") << "\n";
        }
        return 1;
    }
    else {
        std::cout << "No results found.\n";
        return 0;
    }
}

Proposal Proposal::selectProposal(Database& db, int proposalID) {
    std::string query = "SELECT * FROM Proposal WHERE ProposalID = " + std::to_string(proposalID);
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

    if (!results.empty()) {
        std::map<std::string, std::string> proposal = results[0]; // Get the first (and hopefully only) row

        // Now, display the details of the proposal
        std::cout << "Proposal Details:\n";
        std::cout << "Proposal ID: " << proposal["ProposalID"] << "\n";
        std::cout << "Client ID: " << proposal["ClientID"] << "\n";
        std::cout << "Insurance Type: " << proposal["InsuranceType"] << "\n";
        std::cout << "Life Cover Amount: " << proposal["LifeCoverAmount"] << "\n";
        std::cout << "Life Cover Up To Age: " << proposal["LifeCoverUpToAge"] << "\n";
        std::cout << "Premium Per Month: " << proposal["PremiumPerMonth"] << "\n";
        std::cout << "Selected Top Ups: " << proposal["SelectedTopUps"] << "\n";
        std::cout << "Payment Tenure: " << proposal["PaymentTenure"] << "\n";
        std::cout << "Payment Mode: " << proposal["PaymentMode"] << "\n";
        std::cout << "Status: " << proposal["Status"] << "\n";
        std::cout << "Policy Number: " << proposal["PolicyNumber"] << "\n";
        std::cout << "Form: " << proposal["Form"] << "\n";
        std::cout << "Created At: " << proposal["CreatedAt"] << "\n";
    }
    else {
        std::cout << "No proposal found with ProposalID " << proposalID << "\n";
    }
    std::map<std::string, std::string> proposal = results[0];

    return Proposal(proposalID, 0 , "", 0, "" ,"", proposal["PaymentMode"], proposal["PremiumPerMonth"]);
}

Proposal Proposal::selectPolicy(Database& db, int proposalID) {
    std::string query = "SELECT * FROM Proposal WHERE ProposalID = " + std::to_string(proposalID);
    std::vector<std::map<std::string, std::string>> results = db.RunQuerydisplay(db.ConnectToSQLServer(true), query);

    if (!results.empty()) {
        std::map<std::string, std::string> proposal = results[0]; // Get the first (and hopefully only) row

        // Now, display the details of the proposal
        std::cout << "Proposal Details:\n";
        std::cout << "Proposal ID: " << proposal["ProposalID"] << "\n";
        std::cout << "Client ID: " << proposal["ClientID"] << "\n";
        std::cout << "Insurance Type: " << proposal["InsuranceType"] << "\n";
        std::cout << "Life Cover Amount: " << proposal["LifeCoverAmount"] << "\n";
        std::cout << "Life Cover Up To Age: " << proposal["LifeCoverUpToAge"] << "\n";
        std::cout << "Premium Per Month: " << proposal["PremiumPerMonth"] << "\n";
        std::cout << "Selected Top Ups: " << proposal["SelectedTopUps"] << "\n";
        std::cout << "Payment Tenure: " << proposal["PaymentTenure"] << "\n";
        std::cout << "Payment Mode: " << proposal["PaymentMode"] << "\n";
        std::cout << "Status: " << proposal["Status"] << "\n";
        std::cout << "Policy Number: " << proposal["PolicyNumber"] << "\n";
        std::cout << "Form: " << proposal["Form"] << "\n";
        std::cout << "Created At: " << proposal["CreatedAt"] << "\n";
    }
    else {
        std::cout << "No proposal found with ProposalID " << proposalID << "\n";
    }
    std::map<std::string, std::string> proposal = results[0];

    return Proposal(proposalID, 0, "", 0, proposal["Status"], proposal["Form"], proposal["PaymentMode"], proposal["PremiumPerMonth"]); //need to change
}

void Proposal::showClientDashboard(Database& db, Proposal pd) {
    //std::cout << "Client Dashboard\n";
    //std::cout << "1. Create New Proposal\n";
    //std::cout << "2. List Policies\n"; 
    //std::cout << "3. Cancel Policy\n";
    FDclientDashboard::ClientdisplayProposal (db, pd);
}
void Proposal::showClientDashboardUW(Database& db, Proposal pd) {
    //std::cout << "Client Dashboard\n";
    //std::cout << "1. Create New Proposal\n";
    //std::cout << "2. List Policies\n"; 
    //std::cout << "3. Cancel Policy\n";
    FDclientDashboard::ClientdisplayPolicy(db, pd);
}