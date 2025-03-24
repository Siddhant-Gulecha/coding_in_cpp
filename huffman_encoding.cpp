#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Node structure for Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
}; 

// Comparison class for the priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to build the Huffman Tree
Node* buildHuffmanTree(const int freq[]) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character with a non-zero frequency
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            pq.push(new Node((char)i, freq[i]));
        }
    }

    // Combine nodes until one node remains in the queue
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a new internal node with a combined frequency
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Function to generate Huffman codes
void generateCodes(Node* root, const string& code, string huffmanCodes[]) {
    if (!root) return;

    // If it's a leaf node, store the character's code
    if (!root->left && !root->right) {
        huffmanCodes[(unsigned char)root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Function to calculate character frequencies (excluding spaces)
void calculateFrequencies(const string& message, int freq[]) {
    for (char ch : message) {
        if (ch != ' ') { // Exclude spaces
            freq[(unsigned char)ch]++;
        }
    }
}

// Function to encode the message
string encodeMessage(const string& message, const string huffmanCodes[]) {
    string encodedMessage;
    for (char ch : message) {
        if (ch != ' ') { // Skip spaces during encoding
            encodedMessage += huffmanCodes[(unsigned char)ch];
        } else {
            encodedMessage += " "; // Keep spaces in the encoded output
        }
    }
    return encodedMessage;
}

// Function to print the Huffman codes
void printHuffmanCodes(const string huffmanCodes[]) {
    cout << "Huffman Codes:" << endl;
    for (int i = 0; i < 256; i++) {
        if (!huffmanCodes[i].empty()) {
            cout << (char)i << ": " << huffmanCodes[i] << endl;
        }
    }
    cout << endl;
}

int main() {
    string message;

    cout << "Enter the message: ";
    getline(cin, message);

    // Step 1: Calculate frequencies of characters (excluding spaces)
    int freq[256] = {0}; // Array to store frequencies of all ASCII characters
    calculateFrequencies(message, freq);

    cout << "\nCharacter Frequencies (excluding spaces):" << endl;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            cout << (char)i << ": " << freq[i] << endl;
        }
    }

    // Step 2: Build Huffman Tree
    Node* root = buildHuffmanTree(freq);

    // Step 3: Generate Huffman codes
    string huffmanCodes[256];
    generateCodes(root, "", huffmanCodes);

    // Step 4: Print Huffman codes
    printHuffmanCodes(huffmanCodes);

    // Input: Message to encode
    string encodeMessageInput;
    cout << "Enter the message to encode: ";
    getline(cin, encodeMessageInput);

    // Step 5: Encode the message
    string encodedMessage = encodeMessage(encodeMessageInput, huffmanCodes);
    cout << "Encoded Message: " << encodedMessage << endl;

    encodeMessageInput;
    cout << "Enter the message to encode: ";
    getline(cin, encodeMessageInput);

    // Step 5: Encode the message
    encodedMessage = encodeMessage(encodeMessageInput, huffmanCodes);
    cout << "Encoded Message: " << encodedMessage << endl;

    return 0;
}
