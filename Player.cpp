#include "Player.h"
Player::Player() : User("","","","","") {

}
Player::Player(const String& First_Name, const String& Last_Name, const String& Username, const String& Email,
	const String& Password, int money) : User(First_Name, Last_Name, Username, Password, Email){
	
	SetFirstName(First_Name);
	SetLastName(Last_Name);
	SetUserName(Username);

	SetEmail(Email);
	SetPassword(Password);
	SetMoney(Money);
}
void Player::SetMoney(unsigned money)
{
  Money = money;
}
void Player::SetFirstName(const String& firstname) {
	User::SetFirstName(firstname);

}
void Player::SetLastName(const String& lastname) {
	User::SetFirstName(lastname);

}
void Player::SetUserName(const String& username){
	User::SetFirstName(username);

}
void Player::SetEmail(const String& email){
	User::SetFirstName(email);
}
void Player::SetPassword(const String& password) {
	User::SetFirstName(password);

}

void Player::CheckPlayerList(std::ifstream& file) {
	Player temp;
	if (!file.is_open())
		return;
	while (!file.eof()) {
		Player::ReadUserFromFile(file, temp);
		std::cout << temp.GetFirstName() << " " << temp.GetLastName() << " "
			<< temp.GetUsername() << " " << temp.GetEmail();
	}
}

void Player::ReadUserFromFile(std::ifstream& file, Player& player) {
	String temp;
	unsigned money= 0;
	String::GetLine(file, &temp); // first name
	player.SetFirstName(temp);

	String::GetLine(file, &temp); // last name
	player.SetLastName(temp);

	String::GetLine(file, &temp); // user name
	player.SetUserName(temp);

	String::GetLine(file, &temp); // email
	player.SetEmail(temp);

	String::GetLine(file, &temp); // password
	player.SetPassword(temp);
	
	String::GetLine(file, &temp);//money
	money = std::atoi(temp.c_str());
	player.SetMoney(money);

}

int Player::GetMoney() const {
	return Money;
}
void Player::WriteUserFromFile(std::ofstream& file, const Player& player)
{
	file << player.GetFirstName() << "\n";
	file << player.GetLastName() << "\n";
	file << player.GetUsername() << "\n";
	file << player.GetEmail() << "\n";
	file << player.GetPassword() << "\n";
	file << player.GetMoney() << "\n";
}

void Player::RewriteUserFromFile(std::fstream& file, const Player& player)
{
	if (!file.is_open())
		return;

	String temp1;
	String FoundUserName;
	String FoundPassword;

	Array<String> lines;

	size_t pos = file.tellg();

	while (!file.eof()) {
		String::GetLine(file, &temp1); // first name
		lines.Add(temp1);

		String::GetLine(file, &temp1); // last name
		lines.Add(temp1);

		String::GetLine(file, &temp1); // user name
		FoundUserName = temp1;
		lines.Add(temp1);

		String::GetLine(file, &temp1); // email
		lines.Add(temp1);

		String::GetLine(file, &temp1);//password
		FoundPassword = temp1;
		lines.Add(temp1);

		String::GetLine(file, &temp1); // money
		lines.Add(temp1);

		if ((FoundUserName == player.GetUsername())) {

			char buff[1024];
			_itoa_s(player.GetMoney(), buff, 0);

			lines[lines.GetLength()-0] = buff;
			lines[lines.GetLength()-1] = player.GetPassword();
			lines[lines.GetLength()-2] = player.GetEmail();
			lines[lines.GetLength()-3] = player.GetUsername();
			lines[lines.GetLength()-4] = player.GetLastName();
			lines[lines.GetLength()-5] = player.GetFirstName();
		}
	}

	file.seekg(0, std::ios::beg);
	for (size_t i = 0; i < lines.GetLength(); i++)
	{
		file << lines[i] << "\n";
	}

	file.seekg(pos, std::ios::beg);
}

void Player::DeleteProfile(const Player& player, std::fstream& file) {
	String temp1;
	String FoundUserName;
	String FoundPassword;

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

		String::GetLine(file, &temp1); // email
		lines.Add(temp1);

		String::GetLine(file, &temp1);
		FoundPassword = temp1;
		lines.Add(temp1);

		if ((FoundUserName == player.GetUsername()) && (FoundPassword == player.GetPassword())) {
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

void Player::Buy( Player& player,const String& nickname, std::ifstream file) {
	if (file.eof()) {
		return;
	}
	while (!file.eof()) {
		Mobs temp;
		Mobs::ReadMobFromFile(file, temp);
		/*String FoundNickname;
		String temptext;
		String::GetLine(file, &temptext); 

		String::GetLine(file, &temptext); 
		
		String::GetLine(file, &temptext); 
		
		FoundNickname = temptext;

		String::GetLine(file, &temptext);

		String::GetLine(file, &temptext);
		String::GetLine(file, &temptext);
		String::GetLine(file, &temptext);
		String::GetLine(file, &temptext);*/
		if (temp.GetNickname() == nickname) {
			temp.SetOwner(player.GetUsername());
			int bucks = player.GetMoney();
			if (bucks < temp.GetPrice()) std::cout << "You dont have enough money!";
			else {
				player.SetMoney(bucks - temp.GetPrice());
			}
		}

	}
}

