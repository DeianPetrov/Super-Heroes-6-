#include "Mobs.h"
#include "Player.h"


Mobs::Mobs() {
	
}

Mobs::Mobs( const String& FirstName, const String& LastName, const String& Nickname,
	Element power, unsigned strength, unsigned price, Stance st,String owner) {
	SetFirstName(FirstName);
	SetLastName(LastName);
	SetUserName(Nickname);
	SetElement(power);
	SetStrength(strength);
	SetPrice(price);
	st = Stance::Attack;
	owner = "";
}
void Mobs::ReadMobFromFile(std::ifstream& file, Mobs& Mob) {
	String temp;
	unsigned strength;
	unsigned price;
	String::GetLine(file, &temp); // first name
	Mob.SetFirstName(temp);

	String::GetLine(file, &temp); // last name
	Mob.SetLastName(temp);

	String::GetLine(file, &temp); // user name
	Mob.SetUserName(temp);

	String::GetLine(file, &temp); // element
	Mob.SetElement(temp);

	String::GetLine(file, &temp); // strength
	strength = std::atoi(temp.c_str());
	Mob.SetStrength(strength);

	String::GetLine(file, &temp); // price
	price = std::atoi(temp.c_str());
	Mob.SetPrice(price);

	String::GetLine(file, &temp); // owner
	Mob.SetOwner(temp);
}

bool Mobs::ExistsInList(const String& Nickname, std::ifstream& file) {
	Mobs temp;
	if (!file.is_open())
		return false;
	while (!file.eof()) {
		Mobs::ReadMobFromFile(file, temp);
		if (Nickname==temp.GetNickname()) {
			return true;
		 }
	}
	return false;
}


void Mobs::SetFirstName(const String& firstname)
{
	FirstName = firstname;
}
void Mobs::SetLastName(const String& lastname)
{
	LastName = lastname;
}
void Mobs::SetUserName(const String& username)
{
	Nickname = username;
}
void Mobs::SetElement(Element element) {
	this->element = element;
}

void Mobs::SetElement(const String& elements)
{ 

	if (elements == "Water") {
		element = Element::Water;

	}
	if (elements == "Fire") {
		element = Element::Fire;
	}
	if (elements == "Earth") {
		element = Element::Earth;
	}
	
}
void Mobs::SetStrength( unsigned strenght)
{
	Strength = strenght;
}
void Mobs::SetPrice( unsigned price) {
	Price = price;
}

void Mobs::RemoveMobOnDeath(const Mobs& mob, std::fstream& file){
	String temp1;
	String FoundUserName;
	

	Array<String> lines;

	if (!file.is_open())
		return;

	size_t pos = file.tellg();

	while (!file.eof()) {
		String::GetLine(file, &temp1); // first name
		lines.Add(temp1);

		String::GetLine(file, &temp1); // last name
		lines.Add(temp1);

		String::GetLine(file, &temp1); // user name
		FoundUserName = temp1;
		lines.Add(temp1);

		String::GetLine(file, &temp1); // element
		lines.Add(temp1);

		String::GetLine(file, &temp1);
		lines.Add(temp1);

		String::GetLine(file, &temp1); // Strenght
		lines.Add(temp1);

		String::GetLine(file, &temp1); // Price
		lines.Add(temp1);

		String::GetLine(file, &temp1); // stance
		lines.Add(temp1);
		
		String::GetLine(file, &temp1); // owner
		lines.Add(temp1);

		if ((FoundUserName == mob.GetNickname())) {
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
			lines.RemoveFromBack();
		}
	}

	file.seekg(0, std::ios::beg);
	for (size_t i = 0; i < lines.GetLength(); i++)
	{
		file << lines[i] << "\n";
	}

	file.seekg(pos, std::ios::beg);
}


void Mobs::PowerAdvantage(Element otherElement, unsigned& powerFirst, unsigned& powerSecond) {
	switch(otherElement) {
	case(Element::Earth):
		if (element == Element::Earth) {
			return;
		}
		if (element == Element::Fire) {
			powerFirst *= 2;
		}
		if (element == Element::Water) {
			powerSecond *= 2;
		}

	case(Element::Fire):
		if (element == Element::Earth) {
			powerSecond *= 2;

		}
		if (element == Element::Fire) {
			return;
		}
		if (element == Element::Water) {
			powerFirst *= 2;

		}
	case(Element::Water):
		if (element == Element::Earth) {
			powerFirst *= 2;
		}
		if (element == Element::Fire) {
			powerSecond *= 2;

		}
		if (element == Element::Water) {
			return;
		}
	}
}
void Mobs::FightMob(Mobs& other, std::fstream& file) {
	std::ifstream fileplayers("players.txt");
//for now we suppose that we will have correct input 
	Player p1, p2;
	int amountfnChange = 100;
	while (!fileplayers.eof())
	{
		Player::ReadUserFromFile(fileplayers, p1);

		if (p1.GetUsername() == Owner)
			break;
	}

	fileplayers.seekg(0, std::ios::beg);

	while (!fileplayers.eof())
	{
		Player::ReadUserFromFile(fileplayers, p2);

		if (p2.GetUsername() == other.Owner)
			break;
	}

	fileplayers.close();

	unsigned power1 = this->GetStrength();
	unsigned power2 = other.GetStrength();

	if (other.GetStance() == Stance::Defense)
	{
		PowerAdvantage(other.GetElement(), power1, power2);

		if (Strength > other.Strength) {
			RemoveMobOnDeath(other, file);
			p1.SetMoney(p1.GetMoney() +amountfnChange);
		//	p2.SetMoney(p2.GetMoney() - amountfnChange);
			
		}
		if (Strength < other.Strength) 
		{
			RemoveMobOnDeath((*this),file);
			p1.SetMoney(p1.GetMoney() + amountfnChange);
			p2.SetMoney(p2.GetMoney() - amountfnChange);
		}
		if (Strength == other.Strength)
		{
			std::cout << "STALEMATE";
		}
	}
	if (other.GetStance() == Stance::Attack) 
	{
		PowerAdvantage(other.GetElement(), power1, power2);

		if (Strength > other.Strength) {
			RemoveMobOnDeath(other, file);
			p1.SetMoney(p1.GetMoney() + amountfnChange);
			p2.SetMoney(p2.GetMoney() - amountfnChange);
		}
		if (Strength < other.Strength) {
			RemoveMobOnDeath((*this),file);
		}
		if (Strength == other.Strength) {
			std::cout << "STALEMATE";
		}
	}

	std::fstream fileplayers1("players.txt");

	Player::RewriteUserFromFile(fileplayers1, p1);
	Player::RewriteUserFromFile(fileplayers1, p2);

	fileplayers1.close();
}
void Mobs::Attack() {
	/*because for now there isn't a checking if the mobs are repeating themselves,
	we say that the admin had made the heroes without repetition 
	*/
	String name;
	String Mob1;
	String Mob2;
	std::cout << "Enter a First Name ";
	String::GetLine(std::cin, &name);

	std::cout << "Enter the mob you wish to attack with ";
	String::GetLine(std::cin, &name);

	std::cout << "Enter the mob you wish to attack ";
	String::GetLine(std::cin, &name);


}
void Mobs::ChangeStance(Mobs& mob) {
	if (mob.stance == Stance::Attack) {
		mob.stance = Stance::Defense;
		std::cout << "stance changed to defense";

	}
	else {
		mob.stance = Stance::Attack;
		std::cout << "stance changed to attack";

	}
}
void Mobs::SetOwner(const String& owner) {
	Owner = owner;
}

const String& Mobs::GetFirstName() const {
	return FirstName;
}
const String& Mobs::GetLastName() const {
	return LastName;
}
const String& Mobs::GetNickname() const {
	return Nickname;
}
unsigned  Mobs::GetStrength() const {
	return Strength;
}
double  Mobs::GetPrice() const {
	return Price;
}
Stance  Mobs::GetStance() const {
	return stance;
}
Element  Mobs::GetElement() const {
	return element;
}
const String& Mobs::GetOwner()const {
	return Owner;
}
Mobs::~Mobs() {

}