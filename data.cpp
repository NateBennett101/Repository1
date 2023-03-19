#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*

Description:

When this function is called, it should produce a menu to prompt user input that should take user input between 1 to 4, the input should then execute the appropriate Python function
A user input of 1 should output a list of unique words and their number of appearances, input of 2 should search for the number of a single item's appearances
An input of 3 should print a histogram of each item's appearances,
An input of 4 should quit the program

*/

void OutputMenu() {

	// This should declare method-specific variables
	int loopMenu = 0;
	int wordNumber = 0;
	int itemNumber = 0;
	string searchTerm;
	string itemName;
	string differentColor = "\034[32;1m";
	string defaultColor = "\033[0m";
	// This should open ifstream for file
	ifstream fileInput; 

	while (loopMenu != 4) {
		// This should prompt the user for input
		std::cout << "[1] Calculate the number of times each item appears" << std::endl;
		std::cout << "[2] Calculate the frequency of a specific item" << std::endl;
		std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;
		std::cout << "[4] Quit" << std::endl;
		std::cin >> loopMenu;
		//This should check if user input is valid
		while (std::cin.fail()) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input a valid selection: ";
			std::cin >> loopMenu;

		}
		// This switch statement should output the proper command for user input
		switch (loopMenu) {
		//Case 1 should Calculate the number of times each item appears, then print a list
		case 1:

			system("CLS");
			CallProcedure("CountAll");
			std::cout << std::endl;
			break;
		//Case 2 should calculate the number of times a specific item appears, then print the result
		case 2:

			system("CLS");
			std::cout << "What item would you like to search for?" << std::endl;
			std::cin >> searchTerm;
			wordNumber = callIntFunc("CountInstances", searchTerm);
			std::cout << std::endl << searchTerm << " : " << wordNumber << std::endl << std::endl;
			break;
		//Case 3 should print a histogram based on how many times each item appears. Like case 1, but with stars
		case 3:

			system("CLS");
			CallProcedure("CollectData");
			fileInput.open("frequency.dat");
			fileInput >> itemName;
			fileInput >> itemNumber;
			//This should print a histogram for each line in the file and after every line has been parsed, break
			while (!fileInput.fail()) {

				std::cout << defaultColor;
				std::cout << std::setw(14) << std::left << itemName << std::setw(6);

				std::cout << differentColor;

				for (int i = 0; i < itemNumber; i++) {

					std::cout << std::right << "*";

				}

				std::cout << std::endl;
				fileInput >> itemName;
				fileInput >> itemNumber;

			}

			fileInput.close();
			std::cout << defaultColor << endl;
			break;

			//Case 4 should quit the program

		case 4:

			return;

			//This should be the default case, and output something about the input being invalid

		default:

			std::cout << "Input a valid selection";
			std::cout << std::endl;
			break;

		}

	}

}

//The Main method should call the OutputMenu method and gather input

void main(){

	OutputMenu();

}
