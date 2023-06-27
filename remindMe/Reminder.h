#pragma once

class Reminder {
	private:
		SYSTEMTIME rTime;

	public:
		
		//Member Attributes/Variables
		std::string name = "";


		/*Constructors / Destructor*/
		Reminder();								//Default Constructor
		Reminder(std::string rName);

		/*Function Declarations*/
		void runMenu();

		void getUserInput();

		void addReminder();
		void editReminder();
		void delReminder();
		void addPhone();

		void startCheck();
		void alertUser();

		void saveFile(std::string fName);

		void printList();

	};
