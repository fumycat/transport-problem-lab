#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>

using namespace std;

void out(vector<vector<int>> v, int y, int x, vector<int> storage, vector<int> need, int hy, int hx) {
    if (hy - 1 > y) {
        cout << "err" << endl;
        hy = -1;
    }
    if (hx - 1 > x) {
        cout << "err" << endl;
        hx = -1;
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            cout << setw(3) << v[i][j] << " ";
        }
        cout << "   " << storage[i];
        if (i == hy - 1) cout << setw(3) << "+";
        cout << endl;
    }
    cout << endl;
    for (int j = 0; j < x; j++) {
        cout << setw(3) << need[j] << " ";
    }
    cout << endl;
    if (hx != -1) {
        for (int i = 0; i < hx - 1; i++) {
            cout << setw(3) << " " << " ";
        }
        cout << setw(3) << "+" << endl;
    }
}

int main() {
    int y = 1, x = 1;
    vector<vector<int>> m;
    vector<int> storage;
    vector<int> need;

    ifstream input("input.txt");
    input >> y >> x;
    
    for (int i = 0; i < y; i++) {
        vector<int> v;
        for (int j = 0; j < x; j++) {
            int t;
            input >> t;
            v.push_back(t);
        }
        m.push_back(v);
    }
    for (int _ = 0; _ < y; _++) {
        int t;
        input >> t;
        storage.push_back(t);
    }
    for (int _ = 0; _ < x; _++) {
        int t;
        input >> t;
        need.push_back(t);
    }

    out(m, y, x, storage, need, -1, -1);
    
    cout << "\nSum(a):\n";
    for (int i = 0; i < y - 1; i++) cout << storage[i] << " + ";
    int sumA = accumulate(storage.begin(), storage.end(), 0);
    cout << storage[y - 1] << " = " << sumA << endl;

    cout << "\nSum(b):\n";
    for (int i = 0; i < x - 1; i++) cout << need[i] << " + ";
    int sumB = accumulate(need.begin(), need.end(), 0);
    cout << need[x - 1] << " = " << sumB << endl << endl;

    if (sumA == sumB) {
        cout << "sum(a) = sum(b) OK\n";
    } else if (sumA < sumB) {
        cout << "sum(a) < sum(b) adding row\n";
        cout << sumB << " - " << sumA << " = " << sumB - sumA << endl << endl;
        y++;
        vector<int> t(x, 0);
        m.push_back(t);
        storage.push_back(sumB - sumA);
    } else if (sumA > sumB) {
        cout << "sum(a) > sum(b) adding column\n";
        cout << sumA << " - " << sumB << " = " << sumA - sumB << endl << endl;
        x++;
        for (int i = 0; i < y; i++) {
            m[i].push_back(0);
        }
        need.push_back(sumA - sumB);
    }

    out(m, y, x, storage, need, 3, 3);

    

    return 0;
}