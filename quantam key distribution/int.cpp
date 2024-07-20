#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

// Quantum Key Distribution (QKD) simulation in C++

// Function to generate random bases
void generate_bases(vector<int> &bases, int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < n; ++i) {
        bases.push_back(dis(gen));
    }
}

// Function to sift the keys based on matching bases
void sift_keys(const vector<int> &alice_bases, const vector<int> &bob_bases, 
               const vector<int> &alice_bits, const vector<int> &bob_bits, 
               vector<int> &alice_key, vector<int> &bob_key, int n) {
    for (int i = 0; i < n; ++i) {
        if (alice_bases[i] == bob_bases[i]) {
            alice_key.push_back(alice_bits[i]);
            bob_key.push_back(bob_bits[i]);
        }
    }
}

// Main function to simulate BB84 protocol
int main() {
    srand(time(0)); // Seed random number generator

    int n;
    cout << "Enter the number of qubits: ";
    cin >> n; // Number of qubits

    vector<int> alice_bases, alice_bits;
    vector<int> bob_bases, bob_bits;
    vector<int> alice_key, bob_key;

    // Generate Alice's and Bob's bases
    generate_bases(alice_bases, n);
    generate_bases(bob_bases, n);

    // Take Alice's bits from user
    cout << "Enter Alice's bits (0 or 1) for " << n << " qubits: ";
    for (int i = 0; i < n; ++i) {
        int bit;
        cin >> bit;
        alice_bits.push_back(bit);
    }

    // Take Bob's bits from user
    cout << "Enter Bob's bits (0 or 1) for " << n << " qubits: ";
    for (int i = 0; i < n; ++i) {
        int bit;
        cin >> bit;
        bob_bits.push_back(bit);
    }

    // Sift the keys
    sift_keys(alice_bases, bob_bases, alice_bits, bob_bits, alice_key, bob_key, n);

    // Output the results
    cout << "Alice's key: ";
    for (int bit : alice_key) {
        cout << bit;
    }
    cout << endl;

    cout << "Bob's key:   ";
    for (int bit : bob_key) {
        cout << bit;
    }
    cout << endl;

    // Check key agreement
    if (alice_key == bob_key) {
        cout << "Keys match!" << endl;
    } else {
        cout << "Keys do not match!" << endl;
    }

    return 0;
}

