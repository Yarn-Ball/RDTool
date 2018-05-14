#pragma once
#include"Computer.h"
#include"ComputerTree.h"
#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <windows.h>
#include"MainWindow.h"
using namespace std;
using namespace System;
using namespace System::Windows::Forms;

string exec(const char* cmd) 
{
	char buffer[128];
	string result = "";

	//pid_t processKiller = fork();

	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw runtime_error("_popen() failed!");
	try
	{
		while (!feof(pipe))
		{
			if (fgets(buffer, 128, pipe) != NULL)
			{
				result += buffer;
			}
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

string command(const char* cmd)
{
	BOOL bSuccess;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	string result;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	bSuccess = CreateProcess(NULL,
		(LPWSTR) cmd,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);
	
	WaitForSingleObject(pi.hProcess, 1000);

	//Sleep(1000);

	if (bSuccess == false)
	{
		result = exec(cmd);
	}
	else
	{
		result = "computer in error";
	}

	CloseHandle(pi.hProcess); 
	CloseHandle(pi.hThread);

	return result;
}

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	//TODO: Replace this with the actual data structure
	ComputerTree<Computer> *testerino = new ComputerTree<Computer>();
	char* header = new char[250];				//Will hold the header
	string computerInfo;						//Will hold each line of the file
	string inputFileName;						//Will hold the name of the file
	char* computerName = new char[100];			//Holds the Comp name as a cstring
	char* computerIP = new char[100];			//^^ IP
	char* computerMac = new char[100];			//^^ Mac
	int numberOfInfo = 0;						//Keeps track of which information is being read
	int letterIndex = 0;						//Keeps track of where the cin is on computerInfo
	int writeIndex = 0;							//Keeps track of where to write. Resetes after after each coloumn
	bool isDone = false;						//isDone reading the computerLine reset on every line
	string* name = nullptr;
	string* ip = nullptr;
	string* mac = nullptr;


	//TODO: Uncomment this when using on the actual thing
	//cin.getline(header, 250);

	//Set the name for the input file name
	inputFileName = "SP18 Computer List.csv";

	//Create input file object
	fstream inputFile(inputFileName);

	std::getline(inputFile, computerInfo);

	//Open the file and pull information
	if (inputFile.is_open())
	{

		// Read while its not the end of the file
		while (!inputFile.eof())
		{

			//cin.getline(computerInfo, 55);
			std::getline(inputFile, computerInfo);

			/* This part of the program will take the line aquired from the CSV file (computer info)
			* and split it accordingly to extract the comptuer name, ip address, and mac. */

			//To extract the computer name we start create a substring starting at index 0 an going all the way to the first comma
			string computerName = computerInfo.substr(0, computerInfo.find(",", 0));

			cout << "Loading computer: " << computerName << "..." << endl;

			//To extract the ip address we start in the fist comma and add one to move the index off the comma
			//then the length of the substring will be dictated by the length of charactares in-between the first and second comma
			string ipAddress = computerInfo.substr(computerInfo.find(",", 0) + 1, computerInfo.find(",", 17) - (computerInfo.find(",", 0) + 1));

			//Finally, the mac address will start at the index after the second comma, and will be of length 17
			string macAddress = computerInfo.substr(computerInfo.find(",", 17) + 1, 17);

			size_t found = computerInfo.find_last_of(',');
			string college = computerInfo.substr(found + 1, computerInfo.length());

			//Here we create the computer objects and parse the information for the constructor
			//Once the objec is in place, we add it to the tree
			Computer* temp = new Computer((computerName), (ipAddress), (macAddress), (college));
			testerino->insert(temp);
			inputFile.peek();
			
		}
	}
	else
	{
		std::cout << "File is not available" << endl;
	}

	//Displays tree
	cout << "************************************************************" << endl;

	/*
	//testerino->inOrderDisplay();

	testerino->generateReport();
	cout << endl;
	cout << "Report has been generated" << endl;

	//This will let you see whats going on
	system("PAUSE");
	//RDToolGUI::MainWindow form(testerino);
	//Application::Run(%form);

	string computerName = "lab-sec360-03";
	
	string cmd = "wmic /node:\""; 
	cmd = cmd + computerName;
	cmd = cmd + "\" nicconfig get IPAddress";
	*/

	string compName = "lab-sec360-01";

	string cmd = "wmic /node:\"" + compName + "\" nicconfig get IPAddress";


	string rawResult = command(cmd.c_str());

	cout << "rawResult: " <<  rawResult << endl;

	string result;

	result = rawResult.substr(rawResult.find('{') + 2, 14);

	cout << "Result: " <<  result << endl;

	//Name the output file
	string outputFileName = "RDTool Report.csv";

	//Create the file output object
	ofstream outputFile(outputFileName);

	if (outputFile.is_open())
	{
		outputFile << result << endl;

		outputFile.close();
	}
	else
	{
		cout << "File not accessible" << endl;
	}


	system("PAUSE");

	

	
	return 0;
}