#include <fstream>
#include <iostream>

using std::string;
int MAX = 2147483647;

int DPChange(int M, int* c, int d) {
    int* bestNumCoins = new int [M + 1];
    bestNumCoins[0] = 0;

    for (int i = 1; i <= M; i++) {
        bestNumCoins[i] = MAX;

        for (int j = 0; j < d; j++) {
            if (i >= c[j]) {
                if (bestNumCoins[i - c[j]] + 1 < bestNumCoins[i]) {
                    bestNumCoins[i] = bestNumCoins[i - c[j]] + 1;
                }
            }
        }
    }
    return bestNumCoins[M];
}

int main() {
    int M;

    std::ifstream file;
    file.open("input.txt", std::ios::out);
    file >> M;
    string temp;

    file >> temp;

    int j = 0;
    int k = 1;
    int n = temp.length();
    int *c = new int[n];

    for (int i = 0; i < n; ++i){
        c[j] = 0;
        while ((temp[i] != ',') && (i < n)) {
            c[j] *= k;
            c[j] += (temp[i] - '0');
            k *= 10;
            i++;
        }
        j++;
        k = 1;
    }

    int res = DPChange(M, c, j);

    file.close();
    std::ofstream fout;
    fout.open("output.txt");
    fout << res;
    fout.close();

    delete[] c;

    return 0;
}