#pragma once
#include "MyString.h"
#include <iostream>
#include "Mobs.h"
class User
{
	String First_Name;
	String Last_Name;
	String Username;
	String Email;
	String Password;
public:

	User(const String& firstName, const String& lastName, const String& username, 
		const String& Password, const String& email);

	static bool CheckIsPasswordCorrect(const String& password);
	static bool CheckUsername(const String& username/*, std::ifstream& file*/);
	virtual void login();
	
	
	const String& GetFirstName() const;
	const String& GetLastName() const;
	const String& GetEmail() const;
	const String& GetUsername() const;
	const String& GetPassword() const;


	void ShowMobMarket(std::ifstream& file);

	

protected:
	void SetFirstName(const String& firstname);
	void SetLastName(const String& lastname);
	void SetUserName(const String& username);
	void SetEmail(const String& email);
	void SetPassword(const String& password);

	bool AuthenticateUser(const String& name, const String& password, std::ifstream& file);


};

