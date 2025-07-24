#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int main() {
    string line;
    string received_message;
    string original_payload;
    
    // Read File3
    ifstream file("File3.txt");
    for(int i = 0; i < 4; i++) {
        getline(file, line);
        if(i == 0) {
            original_payload = line.substr(line.find(": ") + 2);
        }
        if(i == 3) {
            received_message = line.substr(line.find(": ") + 2);
        }
    }
    file.close();
    
    int total_bits = received_message.length();
    int hamming[31] = {0};
    
    // Convert received message to array
    for(int i = 0; i < total_bits; i++) {
        hamming[i+1] = received_message[i] - '0';
    }
    
    // Calculate syndrome (error position)
    int syndrome = 0;
    int r = 0;
    while(pow(2, r) < total_bits) {
        r++;
    }
    
    for(int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for(int j = pos; j <= total_bits; j += 2*pos) {
            for(int k = j; k < j + pos && k <= total_bits; k++) {
                parity ^= hamming[k];
            }
        }
        if(parity != 0) {
            syndrome += pos;
        }
    }
    
    string is_corrupted = (syndrome == 0) ? "No" : "Yes";
    
    // Correct error if found
    if(syndrome != 0) {
        hamming[syndrome] = 1 - hamming[syndrome]; // flip bit
    }
    
    // Extract original data bits
    string rectified_message = "";
    for(int i = 1; i <= total_bits; i++) {
        if((i & (i-1)) != 0) { // not power of 2
            rectified_message += to_string(hamming[i]);
        }
    }
    
    string match = (rectified_message == original_payload) ? "Yes" : "No";
    
    // Write to File4
    ofstream outfile("File4.txt");
    outfile << "Message received: " << received_message << endl;
    outfile << "Is message corrupted: " << is_corrupted << endl;
    outfile << "Rectified Message: " << rectified_message << endl;
    outfile << "Original Message: " << original_payload << endl;
    outfile << "Is there a match between rectified message and original message? " << match << endl;
    outfile.close();
    
    cout << "Receiver: Error correction completed!" << endl;
    cout << "Received: " << received_message << endl;
    cout << "Corrupted: " << is_corrupted << endl;
    if(syndrome != 0) {
        cout << "Error found at position: " << syndrome << endl;
    }
    cout << "Rectified: " << rectified_message << endl;
    cout << "Match with original: " << match << endl;
    
    return 0;
}