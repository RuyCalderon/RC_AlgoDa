#pragma once

class RC_Algorithm 
{
private:
	bool _ProfileOn;
	void Merge(int *Source, int start, int end);
	void QSort(int *Source, int start, int end, float suggestion = -1.0f);
	void HSort(int *Source, int length, int h);
public:
	RC_Algorithm() :_ProfileOn(false) {};
	~RC_Algorithm() {};
	void FillRandomData(int *DataSet, int length, int RangeMin, int RangeMax, unsigned int Seed);
	void MergeSort(int *DataSet, int length);
	void ShellSort(int *Source, int length, int *gapLengths, int numGapLengths);
	void InsertionSort(int *Source, int length);
	void SelectionSort(int *Source, int length);
	void BucketSort(int *Source, int length, int numBuckets, int StartRange, int EndRange);
	void RadixSort(int *Source, int length);
	void QuickSort(int *DataSet, int length, float suggestion = -1.0f);
};