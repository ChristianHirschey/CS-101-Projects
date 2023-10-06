#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip> 
#include <string>
#include <cctype> 
#include <cmath>

using namespace std;

bool compareInt(int arr[], int sortArr[], int sortNum, int sortCount, int leftPos, int rightPos, int maxInd){
    if(sortNum >= sortCount) return true;
    
    int comp = arr[leftPos];
    int comp1 = arr[rightPos];

    if(sortArr[sortNum] == 0){
        comp = comp % 10;
        comp1 = comp1 % 10;
    }
    else {
        for(int i = 0; i < sortArr[sortNum]; i++){
            comp /= 10;
            comp1 /= 10;
        }
        comp = comp % 10;
        comp1 = comp1 % 10;
    }

    if (comp < comp1) return true;
    else if (comp > comp1) return false;
    
    return compareInt(arr, sortArr, sortNum+1, sortCount, leftPos, rightPos, maxInd);
}

void mergeInt(int arr[], int sortArr[], int sortCount, int i, int j, int k, int maxInd) {
    int mergedSize = k - i + 1;
    int mergePos = 0;
    int leftPos = i; // Initialize left partition position
    int rightPos = j + 1; // Initialize right partition position
    int* mergedInt = new int[mergedSize]; // Dynamically allocates temporary array for merged arr

    while (leftPos <= j && rightPos <= k) { // Add smallest element from left or right partition to merged arr
        if (compareInt(arr, sortArr, 0, sortCount, leftPos, rightPos, maxInd)) {
            mergedInt[mergePos] = arr[leftPos];
            ++leftPos;
        }
        else {
            mergedInt[mergePos] = arr[rightPos];
            ++rightPos;
         
        }
        ++mergePos;
    }
   
    while (leftPos <= j) { // If left partition is not empty, add remaining elements to merged arr
        mergedInt[mergePos] = arr[leftPos];
        ++leftPos;
        ++mergePos;
    }
   
    while (rightPos <= k) { // If right partition is not empty, add remaining elements to merged arr
        mergedInt[mergePos] = arr[rightPos];
        ++rightPos;
        ++mergePos;
    }
   
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) { // Copy merge number back to arr
        arr[i + mergePos] = mergedInt[mergePos];
    }
    delete[] mergedInt;
}

void mergeSortInt(int arr[], int sortArr[], int sortCount, int i, int k, int maxInd) {
    int j;
    if (i < k) {
        j = (i + k) / 2; // Find the midpoint in the partition

        mergeSortInt(arr, sortArr, sortCount, i, j, maxInd); // Recursively sort left and right partitions
        mergeSortInt(arr, sortArr, sortCount, j + 1, k, maxInd);
      
        mergeInt(arr, sortArr, sortCount, i, j, k, maxInd);// Merge left and right partition in sorted order
    }
}

bool compare(string arr[], int sortArr[], int sortNum, int sortCount, int leftPos, int rightPos){
    if(sortNum >= sortCount) return true;
    
    int compareIndex = sortArr[sortNum];
    char comp = (compareIndex < arr[leftPos].size() ? arr[leftPos][compareIndex] : '\0');
    char comp1 = (compareIndex < arr[rightPos].size() ? arr[rightPos][compareIndex] : '\0');
    
    if (comp < comp1) return true;
    else if (comp > comp1) return false;
    
    return compare(arr, sortArr, sortNum+1, sortCount, leftPos, rightPos);
}

void mergeStr(string arr[], int sortArr[], int sortCount, int i, int j, int k) {
    int mergedSize = k - i + 1;
    int mergePos = 0;
    int leftPos = i;
    int rightPos = j + 1;
    string* mergedStr = new string[mergedSize];

    while (leftPos <= j && rightPos <= k) {
        if (compare(arr, sortArr, 0, sortCount, leftPos, rightPos)) {
            mergedStr[mergePos] = arr[leftPos];
            ++leftPos;
        }
        else {
            mergedStr[mergePos] = arr[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    while (leftPos <= j) {
        mergedStr[mergePos] = arr[leftPos];
        ++leftPos;
        ++mergePos;
    }

    while (rightPos <= k) {
        mergedStr[mergePos] = arr[rightPos];
        ++rightPos;
        ++mergePos;
    }

    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        arr[i + mergePos] = mergedStr[mergePos];
    }

    delete[] mergedStr;
}


void mergeSortStr(string arr[], int sortArr[], int sortCount, int i, int k) {
    int j;
   
    if (i < k) {
        j = (i + k) / 2; // Find the midpoint in the partition
      
        mergeSortStr(arr, sortArr, sortCount, i, j); // Recursively sort left and right partitions
        mergeSortStr(arr, sortArr, sortCount, j + 1, k);
      
        mergeStr(arr, sortArr, sortCount, i, j, k); // Merge left and right partition in sorted order
    }
}

int main(int argc, char *argv[]){
    if(argc != 5){
        cout << "Usage: ./a.out i|s sort_filename input_filename output_filename";
        return 1;
    }
    
    string datatype, sFile, iFile, oFile;

    ifstream sortFS, inFS;
    ofstream outFS;

    datatype = argv[1];
    sFile = argv[2];
    iFile = argv[3];
    oFile = argv[4];

    sortFS.open(sFile);
    inFS.open(iFile);
    outFS.open(oFile);

    string arr[2001];
    int arrInt[2001];

    int temp;
    string tempStr;
    int count = 0;

    int sortArr[2001];
    int sortArg;
    int sortCount = 0;

    int max, maxInd;

    if(datatype != "i" && datatype != "s"){
        cout << "Invalid datatype \"" << datatype << "\" (must be \"i\" or \"s\")";
        return 2;
    }
    else if(!sortFS.is_open()){
        cout << "Unable to open sort file";
        return 3;
    }
    else if(!inFS.is_open()){
        cout << "Unable to open input file";
        return 4;
    }
    else if(!outFS.is_open()){
        cout << "Unable to open output file";
        return 5;
    }

    while(!sortFS.eof()){
        sortFS >> sortArg;
        sortArr[sortCount] = sortArg;
        sortCount++;
    }

    sortFS.close();

    if(datatype == "i"){
        inFS >> max;
        maxInd = count;
        arrInt[count] = max;
        count++;
        while(inFS >> temp) {
            if(temp > max) {
                max = temp;
                maxInd = count - 1;
            }
            arrInt[count] = temp;
            count++;
        }

        mergeSortInt(arrInt, sortArr, sortCount, 0, count-1, maxInd);

        for(int i = 0; i < count; i++){
            outFS << right << setw(10) << arrInt[i] << endl;
        }
    }
    else if(datatype == "s"){
        while(inFS >> tempStr){
            arr[count] = tempStr;
            count++;
        }

        mergeSortStr(arr, sortArr, sortCount, 0, count-1);

        for(int i = 0; i < count; i++){
            outFS << arr[i] << endl;
        }
    }

    inFS.close();
    outFS.close();
}