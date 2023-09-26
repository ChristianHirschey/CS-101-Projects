#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

class Record {
public:
	string source, dest;
	int band, bandA, bandA2, bandB, bandB2;
	
	Record(string sourceA, string destA, int bandA2) {
		source = sourceA;
		dest = destA;
		band = bandA2;
	}

	Record(string sourceA, int bandA2, int bandB2) {
		source = sourceA;
		bandA = bandA2;
		bandB = bandB2;
	}

	Record() {
		source = "UNKNOWN";
		dest = "UNKNOWN";
		bandA = 0;
		bandB = 0;
	}
};

void upper(Record recordArr[], int lineNum) {
	for (int i = 0; i < lineNum; i++) {
		for (int c = 0; c < recordArr[i].source.size(); c++) {
			recordArr[i].source[c] = toupper(recordArr[i].source[c]); // convert each char in source to uppercase
		}
    			for (int ch = 0; ch < recordArr[i].dest.size(); ch++) {
			recordArr[i].dest[ch] = toupper(recordArr[i].dest[ch]); // convert each char in dest to uppercase
		}
	}
}

bool inList(int lineNum, Record recordArr[], string compare){
	for(int i = 0; i < lineNum; i++){
		if(compare == recordArr[i].source){
			return true;
		}
	}
	return false;
}

bool inList(int lineNum, string arr[], string compare){
	for(int i = 0; i < lineNum; i++){
		if(compare == arr[i]){
			return true;
		}
	}
	return false;
}

int main(int argc, char const *argv[]) {
	ifstream inFS;
	ofstream outFS;
	string inFile, outFile;
	int lineNum = 0;

	string sourceA, destA; 
	int bandA2;

	string str1, str2;
	int usedNum = 0;
	
	string leafSource[1001];
	Record recordCheck[1001];
	int leafNum = 0;

	Record recordArr[1001];
	string usedSD[4004];

	inFS.open(argv[1]); 

	outFS.open(argv[2]);

	if (!inFS.is_open()) { 
		return 1; // return error if file is unable to open
	}

	while (!inFS.eof()) { // true until reaches end of file
			inFS >> sourceA >> destA >> bandA2;
			recordArr[lineNum] = Record(sourceA, destA, bandA2);
			lineNum++;
	}

	inFS.close();
	
	upper(recordArr, lineNum);

	for(int i = 0; i < lineNum; i++) {
		if(!inList(1001, usedSD, recordArr[i].source)){
			usedSD[usedNum] = recordArr[i].source;
			usedNum++;
		}
		if(!inList(1001, usedSD, recordArr[i].dest)){
			usedSD[usedNum] = recordArr[i].dest;
			usedNum++;
		}
	}

	for(int i = 0; i < usedNum; i++){
		outFS << usedSD[i] << endl;
	}
	
	outFS << endl;

	for (int h = 0; h < usedNum; h++) {
    	for (int i = 0; i < lineNum; i++) {
            for (int j = 0; j < lineNum; j++) { // loop through sources
                if ((recordArr[i].source == recordArr[j].dest) && (!inList(leafNum, leafSource, recordArr[i].source)) && (recordArr[i].source == usedSD[h])) {
                    leafSource[leafNum] = recordArr[i].source;
                    leafNum++;
                }
            }
        }
    }

	int leafLen = leafNum + 1;

	for(int i = 0; i < leafLen + 1; i++) {
		for(int j = 0; j < lineNum - 1; j++) {
			if(leafSource[i] == recordArr[j].source) {
				recordCheck[i].source = leafSource[i];
				recordCheck[i].bandA += recordArr[j].band;
			}
			if(leafSource[i] == recordArr[j].dest) {
				recordCheck[i].source = leafSource[i];
				recordCheck[i].bandB += recordArr[j].band;
			}
		}
	}

	for(int i = 0; i <= leafLen; i++) {
		if(recordCheck[i].bandA != 0) outFS << recordCheck[i].source << " " << recordCheck[i].bandA << " " << recordCheck[i].bandB << " " << setprecision(2) << fixed << double(recordCheck[i].bandB)/double(recordCheck[i].bandA) << endl;
	}
}