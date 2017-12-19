#include <fstream>
#include <iostream>

using std::string;

void next_vertex(int t, int *mas, int &level, int l, int n) {
    if (level < t) {
        level = level + 1;
    } else {
        level = level -1;
        for (int j = t - 1; (j >= 0) && (mas[j] == n - l ); j--) {
            mas[level] = 0;
            level = level - 1;
        }
        if (mas[level] < n - l) {
            mas[level]++;
        }
    }
}

void by_pass(int *mas, int &level, int l, int n) {
    for (int j = level; (j >= 0) && (mas[j] == n - l ); j--) {
        mas[level] = 0;
        level = level - 1;
    }
    if (mas[level] < n- l) {
        mas[level]++;
    }
}

int score_motiv(string *mas, int t, int l) {
    int* max_ACGT = new int[l];
    int score = 0, A, C, G, T;

    for (int i = 0; i < l; i++) {
        A = 0;
        C = 0;
        G = 0;
        T = 0;
        for (int j = 0; j < t; j++) {
            if (mas[j][i] == 'A') {
                A++;
            }
            else if (mas[j][i] == 'C') {
                C++;
            }
            else if (mas[j][i] == 'G') {
                G++;
            }
            else if (mas[j][i] == 'T') {
                T++;
            }
        }
        max_ACGT[i] = A;
        if (max_ACGT[i] < C) {
            max_ACGT[i] = C;
        }
        else if (max_ACGT[i] < G) {
            max_ACGT[i] = G;
        }
        else if (max_ACGT[i] < T) {
            max_ACGT[i] = T;
        }
    }
    for (int i = 0; i < l; i++) {
        score += max_ACGT[i];
    }
    delete[] max_ACGT;
    return score;
}

void search_motiv(int t, int l, string* mas, string* res) {
    int* s = new int[t];
    int max_score = 0;
    int optimistic_score = 0;
    for (int i = 0; i < t; i++) {
        s[i] = 0;
    }
    int n = mas[0].size();
    string* motiv = new string[t];
    int i = 0;
    while (i >= 0) {
        if (i < t) {
            motiv[i] = (mas[i]).substr(s[i], l);
            optimistic_score = score_motiv(motiv, i + 1, l) + (t - i - 1)*l;
            if (optimistic_score < max_score) {
                by_pass(s, i, l, n);
            }
            else {
                next_vertex(t, s, i, l, n);
            }
        }
        else {
            optimistic_score = score_motiv(motiv, t, l);
            if (optimistic_score > max_score) {
                max_score = optimistic_score;
                for (int j = 0; j < t; j++) {
                    res[j] = motiv[j];
                }
            }
            next_vertex(t, s, i, l, n);
        }
    }
    delete[] motiv;
}

int main() {
    string input_string;
    int l, t;

    std::ifstream file;
    file.open("input.txt", std::ios::out);
    file >> input_string;
    l = input_string[0] - '0';
    file >> input_string;
    t = input_string[0] - '0';
    string* pattern = new string[t];

    for (int i = 0; i < t; i++) {
        file >> pattern[i];
    }
    file.close();

    string* result = new string[t];
    search_motiv(t, l, pattern, result);
    std::ofstream fout;
    fout.open("output.txt");

    for (int i = 0; i < t; i++) {
        fout << result[i];
        fout << std::endl;

    }
    fout.close();

    return 0;

}