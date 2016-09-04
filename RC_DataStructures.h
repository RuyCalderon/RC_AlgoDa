#pragma once
#include<iostream>
#include<cassert>
#include<cmath>

namespace RC_DataStructures	{
	class RC_LinkedList_Single {
	public:
		RC_LinkedList_Single(int First);
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
		RC_LinkedList_Double(int First);
		~RC_LinkedList_Double();
		void AddNode(int Val);
		void InsertNode(int Val);
		void RemoveNode();
		bool Find(int Val);
		int* Next();
		int* Previous();

		void ToHead();
		void ToTail();
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
		Node Tail;
	};
	class RC_Set {
	public:
		static RC_Set Union(RC_Set A, RC_Set B);
		static RC_Set Intersection(RC_Set A, RC_Set B);
		static RC_Set IsEquivalent(RC_Set A, RC_Set B);
		static RC_Set NullSet();

		RC_Set(int Elements[]);
		RC_Set(int *Elements, int ElementCount);
		~RC_Set();
		RC_Set Subset();
		RC_Set Difference(RC_Set B);
		int Cardinality();
		
		bool isElement(int Value);
	private:
		RC_Set();
		struct Container {
			int Value;
		};
		Container *Elements;
		int numElements;
	};
	class RC_Tree {

	};
	class RC_BinaryTree {

	};
	class RC_HashMap {

	};
};