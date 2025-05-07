#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

#define MAX 100

class OBST {
    float e[MAX][MAX];     // Expected cost table
    float w[MAX][MAX];     // Weight table
    int root[MAX][MAX];    // Root index table

public:
    void construct(const vector<float>& p, const vector<float>& q, int n) {
        for (int i = 0; i <= n; i++) {
            e[i][i] = q[i];
            w[i][i] = q[i];
        }

        for (int l = 1; l <= n; l++) { // l = subtree size
            for (int i = 0; i <= n - l; i++) {
                int j = i + l;
                e[i][j] = INT32_MAX;
                w[i][j] = w[i][j - 1] + p[j - 1] + q[j];

                for (int r = i + 1; r <= j; r++) {
                    float cost = e[i][r - 1] + e[r][j] + w[i][j];
                    if (cost < e[i][j]) {
                        e[i][j] = cost;
                        root[i][j] = r;
                    }
                }
            }
        }

        cout << fixed << setprecision(2);
        cout << "\nMinimum expected cost: " << e[0][n] << endl;
        printRootTable(n);
    }

    void printRootTable(int n) {
        cout << "\nRoot Table (root[i][j] = root of subtree [i+1...j]):\n";
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i < j)
                    cout << root[i][j] << "\t";
                else
                    cout << "-\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<float> p(n), q(n + 1);

    cout << "Enter successful search probabilities p[0.." << n - 1 << "]:\n";
    for (int i = 0; i < n; i++)
        cin >> p[i];

    cout << "Enter unsuccessful search probabilities q[0.." << n << "]:\n";
    for (int i = 0; i <= n; i++)
        cin >> q[i];

    OBST tree;
    tree.construct(p, q, n);

    return 0;
}
