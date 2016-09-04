#include "RC_DataStructures.h"


RC_DataStructures::RC_LinkedList_Double::RC_LinkedList_Double(int First = 0) {
	Head = *new Node(First);
	Current = Head;
	Tail = Head;
}
RC_DataStructures::RC_LinkedList_Double::~RC_LinkedList_Double() {
	ToHead();
	while (Next()) {
		Current = *Current.Next;
		delete Current.Previous;
	}
}
void RC_DataStructures::RC_LinkedList_Double::AddNode(int Val) {
	Tail.Next = new Node(Val, &Tail, 0);
	Tail = *Tail.Next;
}
void RC_DataStructures::RC_LinkedList_Double::InsertNode(int Val) {
	Current.Next = new Node(Val, Current.Next, &Current);
	Current.Next->Next->Previous = Current.Next;
}
void RC_DataStructures::RC_LinkedList_Double::RemoveNode() {
	if (!Current.Next) {
		Node *NewTail = Tail.Previous;
		delete &Tail;
		Tail = *NewTail;
		Tail.Next = 0;
	}
	if (!Current.Previous) {
		Node *NewHead = Head.Next;
		delete &Head;
		Head = *NewHead;
		Head.Previous = 0;
	}
	Current.Previous->Next = Current.Next;
	Current.Next->Previous = Current.Previous;
	Node *NewCurrent = Current.Previous;
	delete &Current;
	Current = *NewCurrent;
}
bool RC_DataStructures::RC_LinkedList_Double::Find(int Val) {
	ToHead();
	while (Next()) {
		if (Val == Current.val) {
			return true;
		}
	}
	return false;
}
int* RC_DataStructures::RC_LinkedList_Double::Next() {
	if (Current.Next) {
		Current = *Current.Next;
		return &Current.val;
	}
	return 0;
}
int* RC_DataStructures::RC_LinkedList_Double::Previous() {
	if (Current.Previous) {
		Current = *Current.Previous;
		return &Current.val;
	}
	return 0;
}

void RC_DataStructures::RC_LinkedList_Double::ToHead() {
	Current = Head;
}
void RC_DataStructures::RC_LinkedList_Double::ToTail() {
	Current = Tail;
}