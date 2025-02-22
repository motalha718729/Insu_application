#pragma once
//ClientDashboard.h

#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <iostream>
#include <string>
#include "Database.h"
#include "Client.h"


class FDclientDashboard  {
public:
	static void ClientdisplayMenu(Database& db , Client cd);
};

#endif 
//ClientDashboard.h

