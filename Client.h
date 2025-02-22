#pragma once
// Client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Database.h"

class Client {
private:
    /*int clientID;*/
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;

public:
    int clientID;
    Client(int id, std::string fName, std::string lName, std::string mail, std::string ph);
    static void createNewClient(Database& db);
    static void displayClients(Database& db);
    static Client selectClient(Database& db, int clientID);
   void showClientDashboard(Database& db , Client cd);
};

#endif // CLIENT_H