// Proposal.cpp

#include "Proposal.h"
#include "Database.h"
#include "Client.h"
#include "FDclientDashboard.h"

Proposal::Proposal(int pid, int cid, std::string InsuType, long lyfcvramt, std::string status, std::string form) : proposalID(pid), clientID(cid), InsuranceType(InsuType), LifecoverAmount(lyfcvramt), status(status), form(form) {}

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
    std::cout << "Enter CreatedAt (e.g., YYYY-MM-DD HH:MM:SS): ";
    std::getline(std::cin, CreatedAt);

    std::string query =  "INSERT INTO dbo.Proposal (ProposalID, ClientID, InsuranceType, LifeCoverAmount, LifeCoverUpToAge, PremiumPerMonth, SelectedTopUps, PaymentTenure, PaymentMode,  Status, PolicyNumber, Form, CreatedAt) VALUES ('" + propID + "','" + clientid + "', '" + InsuType + "', "+ std::to_string(LifeCoverAmount) + ", " + std::to_string(LifeCoverUpToAge) + ", " + std::to_string(PremiumPerMonth) + ", '" + SelectedTopUps + "', "
        + std::to_string(PaymentTenure) + ", '" + PaymentMode + "', '" + Status + "', '" + PolicyNumber + "', '"
        + Form + "', '" + CreatedAt + "')";

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
for (const auto& row : results) {
    std::cout << "ProposalID: " << row.at("ProposalID")
        << ", InsuranceType: " << row.at("InsuranceType")
        << ", LifeCoverAmount: " << row.at("LifeCoverAmount")
        << ", LifeCoverUpToAge: " << row.at("LifeCoverUpToAge")
        << ", TobaccoConsumption: " << row.at("SmokerStatus")
        << ", AnnualIncome: " << row.at("AnnualIncome")
        << ", PremiumPerMonth: " << row.at("PremiumPerMonth")
        << ", SelectedTopUps: " << row.at("SelectedTopUps")
        << ", PaymentTenure: " << row.at("PaymentTenure")
        << ", PaymentMode: " << row.at("PaymentMode")
        << ", Status: " << row.at("Status")
        << ", PolicyNumber: " << row.at("PolicyNumber")
        << ", Form: " << row.at("Form")
        << ", CreatedAt: " << row.at("CreatedAt")
        << ", FirstName: " << row.at("FirstName")
        << ", LastName: " << row.at("LastName")
        << ", Email: " << row.at("Email")
        << ", Mobile: " << row.at("Mobile")
        << "\n";
}
}


void Proposal::cancellation(Database& db, int proposalID) {
    std::cout << "Cancel policy"; 

}
