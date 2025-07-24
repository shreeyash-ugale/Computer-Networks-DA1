#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string line;
    string received_message;
    
    ifstream file("File1.txt");
    for(int i = 0; i < 4; i++) {
        getline(file, line);
        if(i == 3) {
            received_message = line.substr(line.find(": ") + 2); // read File1
        }
    }
    file.close();
    
    // Check for corruption using parity
    int count = 0;
    for(int i = 0; i < received_message.length(); i++) {
        if(received_message[i] == '1') {
            count++;
        }
    }
    
    string is_corrupted = (count % 2 == 0) ? "No" : "Yes";
    
    // Write to File2
    ofstream outfile("File2.txt");
    outfile << "Message received: " << received_message << endl;
    outfile << "Is message corrupted: " << is_corrupted << endl;
    outfile.close();
    
    cout << "Receiver: Message processed!" << endl;
    cout << "Received: " << received_message << endl;
    cout << "Corrupted: " << is_corrupted << endl;
    
    return 0;
}