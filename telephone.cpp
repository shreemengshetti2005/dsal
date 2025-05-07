#include <iostream>
using namespace std;

class HashTable {
public:
    long long* tableWithoutReplace;
    long long* tableWithReplace;
    int tableSize;

    HashTable(int size) {
        tableSize = size;
        tableWithoutReplace = new long long[size];
        tableWithReplace    = new long long[size];
        for (int i = 0; i < size; i++) {
            tableWithoutReplace[i] = -1;
            tableWithReplace[i]    = -1;
        }
    }

    int getIndex(long long key) {
        return key % tableSize;
    }

    void insertWithoutReplacement(long long key) {
        int idx = getIndex(key);
        while (tableWithoutReplace[idx] != -1)
            idx = (idx + 1) % tableSize;
        tableWithoutReplace[idx] = key;
    }

    void insertWithReplacement(long long key) {
        int idx = getIndex(key);
        long long cur = key;
        while (tableWithReplace[idx] != -1) {
            long long occupant = tableWithReplace[idx];
            if (getIndex(occupant) != idx) {
                tableWithReplace[idx] = cur;
                cur = occupant;
            }
            idx = (idx + 1) % tableSize;
        }
        tableWithReplace[idx] = cur;
    }

    int searchWithoutReplacement(long long key, int &comps) {
        int idx = getIndex(key);
        comps = 1;
        while (tableWithoutReplace[idx] != -1) {
            if (tableWithoutReplace[idx] == key)
                return idx;
            idx = (idx + 1) % tableSize;
            comps++;
            if (comps > tableSize) break;
        }
        return -1;
    }

    int searchWithReplacement(long long key, int &comps) {
        int idx = getIndex(key);
        comps = 1;
        while (tableWithReplace[idx] != -1) {
            if (tableWithReplace[idx] == key)
                return idx;
            idx = (idx + 1) % tableSize;
            comps++;
            if (comps > tableSize) break;
        }
        return -1;
    }
};

int main() {
    HashTable H(10);

    long long phoneNumbers[] = {
        9876545331, 9823453081, 9988773042,
        9345673065, 9712341043, 9223457026,
        9765430019, 9834567021, 9345678099, 9087652087
    };

    for (long long x : phoneNumbers) {
        H.insertWithoutReplacement(x);
        H.insertWithReplacement(x);
    }

    long long toFind = 9876545331;
    int compsWithout, compsWith;

    int posWithout = H.searchWithoutReplacement(toFind, compsWithout);
    cout << "Without Replacement: ";
    if (posWithout != -1)
        cout << "Found " << toFind << " at index " << posWithout;
    else
        cout << toFind << " not found";
    cout << " (Comparisons = " << compsWithout << ")\n";

    int posWith = H.searchWithReplacement(toFind, compsWith);
    cout << "With Replacement:    ";
    if (posWith != -1)
        cout << "Found " << toFind << " at index " << posWith;
    else
        cout << toFind << " not found";
    cout << " (Comparisons = " << compsWith << ")\n";

    return 0;
}
