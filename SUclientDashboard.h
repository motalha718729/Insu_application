#pragma once
#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <iostream>
#include <string>
#include "Database.h"
#include "Client.h"
#include "Proposal.h"
#include "Dashboard.h"


class SUclientDashboard {
public:
	static void ClientdisplayMenu(Database& db, Proposal pd);
};

#endif 
//ClientDashboard.h

