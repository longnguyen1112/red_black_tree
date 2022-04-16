#pragma once
#include "Node.h"
#include <windows.H>
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <fstream>

class RBTree
{
private:
	bool ChildRed, ParentRed;
	Node* Root;
	void AddRec(Node*&,int);
	void SwapColorCase1(Node*);
	void SwapColorCase3(Node*);
	void LeftRotate(Node* &temp);
	void RightRotate(Node* &temp);
	void ClearRec(Node*);
	void PrintRec(Node*);
	void RecDraw(Node*, int, int, int, int);
public:
	RBTree();
	void AddNode(int);
	void Clear();
	void Print();
	void Draw();
	void goTo(int,int,Node*);
	bool Search(int);
	void Load();
};

RBTree::RBTree()
{
	Root = NULL;
	ChildRed = false;
	ParentRed = false;
}

void RBTree::AddNode(int data)
{
	ChildRed = false;
	ParentRed = false;
	AddRec(*&Root, data);
	Root->color = "b";
}

void RBTree::AddRec(Node*& Trav, int data)
{
	if (!Trav)
	{
		Trav = new Node;
		Trav->value = data;
		Trav->color = "r";
		ChildRed = true;
	}
	else
	{
		if (data < Trav->value) //left
		{
			AddRec(Trav->l, data);
			if (ParentRed == true)
			{
				if (Trav->r && Trav->r->color == "r")
				{
					SwapColorCase1(Trav);
					ChildRed = true;
					ParentRed = false;
				}
				else
				{
					if (Trav->l->r && Trav->l->r->color == "r")
					{
						LeftRotate(Trav->l);
					}
					RightRotate(Trav);
					SwapColorCase3(Trav);
					ChildRed = false;
					ParentRed = false;
				}
			}
			else if (Trav->color == "r" && ChildRed == true)
			{
				ParentRed = true;
			}
			else if (Trav->color == "b")
			{
				ChildRed = false;
			}
		}
		else if (data > Trav->value)
		{
			AddRec(Trav->r, data);
			if (ParentRed == true)
			{
				if (Trav->l && Trav->l->color == "r")
				{
					SwapColorCase1(Trav);
					ChildRed = true;
					ParentRed = false;
				}
				else
				{
					if (Trav->r->l && Trav->r->l->color == "r")
					{
						RightRotate(Trav->r);
					}
					LeftRotate(Trav);
					SwapColorCase3(Trav);
					ChildRed = false;
					ParentRed = false;
				}
			}
			else if (Trav->color == "r" && ChildRed == true)
			{
				ParentRed = true;
			}
			else if (Trav->color == "b")
			{
				ChildRed = false;
			}
		}
	}
}

void RBTree::SwapColorCase1(Node* Trav)
{
	Trav->l->color = "b";
	Trav->r->color = "b";
	Trav->color = "r";
}

void RBTree::SwapColorCase3(Node* Trav)
{
	if (Trav->r->color != Trav->color)
	{
		Trav->r->color = "r";
		Trav->color = "b";
	}
	else if (Trav->l->color != Trav->color)
	{
		Trav->l->color = "r";
		Trav->color = "b";
	}
}

void RBTree::LeftRotate(Node* &temp)
{
	Node* temp2 = temp->r->l;
	temp->r->l = temp;
	temp = temp->r;
	temp->l->r = temp2;
}

void RBTree::RightRotate(Node * &temp)
{
	Node* temp2 = temp->l->r;
	temp->l->r = temp;
	temp = temp->l;
	temp->r->l = temp2;
}

void RBTree :: Clear()
{
	if (!Root)
	{
		std::cout << "There is nothinig in the tree! " << std::endl;
		system("pause");
	}
	else
	{
		ClearRec(Root);
		Root = NULL;
	}
	
	std::cout << "Done clearing tree! " << std::endl;
}

void RBTree::ClearRec(Node* Trav)
{
	if (Trav->l)
	{
		ClearRec(Trav->l);
	}
	if (Trav->r)
	{
		ClearRec(Trav->r);
	}

	delete Trav;
	Trav = NULL;
}

void RBTree::Print()
{
	if (Root)
	{
		std::cout << "The tree is: ";
		PrintRec(Root);
	}
	else {
		std::cout << "There is nothing in the tree." << std::endl;
	}

	system("pause");
}

void RBTree::PrintRec(Node* Trav)
{
	if (Trav->l)
		PrintRec(Trav->l);

	std::cout << Trav->value << " ";

	if (Trav->r)
		PrintRec(Trav->r);
}

void RBTree::Draw()
{
	RecDraw(Root, 0, 39, 79, 0);
	goTo(0, 20,Root);
}

void RBTree::RecDraw(Node* Trav, int LeftEdge, int x, int RightEdge, int y)
{
	if (Trav)
	{
		goTo(x, y,Trav);
		std::cout << Trav->value;
		goTo(x, y + 1, Trav);

		int LeftX = (LeftEdge + x) / 2;
		int RightX = (x + RightEdge) / 2;

		RecDraw(Trav->l, LeftEdge, LeftX, x, y + 2);
		RecDraw(Trav->r, x, RightX, RightEdge, y + 2);
	}
}

void RBTree::goTo(int x, int y, Node* Trav)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	pos.X = x; //Column
	pos.Y = y; //Row
	SetConsoleCursorPosition(hConsole, pos);
	if (Trav->color == "r")
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	}
}

bool RBTree::Search(int searchVal)
{
	Node* Temp = Root;

	while (Temp)
	{
		if (Temp->value == searchVal)
		{
			return true;
		}

		if (searchVal > Temp->value)
		{
			Temp = Temp->r;
		}
		else {
			Temp = Temp->l;
		}
	}

	return false;
}

void RBTree::Load()
{
	
}