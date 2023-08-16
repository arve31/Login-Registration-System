#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <iomanip>
#include <cctype>


bool ValidateEmail(std::string email);
void Login();
void Registration();
bool CheckUsername(std::string username);

int main()
{
    char logRegChoice;

    do
    {
        std::cout << "are you already an user? (y/n): ";
        std::cin >> logRegChoice;
        tolower(logRegChoice);
    } while (logRegChoice != 'y' && logRegChoice != 'n');

    if (logRegChoice == 'y')
    {
        Login();
    }
    else
    {
        Registration();
    }
    

    return 0;
}

bool ValidateEmail(std::string email)
{
    std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool CheckUsername(std::string username)
{
	bool status = false;

	std::ifstream file("users.txt");

	if (!file)
	{
        std::cout << "Unable to open file!" << std::endl;
    }
	else
    {
        for (std::string user; !status && (file >> user);)
        {
           status = username == user; 
        }
    }

	return status;
}

void Registration()
{
    std::string username;
    std::string password;
    char confirmation;
    int count = 0;
    std::string temp;
    std::string email;

    std::cout << "************" << std::endl;
    std::cout << "Registration" << std::endl;
    std::cout << "************" << std::endl;

    do
    {
        do
        {
            std::cout << "Username: ";
            std::getline(std::cin >> std::ws, username);

            for(int i = 0; i < username.length(); i++)
            {
                if(username[i] == ' ')
                {
                    username[i] = '_';
                }

                CheckUsername(username);

                if(CheckUsername(username) == true)
                {
                    std::cout << "************************" << std::endl;
                    std::cout << "Username already exists!" << std::endl;
                    std::cout << "************************" << std::endl;
                    break;
                }
            }
        } while (CheckUsername(username) == true);

        std::cout << "Username: " << username << " Would you like to continue with this username? (y/n): ";
        std::cin >> confirmation;
        tolower(confirmation);
    } while (confirmation != 'y');

    do
    {
        do
        {
            std::cout << "Password: ";
            std::getline(std::cin >> std::ws, password);
            if(password.length() < 8)
            {
                std::cout << "*******************************************" <<std::endl;
                std::cout << "Password must be at least 8 characters long!" <<std::endl;
                std::cout << "*******************************************" <<std::endl;
            }
            
        } while (password.length() < 8);
        std::cout << "confirm your password: ";
        std::getline(std::cin >> std::ws, temp);
        if(password != temp)
        {
            std::cout << "******************************" << std::endl;
            std::cout << "Password don't match try again!" << std::endl;
            std::cout << "******************************" << std::endl;
        }
    } while (password != temp);
    
    do
    {
        std::cout << "Email: ";
        std::getline(std::cin >> std::ws, email);
        ValidateEmail(email);
        if (ValidateEmail(email) == false)
        {
            std::cout << "*************************" << std::endl;
            std::cout << "enter valid email addres!" << std::endl;
            std::cout << "*************************" << std::endl;
        }
    } while (ValidateEmail(email) == false);
    
    std::ofstream file("users.txt", std::ios::app);
    {
		if (!file.is_open()) 
        {
			std::cout << "Unable to open file" <<std::endl;
		}

		file << username << " " << password << std::endl;
		file << std::endl;
		file.close();
    }

    std::cout << "You have been successfully registered!" << std::endl;
    std::cout << "Redirectiong to login page..." << std::endl;

    Login();

}

bool CheckCredentials(std::string username, std::string password)
{
	bool status = false;

	std::ifstream file("users.txt");

	if (!file)
	{
        std::cout << "Unable to open file!" << std::endl;
    }
	else
    {
		for (std::string user, passwd; !status && (file >> user >> passwd);)
        {
            status = username == user && password == passwd;
        }
    }
	return status;
}

void Login()
{
    std::string username;
    std::string password;
    int count = 0;

    std::cout << "*****" << std::endl;
    std::cout << "LogIn" << std::endl;
    std::cout << "*****" << std::endl;

    do
    {
        count++;

        std::cout << "Username: ";
        std::getline(std::cin >> std::ws, username);
        std::cout << "Password: ";
        std::getline(std::cin >> std::ws, password);

        CheckCredentials(username, password);

    } while(CheckCredentials(username, password) != true);

    std::cout << "************************" << std::endl;
    std::cout << "Welcome, " << username << std::endl;
    std::cout << "************************" << std::endl; 
}