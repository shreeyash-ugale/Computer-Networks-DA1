#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

// Convert binary string back to text
string binaryToText(const string& binary) {
    string result = "";
    for (size_t i = 0; i < binary.length(); i += 8) {
        if (i + 8 <= binary.length()) {
            bitset<8> bits(binary.substr(i, 8));
            result += static_cast<char>(bits.to_ulong());
        }
    }
    return result;
}

// Calculate parity bits used in encoding
int calculateParityBits(int totalLength) {
    int m = totalLength;  // total codeword length
    int r = 1;            // parity bits
    
    while (pow(2, r) < m) {
        r++;
    }
    return r;
}

// Hamming syndrome decoding for error detection and correction
string checkAndCorrectErrors(const string& receivedData) {
    int m = receivedData.length();  // total codeword length
    int hammingCode[200] = {0};
    
    cout << "Received: " << receivedData << endl;
    
    // Convert to array (1-indexed)
    for (int i = 0; i < m; i++) {
        hammingCode[i + 1] = (receivedData[i] == '1') ? 1 : 0;
    }
    
    // Calculate syndrome
    int syndrome = 0;  // error position
    int r = calculateParityBits(m);
    
    cout << "\nSyndrome calculation:" << endl;
    
    // Check each parity bit
    for (int i = 0; i < r; i++) {
        int parityPosition = pow(2, i);
        int calculatedParity = 0;
        
        cout << "Checking parity bit P" << parityPosition << " (positions: ";
        
        for (int j = parityPosition; j <= m; j += (parityPosition * 2)) {
            for (int k = j; k < j + parityPosition && k <= m; k++) {
                cout << k << " ";
                calculatedParity ^= hammingCode[k];
            }
        }
        
        cout << ") = " << calculatedParity << endl;
        
        if (calculatedParity != 0) {
            syndrome += parityPosition;
            cout << "  -> Parity error! Adding " << parityPosition << " to syndrome" << endl;
        } else {
            cout << "  -> Parity OK" << endl;
        }
    }
    
    // Error correction
    if (syndrome != 0) {
        cout << "\nERROR DETECTED at position " << syndrome << endl;
        cout << "Original bit value: " << hammingCode[syndrome] << endl;
        hammingCode[syndrome] = 1 - hammingCode[syndrome];  // flip bit
        cout << "Corrected bit value: " << hammingCode[syndrome] << endl;
        cout << "Error successfully corrected!" << endl;
        
        cout << "Corrected codeword: ";
        for (int i = 1; i <= m; i++) {
            cout << hammingCode[i];
        }
        cout << endl;
    } else {
        cout << "\nNo errors detected - data is error-free!" << endl;
    }
    
    // Extract data bits (skip parity positions)
    string originalData = "";
    for (int i = 1; i <= m; i++) {
        if ((i & (i - 1)) != 0) {  // not power of 2
            originalData += to_string(hammingCode[i]);
        }
    }
    
    return originalData;
}

int main() {
    string receivedData = "";
    
    // Read data from channel
    ifstream inputFile("channel.txt");
    if (inputFile.is_open()) {
        getline(inputFile, receivedData);
        inputFile.close();
    } else {
        cout << "Error: Could not open channel.txt" << endl;
        return 1;
    }
    
    // Error detection and correction
    string correctedBinary = checkAndCorrectErrors(receivedData);
    
    // Convert binary back to text
    string finalText = binaryToText(correctedBinary);
    cout << "Decoded: " << finalText << endl;
    
    return 0;
}
