#include "RC_DataStructures.h"

using namespace RC_DataStructures;

RC_Set RC_Set::Union(RC_Set A, RC_Set B) {

}
RC_Set RC_Set::Intersection(RC_Set A, RC_Set B) {
}
bool RC_Set::IsEquivalent(RC_Set A, RC_Set B) {
}
RC_Set RC_Set::NullSet() {
}

RC_Set::RC_Set() {}
//TODO(Ruy): next two constructors are duplicates
RC_Set::RC_Set(int *InputData, int SetSize) {
	int *NewSetStorageLocation = 0;
	if (!GlobalSet) {
		//reserve size is always greater than 8192 elements or between 2 and 4 times the initial set size
		GlobalMemReserveSize = (SetSize < 4096) ? 8192 : 2 << ((int)log2(SetSize) + 1);
		GlobalSet = RC_RESERVE_MEM(int, GlobalMemReserveSize);
		NewSetStorageLocation = RC_COMMIT_MEM(int, SetSize, GlobalSet);
		numGlobalElements = SetSize;
	}
	else if(SetSize + numGlobalElements < GlobalMemReserveSize){
		NewSetStorageLocation = RC_COMMIT_MEM(int, SetSize, GlobalSet+numGlobalElements);
		numGlobalElements += SetSize;
	}
	else {
		//deal with this later
	}
	assert(NewSetStorageLocation);



}
RC_Set::RC_Set(int InputData[]) : RC_Set::RC_Set((int*)InputData, sizeof(InputData) / sizeof(InputData[0])){}
RC_Set::~RC_Set() {

}
RC_Set RC_Set::Subset(int start, int end) {
}
RC_Set RC_Set::Difference(RC_Set B) {
}
bool RC_Set::isSubset(RC_Set SuperSet) {

}
bool RC_Set::ContainsElement(int Value) {

}
int RC_Set::Cardinality() {
	return numElements;
}