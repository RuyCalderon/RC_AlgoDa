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
RC_Set::RC_Set(int InputData[]) {
	int SetSize = sizeof(InputData) / sizeof(InputData[0]);
	if (!GlobalSet) {
		GlobalMemReserveSize = (SetSize < 4096) ? 8192 : 2 << ((int)log2(SetSize) + 1);
		GlobalSet = RC_RESERVE_MEM(int, GlobalMemReserveSize);
		int *FirstSet = RC_COMMIT_MEM(int, SetSize, GlobalSet);
		numGlobalElements = SetSize;
	}
	else if(SetSize + numGlobalElements < GlobalMemReserveSize){
		int *NextSet = RC_COMMIT_MEM(int, SetSize, GlobalSet+numGlobalElements);
		numGlobalElements += SetSize;
	}
}
RC_Set::RC_Set(int *InputData, int InputSize) {

}
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