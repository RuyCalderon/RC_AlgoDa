#include "RC_DataStructures.h"

using namespace RC_DataStructures;

RC_LinkedList_Single::RC_LinkedList_Single(int First = 0) {
	Head = *new Node(First);
	Current = Head;
}
RC_LinkedList_Single::~RC_LinkedList_Single() {
	Current = Head;
	while (Current.Next) {
		Node *NextToDelete = Current.Next;
		delete &Current;
		Current = *NextToDelete;
	}
	delete &Current;
}
void RC_LinkedList_Single::AddNode(int Val = 0) {
	ToTail();
	Current.Next = new Node(Val);
	Current = *Current.Next;
}
void RC_LinkedList_Single::InsertNode(int Val = 0) {
	Node *OldNext = Current.Next;
	Current.Next = new Node(Val);

	Current = *Current.Next;
	Current.Next = OldNext;
}
void RC_LinkedList_Single::ToHead() {
	Current = Head;
}
void  RC_LinkedList_Single::ToTail() {
	Node *This=&Current;
	while (This->Next) {
		This = This->Next;
	}
	Current = *This;
}
int RC_LinkedList_Single::Pop() {
	Node *LastCurrent;
	while (Current.Next) {
		LastCurrent = &Current;
		Current = *Current.Next;
	}

	LastCurrent->Next = 0;
	int val = Current.val;
	delete &Current;
	Current = *LastCurrent;
	return val;
}
int* RC_LinkedList_Single::Next() {
	if (Current.Next) {
		Current = *Current.Next;
		return &Current.val;
	}
	return 0;
}
bool RC_LinkedList_Single::Find(int Val) {
	Current = Head;
	int *CheckVal;
	while (CheckVal = Next()) {
		if (*CheckVal == Val) {
			return true;
		}
	}
	return false;
}