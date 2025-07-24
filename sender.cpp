#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

// Convert text to binary string
string textToBinary(const string& text) {
    string binaryResult = "";
    for (char character : text) {
        binaryResult += bitset<8>(character).to_string();
    }
    return binaryResult;
}

// Calculate parity bits needed: 2^r >= n + r + 1
int calculateParityBits(int dataLength) {
    int n = dataLength;  // data bits
    int r = 1;           // parity bits
    
    while (pow(2, r) < n + r + 1) {
        r++;
    }
    cout << "Data bits: " << n << ", Parity bits: " << r << ", Total: " << (n + r) << endl;
    return r;
}

// Calculate parity bit using even parity
int calculateParityBit(int hammingCode[], int position, int totalLength) {
    int parityValue = 0;
    
    for (int i = position; i <= totalLength; i += (position * 2)) {
        for (int j = i; j < i + position && j <= totalLength; j++) {
            if (j != position) {
                parityValue ^= hammingCode[j];
            }
        }
    }
    return parityValue;
}

// Generate Hamming code with systematic encoding
string createHammingCode(const string& binaryData) {
    int n = binaryData.length();  // data bits
    int r = calculateParityBits(n);  // parity bits
    int m = n + r;  // total codeword length
    
    int hammingCode[200] = {0};
    
    // Place data bits in non-power-of-2 positions
    int dataIndex = 0;
    for (int i = 1; i <= m; i++) {
        if ((i & (i - 1)) == 0) {  // power of 2 position
            hammingCode[i] = 0;
        } else {
            hammingCode[i] = (binaryData[dataIndex] == '1') ? 1 : 0;
            dataIndex++;
        }
    }
    
    // Calculate parity bits
    for (int i = 1; i <= m; i *= 2) {
        hammingCode[i] = calculateParityBit(hammingCode, i, m);
    }
    
    // Convert to string
    string result = "";
    for (int i = 1; i <= m; i++) {
        result += to_string(hammingCode[i]);
    }
    
    cout << "Hamming code: " << result << endl;
    return result;
}

int main() {
    string originalText;
    cout << "Enter text to send: ";
    cin >> originalText;
    
    cout << "\nOriginal: " << originalText << endl;
    
    // Convert text to binary
    string binaryData = textToBinary(originalText);
    cout << "Binary: " << binaryData << endl;
    
    // Create Hamming code
    string hammingCode = createHammingCode(binaryData);
    
    // Save to file
    ofstream outputFile("channel.txt");
    if (outputFile.is_open()) {
        outputFile << hammingCode;
        outputFile.close();
        cout << "Data saved to channel.txt" << endl;
    } else {
        cout << "Error: Could not create file!" << endl;
    }
    return 0;
}
