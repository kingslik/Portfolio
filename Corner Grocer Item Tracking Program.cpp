//Alex Wyatt
// 2-21-2026

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;


 //  ItemTracker class Handles reading purchase records, calculating frequencies, and displaying data in various formats.
class ItemTracker {
private:
    map<string, int> itemFrequencies;

    // Helper that loads data from the input file into the map
    void loadData(string fileName) {
        ifstream inputFile(fileName);
        string itemName;
        if (inputFile.is_open()) {
            while (inputFile >> itemName) {
                itemFrequencies[itemName]++;
            }
            inputFile.close();
        }
        else {
            cerr << "Error: Could not open input file." << endl;
        }
    }

    // Creates frequency.dat for backup
    void createBackupFile() {
        ofstream outFile("frequency.dat");
        if (outFile.is_open()) {
            for (auto const& [item, count] : itemFrequencies) {
                outFile << item << " " << count << endl;
            }
            outFile.close();
        }
    }

public:
    // Constructor initializes data and creates the backup
    ItemTracker(string fileName) {
        loadData(fileName);
        createBackupFile();
    }

    // Option 1 Search for specific item frequency
    void searchItem() {
        string searchTerm;
        cout << "Enter the item name to search: ";
        cin >> searchTerm;
        if (itemFrequencies.count(searchTerm)) {
            cout << searchTerm << " appears " << itemFrequencies[searchTerm] << " times." << endl;
        }
        else {
            cout << "Item not found." << endl;
        }
    }

    // Option 2 Print all frequencies
    void printAllFrequencies() {
        for (auto const& [item, count] : itemFrequencies) {
            cout << item << " " << count << endl;
        }
    }

    // Option 3 Print histogram
    void printHistogram() {
        for (auto const& [item, count] : itemFrequencies) {
            cout << left << setw(12) << item << " ";
            for (int i = 0; i < count; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

void DisplayMenu() {
    cout << "\n----- Corner Grocer Menu -----" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print frequency histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // Initialize the tracker with the input file 
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");
    int choice = 0;

    while (choice != 4) {
        DisplayMenu();
        // Basic input validation for menu selection
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number (1-4)." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        switch (choice) {
        case 1: tracker.searchItem(); break;
        case 2: tracker.printAllFrequencies(); break;
        case 3: tracker.printHistogram(); break;
        case 4: cout << "Exiting program..." << endl; break;
        default: cout << "Invalid selection. Try again." << endl;
        }
    }
    return 0;
}