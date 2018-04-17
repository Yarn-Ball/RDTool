#pragma once
#include<string>

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
	DT* find(DT* computer);
	ComputerTree<DT>& getLeft();
	ComputerTree<DT>& getRight();
	void balance();
	int height();
	void display();
	void zig();
	void zag();
	void inOderDisplay();
	void preOrderDisplay();
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
	delete _info;
	delete _left;
	delete _right;
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
		
	}else if ((*computer) < (*_info))
	{
		(*_left).insert(computer);
	}else if ((*computer) > (*_info))
	{
		(*_right).insert(computer);
		
	}
	return;

}

template<class DT>
inline DT* ComputerTree<DT>::find(DT * computer)
{
	if ((*_info) == (*computer))
	{
	return _info;
	}
	else if (_left == nullptr &&_right == nullptr)
	{
		return _info;
	}
	if ((*_info) <= (*computer))
	{
	return (*_left).find(computer);
	}
	if ((*_info) >= (*computer))
	{
	return (*_left).find(computer);
	}
	
}

template<class DT>
inline ComputerTree<DT>& ComputerTree<DT>::getLeft()
{
	return (*_left);
}

template<class DT>
inline ComputerTree<DT>& ComputerTree<DT>::getRight()
{
	return (*_right);
}

template<class DT>
inline int ComputerTree<DT>::height()
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (_info != nullptr)
	{
		leftHeight = _left->height() + 1;
	}
	if (_info != nullptr)
	{
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
inline void ComputerTree<DT>::zig()
{
	//Creating the temp tree and copying the right to the right of the temp tree...
	ComputerTree<DT>* T = new ComputerTree<DT>();
	(*T)._right = _right;
	//_right = new ComputerTree<DT>();
	
	//Copying the left right leaf over to the temp tree and replacing the left right with a new pointer...
	(*T)._left = (*_left)._right;
	//(*_left)._right = new ComputerTree<DT>();

	//Copying the info to the temp info and setting the info to the left info
	(*T).setInfo(_info);
	(*this).setInfo((*_left).getInfo());

	//Copying left left to the left..." << endl;
	_left = (*_left)._left;

	//Copying temp tree over to the right...
	_right =  T;
}

template<class DT>
inline void ComputerTree<DT>::zag()
{
	//Creating the temp tree and copying the left to the left of the temp tree...
	ComputerTree<DT>* T = new ComputerTree<DT>();
	(*T)._right = (*_right).left;

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
inline void ComputerTree<DT>::inOderDisplay()
{
	if (_left != nullptr)
	{
		_left->display();
		cout << endl;
	}
	if (_info != nullptr)
	{
		_info->display();
		cout << endl;
	}
	if (_right != nullptr)
	{
		_right->display();
		cout << endl;
	}
}

template<class DT>
inline void ComputerTree<DT>::preOrderDisplay()
{
	if (_info != nullptr)
	{
		_info->display();
		cout << endl;
	}
	if (_left != nullptr)
	{
		_left->display();
		cout << endl;
	}
	if (_right != nullptr)
	{
		_right->display();
		cout << endl;
	}
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
