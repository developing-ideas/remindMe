#include <Windows.h>	//Win32API functions
#include <fstream>		//File Reading/Writing   -   stringstream class
#include <iostream>		//Input/Output
#include <string>		//String Functionality
#include <vector>		//Vector Container/Structure
#include <limits>		
#include <utility>
#include <sstream>	
#include "Reminder.h"	//Reminder Class





/*Global Variables/Declarations*/
std::vector<Reminder> myReminderList_g; 
std::string phoneNumber;


//Constructors and Destructors
Reminder::Reminder() {

}

Reminder::Reminder(std::string rName) {
	name = rName;
}




/*Function Definitions / Implementation*/

//Menu
void Reminder::runMenu() {
	SetConsoleTitle(L"Remind Me");

	
	std::cout << R"(______  _____ ___  ___ _____  _   _ ______         ___  ___ _____ 
| ___ \|  ___||  \/  ||_   _|| \ | ||  _  \        |  \/  ||  ___|
| |_/ /| |__  | .  . |  | |  |  \| || | | | ______ | .  . || |__  
|    / |  __| | |\/| |  | |  | . ` || | | ||______|| |\/| ||  __| 
| |\ \ | |___ | |  | | _| |_ | |\  || |/ /         | |  | || |___ 
\_| \_|\____/ \_|  |_/ \___/ \_| \_/|___/          \_|  |_/\____/ )" << "\n";
                                                                                                                             
	
	
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "Phone Number Attached: " << phoneNumber << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	std::cout << "\nF1 - Add Reminder\n" << std::endl;
	std::cout << "F2 - Start Loop Check (30seconds) and Minimize To Taskbar\n\n" << std::endl;
	std::cout << "F7 - Attach Phone Number\n" << std::endl;
	std::cout << "F8 - Exit" << std::endl;


	while (!GetAsyncKeyState(VK_F8)) {

		if (GetAsyncKeyState(VK_F1)) {
			addReminder();
		}

		else if (GetAsyncKeyState(VK_F2)) {
			startCheck();
		}

		else if (GetAsyncKeyState(VK_F7)) {
			addPhone();
		}


		else {
			//Do Nothing
		}
	}

}


//Get User Input 
void Reminder::getUserInput() {
	//Fix the error handling up

	Reminder newReminder;

	/*Get Name*/
	bool nameStatus = true;

	while (nameStatus) {
		std::cout << "\nPlease enter the reminder name" << std::endl;
		std::string reminderName;
		std::getline(std::cin, reminderName);						//gets input with cin and stores it in our buffer reminderName

		//check for previous failed extraction from cin
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		else if (!reminderName.empty()) {
			newReminder.name = reminderName;
			nameStatus = false;
		}

		else {
			runMenu();
			//Repeat
		}

	}


	/*Get Day*/
	bool dayStatus = true;

	while (dayStatus) {

		std::cout << "\nPlease enter reminder day (0-6)" << std::endl;
		int newDay;
		std::cin >> newDay;

		//check for previous failed extractions from cin
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		else if (newDay >= 0 && newDay <= 6) {
			newReminder.rTime.wDayOfWeek = newDay;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			dayStatus = false;
		}

		else {
			std::cout << "Invalid Option" << std::endl;
			std::cin.ignore(100, '\n');
			std::cin.clear();
		}
	}

	/*Get Hour*/
	bool hourStatus = true;

	while (hourStatus) {
		std::cout << "\nPlease enter which hour in 24 hour time (0-24)" << std::endl;
		int newHour;
		std::cin >> newHour;

		//Check for previous failed extraction
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		else if (newHour >= 0 && newHour <= 23) {
			newReminder.rTime.wHour = newHour;
			std::cin.clear();
			std::cin.ignore(100, '\n');
			hourStatus = false;
		}

		else {
			std::cout << "Invalid Option" << std::endl;
			std::cin.ignore(100, '\n');
			std::cin.clear();
		}

	}

	//Add New Reminder object to global Reminder Vector
	myReminderList_g.push_back(newReminder);

	
	saveFile("Reminderss.csv");
	

}


//Phone
void Reminder::addPhone() {
	bool phoneLoop = true;

	while (phoneLoop) {

		std::cout << "\nPlease enter a valid phone number including the country code. (e.g +610341444555)" << std::endl;
		std::string phoneNumberBuffer;
		std::getline(std::cin, phoneNumberBuffer);

		//check for previous failed extraction from cin
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}

		//Error Handling
		else if (phoneNumberBuffer.empty()) {
			std::cout << "Please enter a valid phone number" << std::endl;
			std::cin.clear();
		}



		else {
			phoneNumber = phoneNumberBuffer;
			phoneLoop = false;
		}

	}
	system("cls");
	runMenu();
}


//Add,Edit,Delete
void Reminder::addReminder() {
		
		getUserInput();

		system("CLS");

		printList();

		runMenu();
	}

void Reminder::editReminder() {}

void Reminder::delReminder() {


}


//Alert
void Reminder::alertUser() {

	for (int i = 0; i < 10; i++) {
		MessageBoxA(NULL, "Alert", "REMINDER", MB_OK);
	}

}


//Loop Check
void Reminder::startCheck() {
	bool isRunning = true;
	SYSTEMTIME time;
	GetLocalTime(&time);

	system("CLS");
	std::cout << "Loop check started\n" << std::endl;

	//Conditional Check
	while (isRunning) {
		std::cout << "Checking..." << std::endl;
		Sleep(1000);

		for (Reminder r : myReminderList_g) {
			if (time.wDayOfWeek == r.rTime.wDayOfWeek && time.wHour == r.rTime.wHour) {
				std::cout << "Conditions Met" << std::endl;
				std::cout << "Reminder Alert SMS Messaged to " << phoneNumber << std::endl;
				isRunning = false;

				//Alert User
				for (int i = 0; i < 10; i++) {
					MessageBoxA(NULL, r.name.c_str(), r.name.c_str(), MB_OK | MB_ICONEXCLAMATION);
				}
				//alertUser();
				system("cls");
				runMenu();
			}
		}
	}

		
}



//File Handling
void Reminder::saveFile(std::string fName) {
	std::ofstream reminderFile;
	reminderFile.open(fName, std::ios_base::app);

	//iterate through our reminder vector and write to file

	for (int i = 0; i < myReminderList_g.size(); i++) {
		reminderFile << myReminderList_g[i].name << "," << myReminderList_g[i].rTime.wDayOfWeek << "," << myReminderList_g[i].rTime.wHour << std::endl;
	}

	//close file
	reminderFile.close();

}


//Misc
void Reminder::printList() {
	std::cout << "============================================" << std::endl;
	std::cout << "Reminder List" << std::endl;
	std::cout << "============================================" << std::endl;

	for (int i = 0; i < myReminderList_g.size(); i++) {
		std::cout << "Reminder Name: " << myReminderList_g[i].name << std::endl;
		std::cout << "Reminder Day Of Week: " << myReminderList_g[i].rTime.wDayOfWeek << std::endl;
		std::cout << "Reminder Hour: " << myReminderList_g[i].rTime.wHour << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	}
}