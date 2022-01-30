#include <iostream>
#include <vector>

template <typename T>
class TreeNode {
private:
	T value;		//Wartosc przechowywana w elemencie kolejki
	TreeNode<T> * parent;	//Wskaznik na kolejny element kolejki
	std::vector<TreeNode*> child;
public:
	//Konstruktor 
	TreeNode(const T & a, TreeNode * ptr = 0)
	{
		value = a;
		parent = ptr;
	}
		
	//Destruktor
	~TreeNode()
	{
		for (int k = 0; k < child.size(); k++)
		delete child[k];
	}

	//Metoda zwracajaca wartosc przechowywana w elemencie
	T getValue() const
	{
		return value;
	}
	
	//Metoda zwracajaca wartosc wskaznik na kolejny element kolejki
	TreeNode * getParent() const
	{
		return parent;
	}
	
	//Metoda zwracajaca wartosc wskaznik na kolejny element kolejki
	TreeNode * getChild(int i) const
	{
		return child[i];
	}
	
	//Metoda zwracajaca wartosc wskaznik na kolejny element kolejki
	std::vector<TreeNode*> getChild() const
	{
		return child;
	}
	
	//Metoda zmieniajaca wartosc wskaznika na kolejny element kolejki
	void setParent(TreeNode * ptr)
	{
		parent = ptr;
	}
	
	//Metoda zmieniajaca wartosc wskaznika na kolejny element kolejki
	void addChild(T a)
	{
		TreeNode<T> * childNew = new TreeNode<T>(a);
		childNew->setParent(this);
		child.push_back(childNew);
	}
	
	//Metoda zmieniajaca wartosc wskaznika na kolejny element kolejki
	void removeChild(int i)
	{
		child.erase(child.begin()+i);
	}
	
	//Metoda zmieniajaca wartosc elementu
	void setValue(T a)
	{
		value = a;
	}
	
	bool isRoot()
	{
		return parent==0;
	}
	
	bool isExternal()
	{
		return child.empty();
	}
};


