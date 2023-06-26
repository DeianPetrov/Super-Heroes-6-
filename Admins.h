#pragma once
#include <iostream>
#include "User.h"
#include "Mobs.h"
#include "MyString.h"
#include <fstream>
#include "Player.h"

class Admins : public User
{
public:
	Admins();
	Admins(const String& First_Name, const String& Last_Name, const String& Username, const String& Email,
		const String& Password);

	void SetFirstName(const String& firstname);
    void SetLastName(const String& firstname);
    void SetUserName(const String& firstname);
    void SetEmail(const String& firstname);
    void SetPassword(const String& firstname);


	void login() override;

	Player AddPlayer();
	Admins AddAdmin();
	static void DeleteProfile(const String& username, std::fstream& file);//changed admins to player 
	static void CheckPlayerList(std::ifstream& file);
	static void CheckAdminList(std::ifstream& file);
	
	Mobs AddMobs(std::ofstream& file);
	
	
	bool AuthenticateUser(const String& name, const String& password, std::ifstream& file);


	static void ReadUserFromFile(std::ifstream& file, Admins& admin);
	static void WriteUserToFile(std::ofstream& file, const Admins& user);
};



