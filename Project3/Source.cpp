#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

const char* cyan = "\033[0;36m";
const char* green = "\033[0;32m";
const char* blue = "\033[0;34m";
const char* white = "\033[0;37m";
const char* black = "\033[0;30m";
const char* yellow = "\033[0;33m";
const char* purple = "\033[;35m";
const char* red = "\033[0;31m";

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

void CreateAFile(string filename, string myString) {
	ofstream file;
	file.open(filename);
	file << myString;
	file.close();
}

bool isValidNumber(string myNum) {
	int n = myNum.length();
	for (int i = 0; i < n; ++i) {
		if (isdigit(myNum[i]) == 0) return false;
	}
	return true;
}

/*
*Function to return the line count of the .dat file
*/
int LinesInFile() {
	string line;
	ifstream file("U:/Project3/Release/frequency.dat");
	int count = 0;
	while (getline(file, line)) {
		count++;
	}
	count = count + count;
	file.close();
	return count;
}

/*
*Funtion to read .dat file and print formatted graph based on item and frequency counts
*/
void PrintItemFrequencyGraph() {

	ifstream file("U:/Project3/Release/frequency.dat");
	string item;
	vector<string> temp;

	int count = LinesInFile();

	for (int i = 0; i < count; ++i) {
	
		file >> item;
		
		temp.push_back(item);
		
		if (!isValidNumber(item)) 
		{
			cout << red << setw(12)<< left << item;
		}
		else if (isValidNumber(item)) 
		{
			int num = stoi(item);
			for (int x = 0; x < num; ++x) {
				cout << yellow << "*";
			}
			cout << endl;
		}
		
	}
	file.close();
};


/* Function to print the selection menu */
void PrintSelections() {
	
	cout << purple <<"******GROCERY TRACKING PROGRAM******" << endl;
	cout << endl;
	cout << cyan << "1. Display the products purchased and their frequency" << endl;
	cout << "2. Display the frequency of a specific product" << endl;
	cout << "3. Display graph of items and the frequency of purchase" << endl;
	cout << "4. Exit" << endl;
	cout << endl;
	cout << white << "Enter your number as 1, 2, 3, or 4" << endl;
}


int main()
{
	// vairable declaration 
	boolean letsGo = true;
	string mySelection;

	//check to make sure the program has not been exited 
	while (letsGo == true) {

		//print menu

		PrintSelections();

		//get user input
		cin >> mySelection;

		//make sure user input valid selection
		//if not, have user re-enter selection
		while ((mySelection != "1") && (mySelection != "2") && (mySelection != "3") && (mySelection != "4")) {
			cout << "Please enter a valid selection as 1, 2, 3, or 4" << endl;
			cin >> mySelection;
		}

		//use appropriate function based on selection 
		if (mySelection == "1") {
			cout << endl;
			//system("Color D0");
			cout << purple <<"******LIST OF ALL ITEMS******" << cyan << endl;
			cout << endl;

			CallProcedure("PrintAllItemCounts");
			cout << endl;
			cout << endl;
			
		}
		else if (mySelection == "2") {
			string myItem;
			cout << purple << "******LIST SPECIFIC ITEM******" << cyan << endl;
			cout << endl;

			//get item from user to search data
			cout << white << "What item are you looking for?" << cyan << endl;
			cin >> myItem;

			cout << endl;
			int res = callIntFunc("PrintSingleItemCount", myItem);
			cout << endl;
			cout << endl;
			
		}
		else if (mySelection == "3") {
			cout << endl;
			cout << endl;
			cout << "******GRAPH OF ALL ITEMS******" << endl;
			cout << endl;
			PrintItemFrequencyGraph();
			cout << endl;
			cout << endl;

		}
		else if (mySelection == "4") {
			cout << endl;
			cout << endl;
			cout << "****** EXIT ******" << endl;
			letsGo = false;
		}
	}

}
