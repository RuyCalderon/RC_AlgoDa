#include<windows.h>
#include<iostream>
#include<cassert>
#include "RC_Algorithm.h"


int main()
{
	int DataSet[10000] = {};

	RC_Algorithm Algorithms = RC_Algorithm();
	
	int NumDataPoints = 10000;

	LARGE_INTEGER Cycles_Start;
	LARGE_INTEGER Cycles_End;
	LARGE_INTEGER Cycles_Per_Second;
	QueryPerformanceFrequency(&Cycles_Per_Second);
	QueryPerformanceCounter(&Cycles_Start);
	std::cout << "Wash" << std::endl;

	int Count = 0;
	while (Count <= 6)
	{
		switch (Count) 
		{
			case 1:
			{
				std::cout << "\n\n\nShell Sort" << std::endl;
				int gaps[9] = { 1094, 364, 121, 40, 13, 4, 1 };
				Algorithms.ShellSort(DataSet, NumDataPoints, (int*)gaps, 9);
			}break;
			case 2:
			{
				std::cout << "\n\n\Selection Sort" << std::endl;
				Algorithms.SelectionSort(DataSet, NumDataPoints);
			}break;
			case 3:
			{
				std::cout << "\n\n\Insertion Sort" << std::endl;
				Algorithms.InsertionSort(DataSet, NumDataPoints);
			}break;
			case 4:
			{
				std::cout << "\n\n\Merge Sort" << std::endl;
				Algorithms.MergeSort(DataSet, NumDataPoints);
			}break;
			case 5:
			{
				int rangeStart = 0;
				int bucketSize = 100;
				int rangeEnd = 10000;

				std::cout << "\n\n\Bucket Sort" << std::endl;
				Algorithms.BucketSort(DataSet, NumDataPoints, bucketSize, rangeStart, rangeEnd);
			}break;
			case 6:
			{
				std::cout << "\n\n\Radix Sort" << std::endl;
				Algorithms.RadixSort(DataSet, NumDataPoints);
			}break;
			case 7:
			{
				std::cout << "\n\n\Quick Sort" << std::endl;
				//Algorithms.QuickSort(DataSet, NumDataPoints);
			}break;

			default:
			{
				break;
			}
		}
		QueryPerformanceCounter(&Cycles_End);
		double CycleCount = (double)(Cycles_End.QuadPart - Cycles_Start.QuadPart);
		float Milliseconds = (float)((CycleCount / (double)Cycles_Per_Second.QuadPart) * 1000.0);
		double Counts_Per_Item = CycleCount / (double)NumDataPoints;
		float Microseconds_Per_Item = (float)((Counts_Per_Item / (double)Cycles_Per_Second.QuadPart) * 1000000.0);
		std::cout << "Milliseconds: " << Milliseconds << std::endl;
		std::cout << "Counts Per Item: " << (float)Counts_Per_Item << std::endl;
		std::cout << "Microseconds Per Item: " << Microseconds_Per_Item << std::endl;
		std::cout << "\n\n" << std::endl;
		Count++;
		Algorithms.FillRandomData(DataSet, NumDataPoints, 0, 10000, 2984708234);
		QueryPerformanceCounter(&Cycles_Start);
	}
	/*
	int gaps[3] = { 5,3,1 };
	QueryPerformanceCounter(&Cycles_Start);
	Algorithms.ShellSort(DataSet, NumDataPoints, (int*)gaps, 3);
	Algorithms.SelectionSort(DataSet, NumDataPoints);
	Algorithms.InsertionSort(DataSet, NumDataPoints);
	Algorithms.MergeSort(DataSet, NumDataPoints);
	Algorithms.QuickSort(DataSet, NumDataPoints);
	QueryPerformanceCounter(&Cycles_End);

	LARGE_INTEGER Cycles_Per_Second;
	QueryPerformanceFrequency(&Cycles_Per_Second);

	double CycleCount = (double)(Cycles_End.QuadPart - Cycles_Start.QuadPart);
	float Milliseconds = (float)((CycleCount / (double)Cycles_Per_Second.QuadPart) * 1000.0);
	double Counts_Per_Item = CycleCount / (double)549;
	float Microseconds_Per_Item = (float)((Counts_Per_Item / (double)Cycles_Per_Second.QuadPart) * 1000000.0);
	//std::cout << "Merge Sort" << std::endl;
	std::cout << "Milliseconds: " << Milliseconds << std::endl;
	std::cout << "Counts Per Item: " << (float)Counts_Per_Item << std::endl;
	std::cout << "Microseconds Per Item: " << Microseconds_Per_Item << std::endl;
	std::cout << "\n\n" << std::endl;
	*/
	std::cin >> DataSet[0];



	return 0;
}