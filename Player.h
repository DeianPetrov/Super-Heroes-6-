#pragma once
#include "User.h"
#include <iostream>
#include <fstream>
#include "Mobs.h"
#include "MyString.h"


class Player : public User
{
protected:

	
	int Money=1000;
    public:
	 Player();
	 Player(const String& First_Name, const String& Last_Name, const String& Username, const String& Email,
		const String& Password, int money);
	
	
   

	void SetMoney(unsigned money);
	void SetFirstName(const String& firstname);
	void SetLastName(const String& lastname);
	void SetUserName(const String& username);
	void SetEmail(const String& email);
	void SetPassword(const String& password);

	int GetMoney() const;

	void CheckPlayerList(std::ifstream& file);
	void DeleteProfile(const Player& player, std::fstream& file);

	void Buy( Player& player,const String& nickname,std::ifstream);
	
	static void ReadUserFromFile(std::ifstream& file, Player& player);
	static void WriteUserFromFile(std::ofstream& file, const Player& player);

	static void RewriteUserFromFile(std::fstream& file, const Player& player);
};

