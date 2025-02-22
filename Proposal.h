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
    int proposalID;
    int clientID;
    std::string InsuranceType;
    long LifecoverAmount ;
    std::string status;
    std::string form;

public:
    Proposal(int pid, int cid ,  std::string InsuType , long lyfcvramt, std::string status, std::string form);
    static void createNewPropsal(Database& db , Client cd);
    static void displayPolicy(Database& db, Client cd);
    static void cancellation(Database& db, int proposalID);
};

#endif // CLIENT_H