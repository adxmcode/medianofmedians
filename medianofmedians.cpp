#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int findMedian(vector<int>& arr, int start, int size) {
	cout << "Finding median: " << endl;
	sort(arr.begin() + start, arr.begin() + start + size);
	cout << "median is: " << arr[start + size / 2] << endl;
	return arr[start + size / 2];
}

void printArray(vector<int>& arr) {
	cout << "{";
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << "}" << endl;
	cout << "==========================" << endl;
}

int medianOfMedians(vector<int>& arr, int left, int right) {
	int n = right - left + 1;

	//Base case//
	if (n <= 5) {
		return findMedian(arr, left, n);
	}
	
	vector<int>medians;

	for (int i = left; i <= right; i += 5) {
		int size = min(5, right - i + 1);
		medians.push_back(findMedian(arr, i, size));
	}
	printArray(medians);

	return medianOfMedians(medians, 0, medians.size() - 1);
}

int partition(vector<int>& arr, int left, int right, int pivot) {
	int pivIndex = find(arr.begin() + left, arr.begin() + right, pivot) - arr.begin();
	swap(arr[pivIndex], arr[right]);
	int i = left;
	
	for (int j = left; j < right; j++) {
		if (arr[j] < pivot) {
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[right]);
	printArray(arr);
	return i;
}

//The algorithm that is the shining star//
int selectKth(vector<int>& arr, int left, int right, int k) {
	if (left == right) {
		return arr[left];
	}
	cout << "Splitting array into groups of five" << endl;
	int pivot = medianOfMedians(arr, left, right);
	cout << "Partitioning the array: " << endl;
	int pivotIndex = partition(arr, left, right, pivot);

	int rank = pivotIndex - left + 1;
	if (k == rank) {
		return arr[pivotIndex];
	}
	else if (k < rank) {
		return selectKth(arr, left, pivotIndex - 1, k);
	}
	else {
		return selectKth(arr, pivotIndex + 1, right, k - rank);
	}
}

int medianOfMediansSelect(vector<int>& arr, int k) {
	return selectKth(arr, 0, arr.size() - 1, k);
}

int main() {
	int number = 0;
	vector<int>testArray;
	cout << "Insert numbers: ";
	cin >> number;
	while (number != -1) {
		testArray.push_back(number);
		cin >> number;
	}
	cout << "Give a number " << endl;
	int pick;
	cin >> pick;
	printArray(testArray);
	cout << endl;
	cout << "The " << pick << "th smallest element is: " << medianOfMediansSelect(testArray, pick) << endl;
	return 0;
}
