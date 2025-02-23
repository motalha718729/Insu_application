#pragma once
// Proposal.h
#ifndef PROPOSAL_H
#define PROPOSAL_H

#include <iostream>
#include <string>
#include <vector>
#include "Database.h"
#include "Client.h"

class Proposal {
private:
    
    int clientID;
    std::string InsuranceType;
    long LifecoverAmount ;
    

public:
    int proposalID;
    std::string paymentmode;
    std::string premiumpermon;
    std::string status;
    std::string form;
    Proposal(int pid, int cid ,  std::string InsuType , long lyfcvramt, std::string status, std::string form , std::string paymentmode , std::string premiumpermon);
    static void createNewPropsal(Database& db , Client cd);
    static void displayPolicy(Database& db, Client cd);
    static int displayPolicyUW(Database& db, int clientID);
    static void cancellation(Database& db, int proposalID);
    static void displayProposal(Database& db, int clientID);
    static Proposal selectProposal(Database& db, int proposalID);
    static Proposal selectPolicy(Database& db, int proposalID);
    void showClientDashboard(Database& db, Proposal pd);
    void showClientDashboardUW(Database& db, Proposal pd);
};

#endif // CLIENT_H