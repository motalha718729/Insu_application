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
	  public: void displayMenu(Database& db) override;
	  };
#endif // DASHBOARD_H