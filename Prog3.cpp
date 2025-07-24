#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    // Original 25-bit message
    string message = "1101010110010111001101011";
    
    int n = message.length();
    int r = 0; // parity bits
    
    // Calculate redundant bits
    while(pow(2, r) < n + r + 1) {
        r++;
    }
    
    int total_bits = n + r;
    int hamming[31] = {0};
    
    // Place data bits in non-power-of-2 positions
    int data_index = 0;
    for(int i = 1; i <= total_bits; i++) {
        // Check if i is power of 2
        if((i & (i-1)) == 0) {
            hamming[i] = 0; // parity bit position
        } else {
            hamming[i] = message[data_index] - '0';
            data_index++;
        }
    }
    
    // Calculate parity bits
    for(int i = 1; i <= total_bits; i *= 2) {
        int parity = 0;
        for(int j = i; j <= total_bits; j += 2*i) {
            for(int k = j; k < j + i && k <= total_bits; k++) {
                if(k != i) {
                    parity ^= hamming[k];
                }
            }
        }
        hamming[i] = parity;
    }
    
    // Convert to string
    string hamming_code = "";
    string parity_bits = "";
    for(int i = 1; i <= total_bits; i++) {
        hamming_code += to_string(hamming[i]);
        if((i & (i-1)) == 0) {
            parity_bits += to_string(hamming[i]);
        }
    }
    
    // Write to File3
    ofstream file("File3.txt");
    file << "Original 25 bits payload: " << message << endl;
    file << "Extra bit(s) for correcting errors: " << parity_bits << endl;
    file << "Message sent: " << hamming_code << endl;
    file << "Message received: " << hamming_code << endl;
    file.close();
    
    cout << "Sender: Hamming code generated!" << endl;
    cout << "Original: " << message << endl;
    cout << "Parity bits: " << parity_bits << endl;
    cout << "Hamming code: " << hamming_code << endl;
    
    return 0;
}