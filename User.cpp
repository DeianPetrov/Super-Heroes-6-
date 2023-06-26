#include "User.h"
const String& User:: GetFirstName() const{
	return First_Name;

}
const String& User::GetLastName() const{
	return Last_Name;
}
const String& User::GetEmail() const{
	return Email;
}
const String& User::GetUsername() const{
	return Username;
}
const String& User::GetPassword() const{
	return Password;
}

void User::ShowMobMarket(std::ifstream& file) {
	Mobs temp;
	if (!file.is_open())
		return;

	while (!file.eof()) {
		Mobs::ReadMobFromFile(file, temp);
		std::cout << "name:" << temp.GetNickname() << " " << "price: " << temp.GetPrice() << "$";
	}
}

User::User(const String& firstName, const String& lastName, const String& username, const String& Password, const String& email)
{
	SetFirstName(firstName);
	SetLastName(lastName);
	SetUserName(username);
	SetPassword(Password);
	SetEmail(email);
}

bool User::CheckIsPasswordCorrect(const String& password){
	bool BigLetter = false;
	bool SmallLetter = false;
	bool Number = false;
	for (unsigned i = 0; i < password.GetSize(); i++) {
		if ((BigLetter = true) && (SmallLetter = true) && (SmallLetter = true)) return true;
		if (password[i] <58 && password[i] > 47) {
			Number = true;
		}
		if (password[i] > 64 && password[i] < 91) {
			BigLetter = true;
		}
		if (password[i] > 96 && password[i]<123) {
			SmallLetter = true;
		}

	}
	return BigLetter == false && SmallLetter == false && Number == false;
}
bool User::CheckUsername(const String& username /*std::ifstream& file*/) {
	if (username.GetSize() > 16) {
		return false;
	}
	return true;
}

void User::login() {
	std::cout << "Enter username: ";
	String username = "";
	String::GetLine(std::cin, &username);
	std::cout << "Enter password: ";
	String password = "";
	String::GetLine(std::cin, &password);
	std::ifstream file("players.txt");
	if (AuthenticateUser(username,password, file)) {
		return;
	}
	else throw "Invalid name.Please Register or write it correctly.";
	file.close();
}

void User::SetFirstName(const String& firstname)
{
	First_Name = firstname;
}
void User::SetLastName(const String& lastname)
{
	Last_Name = lastname;
}
void User::SetUserName(const String& username)
{
	Username = username;
}
void User::SetEmail(const String& email)
{
	Email = email;
}
void User::SetPassword(const String& password)
{
	Password = password;
}

bool User::AuthenticateUser(const String& name, const String& password, std::ifstream& file)
{
	String temp1;
	String FoundUserName;
	String FoundPassword;

	if (!file.is_open())
		return false;
	while (!file.eof()) {
		String::GetLine(file, &temp1);

		String::GetLine(file, &temp1);


		String::GetLine(file, &temp1);
		FoundUserName = temp1;

		String::GetLine(file, &temp1);

		String::GetLine(file, &temp1);
		FoundPassword = temp1;

		if ((FoundUserName == name) && (FoundPassword == password)) {
			return true;
		}

	}
	return false;
}