#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <utility>

using namespace std;

int find_min(vector<int> v) {
    vector<int> t(v);
    replace(t.begin(), t.end(), 0, INT_MAX);
    sort(t.begin(), t.end());
    if (t[0] == INT_MAX || t[1] == INT_MAX) {
        return 0;
    }
    return t[1] - t[0];
}

void transpose(vector<vector<int> > &b)
{
    vector<vector<int> > trans_vec(b[0].size(), vector<int>());

    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }
    b = trans_vec;
}

void out(vector<vector<int>> v, int y, int x, vector<int> storage, vector<int> need, int hy, int hx,
    vector<int> right = vector<int>(), vector<int> down = vector<int>()) {
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
            cout << setw(4) << v[i][j] << " ";
        }
        cout << setw(2) << " | " << setw(3) << storage[i];
        if (i == hy) cout << setw(4) << "+"; else cout << setw(4) << " ";
        // diff
        if (right.size() > 0) {
            cout << setw(2) << right[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int j = 0; j < x; j++) {
        cout << setw(4) << need[j] << " ";
    }
    cout << endl;
    if (hx != -1) {
        for (int i = 0; i < hx; i++) {
            cout << setw(4) << " " << " ";
        }
        cout << setw(4) << "+" << endl;
    } else {
        cout << endl;
    }
    if (down.size() > 0) {
        for (int j = 0; j < down.size(); j++) {
            cout << setw(4) << down[j] << " ";
        }
    }
    cout << endl;
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
    
    // sum compare
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

    out(m, y, x, storage, need, -1, -1);

    vector<int> right;
    vector<int> down;

    // algh
    vector<int> path;
    for (int z = 0; z < 2; z++) {
        cout << "---------" << endl;
        for (int i = 0; i < y; i++) {
            right.push_back(find_min(m[i]));
        }
        vector<vector<int>> tmp(m);
        transpose(tmp);
        for (int i = 0; i < x; i++) {
            down.push_back(find_min(tmp[i]));
        }
        int ma = 0, im = -1, rd = -1;
        for (int i = 0; i < y; i++) {
            if (right[i] > ma) {
                ma = right[i];
                im = i;
                rd = 0;
            }
        }
        for (int i = 0; i < x; i++) {
            if (down[i] > ma) {
                ma = down[i];
                im = i;
                rd = 1;
            }
        }
        // cout << "(" << ma << " " << im << " " << rd << " " << endl;
        if (rd == 0) {
            out(m, y, x, storage, need, im, -1, right, down);
        } else {
            out(m, y, x, storage, need, -1, im, right, down);
        }

        int row, col;
        int elem;
        if (rd == 0) {
            int ind = 0, mm = INT_MAX;
            for (int i = 0; i < x; i++) {
                if (m[im][i] < mm) {
                    mm = m[im][i];
                    ind = i;
                }
            }
            row = im;
            col = ind;
            elem = mm;  
        } else {
            // TODO
            cout << "not implemented yet :(" << endl;
            break;
        }
        cout << col << "/" << row << endl;
        int tov;
        if (storage[row] < need[col]) {
            tov = storage[row];
            vector<int> zv(x, 0);
            m[im] = zv;
        } else if (storage[row] > need[col]) {
            tov = need[col];
            for (int i = 0; i < y; i++) {
                m[i][col] = 0;
            }
        } else {
            // ??? вырожденный план ???
        }


        cout << elem << " * " << tov << " = " << elem * tov << endl;
        path.push_back(tov);
        right.clear();
        down.clear();
    }

    return 0;
}