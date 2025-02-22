// Proposal.cpp

#include "Proposal.h"
#include "Database.h"
#include "Client.h"
#include "FDclientDashboard.h"

Proposal::Proposal(int pid, int cid, std::string InsuType, long lyfcvramt, std::string status, std::string form) : proposalID(pid), clientID(cid), InsuranceType(InsuType), LifecoverAmount(lyfcvramt), status(status), form(form) {}

void Proposal::createNewPropsal(Database& db , Client cd) {
    std::string propID,clientid, InsuType, SelectedTopUps, PaymentMode, Status, PolicyNumber, Form;
    int  LifeCoverUpToAge, PaymentTenure;
    double LifeCoverAmount, PremiumPerMonth;
    std::string CreatedAt; // Assuming date will be entered as string in a specific format

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

    std::string query =  "INSERT INTO dbo.Proposal (ProposalID, ClientID, InsuranceType, LifeCoverAmount, LifeCoverUpToAge, PremiumPerMonth, SelectedTopUps, PaymentTenure, PaymentMode,  Status, PolicyNumber, Form, CreatedAt) VALUES ('" + propID + "','" + clientid + " ','  " + InsuType + "', "+ std::to_string(LifeCoverAmount) + ", " + std::to_string(LifeCoverUpToAge) + ", " + std::to_string(PremiumPerMonth) + ", '" + SelectedTopUps + "', "
        + std::to_string(PaymentTenure) + ", '" + PaymentMode + "', '" + Status + "', '" + PolicyNumber + "', '"
        + Form + "', '" + CreatedAt + "')";

    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "Proposal created successfully!\n";



}

void Proposal::displayPolicy(Database& db , Client cd) {
    int clientid;
    clientid = (cd.clientID);

    std::string query = "SELECT * FROM dbo.Proposal WHERE ClientID = " + std::to_string(clientid);
    db.RunQuery(db.ConnectToSQLServer(true), query);
    std::cout << "display Policy";
}

void Proposal::cancellation(Database& db, int proposalID) {
    std::cout << "Cancel policy"; 

}
