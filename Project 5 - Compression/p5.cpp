#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
    int freq;
    char ch;
    Node *left, *right;
    int huffLength;

    Node() {
        huffLength = 0;
        left = nullptr;
        right = nullptr;
        freq = 0;
        ch = '\0';
    }

    Node(int f, char c) {
        huffLength = 0;
        left = nullptr;
        right = nullptr;
        freq = f;
        ch = c;
    }
};

class QueueCompare {
public:
    // Compare the keys of the nodes
    // return true if x's key > y's key; false otherwise
    bool operator()(Node *x, Node *y) {
        return x->freq > y->freq;
    }
};

class Tree {
public:
    Node *root;

    Tree() {
        root = nullptr;
    }

    void buildTree(map<char, Node>& map) {
        priority_queue<Node*, vector<Node*>, QueueCompare> minQueue;
    
        for (int i = 0; i <= 127; i++) {
            if(map.count(i)) { // if map(i) exists
                minQueue.push(new Node(map.at(i).freq, map.at(i).ch));
            }
        }

        while (minQueue.size() >= 2) { // leave last node on heap so can be root node
            Node *left = minQueue.top();
            minQueue.pop();
            Node *right = minQueue.top();
            minQueue.pop();

            // take minimum two nodes and add together

            Node *top = new Node(left->freq + right->freq, '\0');
            top->left = left;
            top->right = right;

            minQueue.push(top);
    }
    root = minQueue.top();
    minQueue.pop();
    }

    int getHuffLength(Node *node, char c, int length) {
        if(node == nullptr || node->freq <=0) return 0; 

        if(node->ch == c) return length; // if character at node == character looking for

        int leftLength = getHuffLength(node->left, c, length+1); // recursively search left nodes
        if(leftLength != 0) return leftLength; // if leftLength exists return it

        return getHuffLength(node->right, c, length+1); // if leftLength doesn't exist recursively search right nodes
    }
};

int main(int argc, char *argv[]) {
    if(argc != 2) return 1; // if incorrect argcount return error
    
    ifstream iss;

    iss.open(argv[1]);

    if(!iss.is_open()) return 2; // if file couldn't open return error

    map<char, Node> map; // Node implementation tracks freq and char within map to make getHuffLength easier
    char c;
    int count = 0; // running count of characters in input file
    int compressedLength = 0; // running compressed length

    Tree t;

    while(iss.get(c)) { // while character can be read (can't use while !iss.eof() since will double count last char)
        count++;
        if(map.count(c)) map.at(c).freq++; // if map(c) exists, increment freq
        else (map.insert({c, Node(1, c)})); // else create map(c)
    }
    
    t.buildTree(map);

    for(int i = 0; i <= 127; i++) {
        if(map.count(i)) {
            map.at(i).huffLength = t.getHuffLength(t.root, char(i), 0);
            compressedLength += (map.at(i).huffLength * map.at(i).freq); // compressedLength == sum of huffLength for each char * freq of each char
        }
    }

    cout << "Uncompressed length: " << count*8 << " bits\n"; // uncompressed bits == character count*8
    cout << "Compressed length: " << compressedLength << " bits\n"; 
    cout << "CHAR|FREQ|CODE_LEN\n";

    for(int i = 0; i <= 127; i++) { // loop through ASCII table numbers
        if(map.count(i)) {
            cout << "\'" << char(i) << "\'|" << map.at(i).freq << "|" << map.at(i).huffLength << endl;
        }
    }   
   
    return 0;
}
