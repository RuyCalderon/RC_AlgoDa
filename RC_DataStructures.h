#pragma once
#include<iostream>
#include<cassert>
#include<cmath>

namespace RC_DataStructures	{
	class RC_LinkedList_Single {
	public:
		RC_LinkedList_Single();
		~RC_LinkedList_Single();

		void AddNode(int Val);
		void InsertNode(int Val);
		int Pop();
		void ToHead();

		int* Next();
		bool Find(int Val);
	private:
		void ToTail();

		struct Node {
			int val;
			Node *Next;

			Node::Node(int Val = 0) : val(Val), Next(0) {};
			Node::~Node();
		};
		Node Head;
		Node Current;
	};

	class RC_LinkedList_Double {
	public:
		RC_LinkedList_Double();
		~RC_LinkedList_Double();

	private:
		struct Node {
			int val;
			Node *Next;
			Node *Previous;

			Node::Node(int Val = 0, Node *Previous = 0, Node *Next = 0) : val(Val), Previous(Previous), Next(Next) {};
			Node::~Node();
		};
		Node Head;
		Node Current;
	};

	class RC_Tree {

	};

	class RC_HashMap {

	};

	class RC_BinaryTree {

	};

	class RC_Set {

	};
};