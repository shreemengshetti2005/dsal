#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class student {
public:
    char name[50];
    char add[50];
    int rno;
    bool exists;

    student() {
        exists = false;
    }

    void scan() {
        cin.ignore();
        cout << "Enter name: ";
        cin.getline(name, 50);
        cout << "Enter address: ";
        cin.getline(add, 50);
        cout << "Enter roll no: ";
        cin >> rno;
        exists = true;
    }

    void display() const {
        cout << "Name: " << name << ", Address: " << add << ", Roll No: " << rno << endl;
    }
};

class filehandler {
public:
    string filename;

    filehandler(const char* fname) {
        filename = fname;
        // create file if it doesn't exist
        fstream f(filename, ios::binary | ios::app);
        f.close();
    }

    void addrec() {
        int ind;
        cout << "Enter record number: ";
        cin >> ind;

        student s;
        s.scan();

        fstream fp(filename, ios::binary | ios::in | ios::out);
        if (!fp) {
            cout << "Error opening file!" << endl;
            return;
        }

        fp.seekp(ind * sizeof(student), ios::beg);
        fp.write(reinterpret_cast<char*>(&s), sizeof(s));
        fp.close();
    }

    void displayy() {
        int ind;
        cout << "Enter record number: ";
        cin >> ind;

        ifstream fp(filename, ios::binary);
        if (!fp) {
            cout << "Error opening file!" << endl;
            return;
        }

        student s;
        fp.seekg(ind * sizeof(student), ios::beg);

        if (!fp.read(reinterpret_cast<char*>(&s), sizeof(s)) || !s.exists) {
            cout << "Record doesn't exist!" << endl;
        } else {
            s.display();
        }

        fp.close();
    }

    void deleterec() {
        int ind;
        cout << "Enter record number: ";
        cin >> ind;

        fstream fp(filename, ios::binary | ios::in | ios::out);
        if (!fp) {
            cout << "Error opening file!" << endl;
            return;
        }

        student s;
        fp.seekg(ind * sizeof(student), ios::beg);
        if (!fp.read(reinterpret_cast<char*>(&s), sizeof(s))) {
            cout << "Record not found!" << endl;
            fp.close();
            return;
        }

        s.exists = false;
        fp.seekp(ind * sizeof(student), ios::beg);
        fp.write(reinterpret_cast<char*>(&s), sizeof(s));
        fp.close();
    }
};

int main() {
    filehandler f("file.txt");

    char ch = 'y';
    while (ch == 'y' || ch == 'Y') {
        int n;
        cout << "\nEnter 1 to Add, 2 to Display, 3 to Delete: ";
        cin >> n;

        switch (n) {
            case 1:
                f.addrec();
                break;
            case 2:
                f.displayy();
                break;
            case 3:
                f.deleterec();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "Continue? (y/n): ";
        cin >> ch;
    }

    cout << "Code exited successfully." << endl;
    return 0;
}
