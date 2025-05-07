#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class student {
public:
    int rn, div;
    string name, address;

    void getdata() {
        cout << "Enter name, roll no, division, address: ";
        cin >> name >> rn >> div >> address;
    }

    void displaydata() {
        cout << name << " " << rn << " " << div << " " << address << endl;
    }
};

class fl {
public:
    string fname;
    student s;
    fstream file;

    fl() {
        cout << "Enter file name: ";
        cin >> fname;
    }

    void addrecord() {
        file.open(fname, ios::app);
        s.getdata();
        file << s.name << " " << s.rn << " " << s.div << " " << s.address << endl;
       
        file.close();
    }

    void display() {
        file.open(fname, ios::in);
        while (file >> s.name >> s.rn >> s.div >> s.address) {
            s.displaydata();
        }
        file.close();
    }

    void deleterecord(int roll) {
        fstream temp;
        temp.open("temp1.txt", ios::out);
        file.open(fname, ios::in);

        while (file >> s.name >> s.rn >> s.div >> s.address) {
            if (s.rn != roll) {
                temp << s.name << " " << s.rn << " " << s.div << " " << s.address << endl;
            }
        }

        file.close();
        temp.close();
        remove(fname.c_str());
        rename("temp1.txt", fname.c_str());
    }
};

int main() {
    fl filew;
    int choice = 0;
int roll;

while (choice != 4) {
    cout << "\nMENU:\n";
    cout << "1. Add Record\n";
    cout << "2. Display Records\n";
    cout << "3. Delete Record\n";
    cout << "4. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        filew.addrecord();
    }
    else if (choice == 2) {
        filew.display();
    }
    else if (choice == 3) {
        cout << "Enter roll number to delete: ";
        cin >> roll;
        filew.deleterecord(roll);
    }
    else if (choice == 4) {
        cout << "Exiting...\n";
        // loop will terminate
    }
    else {
        cout << "Invalid choice!\n";
    }
}

}
