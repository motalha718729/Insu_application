#pragma once
// Dashboard.h
#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <iostream>
#include <string>
#include "Database.h"
class Dashboard {
public:
	virtual void displayMenu(Database& db) = 0; // Pure virtual function 
	virtual ~Dashboard() {} 
};
	  class FrontDeskDashboard : public Dashboard 
	  { 
	  public: void displayMenu(Database& db) override;
	  };
	  class SurveyorDashboard : public Dashboard
	  { 
	  public: void displayMenu(Database& db) override;
	  };
	  class UnderwriterDashboard : public Dashboard
	  { 
	  public: void displayMenu(Database& db) override;
	  };
	  class SuperManagerDashboard : public Dashboard
	  {
	  public: 
		  void displayMenu(Database& db) override;
		  void manageUsers(Database& db);
		  void viewApprovalsTable(Database& db);
		  void viewPaymentsTable(Database& db);
		  void addUser(Database& db);
		  void updateUser(Database& db);
		  void deleteUser(Database& db);
		  void viewAllUsers(Database& db);
	  };
#endif // DASHBOARD_H