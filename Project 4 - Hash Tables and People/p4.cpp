#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <list>
#include <vector>

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    Person(string id, string first, string last, string email, string phone, string city, string state, string postalCode) {
        this->id = id;
        this->first = first;
        this->last = last;
        this->email = email;
        this->phone = phone;
        this->city = city;
        this->state = state;
        this->postalCode = postalCode;
    }
};

class HashTable {
private:
    int size;
    vector<list<Person>> table;

    int h(string key) {
        return djb2(key) % size;
    }

    int h2(string key) {
        return 43 - (djb2(key) % 43);
    }

public:   
    HashTable(int tableSize) {
        size = tableSize;
        table = vector<list<Person>>(tableSize, list<Person>());
    }

    void insert(Person p, string key) {
        int pos = h(getField(p, key));
        int j = 1;
        while(!table[pos].empty() && this->getField(table[pos].front(), key) != getField(p, key)) {
            pos = (h(getField(p, key)) + j * h2(getField(p, key))) % size;
            j++;
        }
        table[pos].push_back(p);
    }

    void print(string key) {
        for(int i = 0; i < size; i++) {
                if(!table[i].empty()) {
                    cout << i << ": " << getField(table[i].front(), key) << " (" << table[i].size() << ")," << endl;
                }
            }
    }

    void lookup(string key, string val) {
        for(int i = 0; i < size; i++) {
            if(!table[i].empty() && this->getField(table[i].front(), key) == val) {
                cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode\n";
                for(Person p : table[i]) {
                    cout << p.id << "," << p.first << "," << p.last << "," << p.email << "," << p.phone << "," << p.city << "," << p.state << "," << p.postalCode << endl;
                }
                return;
            }
        }
        cout << "No results" << endl;
    }

private:
    string getField(Person person, string key) {
        if(key == "Id") return person.id;
        else if (key == "FirstName") return person.first;
        else if (key == "LastName") return person.last;
        else if (key == "Email") return person.email;
        else if (key == "Phone") return person.phone;
        else if (key == "City") return person.city;
        else if (key == "State") return person.state;
        else if (key == "PostalCode") return person.postalCode;
        else return ""; // Invalid key
    }
};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    HashTable hashTable(tableSize);

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
    
    string line, token, id, first, last, email, phone, city, state, postalCode;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);

        getline(iss, id, '\t');
        getline(iss, first, '\t');
        getline(iss, last, '\t');
        getline(iss, email, '\t');
        getline(iss, phone, '\t');
        getline(iss, city, '\t');
        getline(iss, state, '\t');
        getline(iss, postalCode, '\t');

        Person p(id, first, last, email, phone, city, state, postalCode);

        hashTable.insert(p, key);
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            hashTable.print(key);
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            hashTable.lookup(key, val);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
