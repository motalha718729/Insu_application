#pragma once
//ClientDashboard.h

#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <iostream>
#include <string>
#include "Database.h"
#include "Client.h"
#include "Proposal.h"


class FDclientDashboard  {
public:
	static void ClientdisplayMenu(Database& db , Client cd);
	static void ClientdisplayProposal(Database& db, Proposal pd);
	static void ClientdisplayPolicy(Database& db, Proposal pd);
};

#endif 
//ClientDashboard.h

