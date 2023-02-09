#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string.h>
#include <fstream>
#include "ratNum.h"
using namespace std;
//Function prototype
void input(ratNum*);
void menu();
bool login();

int main()
{
	if (login() == true)
		menu();
	return 0;
}

bool login()
{
	char username[100];
	char password[100];
	bool userfound = false; //true if username is in the txt file, false if new new user
	bool passfound = false; //true if password matches the txt file, false if not match
	bool login = false; //flag
	int count = 0; //number of password attempts, max 3 times
	int u_rownum = 1; //row number when looping & strcmp with the user input username, only odd number rows are username rows
	int p_rownum = 1; //row number when looping & strcmp with the user input password, only even number rows are username rows
	char user[100] = { 0 };
	char pass[100] = { 0 };
	cout << "Welcome to rational number calculator! Please enter your username: ";
	cin.getline(username, 100);
	ifstream fin("user_password_pair.txt"); //check for username
	while (fin.getline(user, 100)) //read the txt file line by line
	{
		if (strcmp(user, username) == 0 && u_rownum % 2 != 0) //only when identical username AND odd numbered row detected will return true
		{
			cout << "Username found!" << endl;
			userfound = true;
			break;
		}
		u_rownum++;
	}
	fin.close();
	if (userfound == false) //if username not found in txt file
	{
		cout << "Username not found! Creating a new account for this username..." << endl;
		cout << "Please enter new password that is not longer than 100 characters.\n" << endl;
		cout << "New password: ";
		cin.getline(password, 100); // new password creation
		while (strlen(password) == 0) //check for invalid input
		{
			cout << "No input detected! Please enter a valid new password." << endl;
			cin.getline(password, 100);
		}
		ofstream fout("user_password_pair.txt", ios::app); //create new username-password pair in txt file
		fout << username << endl;
		fout << password << endl;
		fout.close();
		login = true; //access granted
	}
	else
	{
		while (passfound == false && count < 3) //username found, password required, maximum 3 attempts
		{
			p_rownum = 1; //to detect even number rows
			cout << "Please enter password: ";
			cout << "Attempt left: " << 3 - count << endl;
			cin.getline(password, 100);
			ifstream fin("user_password_pair.txt");
			while (fin.getline(pass, 100)) //read the txt file line by line
			{
				if (strcmp(pass, password) == 0 && p_rownum - u_rownum == 1)
					/* Only returns true when:
					* (1) identical password detected
					* (2) the difference between p_rownum and u_rownum is 1 (meaning the row that contains the password must be larger than
					*     the row containing its username by 1 to prevent accident access of other username's password)*/
				{
					cout << "Welcome back, " << username << "!" << endl;
					passfound = true;
					login = true; //access granted
					break;
				}
				p_rownum++;
			}
			count++; //Password attemp counter
			if (count < 3 && passfound == false)
				cout << "Incorrect password! Please try again.\n" << endl;
			fin.close();
		}
		if (passfound == false) //if the user attempted 3 times and still got the password wrong
		{
			cout << "Incorrect password!" << endl;
			cout << "You have used up all the attempts! Program exitting..." << endl;
		}
	}
	return login;
}

void menu()
{
	ratNum* Num1 = new ratNum(); //create the first rational number in heap
	ratNum* Num2 = new ratNum(); //create the second rational number in heap
	char choice;
	cout << "\nWelcome to rational number calculator!" << endl;
	do
	{
		//========================MENU========================
		cout << "\nPlease select operation: " << endl;
		cout << "a. Enter 2 sets of rational number" << endl;
		cout << "b. Find the addition (with LCM)" << endl;
		cout << "c. Find power" << endl;
		cout << "d. Quit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 'a':
			input(Num1); input(Num2); break;
		case 'b':
			Num1->add(Num2); break; //Addition of Num1 and Num2
		case 'c':
			int n;
			cout << "Please enter the value of power, n: ";
			cin >> n;
			Num1->power(n); Num2->power(n);
			break;
		case 'd':
			cout << "Goodbye!" << endl; break;
		default:
			cout << "Wrong input, please select the appropriate operation!" << endl;
		}
	} while (choice != 'd');
}

void input(ratNum* pNum)
{
	int num, denom;
	cout << "Enter a rational number, numerator = "; //Get numerator
	cin >> num;
	while (true) //
	{
		cout << "Enter a rational number, denominator = "; //Get denominator
		cin >> denom;
		if (denom > 0) break;
		cout << "Denominator shound be greater than zero!" << endl;
	}
	pNum->setnum(&num); pNum->setdenom(&denom); //Set the numbers for rational number Num1 and Num2 
	cout << "Rational number created: "; pNum->disp(); cout << endl; //displays the result
}
