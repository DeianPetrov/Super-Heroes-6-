#pragma once
#include "MyString.h"
#include "Elements.h"
#include "Stance.h"
#include <iostream>
#include "Array.hpp"


class Mobs
{
	String FirstName;
	String LastName;
	String Nickname;
	Element element;
	unsigned Strength = 1;
	unsigned Price = 1;
	Stance stance;
	String Owner ;
public:
	Mobs();
	Mobs(const String& FirstName, const String& LastName, const String& Nickname,Element power,
		unsigned strength, unsigned price, Stance st,String owner);
	void PowerAdvantage(Element otherElement, unsigned& powerFirst, unsigned& powerSecond);
	void FightMob( Mobs& other, std::fstream& file);
	void ChangeStance(Mobs& mob);
	void Attack();
	bool ExistsInList(const String& Nickname, std::ifstream& file);
	static void ReadMobFromFile(std::ifstream& file, Mobs& Mob);
	void RemoveMobOnDeath(const Mobs& mob, std::fstream& file);
	
	
	void SetFirstName(const String& firstname);
	void SetLastName(const String& lastname);
	void SetUserName(const String& username);
	void SetElement(const String& element) ;
	void SetElement(Element element);
	void SetOwner(const String& owner);
	void SetStrength(unsigned strength);
	void SetPrice(unsigned price);



	const String& GetFirstName() const;
	const String& GetLastName() const;
	const String& GetNickname() const;
	unsigned GetStrength() const;
	double GetPrice() const;
	Stance GetStance() const;
	Element GetElement() const;
	const String& GetOwner()const;
	~Mobs();

};

