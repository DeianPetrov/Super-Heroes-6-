#pragma once
#include <iostream>
#include <fstream>
#include "MyString.h"
#include "Pair.hpp"
#include "Commands.h"
#include "Admins.h"
#include "Player.h"


class Interface
{   
	static Commands cm;
	static bool runtime;
	static User* loggedUser;
public:

	static bool CommandCheck();
    static void IsRunning();

	static bool IsPlayer();
	static bool IsAdmin();

	static Player* GetPlayerFromLoggedUser();
	static Admins* GetAdminFromLoggedUser();

	static void adminlogin();
	static void playerlogin();
	static void logout();
	static void NoAdmins();
	static bool is_empty(std::ifstream& file);
};

