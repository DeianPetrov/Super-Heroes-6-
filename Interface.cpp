#include "Interface.h"

bool Interface::runtime = true;
User* Interface::loggedUser = nullptr;

void Interface::IsRunning() {//uj ideyata e da e kato kvoya SEtup

    std::cout << "Welcome to the super heroes 6 game!"<<'\n';
    std::cout << "< If you're not familiar with the commands, use the help guide"<< '\n';
    std::cout << "< 1. Admin Commands" << '\n';
    std::cout << "< 2. Player Commands"<< '\n';
    
    String input;
    while (runtime) {
       
        CommandCheck();
        if (!CommandCheck())
            runtime = false;
            break;
    }
}

bool Interface::CommandCheck() {
    String userInput;
    std::cout << "< Enter a command: ";
    String::GetLine(std::cin, &userInput);
    Commands enumValue;
    if (userInput == "adminLog") {
        enumValue = Commands::adminLog;
    }
    else if (userInput == "logout") {
        enumValue = Commands::logout;
    }
    else if (userInput == "exit") {
        enumValue = Commands::exit;
    }
    else if (userInput == "playerlog") {
        enumValue = Commands::playerLog;
    }
    else if (userInput == "deletePlayer") {
        enumValue = Commands::deletePlayer;
    }
    else if (userInput == "showMarket") {
        enumValue = Commands::Market;
    }
    else if (userInput == "logout") {
        enumValue = Commands::logout;

    }
    else if (userInput == "addMob") {
        enumValue = Commands::addMob;
    }
    else {
        std::cout << "Invalid input!" << std::endl;
        return false;
    }

    switch (enumValue)
    {
    case Commands::adminLog:
        //if (IsAdmin()) {
        //    GetAdminFromLoggedUser()->login();
        //}
        //else {
        //    throw "you don't have access to this command!";
        //}
        adminlogin();
        break;

    case Commands::playerLog:
        //if (IsPlayer()) {
        //    GetPlayerFromLoggedUser()->login();

        //}

        playerlogin();
        break;
    case Commands::checkPlayersList:
        if (IsPlayer()) {
            std::ifstream playerFile("players.txt");
            GetPlayerFromLoggedUser()->CheckPlayerList(playerFile);
            playerFile.close();
            
        }

        else if(IsAdmin()){
            throw "you don't have access to this command!";
        }
        break;
    case Commands::checkAdminsList:
        if (IsAdmin()) {
            std::ifstream adminsFile("admins.txt");
            GetAdminFromLoggedUser()->CheckAdminList(adminsFile);
            adminsFile.close();
        }
        else if (IsPlayer()) {
            throw "you don't have access to this command!";
        }

        break;
    case Commands::logout:
        if (!IsAdmin() && !IsPlayer())
            return true;
        else
            logout();
        break;
    case Commands::addMob:
        if (IsAdmin()) {
            std::ofstream file("mobs.txt");
            GetAdminFromLoggedUser()->AddMobs(file);
        }
        if (IsPlayer()) {
            throw "you don't have access to this command!";
        }


    case Commands::Market:
        if (IsAdmin() || IsPlayer()) {
            std::ifstream file("market.txt");
            loggedUser->ShowMobMarket(file);
            file.close();
        }
        break;
    case Commands::buy:
        if (IsAdmin()) {
            throw "As an admin you can't buy heroes!";
        }
        if (IsPlayer()) {

        }
        break;
    case Commands::addNewPlayer:
        if (IsAdmin()) {
			GetAdminFromLoggedUser()->AddAdmin();
        }
        if (IsPlayer()) {
            throw "you don't have access to this command!";
        }
        break;
    case Commands::deletePlayer:
        if (IsAdmin()) {

            String username;
            std::cout << "Enter username to delete: ";
            String::GetLine(std::cin, &username);

            std::fstream playersFile("players.txt");

			GetAdminFromLoggedUser()->DeleteProfile(username, playersFile);//needs rework for players

			playersFile.close();
        }
        if (IsPlayer()) {
            throw "you don't have access to this command!";
        }
        break;
    case Commands::exit:
        return false;
    case Commands::attack:
        if (IsPlayer()) {
            String username;
            std::cout << "Enter username to the player you wish to attack: ";
            String::GetLine(std::cin, &username);

        }
        if (IsAdmin()) {
            throw "you don't have access to this command!";
        }
        break;
    default:
        break;
    }

    return true;

}

Player* Interface::GetPlayerFromLoggedUser(){
    return dynamic_cast<Player*>(loggedUser); 
}

Admins* Interface::GetAdminFromLoggedUser(){
    return dynamic_cast<Admins*>(loggedUser); 
}

bool Interface::IsPlayer() {
    return GetPlayerFromLoggedUser() != nullptr;
}
bool Interface::IsAdmin() { 
    return GetAdminFromLoggedUser() != nullptr; 
}
void Interface::logout()
{
    delete loggedUser;
    loggedUser = nullptr;
}

bool Interface::is_empty(std::ifstream& pFile)
{
    size_t pos = pFile.tellg();
    pFile.seekg(0, std::ios::end);
    size_t len = pFile.tellg();

    pFile.seekg(pos, std::ios::beg);

    return len == 0;

    //return pFile.peek() == std::ifstream::traits_type::eof();
}

void Interface::adminlogin()
{
	if (loggedUser)
		return;

    String Username;
    String Password;
    std::cout << "Enter username "<<'\n';
    String::GetLine(std::cin, &Username);
    std::cout << "Enter password "<<'\n';
    String::GetLine(std::cin, &Password);

	std::ifstream file("admins.txt");

    if(is_empty(file)) // no admins
    {
        file.close();

        Admins a("Ivan","Ivanov","DemonSlayer123","adbc@abv.bg","12345aA");

        std::ofstream f("admins.txt");
        Admins::WriteUserToFile(f, a);
        f.close();
    }

    Admins a;

    while (!file.eof())
    {
        Admins::ReadUserFromFile(file, a);

        if (a.GetUsername() == Username && a.GetPassword() == Password)
        {
            loggedUser = new Admins(a);
        }
    }
}

void Interface::playerlogin()
{
    if(loggedUser)
        return;

	String Username;
	String Password;
	std::cout << "Enter username " << '\n';
	String::GetLine(std::cin, &Username);
	std::cout << "Enter password " << '\n';
	String::GetLine(std::cin, &Password);

	std::ifstream file("players.txt");

	Player p;

	while (!file.eof())
	{
		Player::ReadUserFromFile(file, p);

		if (p.GetUsername() == Username && p.GetPassword() == Password)
		{
			loggedUser = new Player(p);
		}
	}
}

