#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "TreeNode.h"

template <typename T>
class Tree {
private:
	TreeNode<T> * root; //Wskaznik na pierwszy element kolejki
public:
	//Konstruktor pustej kolejki
	Tree()
	{
		root = 0;
	}	
	//Destruktor
	~Tree()
	{
		//while(!isEmpty()) remove(0);
		delete root;
	}
	
	TreeNode<T> * getRoot() const
	{
		return root;
	}

	void setRoot(TreeNode<T> * ptr) 
	{
		root = ptr;
	}

	void setRoot(TreeNode<T> a) 
	{
		root = new TreeNode<T>(a);
	}


	bool isEmpty() const
	{
		return root == 0;
	}
	/*
	int depth(TreeNode<T> * ptr)
	{
		if (ptr->isRoot()) return 0;
		return 1+depth(ptr->getParent());
	}*/
	
	/*int height(TreeNode<T> * ptr)
	{
		if (ptr->isExternal()) return 0;

		int h = 0;
		for (int k = 0; k < ptr->getChild().size(); k++){
			h = max(h, height(ptr->getChild(k)));
		}
		return h+1;
	}*/
	//Wyczyszczenie calego drzeaw
	bool clear(){
		if (root == 0) return false;
		
		delete root;
		root = 0;
		return true;
	}
	
	//Przejscie po calej liscie i zliczenie wszystkich elementow
	/*int size() const
	{
		int size = 0;
		ListElement * ptr = front;	
		while(ptr != 0)			
		{
			size++;
			ptr = ptr->getNext();
		} 
		return size;
	}*/
	
	/*ListElement * atIndex(int p) const
	{
		if (p < 0) throw WrongIndexListException(); //wartosc p nienalezaca do listy
		
		ListElement * ptr = front;	
		for (int i = 0; i < p; i++) 			
		{
			ptr = ptr->getNext();
			if (ptr == 0) throw WrongIndexListException(); //wartosc p nienalezaca do listy
		} 
		return ptr;
	}*/
	
	//ListElement * operator [] (int p) const {return atIndex(p);}
	
	/*int indexOf(const ListElement & element) const
	{
		ListElement * ptr = front;	
		int i = 0;
		while (ptr != &element)			
		{
			ptr = ptr->getNext();
			if (ptr == 0) throw ElementNotFoundListException(); //nieznalezienie elementu w liscie
		} 
		return i;
	}*/
	
	/*void addFirst(Record a)
	{
		ListElement * newElement = new ListElement(a, front, 0);	//Tworzenie nowego elementu kolejki
		if (isEmpty()) back = newElement;
		else front->setPrev(newElement);
		front = newElement; 									//Zmiania wskaznika "front", aby wskazywal nowo utworzony pierwszy element
	}
	
	void addAfter(int p, Record a)
	{
		ListElement * ptr = atIndex(p);	
		ListElement * newElement = new ListElement(a, ptr->getNext(), ptr); 	//Tworzenie nowego elementu
		if (ptr->getNext() != 0) ptr->getNext()->setPrev(newElement);
		else back = newElement;
		ptr->setNext(newElement);
	}
	
	void addBefore(int p, Record a)
	{
		ListElement * ptr = atIndex(p);				
		ListElement * newElement = new ListElement(a, ptr, ptr->getPrev()); 	//Tworzenie nowego elementu
		if (ptr->getPrev() != 0) ptr->getPrev()->setNext(newElement);
		else front = newElement;
		ptr->setPrev(newElement);
	}
	
	void addLast(Record a)
	{
		if (isEmpty())
		{
			addFirst(a);
		}
		else
		{			
			ListElement * newElement = new ListElement(a, 0, back); 	//Tworzenie nowego elementu
			back->setNext(newElement);  				//Zmiania wskaznika "next" ostatniego elementu na nowo utworzony element
			back = newElement;
		}								
	}
	
	Record remove(int p)
	{
		Record popValue;
		if (isEmpty()) throw EmptyListException(); 	//Wyjatek pustej kolejki
		
		ListElement * element = atIndex(p);
		popValue = element->getValue();
		if (element->getPrev() == 0) front = element->getNext();
		else element->getPrev()->setNext(element->getNext());
		if (element->getNext() == 0) back = element->getPrev();
		else element->getNext()->setPrev(element->getPrev());
		
		//element->setNext(0);
		delete element;
		
		return popValue;
	}
	
	Record remove(ListElement * element)
	{
		Record popValue;
		if (isEmpty()) throw EmptyListException(); 	//Wyj±tek pustej kolejki
		
		popValue = element->getValue();
		if (element->getPrev() == 0) front = element->getNext();
		else element->getPrev()->setNext(element->getNext());
		if (element->getNext() == 0) back = element->getPrev();
		else element->getNext()->setPrev(element->getPrev());
	
		//element->setNext(0);
		delete element;
		
		return popValue;
	}*/
};



#endif

