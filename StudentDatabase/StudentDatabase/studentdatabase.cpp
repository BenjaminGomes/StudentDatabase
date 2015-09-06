
/*
*********************************************************************************************
*																							*
*		Programmer:				Ben Gomes													*
*		Instructor:				David Wilke													*
*		Programming Assignment:	Student Database											*
*		Date:					27 March 2014												*
*																							*
*		This program prompts for a menu selection of 1 - 4. The menu choice 4 is used to	*
*		exit the program. Menu selection 1 will create a student record (constisting of		*
*		student number, name, degree program, and G.P.A.) that is written to a text file	*
*		and the program error checks the user's input after each variable is entered. The	*
*		program will ask the user to re-enter any bad data. Menu selection 2 will read the	*
*		text file that is created by menu choice 1, and display all student records to the	*
*		user. The third menu selection will prompt the user to input the student number		*
*		they wish to look up. The program then searches the text file and will verify if	*
*		if the user entered number matches any existing student file. If the record is		*
*		found, the program displays the record to the user. If the record is not found, the *
*		program outputs that the record was not found. After each menu selection the user	*
*		is prompted with the choice of returning to the main menu, or ending the program.	*
*																							*
*********************************************************************************************
*/

/*
*************************************************
*												*
*		Disabling the warning prompted for		*
*		using a strcpy function on line 1210 as	*
*		debugger warns to use strcpy_s instead	*
*												*
*************************************************
*/

#pragma warning(disable: 4996)

/*
*************************************************
*												*
*			Preprocessor Directives				*
*												*
*************************************************
*/

#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<strstream>

/*
*************************************************
*												*
*					Namespace					*
*												*
*************************************************
*/

using namespace std;

/*
*************************************************
*												*
*				Function Prototypes				*
*												*
*************************************************
*/

void DisplayMenu(int*);
void ErrorCheckMenuChoice(int*);
void MenuSelectionSwitch(int*);
void ReturnMenu(char*);
void ProcessStudentRecord();
void RetrieveStudentRecords();
void RetrieveStudentRecord();

bool TestStudentNumber(char[]);
bool TestStudentGPA(char[]);

/*
*************************************************
*												*
*				Constant Variable				*
*												*
*************************************************
*/

const int ALPHA_LENGTH = 1;
const int NUM_LENGTH = 8;
const int NUM_LENGTH_GPA_FIRST = 1;
const int NUM_LENGTH_GPA_SECOND = 4;
const int ALPHA_LENGTH_GPA_PERIOD = 2;

/*
*********************************************************************************************
*																							*
*										Main Class											*
*																							*
*********************************************************************************************
*/

void main()
{
	/*
	*************************************************
	*												*
	*				Declaring Variables				*
	*												*
	*************************************************
	*/

	char Enter = ' ',
		ReturnMenuChoice = ' ';

	int MenuChoice = 0;

	/*
	*************************************************
	*												*
	*				Setting Precision				*
	*												*
	*************************************************
	*/

	cout << setprecision(2) << fixed << showpoint;

	/*
	*************************************************
	*												*
	*	Creating Do-While Loop That Error Checks	*
	*			the Return To Main Menu Input		*
	*												*
	*************************************************
	*/

	do
	{
		/*
		*************************************************
		*												*
		*				Calling Functions				*
		*												*
		*************************************************
		*/

		DisplayMenu(&MenuChoice);
		ErrorCheckMenuChoice(&MenuChoice);
		MenuSelectionSwitch(&MenuChoice);
		ReturnMenuChoice = ' ';
		ReturnMenu(&ReturnMenuChoice);
	}

	while (ReturnMenuChoice == 'Y');

	cin.ignore();
	cin.get(Enter);
}

/*
*********************************************************************************************
*																							*
*									Display Menu Function Header							*
*																							*
*********************************************************************************************
*/

void DisplayMenu(int *pMenuChoice)
{
	system("CLS");
	cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
	cout << setw(46) << " " << "Student Main Menu\n\n\n";
	cout << setw(15) << " " << "1. Enter Student Record Information\n\n";
	cout << setw(15) << " " << "2. Retrieve Student Records\n\n";
	cout << setw(15) << " " << "3. Search Student Record\n\n";
	cout << setw(15) << " " << "4. Exit\n\n";
	cout << setw(15) << " " << "Enter in Menu Choice ==> ";
	cin >> *pMenuChoice;
}

/*
*********************************************************************************************
*																							*
*							Error Check Menu Choice Function Header							*
*																							*
*********************************************************************************************
*/

void ErrorCheckMenuChoice(int *pMenuChoice)
{
	while (*pMenuChoice != 1 && *pMenuChoice != 2 && *pMenuChoice != 3 && *pMenuChoice != 4)
	{
		system("CLS");
		cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(46) << " " << "Student Information\n\n\n";
		cout << setw(15) << " " << "You have entered in an invalid Menu Choice of " << *pMenuChoice << "\n";
		cout << setw(15) << " " << "Please enter menu selection of 1 - 4 ==> ";
		cin >> *pMenuChoice;

	}
}

/*
*********************************************************************************************
*																							*
*								Menu Selection Switch Function Header						*
*																							*
*********************************************************************************************
*/

void MenuSelectionSwitch(int *pMenuChoice)
{
	switch (*pMenuChoice)
	{
	case 1:
		ProcessStudentRecord();
		break;

	case 2:
		RetrieveStudentRecords();
		break;

	case 3:
		RetrieveStudentRecord();
		break;

	case 4:
		system("CLS");
		cout << "\n\n" << setw(10) << " " << "Thank you for using the Student Database Program\n";
		cout << setw(10) << " " << "'Have nice day!'\n\n";
		cout << setw(10) << " ";
		system("Pause");
		break;
	}
}

/*
*********************************************************************************************
*																							*
*								Return Menu Choice Function Header							*
*																							*
*********************************************************************************************
*/

void ReturnMenu(char *pReturnMenuChoice)
{
	while (*pReturnMenuChoice != 'Y' && *pReturnMenuChoice != 'N')
	{
		system("CLS");
		cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(46) << " " << "Student Information\n\n\n";
		cout << setw(26) << " " << "Return Menu\n\n\n";
		cout << setw(15) << " " << "Would you like to return to the Main Menu\n";
		cout << setw(15) << " " << "Answer 'Y' for YES and 'N' for NO ==> ";
		cin >> *pReturnMenuChoice;
		*pReturnMenuChoice = toupper(*pReturnMenuChoice);
		system("CLS");
	}
}

/*
*********************************************************************************************
*																							*
*								Process Student Record Function Header						*
*																							*
*********************************************************************************************
*/

void ProcessStudentRecord()
{
	/*
	*************************************************
	*												*
	*	Creating Variables & Boolean Statements		*
	*												*
	*************************************************
	*/

	bool StuDegreePosition = false;
	bool StuNumberPosition = false;
	bool StuNamePosition = false;
	bool StuGPAPosition = false;

	char Degrees[4] = { 'C', 'E', 'M', 'S' },
		StudentFirstName[32] = {},
		StudentLastName[32] = {},
		Degree[4] = {},
		StudentNumber[18] = {},
		StudentGPA[6] = {},
		Space[] = " ";

	int Length = 0;

	/*
	*************************************************
	*												*
	*  Creating the object "Outfile" using fstream	*
	*												*
	*************************************************
	*/

	fstream OutFile;

	cin.ignore();

	/*
	*************************************************
	*												*
	*		Creating While loop that will run		*
	*		as long as StuNumberPosition = false	*
	*												*
	*************************************************
	*/

	while (!StuNumberPosition)
	{
		system("CLS");
		cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(37) << " " << "Student Information\n\n\n";
		cout << setw(15) << " " << "Student Information\n\n\n";
		cout << setw(15) << " " << "Enter in the Students Number ==> ";

		cin.getline(StudentNumber, 18);
		Length = strlen(StudentNumber);

		/*
		*************************************************
		*												*
		*		Testing Student Number with if,			*
		*		else if, and else to verify that		*
		*			it is 8 characters long				*
		*												*
		*************************************************
		*/

		if (Length == 8)
		{
			/*
			*************************************************
			*												*
			*			Changing boolean statement			*
			*		StuNumberPosition = true so	it			*
			*			fulfills the requirement			*
			*												*
			*************************************************
			*/

			StuNumberPosition = true;
		}
		else if (Length > 8)
		{
			system("CLS");
			cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(37) << " " << "Student Main Menu\n\n\n\n\n";
			cout << setw(15) << " " << "This Student number you entered is " << Length << " characters long\n";
			cout << setw(15) << " " << "This Student number is too long\n\n";
			cout << setw(15) << " " << "Student Number needs to be eight characters in length\n";
			cout << setw(15) << " " << "Please try again\n\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		else
		{
			system("CLS");
			cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(37) << " " << "Student Main Menu\n\n\n\n\n";
			cout << setw(15) << " " << "This Student number you entered is " << Length << " characters long\n";
			cout << setw(15) << " " << "This Student number is too short\n\n";
			cout << setw(15) << " " << "Student Number needs to be eight characters in length\n";
			cout << setw(15) << " " << "Please try again\n\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		/*
		*************************************************
		*												*
		*	Creating If statement to verify the length	*
		*			of the Student Number = 8			*
		*												*
		*************************************************
		*/

		if (Length == 8)
		{
			/*
			*************************************************
			*												*
			*	   Calling the TestStudentNumber boolean 	*
			*	  function to validate the Student Number	*
			*												*
			*************************************************
			*/

			if (TestStudentNumber(StudentNumber))
			{
				system("CLS");
				cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(37) << " " << "Student Main Menu\n\n\n\n\n\n";
				cout << setw(15) << " " << "This Student number has been validated\n";
				cout << setw(15) << " ";

				/*
				*************************************************
				*												*
				*	  Opening the StudentDatabase.txt file to	*
				*			write the StudentNumber to it		*
				*												*
				*************************************************
				*/

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << StudentNumber << ", ";
				OutFile.close();

				system("Pause");
			}

			else
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n";
				cout << setw(24) << " " << "The Students Number starts with an Alpha character 'A'\n";
				cout << setw(30) << " " << "followed by seven Numerical characters\n";
				cout << setw(33) << " " << "Enter in the proper Student number\n\n";
				cout << setw(24) << " ";
				system("Pause");

				/*
				*************************************************
				*												*
				*			Changing boolean statement			*
				*	StuNumberPosition = false so the user is	*
				*			prompted again for to enter			*
				*			   in the Student Number			*
				*												*
				*************************************************
				*/

				StuNumberPosition = false;
			}
		}
	}
	/*
	*************************************************
	*												*
	*		Creating While loop to run while		*
	*		StuNamePosition is Equal to False		*
	*												*
	*************************************************
	*/

	while (!StuNamePosition)
	{
		system("CLS");
		cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(46) << " " << "Student Information\n\n\n\n";
		cout << setw(15) << " " << "Enter in the First name of the student ==> ";
		cin.getline(StudentFirstName, 32);

		/*
		*************************************************
		*												*
		*		Creating if statement that verifies 	*
		*  that StudentFirstName is not too many char's *
		*												*
		*************************************************
		*/

		if (sizeof(StudentFirstName) >= strlen(StudentFirstName) + strlen(Space) + 1)
		{
			/*
			*************************************************
			*												*
			*	Concatenating StudentFirstName and Space	*
			*	to set-up the StudentFirstName variable		*
			*	 to later accept the user's last name		*
			*												*
			*************************************************
			*/

			strcat_s(StudentFirstName, Space);

			cout << setw(15) << " " << "Last name of the student ==> ";

			cin.clear();
			cin.sync();
			cin.getline(StudentLastName, 32);

			/*
			*************************************************
			*												*
			*		Concatenating StudentFirstName and		*
			*	StudentLastName to create a single variable	*
			*												*
			*************************************************
			*/

			if (sizeof(StudentFirstName) >= strlen(StudentFirstName) + strlen(StudentLastName) + 1)
			{
				strcat_s(StudentFirstName, StudentLastName);

				/*
				*************************************************
				*												*
				*		Writing Student's Full Name to the		*
				*			StudentDatabase.txt	file			*
				*												*
				*************************************************
				*/

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << StudentFirstName << ", ";
				OutFile.close();
				StuNamePosition = true;
			}
			/*
			*************************************************
			*												*
			*	 Creating Else statement that prompts the	*
			*	 user that their name must be re-entered	*
			*		as their current entry is too long		*
			*												*
			*************************************************
			*/

			else
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n\n";
				cout << setw(15) << " " << "Your Name is too large to fit into this array\n";
				cout << setw(15) << " " << "Please shorten your Name to fit in the allocatted space.\n";
				cout << setw(15) << " ";
				system("Pause");
				StuNamePosition = false;
			}
		}
		/*
		*************************************************
		*												*
		*	 Creating Else statement that prompts the	*
		*	 user that their name must be re-entered	*
		*		as their current entry is too long		*
		*												*
		*************************************************
		*/

		else
		{
			system("CLS");
			cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(46) << " " << "Student Information\n\n\n\n";
			cout << setw(15) << " " << "Your Name is too large to fit into this array\n";
			cout << setw(15) << " " << "Please shorten your Name to fit in the allocatted space.\n";
			cout << setw(15) << " ";
			system("Pause");
			StuNamePosition = false;
		}
	}
	/*
	*************************************************
	*												*
	*		Creating While loop to run while		*
	*		StuDegreePosition is Equal to False		*
	*												*
	*************************************************
	*/

	while (!StuDegreePosition)
	{
		system("CLS");
		cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(46) << " " << "Student Information\n\n\n\n\n";
		cout << setw(15) << " " << "Enter in the letter that corresponds to the Studen's Degree Program\n";
		cout << setw(15) << " " << "Enter the letter\n\n";
		cout << setw(17) << " " << "Computer Science - C\n";
		cout << setw(17) << " " << "Engineering      - E\n";
		cout << setw(17) << " " << "General Math     - M\n";
		cout << setw(17) << " " << "General Science  - S\n";
		cout << setw(17) << " " << "==> ";
		cin.clear();
		cin.sync();
		cin.getline(Degree, 4);

		/*
		*************************************************
		*												*
		*		Creating if statement to verify that	*
		*	  student's Degree only 1 character long	*
		*												*
		*************************************************
		*/

		if (strlen(Degree) == 1)
		{
			Degree[0] = toupper(Degree[0]);

			/*
			*************************************************
			*												*
			*	  Creating if, else if, else if, else if	*
			*	statements that check the Degree to	make	*
			*  sure that it is a valid degree selection. If	*
			*  the selection is valid, it writes the Degree *
			*	abbreviation to the text file and changes	*
			*			the StuDegreePosition = true		*
			*												*
			*************************************************
			*/

			if (!strcmp(Degree, "C"))
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n\n\n";
				cout << setw(15) << " " << "You Have Chosen the Computer Science Degree\n";
				cout << setw(15) << " ";
				system("Pause");

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << Degree << ", ";
				OutFile.close();

				StuDegreePosition = true;
			}
			else if (!strcmp(Degree, "E"))
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n\n\n";
				cout << setw(15) << " " << "You Have Chosen the Engineering Degree\n";
				cout << setw(15) << " ";
				system("Pause");

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << Degree << ", ";
				OutFile.close();

				StuDegreePosition = true;
			}
			else if (!strcmp(Degree, "M"))
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n\n\n";
				cout << setw(15) << " " << "You Have Chosen the Math Degree\n";
				cout << setw(15) << " ";
				system("Pause");

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << Degree << ", ";
				OutFile.close();

				StuDegreePosition = true;
			}
			else if (!strcmp(Degree, "S"))
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(46) << " " << "Student Information\n\n\n\n\n";
				cout << setw(15) << " " << "You Have Chosen the Science Degree\n";
				cout << setw(15) << " ";
				system("Pause");

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << Degree << ", ";
				OutFile.close();

				StuDegreePosition = true;
			}
		}
		else
		{
			system("CLS");
			cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(46) << " " << "Student Information\n\n\n\n\n";
			cout << setw(15) << " " << "Student Degree was NOT FOUND\n";
			cout << setw(15) << " " << "Please try again\n";
			cout << setw(15) << " ";
			system("Pause");

			StuDegreePosition = false;
		}
	}
	/*
	*************************************************
	*												*
	*		Creating While loop to run while		*
	*		StuGPAPosition is Equal to False		*
	*												*
	*************************************************
	*/

	while (!StuGPAPosition)
	{
		system("CLS");
		cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(46) << " " << "Student Test Scores\n\n\n\n\n";
		cout << setw(15) << " " << "Example GPA    3.75\n\n";
		cout << setw(15) << " " << "Enter in the students Current Grade Point Average ==> ";
		cin.clear();
		cin.sync();
		cin.getline(StudentGPA, 6);
		Length = strlen(StudentGPA);

		/*
		*************************************************
		*												*
		*	Creating if, else if, and else statements 	*
		*	to determine whether StuGPAPosition is 4	*
		*		characters long. If GPA is four, the	*
		*		StuGPAPosition (boolean) = true.		*
		*												*
		*************************************************
		*/

		if (Length == 4)
		{
			StuGPAPosition = true;
		}
		else if (Length > 4)
		{
			system("CLS");
			cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(37) << " " << "Student GPA Information\n\n\n\n\n";
			cout << setw(15) << " " << "Student GPA is " << Length << " characters long\n";
			cout << setw(15) << " " << "This Student number is too long\n\n";
			cout << setw(15) << " " << "Student GPA needs to be four characters in length\n";
			cout << setw(15) << " " << "Please try again\n\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		else
		{
			system("CLS");
			cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(37) << " " << "Student GPA Information\n\n\n\n\n";
			cout << setw(15) << " " << "This Student GPA is " << Length << " characters long\n";
			cout << setw(15) << " " << "This Student number is too short\n\n";
			cout << setw(15) << " " << "Student GPA needs to be four characters in length\n";
			cout << setw(15) << " " << "Please try again\n\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		/*
		*************************************************
		*												*
		*	Creating if statement, with a nested if /	*
		*	else. The first if statement verifies that	*
		*	the length of GPA is four char's. While		*
		*	this was already done, this prevents GPA's 	*
		*	that are not the correct length from even	*
		*	being tested in the TestStudentGPA boolean	*
		*	function.									*
		*												*
		*************************************************
		*/

		if (Length == 4)
		{
			/*
			*************************************************
			*												*
			*	Creating nested if, else statement that 	*
			*	runs TestStudentGPA that passes StudentGPA	*
			*	to the function which checks the validity	*
			*	of the user's input. If the GPA is bad, 	*
			*	the user is returned to re-input the GPA.	*
			*	If the GPA is validated, the program writes	*
			*	the GPA to the text file.					*
			*												*
			*************************************************
			*/

			if (TestStudentGPA(StudentGPA))
			{
				system("CLS");
				cout << "\n\n" << setw(21) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(37) << " " << "Student Main Menu\n\n\n\n\n\n";
				cout << setw(15) << " " << "This Student GPA has been validated\n";
				cout << setw(15) << " ";
				system("Pause");

				OutFile.open("StudentDatabase.txt", ios::out | ios::app);
				OutFile << StudentGPA << ",\n";
				OutFile.close();


			}
			else
			{
				system("CLS");
				cout << "\n\n" << setw(30) << " " << "Student's Data Base, St. Louis Community College\n\n\n";
				cout << setw(30) << " " << "This will not work\n";
				cout << setw(30) << " ";
				system("Pause");

				StuGPAPosition = false;
			}
		}
	}

}

/*
*********************************************************************************************
*																							*
*								Test Student Number Function Header							*
*																							*
*********************************************************************************************
*/

bool TestStudentNumber(char StudentNumber[10])
{
	/*
	*************************************************
	*												*
	*	Creating for loop that verifies that the	*
	*	first element of the array is an 'A'. If 	*
	*	the StudentNumber does not begin with an 'A'*
	*	the boolean function returns false to the	*
	*	ProcessStudentRecord function.				*
	*												*
	*************************************************
	*/

	for (int count = 0; count < ALPHA_LENGTH; count++)
	{
		if (StudentNumber[count] != 'A')
		{
			return false;
		}
	}
	/*
	*************************************************
	*												*
	*	Creating for loop that verifies that the	*
	*	remaining elements of the array are numbers.*
	*	If the StudentNumber's 2nd - 8th element	*
	*	(1-7 subscript) are not numbers, the		*
	*	boolean function returns false to the		*
	*		ProcessStudentRecord function.			*
	*												*
	*************************************************
	*/

	for (int count = ALPHA_LENGTH; count < NUM_LENGTH; count++)
	{
		if (!isdigit(StudentNumber[count]))
		{
			return false;
		}
	}
	/*
	*************************************************
	*												*
	*	If the StudentNumber passes both for loops	*
	*	above, the TestStudentNumber function		*
	*	returns true.								*
	*												*
	*************************************************
	*/

	return true;
}

/*
*********************************************************************************************
*																							*
*								Test Student GPA Function Header							*
*																							*
*********************************************************************************************
*/

bool TestStudentGPA(char StudentGPA[6])
{
	/*
	*************************************************
	*												*
	*	Creating for loop that verifies that the	*
	*	first element of the array is an integer.	*
	*	If the StudentGPA does not begin with an	*
	*	integer, the boolean function returns false	*
	*	to the ProcessStudentRecord function.		*
	*												*
	*************************************************
	*/

	for (int count = 0; count < NUM_LENGTH_GPA_FIRST; count++)
	{
		if (!isdigit(StudentGPA[count]))
		{
			return false;
		}
	}
	/*
	*************************************************
	*												*
	*	Creating for loop that verifies that the	*
	*	2nd element of the StudentGPA array is		*
	*	a "." and if it is not a period, the		*
	*	boolean function returns false to the		*
	*		ProcessStudentRecord function.			*
	*												*
	*************************************************
	*/

	for (int count = 1; count < ALPHA_LENGTH_GPA_PERIOD; count++)
	{
		if (!strcmp(StudentGPA, "."))
		{
			return false;
		}
	}
	/*
	*************************************************
	*												*
	*	Creating for loop that verifies that the	*
	*	3rd-4th elements (2 & 3 subscript) of the	*
	*	StudentGPA array are integers. If they are	*
	*	not, then the boolean function returns		*
	*	false to the ProcessStudentRecord function.	*
	*												*
	*************************************************
	*/

	for (int count = 2; count < NUM_LENGTH_GPA_SECOND; count++)
	{
		if (!isdigit(StudentGPA[count]))
		{
			return false;
		}
	}
	/*
	*************************************************
	*												*
	*	Creating if, else statement that verifies	*
	*	that the StudentGPA's first integer is a	*
	*	number between 0-4. If it is not, then the	*
	*	boolean function returns false to the		*
	*		ProcessStudentRecord function.			*
	*												*
	*************************************************
	*/

	if (StudentGPA[0] >= 48 && StudentGPA[0] <= 52)
	{
		/*
		*************************************************
		*												*
		*	Creating if, else statement with a nested	*
		*	if, else inside of a following if, else to	*
		*	create a testing structure that verifies if	*
		*	the digit of the StudentGPA is a 4. If the	*
		*	first digit is a four, the next two if		*
		*	statements verify that the following two	*
		*	integers are the number 0, as a GPA above	*
		*	4.00 is not possible. If the GPA fulfills	*
		*	this criteria, the TestStudentGPA boolean	*
		*	is returned as true.						*
		*												*
		*************************************************
		*/

		if (StudentGPA[0] == 52)
		{
			if (StudentGPA[2] == 48)
			{
				if (StudentGPA[3] == 48)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

/*
*********************************************************************************************
*																							*
*							Retrieve Student Records Function Header						*
*																							*
*********************************************************************************************
*/

void RetrieveStudentRecords()
{
	char Student[32];

	/*
	*************************************************
	*												*
	*  Creating the object "Infile" using fstream.	*
	*												*
	*************************************************
	*/

	fstream InFile;

	/*
	*************************************************
	*												*
	*	Trying to open the InFile to be able		*
	*			to pull	data from it.				*
	*												*
	*************************************************
	*/

	InFile.open("StudentDatabase.txt", ios::in);

	/*
	*************************************************
	*												*
	*	Creating an if, else statement to test if 	*
	*	the file StudentDatabase.txt is found. If	*
	*	there is a problem opening the file an error*
	*	message displays. Else, the program then	*
	*	displays the header used to display the		*
	*	student records.
	*												*
	*************************************************
	*/

	if (InFile.fail())
	{
		system("CLS");
		cout << "\n\n";
		cout << setw(15) << " " << "There is an error opening the file.\n";
		cout << setw(15) << " ";
		system("Pause");
	}
	else
	{
		system("CLS");
		cout << "\n\n" << setw(32) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(47) << " " << "Student Record Retrieval\n\n\n\n\n";
		cout << "Student Number       Student Name           Degree Program                      GPA\n";
		cout << "--------------       ------------           --------------                      ---\n";

		/*
		*************************************************
		*												*
		*	Pulling the first line from the text file. 	*
		*	While the file can pull a line from the text*
		*	file it reads and displays the information,	*
		*	but once the file ends it exits out of the	*
		*	while loop.									*
		*												*
		*************************************************
		*/

		InFile.getline(Student, 32, ',');
		while (!InFile.fail())
		{
			cout << Student << right << setw(25);
			InFile.getline(Student, 32, ',');
		}
		/*
		*************************************************
		*												*
		*			Closing the text file				*
		*												*
		*************************************************
		*/

		InFile.close();
		cout << "\n\n";
		system("Pause");
	}
}

/*
*********************************************************************************************
*																							*
*							Retrieve Student Record Function Header							*
*																							*
*********************************************************************************************
*/

void RetrieveStudentRecord()
{
	bool Position = false;

	char StudentNumber[28];

	string StudentStr;

	/*
	*************************************************
	*												*
	*	Creating vectors that we can copy to the	*
	*	tokenization of the string to each selected	*
	*	vector segment.								*
	*												*
	*************************************************
	*/

	vector<string> vecStudentNumber;
	vector<string> vecStudentName;
	vector<string> vecStudentDegree;

	/*
	*************************************************
	*												*
	*  Creating the object "Infile" using fstream.	*
	*												*
	*************************************************
	*/

	fstream InFile;

	/*
	*************************************************
	*												*
	*	Trying to open the InFile to be able		*
	*			to pull	data from it.				*
	*												*
	*************************************************
	*/

	InFile.open("StudentDatabase.txt", ios::in);

	/*
	*************************************************
	*												*
	*	Creating an if, else statement to test if 	*
	*	the file StudentDatabase.txt is found. If	*
	*	there is a problem opening the file an error*
	*	message displays. Else, the program then	*
	*	prompts the user to enter the Student Number*
	*	they wish to search for.					*
	*												*
	*************************************************
	*/

	if (InFile.fail())
	{
		system("CLS");
		cout << "\n\n";
		cout << setw(15) << " " << "There is an error opening the file.\n";
		cout << setw(15) << " ";
		system("Pause");
	}
	else
	{
		system("CLS");
		cout << "\n\n" << setw(32) << " " << "Student's Data Base, St. Louis Community College\n";
		cout << setw(47) << " " << "Student Record Finder\n\n\n\n\n";
		cout << setw(15) << " " << "Enter in the Student Number ==> ";
		cin.clear();
		cin.sync();
		cin.ignore();
		cin.getline(StudentNumber, 28);

		/*
		*************************************************
		*												*
		*	Using a while loop to search the text file	*
		*	for the Student Number the user imputed.	*
		*	While the program can get a line (student	*
		*	record) it runs the loop again until the	*
		*	end of the file.							*
		*												*
		*************************************************
		*/

		while (getline(InFile, StudentStr))
		{
			/*
			*************************************************
			*												*
			*	Creating a pointer to a char that the		*
			*	program will use along with the user		*
			*	imputed StudentNumber to search the text	*
			*	file for a identical string copy.			*
			*												*
			*************************************************
			*/

			char *sStudentNumber = new char[StudentStr.length() + 1];

			/*
			*************************************************
			*												*
			*	Creating a string copy of the StudentStr	*
			*	string and placing the value into the		*
			*	sStudentNumber pointer.						*
			*												*
			*************************************************
			*/

			strcpy(sStudentNumber, StudentStr.c_str());

			/*
			*************************************************
			*												*
			*	Creating a pointer pChar that is equal to 	*
			*	tokinization of sStudentNumber (pointer)	*
			*	up to the null terminator ",".				*
			*												*
			*************************************************
			*/

			char *pChar = strtok(sStudentNumber, ",");

			/*
			*************************************************
			*												*
			*	Creating an if else statement that test 	*
			*	whether the user entered StudentNumber		*
			*	matches with the pointer sSTudentNumber. If	*
			*	the two match, the menu prompts the header	*
			*	information and displays the correct		*
			*	record. Else, the program displays no 		*
			*	student information.						*
			*												*
			*************************************************
			*/

			if (strcmp(StudentNumber, sStudentNumber) == 0)
			{
				/*
				*************************************************
				*												*
				*	Displaying the Student Information Header	*
				*												*
				*************************************************
				*/

				system("CLS");
				cout << "\n\n" << setw(32) << " " << "Student's Data Base, St. Louis Community College\n";
				cout << setw(47) << " " << "Student Record Retrieval\n\n\n\n\n";
				cout << setw(10) << " " << "Found the Student Record\n\n";
				cout << setw(10) << " " << "Student Number       Student Name        Degree Program              GPA\n";
				cout << setw(10) << " " << "--------------       ------------        --------------              ---\n\n\n";

				/*
				*************************************************
				*												*
				*	Displaying the sStudentNumber pointer as 	*
				*				a match was found				*
				*												*
				*************************************************
				*/

				cout << setw(10) << " " << sStudentNumber;

				/*
				*************************************************
				*												*
				*	Pushing back the information stored in the	*
				*	vector by the pChar pointer. Each vector	*
				*	contains a segment of string up to the		*
				*	delimator ",". Once the segment of the 		*
				*	string was grabbed, the program displays	*
				*	vector.										*
				*												*
				*************************************************
				*/

				vecStudentNumber.push_back(pChar);
				pChar = strtok(NULL, ",");
				cout << setw(12) << " " << pChar;

				vecStudentName.push_back(pChar);
				pChar = strtok(NULL, ",");
				cout << setw(8) << " " << " " << pChar;

				vecStudentDegree.push_back(pChar);
				pChar = strtok(NULL, ",");
				cout << setw(23) << " " << pChar << "\n\n";
				cout << setw(10) << " ";
				system("Pause");

				/*
				*************************************************
				*												*
				*	Deleting the sStudentNumber pointer			*
				*												*
				*************************************************
				*/

				delete[] sStudentNumber;

				/*
				*************************************************
				*												*
				*	Since the user's Student Number was found	*
				*	the Position boolean = true.				*
				*												*
				*************************************************
				*/

				Position = true;
			}

			else
			{
				/*
				*************************************************
				*												*
				*	Pushing back the information stored in the	*
				*	vector by the pChar pointer. Each vector	*
				*	contains a segment of string up to the		*
				*	delimator ",".								*
				*												*
				*************************************************
				*/

				vecStudentNumber.push_back(pChar);
				pChar = strtok(NULL, ",");

				vecStudentName.push_back(pChar);
				pChar = strtok(NULL, ",");

				vecStudentDegree.push_back(pChar);
				pChar = strtok(NULL, ",");

				/*
				*************************************************
				*												*
				*	Deleting the sStudentNumber pointer			*
				*												*
				*************************************************
				*/

				delete[] sStudentNumber;
			}
		}
		/*
		*************************************************
		*												*
		*	Creating an if, else statement that is run	*
		*	based upon whether the Position boolean is	*
		*	true or false. If true, the user entered	*
		*	StudentNumber was found. Else false, the	*
		*	StudentNumber was not found.				*
		*												*
		*************************************************
		*/

		if (Position)
		{
			system("CLS");
			cout << "\n\n" << setw(32) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(47) << " " << "Student Record Finder\n\n\n\n\n";
			cout << setw(15) << " " << "Student Record using " << StudentNumber << " was found\n\n";
			cout << setw(15) << " " << "This program will now end\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		else
		{
			system("CLS");
			cout << "\n\n" << setw(32) << " " << "Student's Data Base, St. Louis Community College\n";
			cout << setw(47) << " " << "Student Record Finder\n\n\n\n\n";
			cout << setw(15) << " " << "Student Record using " << StudentNumber << " was not found\n\n";
			cout << setw(15) << " " << "This program will now end\n";
			cout << setw(15) << " ";
			system("Pause");
		}
		/*
		*************************************************
		*												*
		*			Closing the text file				*
		*												*
		*************************************************
		*/

		InFile.close();
	}
}