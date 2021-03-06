#pragma once
#include<string>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<windows.h>

template <class DT>
class ComputerTree
{
private:
	DT * _info;
	ComputerTree<DT>* _left;
	ComputerTree<DT>* _right;
public:
	ComputerTree<DT>();
	ComputerTree<DT>(DT* computer);
	~ComputerTree<DT>();

	DT* getInfo();
	void setInfo(DT* info);
	void insert(DT* computer);
	void remove(DT* computer);
	ComputerTree<DT>* find(string name);
	ComputerTree<DT>* getLeft();
	ComputerTree<DT>* getRight();
	ComputerTree<DT>& getMax();
	ComputerTree<DT>& getMin();
	void checkStatus();
	void balance();
	int height();
	void display();
	void zig();
	void zag();
	void inOrderDisplay();
	void writeFile(ofstream& outputFile,string cmd);
	void preOrderDisplay();
	void documentTreeTraversal(ofstream& outputFile,string cmd);
	void generateReport(string cmd);
	string runCommand(string cmd);
	void displayIP();
	void traverseIP();
	void operator=(const ComputerTree<DT>& compTree);
	template<class DT>
	friend ostream& operator<<(ostream& os, const ComputerTree<DT>& comp);
};

template<class DT>
inline ComputerTree<DT>::ComputerTree()
{
	_info = nullptr;
	_left = nullptr;
	_right = nullptr;
}

template<class DT>
inline ComputerTree<DT>::ComputerTree(DT* computer)
{
	_info = computer;
	_left = nullptr;
	_right = nullptr;
}

template<class DT>
inline ComputerTree<DT>::~ComputerTree()
{
	_left = nullptr;
	delete _left;
	_right = nullptr;
	delete _right;
	_info = nullptr;
}

template<class DT>
inline DT * ComputerTree<DT>::getInfo()
{
	return _info;
}

template<class DT>
inline void ComputerTree<DT>::setInfo(DT * info)
{
	_info = info;
}

template<class DT>
inline void ComputerTree<DT>::insert(DT* computer)
{
	if (_info == nullptr)
	{
		_info = computer;
		_left = new ComputerTree<DT>();
		_right = new ComputerTree<DT>();

	}
	else if ((*computer) < (*_info))
	{
		(*_left).insert(computer);
	}
	else if ((*computer) > (*_info))
	{
		(*_right).insert(computer);
	}
	balance();

}

template<class DT>
inline void ComputerTree<DT>::remove(DT * computer)
{
	ComputerTree<DT>* temp = find(computer->getName());
	// case 2 one child
	if ((*temp)._left->_info == nullptr)
	{
		//At most one child
		if ((*temp)._right->_info != nullptr)
		{
			ComputerTree<DT> min = (*temp)._right->getMin();
			//(*temp)._info = nullptr;
			//delete (*temp)._info;
			(*temp)._info = min._info;
			(*temp)._right->remove((min)._info);
		}
		// No child
		else
		{
			delete (*temp)._left;
			delete (*temp)._right;
			(*temp)._left = nullptr;
			(*temp)._right = nullptr;
			(*temp)._info = nullptr;
			//delete (*temp)._info;
		}
	}
	else
	{
		ComputerTree<DT> max = (*temp)._left->getMax();
		//Case 3 two children
		if ((*temp)._right->_info != nullptr)
		{
			//(*temp)._info = nullptr;
			//delete (*temp)._info;
			(*temp)._info = max._info;
			(*temp)._left->remove((max)._info);
		}
		// One child
		else
		{
			//(*temp)._info = nullptr;
			//delete (*temp)._info;
			(*temp)._info = max._info;
			(*temp)._left->remove((max)._info);
		}
	}
}

template<class DT>
inline ComputerTree<DT>* ComputerTree<DT>::find(string name)
{
	if (_info->getName() == (name))
	{
		return this;
	}
	else if (_left == nullptr && _right == nullptr)
	{
		if (_info == nullptr)
		{
			cout << "NOT FOUND" << endl;
		}
		else
		{
			this;
		}
	}
	if ((*_info).getName() <= name)
	{
		return (*_right).find(name);
	}
	if ((*_info).getName() >= (name))
	{
		return (*_left).find(name);
	}
}

template<class DT>
inline ComputerTree<DT>* ComputerTree<DT>::getLeft()
{
	return (_left);
}

template<class DT>
inline ComputerTree<DT>* ComputerTree<DT>::getRight()
{
	return (_right);
}

template<class DT>
inline ComputerTree<DT>& ComputerTree<DT>::getMax()
{
	// Used in balance
	if ((*_right)._info != nullptr)
	{
		return (*_right).getMax();
	}
	else
	{
		return (*this);
	}
}

template<class DT>
inline ComputerTree<DT>& ComputerTree<DT>::getMin()
{
	// Used in balance
	if ((*_left)._info != nullptr)
	{
		return (*_left).getMin();
	}
	else
	{
		return (*this);
	}
}

template<class DT>
inline void ComputerTree<DT>::checkStatus()
{
	//In order traversal checking statuses
	if (_left != nullptr)
	{
		_left->checkStatus();
	}
	if (_info != nullptr)
	{
		_info->checkUser();
	}
	if (_right != nullptr)
	{
		_right->checkStatus();
	}
}

template<class DT>
inline void ComputerTree<DT>::balance()
{
	int balanceFactor;

	//Go down left of the tree and balance
	if (_left != nullptr)
	{
		_left->balance();
	}
	//balance this tree
	if (_info != nullptr)
	{
		balanceFactor = (*_left).height() - (*_right).height();

		if (balanceFactor < -1)
		{
			zag();
		}
		else if (balanceFactor > 1)
		{
			zig();
		}
	}
	//Balance the right trees
	if (_right != nullptr)
	{
		_right->balance();
	}


}

template<class DT>
inline int ComputerTree<DT>::height()
{
	//Intialize the hieights to 0
	int leftHeight = 0;
	int rightHeight = 0;
	if (_info != nullptr)
	{
		//Get left and right heights
		leftHeight = _left->height() + 1;
		rightHeight = _right->height() + 1;
	}
	if (leftHeight >= rightHeight)
	{
		return leftHeight;
	}
	else
	{
		return rightHeight;
	}
}

template<class DT>
inline void ComputerTree<DT>::display()
{
	cout << (*this) << endl;
}

template<class DT>
inline void ComputerTree<DT>::writeFile(ofstream& outputFile, string cmd)
{
	//Writes the computer name opening tag
	outputFile << "<" << (*_info).getName() << ">";
	outputFile << "<Output>";
	string report;
	//if the computer is unknown status then don't run the command
	if (_info->getStatus() == 2)
	{
		report = "Computer in Error State!";
	}
	else
	{
		report = _info->runCommand(cmd,false);
		int find = report.find('<');
		while (find != string::npos)
		{
			report.replace(find, 1, "&#60;");
			find = report.find('<');
		}
		find = report.find('>');
		while (find != string::npos)
		{
			report.replace(find, 1, "&#62;");
			find = report.find('>');
		}
	}
	//Write the report
	outputFile << report << endl;
	//Close all tags
	outputFile << "</Output>";
	outputFile << "</" << _info->getName() << ">";
}

template<class DT>
inline void ComputerTree<DT>::zig()
{
	//Creating the temp tree and copying the right to the right of the temp tree...
	ComputerTree<DT>* T = new ComputerTree<DT>();
	(*T)._right = _right;

	//Copying the left right leaf over to the temp tree and replacing the left right with a new pointer...
	(*T)._left = (*_left)._right;

	//Copying the info to the temp info and setting the info to the left info
	(*T).setInfo(_info);
	(*this).setInfo((*_left).getInfo());

	//Copying left left to the left..." << endl;
	_left = (*_left)._left;

	//Copying temp tree over to the right...
	_right = T;
}

template<class DT>
inline void ComputerTree<DT>::zag()
{
	//Creating the temp tree and copying the left to the left of the temp tree...
	ComputerTree<DT>* T = new ComputerTree<DT>();
	(*T)._right = (*_right)._left;

	//Copying the right left leaf over to the temp tree and replacing the right left with a new pointer... 
	(*T)._left = _left;

	//Copying the info to the temp info and setting the info to the right info
	(*T).setInfo(_info);
	(*this).setInfo((*_right).getInfo());

	//Copying left right to the right...
	_right = (*_right)._right;

	//Copying temp tree over to the left...
	_left = T;
}

template<class DT>
inline void ComputerTree<DT>::inOrderDisplay()
{
	if ((*_left)._info != nullptr)
	{
		_left->inOrderDisplay();
		cout << endl;
	}
	if (_info != nullptr)
	{
		_info->display();
		cout << endl;
	}
	if ((*_right)._info != nullptr)
	{
		_right->inOrderDisplay();
		cout << endl;
	}
}

template<class DT>
inline void ComputerTree<DT>::preOrderDisplay()
{
	if (_left != nullptr)
	{
		_left->preOrderDisplay();
		cout << endl;
	}
	if (_info != nullptr)
	{
		_info->display();
		cout << endl;
	}
	if (_right != nullptr)
	{
		_right->preOrderDisplay();
		cout << endl;
	}
}

template<class DT>
inline void ComputerTree<DT>::documentTreeTraversal(ofstream& outputFile, string cmd)
{
	if ((*_left)._info != nullptr)
	{
		_left->documentTreeTraversal(outputFile,cmd);
	}
	if (_info != nullptr)
	{
		writeFile(outputFile,cmd);
	}
	if ((*_right)._info != nullptr)
	{
		_right->documentTreeTraversal(outputFile,cmd);
	}
}

template<class DT>
inline void ComputerTree<DT>::generateReport(string cmd)
{
	//Set the output file to write to the desktop
	string userProfile = "echo %userprofile%";
	string outputFileName = "";
	char buffer[128];
	//Runs a command to get the users directory
	FILE* f = _popen(userProfile.c_str(), "r");
	while (!feof(f))
	{
		if (fgets(buffer, 128, f) != NULL)
		{
			outputFileName += buffer;
		}
	}
	int endLine = outputFileName.find_last_of('\n');
	outputFileName = outputFileName.substr(0, endLine);
	//Appends the desktop portion to the user profile
	outputFileName += "\\Desktop\\RDTool Report.xml";


	//Create the file output object
	ofstream outputFile(outputFileName);

	if (outputFile.is_open())
	{
		//Starts the xml
		outputFile << "<?xml version=\"1.0\"?><Command>";
		//Traveres the tree passing the file and 
		documentTreeTraversal(outputFile, cmd);
		outputFile << "</Command>";
		outputFile.close();
	}
	else
	{
		cout << "File not accessible" << endl;
	}


}

template<class DT>
inline string ComputerTree<DT>::runCommand(string cmd)
{
	if ((*_left)._info != nullptr)
	{
		_left->runCommand(cmd);
	}
	if (_info != nullptr)
	{
		//_info->write();
	}
	if ((*_right)._info != nullptr)
	{
		_right->traverseIP();
		cout << endl;
	}
	return "duh";
}

template<class DT>
inline void ComputerTree<DT>::traverseIP()
{
	if ((*_left)._info != nullptr)
	{
		_left->traverseIP();
		cout << endl;
	}
	if (_info != nullptr)
	{
		//_info->displayIP();
		displayIP();
		cout << endl;
	}
	if ((*_right)._info != nullptr)
	{
		_right->traverseIP();
		cout << endl;
	}
}

template<class DT>
inline void ComputerTree<DT>::displayIP()
{
	string ip;

	string cmd = "wmic /node:\"" + (*_info).getName() + "\" nicconfig get IPAddress";

	string rawResult = runCommand(cmd);

	ip = rawResult.substr(rawResult.find('{') + 2, 14);

	cout << (*_info).getName() << "'s IP Address: " << ip << endl;
}

template<class DT>
inline void ComputerTree<DT>::operator=(const ComputerTree<DT>& compTree)
{
	DT* temp = compTree._info;
	_info = new DT(*temp);

	_left = compTree._left;
	_right = compTree._right;
}

template<class DT>
inline ostream & operator<<(ostream & os, const ComputerTree<DT>& comp)
{
	os << (*comp._info);

	return os;
}