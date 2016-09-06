#include "RC_DataStructures.h"

using namespace RC_DataStructures;
//static functions
RC_Set* RC_Set::Union(RC_Set *A, RC_Set *B) {}
RC_Set* RC_Set::Intersection(RC_Set *A, RC_Set *B) {}
bool RC_Set::IsEquivalent(RC_Set *A, RC_Set *B) {}
RC_Set* RC_Set::NullSet() {}

//member functions
RC_Set::RC_Set() {}
RC_Set::~RC_Set() {}
RC_Set* RC_Set::Subset(int start, int end) {}
RC_Set* RC_Set::Difference(RC_Set *B) {}
bool RC_Set::isSubset(RC_Set *B) {}
bool RC_Set::ContainsElement(int Value) {}
int RC_Set::Cardinality() {
	return numElements;
}