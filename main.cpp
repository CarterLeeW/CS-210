// Carter Wooton CS 210 April 17, 2022
#include <Python.h>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void CallProcedure(string pName);
int callStringFunc(string proc, string param);
void ItemFrequencyCall();
void DisplayMenu();

// Option 2
void ItemFrequencyCall() {
	string itemName;
	cout << endl;
	cout << "Enter the name of the item:" << endl;
	cin.ignore();
	getline(cin, itemName);
	cout << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "There were " << callStringFunc("item_frequency", itemName) << " \"" << itemName << "\" purchased today" << endl;
}

// Option 3
void ItemGraphicCall() {
	ifstream groceryListFS;
	int amount = 0;
	string item = "None";
	// Creates frequency.dat file
	CallProcedure("item_graphic");

	groceryListFS.open("frequency.dat");
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;
	cout << "Graphical representation of items sold today" << endl;
	while (!groceryListFS.eof()) {
		groceryListFS >> item;
		groceryListFS >> amount;
		// Ignores empty line at the end of the file
		if (groceryListFS.fail()) {
			break;
		}
		cout << setfill('\'') << left << setw(15) << item << setfill('*') << setw(amount) << "" << endl;
		groceryListFS.clear();
	}
	groceryListFS.close();
}

void DisplayMenu() {
	SetConsoleTextAttribute(hConsole, 11);
	cout << endl;
	cout << "1: List of items purchased with quantities" << endl;
	cout << "2: Number of times a specific item was purchased" << endl;
	cout << "3: Graphical representation of items purchased" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4" << endl;
}

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("Grocer");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callStringFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"Grocer");
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

int main()
{
	int userInput;

	do {
		try {
			DisplayMenu();
			cin >> userInput;

			// Processes user's menu selection
			switch (userInput) {
				// Displays multiplication table
			case 1:
				SetConsoleTextAttribute(hConsole, 15);
				CallProcedure("items_list");
				break;
			case 2:
				ItemFrequencyCall();
				break;
			case 3:
				ItemGraphicCall();
				break;
			case 4:
				cout << "Exiting program" << endl;
				break;
				// Invalid input
			default:
				cin.clear();
				cin.ignore(256, '\n');
				throw runtime_error("Invalid input.");
			}
		}
		// Handles invalid input from all cpp functions
		catch (runtime_error excpt) {
			SetConsoleTextAttribute(hConsole, 12);
			cout << excpt.what() << endl;
			cout << "Returning to menu." << endl;
		}
	} while (userInput != 4);
	return 0;
}