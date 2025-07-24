#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Original 25-bit message
    string message = "1101010110010111001101011";
    
    // Calculate parity bit (even parity)
    int count = 0;
    for(int i = 0; i < message.length(); i++) {
        if(message[i] == '1') {
            count++;
        }
    }
    
    string parity_bit = (count % 2 == 0) ? "0" : "1";
    string message_sent = message + parity_bit;
    
    // Write to File1
    ofstream file("File1.txt");
    file << "Original 25 bits payload: " << message << endl;
    file << "Extra bit(s) for detecting errors: " << parity_bit << endl;
    file << "Message sent: " << message_sent << endl;
    file << "Message received: " << message_sent << endl;
    file.close();
    
    cout << "Sender: Message sent successfully!" << endl;
    cout << "Original message: " << message << endl;
    cout << "Parity bit: " << parity_bit << endl;
    cout << "Message with parity: " << message_sent << endl;
    
    return 0;
}