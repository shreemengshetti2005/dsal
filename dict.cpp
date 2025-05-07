#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Dictionary {
    public:
    int tableSize;
    vector<pair<string, string>>* table;

    int hash(string key) {
        int sum = 0;
        for (int i = 0; i < key.length(); i++)
            sum += key[i];
        return sum % tableSize;
    }

    Dictionary(int size) {
        tableSize = size;
        table = new vector<pair<string, string>>[tableSize];
    }

    void insert(string key, string value) {
        int idx = hash(key);
        for (int i = 0; i < table[idx].size(); i++) {
            if (table[idx][i].first == key) {
                table[idx][i].second = value;
                return;
            }
        }
        table[idx].push_back({key, value});
    }

    void search(string key) {
        int idx = hash(key);
        for (int i = 0; i < table[idx].size(); i++) {
            if (table[idx][i].first == key) {
                cout << "Found: " << table[idx][i].second << endl;
                return;
            }
        }
        cout << "Key not found.\n";
    }

    void remove(string key) {
        int idx = hash(key);
        for (int i = 0; i < table[idx].size(); i++) {
            if (table[idx][i].first == key) {
                table[idx].erase(table[idx].begin() + i);
                cout << "Deleted.\n";
                return;
            }
        }
        cout << "Key not found.\n";
    }

    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << i << ":";
            for (int j = 0; j < table[i].size(); j++) {
                cout << " [" << table[i][j].first << "->" << table[i][j].second << "]";
            }
            cout << endl;
        }
    }
};

int main() {
    Dictionary dict(10);
    int choice;
    string key, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert key-value\n";
        cout << "2. Search by key\n";
        cout << "3. Delete by key\n";
        cout << "4. Display table\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                dict.search(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;
            case 4:
                dict.display();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
