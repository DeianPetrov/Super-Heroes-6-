#include "Admins.h"
#include "Array.hpp"

Admins::Admins() :User("", "", "", "", "")
{ 

}

Admins::Admins(const String& First_Name, const String& Last_Name, const String& Username, const String& Email,
    const String& Password) : User(First_Name, Last_Name, Username, Password, Email) {
    SetFirstName(First_Name);
    SetLastName(Last_Name);
    SetUserName(Username);
    SetEmail(Email);
    SetPassword(Password);
}
Admins Admins::AddAdmin() {

    std::ofstream file("admins.txt");
    String FirstName, LastName, UserName, Email, Password;
    std::cout << "Enter a First Name";
    String::GetLine(std::cin, &FirstName);

    std::cout << "Enter a Last Name";
    String::GetLine(std::cin, &LastName);

    std::cout << "Enter a User Name";
    String::GetLine(std::cin, &UserName);
    if (!CheckUsername(UserName)) throw "Please,the length must be less than 16 characters!";
    std::cout << "Enter an Email";
    String::GetLine(std::cin, &Email);

    std::cout << "Enter a Password";
    String::GetLine(std::cin, &Password);
    if (!CheckIsPasswordCorrect(Password)) 
        throw "Incorrect password format! please follow the guidelines.";
    
    Admins a(FirstName,LastName,UserName,Email,Password);
    WriteUserToFile(file, a);

    return a;
}
void Admins::SetFirstName(const String& firstname){
	User::SetFirstName(firstname);
}
void Admins::SetLastName(const String& firstname){
	User::SetLastName(firstname);
}
void Admins::SetUserName(const String& firstname){
    User::SetUserName(firstname);
}
void Admins::SetEmail(const String& firstname)
{
    User::SetEmail(firstname);
}
void Admins::SetPassword(const String& firstname)
{
    User::SetPassword(firstname);
}

void Admins::DeleteProfile(const String& username, std::fstream& file){
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

        if ((FoundUserName == username)) {
            lines.RemoveFromBack();
            lines.RemoveFromBack();
            lines.RemoveFromBack();
            lines.RemoveFromBack();
            lines.RemoveFromBack();
        }
    }

    file.seekg(0, std::ios::beg);
    for(size_t i = 0; i < lines.GetLength(); i++)
    {
        file << lines[i] << "\n";
    }

    file.seekg(pos, std::ios::beg);
}
void Admins::CheckPlayerList(std::ifstream& file){
    Player temp;
    if (!file.is_open())
        return;
    while (!file.eof()) {
        Player::ReadUserFromFile(file, temp);
        std::cout << temp.GetFirstName() << " " << temp.GetLastName() << " "
            << temp.GetUsername() << " " << temp.GetEmail();
    }
}
void Admins::CheckAdminList(std::ifstream& file){
    Admins temp;
    if (!file.is_open())
        return;

    while (!file.eof()) {
        Admins::ReadUserFromFile(file, temp);
        std::cout << temp.GetFirstName() << " " <<temp.GetLastName()<<" "
            <<temp.GetUsername() << " " <<temp.GetEmail();
    }
}
Mobs Admins::AddMobs(std::ofstream& file){
   
    String FirstName, LastName, UserName;
    String power;
    String stance;
    Element element;
    unsigned strength;
    unsigned price;
    Stance st;
    String owner = "";
    std::cout << "Enter a First Name";
    String::GetLine(std::cin, &FirstName);

    std::cout << "Enter a Last Name";
    String::GetLine(std::cin, &LastName);

    std::cout << "Enter a User Name";
    String::GetLine(std::cin, &UserName);

    std::cout << "Enter a Power: fire,earth,water";
    String::GetLine(std::cin, &power);
    if (power == "earth") {
        element =Element::Earth;//changed from ==
    }
    if (power == "fire") {
        element = Element::Fire;//changed from ==
    }

    if (power == "water") {
        element = Element::Water;//changed from ==
    }

     std::cout << "Enter the Strength of the mob;";
    std::cin>>strength;
    std::cin.ignore();

    std::cout << "Enter the price of the mob;";
    std::cin >> price;
    std::cin.ignore();

    std::cout << "Enter the stance of the mob;";
    String::GetLine(std::cin, &stance);
    if (stance == "Defense") {
        st = Stance::Defense;
    }
    if (stance == "Attack") {
        st = Stance::Attack;
    }
    return Mobs( FirstName, LastName, UserName, element, strength, price, st,owner);

}

void Admins::ReadUserFromFile(std::ifstream& file, Admins& admin){

    String temp;

    String::GetLine(file, &temp); // first name
    admin.SetFirstName(temp);

	String::GetLine(file, &temp); // last name
	admin.SetLastName(temp);

	String::GetLine(file, &temp); // user name
    admin.SetUserName(temp);

	String::GetLine(file, &temp); // email
    admin.SetEmail(temp);

	String::GetLine(file, &temp); // password
    admin.SetPassword(temp);

}
void Admins::login() {//override se slaga v header a samo
    std::cout << "Enter username: ";
    String username = "";
    String::GetLine(std::cin, &username);
    std::cout << "Enter password: ";
    String password = "";
    String::GetLine(std::cin, &password);
    std::ifstream file("Admin.txt");
    if (AuthenticateUser(username,password,file)) {///CheckUsername ne e razpisan da chekva ot failove ----> da izpolzvam i tuk AutenticateUser ?? 
        std::cout << "Login Successful";
        return;
    }
    else throw "Invalid name.Please Register or write it correctly.";
    file.close();
}

void Admins::WriteUserToFile(std::ofstream& file, const Admins& user){

    file << user.GetFirstName() << "\n";
    file << user.GetLastName() << "\n";
    file << user.GetUsername() << "\n";
    file << user.GetEmail()<< "\n";
    file << user.GetPassword() << "\n";

}


bool Admins::AuthenticateUser(const String& name,const String& password, std::ifstream& file) {
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
