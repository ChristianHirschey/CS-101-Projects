#include <iostream>
#include <fstream> 
#include <sstream>
#include <iomanip> 
#include <string>
#include <cctype> 
#include <cmath>

using namespace std;

bool compareInt(int arrInt[], int sortArr[], int sortNum, int sortCount, int leftPos, int rightPos){
    if(sortNum >= sortCount) return true;
    
    int comp = arrInt[leftPos];
    int comp1 = arrInt[rightPos];

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
    
    return compareInt(arrInt, sortArr, sortNum+1, sortCount, leftPos, rightPos);
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

void merge(string arr[], int sortArr[], int arrInt[], string datatype, int sortCount, int i, int j, int k) {
    int mergedSize = k - i + 1;
    int mergePos = 0;
    int leftPos = i;
    int rightPos = j + 1;

    if(datatype == "s"){
        string* merged = new string[mergedSize];
        while (leftPos <= j && rightPos <= k) {
            if (compare(arr, sortArr, 0, sortCount, leftPos, rightPos)) {
                merged[mergePos] = arr[leftPos];
                ++leftPos;
            }
            else {
                merged[mergePos] = arr[rightPos];
                ++rightPos;
            }
            ++mergePos;
        }

        while (leftPos <= j) {
            merged[mergePos] = arr[leftPos];
            ++leftPos;
            ++mergePos;
        }

        while (rightPos <= k) {
            merged[mergePos] = arr[rightPos];
            ++rightPos;
            ++mergePos;
        }

        for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
            arr[i + mergePos] = merged[mergePos];
        }

        delete[] merged;
    }
    if(datatype == "i"){
        int* merged = new int[mergedSize];
        while (leftPos <= j && rightPos <= k) { // Add smallest element from left or right partition to merged arr
            if (compareInt(arrInt, sortArr, 0, sortCount, leftPos, rightPos)) {
                merged[mergePos] = arrInt[leftPos];
                ++leftPos;
            }
            else {
                merged[mergePos] = arrInt[rightPos];
                ++rightPos;

            }
            ++mergePos;
        }

        while (leftPos <= j) {
            merged[mergePos] = arrInt[leftPos];
            ++leftPos;
            ++mergePos;
        }

        while (rightPos <= k) {
            merged[mergePos] = arrInt[rightPos];
            ++rightPos;
            ++mergePos;
        }

        for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
            arrInt[i + mergePos] = merged[mergePos];
        }
        delete[] merged;
    }
}


void mergeSort(string arr[], int sortArr[], int arrInt[], string datatype, int sortCount, int i, int k) {
    int j;
   
    if (i < k) {
        j = (i + k) / 2; // Find the midpoint in the partition
      
        mergeSort(arr, sortArr, arrInt, datatype, sortCount, i, j); // Recursively sort left and right partitions
        mergeSort(arr, sortArr, arrInt, datatype, sortCount, j + 1, k);
      
        merge(arr, sortArr, arrInt, datatype, sortCount, i, j, k); // Merge left and right partition in sorted order
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

    int max;

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
        arrInt[count] = max;
        count++;
        while(inFS >> temp) {
            if(temp > max) {
                max = temp;
            }
            arrInt[count] = temp;
            count++;
        }

        mergeSort(arr, sortArr, arrInt, datatype, sortCount, 0, count-1);

        for(int i = 0; i < count; i++){
            outFS << right << setw(10) << arrInt[i] << endl;
        }
    }
    else if(datatype == "s"){
        while(inFS >> tempStr){
            arr[count] = tempStr;
            count++;
        }

        mergeSort(arr, sortArr, arrInt, datatype, sortCount, 0, count-1);

        for(int i = 0; i < count; i++){
            outFS << arr[i] << endl;
        }
    }

    inFS.close();
    outFS.close();
}