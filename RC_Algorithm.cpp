#include "RC_Algorithm.h"


unsigned int BitwiseReverse(unsigned int Number, int Size) 
{
	unsigned int New = 0;
	for (int i = 0;
		i < 32;
		++i) {

		unsigned int NextBit = (Number << (31 - i)) >> 31;
		New |= (NextBit << (31 - i));
	}

	return New;
}

void RC_Algorithm::FillRandomData(int DataSet[], int length, int RangeMin, int RangeMax, unsigned int Seed)
{
	assert(RangeMax > RangeMin);
	unsigned int ReverseSeed = BitwiseReverse(Seed,32);
	long long unsigned int XOR_Value = ((unsigned long long int)ReverseSeed << 32) | Seed;

	for (int i = 0;
		i < length;
		++i) 
	{
		XOR_Value ^= XOR_Value >> 12;
		XOR_Value ^= XOR_Value << 17;
		XOR_Value ^= XOR_Value >> 3;
		XOR_Value ^= XOR_Value << 22;
		
		int New = (int)(unsigned int)(XOR_Value >> 16);
		int Intermediate = std::abs((New % (RangeMax - RangeMin)) + RangeMin);
		if (!(RangeMax > Intermediate && RangeMin <= Intermediate))
		{
			assert(false);
		}
		DataSet[i] = Intermediate;
	}
}

void RC_Swap(int *First, int *Second)
{
	int temp = *First;
	*First = *Second;
	*Second = temp;
};
void RC_Algorithm::Merge(int *Source, int start, int end)
{
	if ((end - start) > 2) 
	{
		Merge(Source, start, start + ((end - start) / 2));
		Merge(Source, start + ((end - start) / 2), end);
		
		int *Temp = (int *)malloc(sizeof(int)*(end - start));
		memcpy((void*)Temp, (void*)(&Source[start]), sizeof(int)*(end - start));

		for (int first = 0, second = (end - start) / 2, Total = 0;
			first < (end - start) / 2 || second < (end - start);
			++Total) {
			if (second >= (end - start)) 
			{
				Source[start + Total] = Temp[first++];
				continue;
			}
			if (first >= (end - start) / 2) 
			{
				Source[start + Total] = Temp[second++];
				continue;
			}
			if (Temp[first] >= Temp[second])
			{
				Source[start + Total] = Temp[second++];
			}
			else
			{
				Source[start + Total] = Temp[first++];
			}
		}
		free((void*)Temp);
	}
	else 
	{
		if (Source[start] > Source[end - 1])
		{
			RC_Swap(&Source[start], &Source[end - 1]);
		}
		//else, the two happen to be in correct order!
	}
}
void RC_Algorithm::MergeSort(int DataSet[], int length)
{
	Merge(DataSet, 0, length);
}

void RC_Algorithm::InsertionSort(int *Source, int length) 
{
	for (int j = 0; j < length; ++j){
		for (int i = 0; i <= j; ++i){
			if (Source[i] >= Source[j]){
				int temp = Source[i];
				Source[i] = Source[j];
				Source[j] = temp;
			}
		}
	}
}

void RC_Algorithm::SelectionSort(int *Source, int length) 
{
	for (int CursorLocation = 0;
		CursorLocation < length;
		++CursorLocation) {
		int Smallest = CursorLocation;
		for (int i = CursorLocation;
			i < length;
			++i) {
			if (Source[i] < Source[Smallest]) {
				Smallest = i;
			}
		}
		int Temp = Source[CursorLocation];
		Source[CursorLocation] = Source[Smallest];
		Source[Smallest] = Temp;
	}
}

void RC_Algorithm::HSort(int *Source, int length, int h) 
{
	int *Start = Source;
	int *End = Source + length;

	for (int *j=Start; j < End; j+=h) {
		for (int *i = Start; i <= j; i+=h) {
			if (*i >= *j) 
			{
				int temp = *i;
				*i = *j;
				*j = temp;
			}
		}
	}
}
void RC_Algorithm::ShellSort(int *Source, int length, int *gapLengths, int numGapLengths) 
{
	for (int *gap = gapLengths; gap < gapLengths + numGapLengths; ++gap) 
	{
		for (int subArrayOffset = 0; subArrayOffset < *gap; ++subArrayOffset) {
			HSort(Source + subArrayOffset, length - subArrayOffset, *gap);
		}
	}
}

struct Pivot_Results 
{
	int MiddleIndex;
	float HighSuggestion;
	float LowSuggestion;
};
Pivot_Results RC_Pivot(int *Source, int first_index, int last_index, float pivotSuggestion)
{
	//last is not being sorted
	bool Running = true;
	float _avg_high = 0.0f;
	float _avg_low = 0.0f;
	int Low = first_index;
	int High = last_index;
	
	while (Running) 
	{
		if (High <= Low)
		{
			Pivot_Results Result = {};
			Result.MiddleIndex = (High + Low) / 2;
			if (Source[Result.MiddleIndex] > pivotSuggestion) 
			{
				Result.MiddleIndex -= 1;
			}
			if (Result.MiddleIndex == first_index || Result.MiddleIndex == last_index)
			{
				Result.MiddleIndex = (last_index - first_index) / 2 + first_index;
				Result.LowSuggestion = (float)Source[(Result.MiddleIndex - first_index)/ 2];
				Result.HighSuggestion = (float)Source[(last_index - Result.MiddleIndex) / 2];
				return Result;
			}
			int numberLowIndices = Result.MiddleIndex - first_index + 1;
			Result.LowSuggestion = _avg_low / (float)((numberLowIndices <= 0) ? 1 : numberLowIndices);
			int numberHighIndices = (last_index - Result.MiddleIndex);
			Result.HighSuggestion = _avg_high / (float)((numberHighIndices <= 0) ? 1 : numberHighIndices);

			if (!(Result.LowSuggestion>= 0.0f && Result.HighSuggestion >= 0.0f &&
				Result.LowSuggestion <= 1000.0f && Result.HighSuggestion <= 1000.0f))
			{
				//Finishes, but incorrect sort. THere is a large-scale 
				//trend of it being sorted but on the small scale it is fucked
				assert(false);
			}
			if ((numberLowIndices + numberHighIndices) != (last_index - first_index + 1)) 
			{
				assert(false);
			}
			return Result;
		}
		float LowValue = (float)Source[Low];
		float HighValue = (float)Source[High];
		if (HighValue >= pivotSuggestion)
		{
			_avg_high += HighValue;
			High--;
			continue;
		}
		if (LowValue <= pivotSuggestion)
		{
			_avg_low += LowValue;
			Low++;
			continue;
		}
		// the high and low values ar about to be swapped, so low value will be in high slot and high value will be in low slot
		_avg_low += HighValue;
		_avg_high += LowValue;
		RC_Swap(&(Source[Low++]), &(Source[High--]));
	}
}
void RC_Algorithm::QSort(int *Source, int first_index, int last_index, float suggestion)
{
	if (last_index > first_index) 
	{
		Pivot_Results Pivot = RC_Pivot(Source, first_index, last_index, suggestion);
		QSort(Source, Pivot.MiddleIndex + 1, last_index, Pivot.HighSuggestion);
		QSort(Source, first_index, Pivot.MiddleIndex, Pivot.LowSuggestion);
	}
	
}
void RC_Algorithm::QuickSort(int DataSet[], int length, float suggestion) 
{
	//not necessary but I want to be clear that these are intended to be two separate code paths
	if (suggestion >= 0) 
		QSort((int *)DataSet, 0, length - 1, suggestion);
	else 
		QSort((int *)DataSet, 0, length - 1, (float)DataSet[0]);
}
void RC_Algorithm::BucketSort(int *Source, int length, int numBuckets, int StartRange, int EndRange) 
{
	int *bucketSlotsRemaining = (int *)malloc(sizeof(int) * numBuckets);
	int *bucketCurrentIndex = (int *)malloc(sizeof(int) * numBuckets);

	memset((int*)bucketSlotsRemaining, 0, sizeof(int)*numBuckets);
	memset((int*)bucketCurrentIndex, 0, sizeof(int)*numBuckets);

	int bucketRange = (EndRange - StartRange) / numBuckets;
	for (int i = 0;
		i < length;
		++i) {
		int appropriateBucket = Source[i] / bucketRange;
		bucketSlotsRemaining[appropriateBucket]++;
	}

	//now are bucket starting indices
	for (int i = 1;
		i < numBuckets;
		++i) {
		bucketCurrentIndex[i] += bucketSlotsRemaining[i - 1] + bucketCurrentIndex[i-1];
	}
	
	
	int currentIndex = 0;
	int firstUnfilledBucket = 0;
	int appropriateBucket;

	while (firstUnfilledBucket < numBuckets) {
		if (bucketSlotsRemaining[firstUnfilledBucket] == 0) {
			firstUnfilledBucket++;
			currentIndex = bucketCurrentIndex[firstUnfilledBucket];
			continue;
		}
		appropriateBucket = Source[currentIndex] / bucketRange;
		assert(bucketSlotsRemaining[firstUnfilledBucket] > 0);
		
		while (currentIndex != bucketCurrentIndex[appropriateBucket]) {
			int Temp = Source[bucketCurrentIndex[appropriateBucket]];
			Source[bucketCurrentIndex[appropriateBucket]++] = Source[currentIndex];
			Source[currentIndex] = Temp;
			
			bucketSlotsRemaining[appropriateBucket]--;
			assert(bucketSlotsRemaining[appropriateBucket] >= 0);
			if (bucketSlotsRemaining[firstUnfilledBucket] == 0) {
				for (int i = 0;
					i < numBuckets;
					++i) {
					if (bucketSlotsRemaining[i] > 0) {
						firstUnfilledBucket = i;
						break;
					}
				}
			}
			appropriateBucket = Source[currentIndex] / bucketRange;
		}
		if (bucketSlotsRemaining[appropriateBucket] > 0) {
			currentIndex = ++bucketCurrentIndex[appropriateBucket];
			bucketSlotsRemaining[appropriateBucket]--;
		}
	}
	RC_Algorithm::InsertionSort(Source, bucketCurrentIndex[0]);
	for (int *j = &bucketCurrentIndex[1]; j < &bucketCurrentIndex[numBuckets]; ++j) {
		RC_Algorithm::InsertionSort(&Source[*(j - 1)], *(j)-*(j-1));
	}

	free((void*)bucketSlotsRemaining);
	free((void*)bucketCurrentIndex);

}
void RC_Algorithm::RadixSort(int *Source, int length) {
	//could do this in one allocation
	int bucketSizes[16] = {};
	int bucketCurrentIndex[16] = {};
	int digitSize = 0x0000000f;
	
	int *tempSource = (int *)malloc(sizeof(int)*length);
	memset((void*)tempSource, 0, sizeof(int)*length);
	int *tempCurrentIndex = (int *)malloc(sizeof(int) * 16);
	int *writeLocation;
	int *readLocation;
	bool tempNextDestination = true;
	for (int radix = 0; radix < 16; ++radix) {
		if (tempNextDestination) {
			(int*)writeLocation = (int*)tempSource;
			(int*)readLocation = (int*)Source;
			tempNextDestination = false;
		}
		else {
			(int*)writeLocation = (int*)Source;
			(int*)readLocation = (int*)tempSource;
			tempNextDestination = true;
		}
		
		
		int hexShift = radix * 4;
		int hexMask = (radix == 0) ? digitSize : digitSize << hexShift;
		
		memset((int*)bucketSizes, 0, sizeof(int) * 16);
		memset((int*)bucketCurrentIndex, 0, sizeof(int) * 16);
		for (int val = 0; val < length; ++val) {
			int appropriateBucket = (readLocation[val] & hexMask) >> hexShift;
			bucketSizes[appropriateBucket]++;
		}
		for (int bucket = 1; bucket < 16; ++bucket) {
			bucketCurrentIndex[bucket] += bucketSizes[bucket-1] + bucketCurrentIndex[bucket-1];
		}
		
		for (int val = 0;
			val < length;
			++val) {
			int bucket = (readLocation[val] & hexMask) >> hexShift;
			writeLocation[bucketCurrentIndex[bucket]++] = readLocation[val];
		}
	}
	if (readLocation != &Source[0]) {
		memcpy((void*)&Source[0], (void*)readLocation, sizeof(int)*length);
	}
	free((void*)tempSource);
	free((void*)tempCurrentIndex);
}