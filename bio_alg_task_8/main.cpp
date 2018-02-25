#include <fstream>
#include <iostream>

using std::string;

int Manhatten_Tourist(int** south, int** eath, int n, int m) {
    int ** result = new int* [n + 1];

    for (int i = 0; i <= n; i++) {
        result[i] = new int[m + 1];
    }

    result[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        result[i][0] = result[i - 1][0] + south[i - 1][0];
    }

    for (int i = 1; i <= m; i++) {
        result[0][i] = result[0][i - 1] + eath[0][i - 1];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((result[i - 1][j] + south[i - 1][j]) > (result[i][j - 1] + eath[i][j - 1])) {
                result[i][j] = result[i - 1][j] + south[i - 1][j];
            }
            else {
                result[i][j] = result[i][j - 1] + eath[i][j - 1];
            }
        }
    }

    return result[n][m];
}

int main() {
    int n, m;

    std::ifstream file;
    file.open("input.txt", std::ios::out);
    file >> n;
    file >> m;

    int** south = new int*[n];
    int** eath = new int*[m+1];

    for (int i = 0; i < n; i++) {
        south[i] = new int[m + 1];
        for (int k = 0; k < m + 1; ++k) {
            file >> south[i][k];
        }
    }

    string skip;
    file >> skip;

    for (int i = 0; i < m + 1; i++) {
        eath[i] = new int[n];
        for (int k = 0; k < n ; ++k) {
            file >> eath[i][k];
        }
    }

    file.close();

    int res = Manhatten_Tourist(south, eath, n, m);

    std::ofstream fout;
    fout.open("output.txt");
    fout << res;
    fout.close();

    for (int i = 0; i < n; i++) {
        delete[] south[i];
    }
    for (int i = 0; i < m + 1; i++) {
        delete[] eath[i];
    }

    delete[] eath;
    delete[] south;

    return 0;
}