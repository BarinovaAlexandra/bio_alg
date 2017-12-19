#include <fstream>
#include <iostream>

using std::string;

bool next_vertex(string *mas, int &level, int l) {
    if (level < l) {
        level++;
    }
    else {
        for (int j = level; (j > 0) && ((*mas)[j-1] == 'T'); j--) {
            (*mas)[level-1] = 'A';
            level--;
        }
        if (level == 0)
            return 0;
        if ((*mas)[level-1] != 'T') {
            if ((*mas)[level-1] == 'A') {
                (*mas)[level-1] = 'C';
            }
            else if ((*mas)[level-1] == 'C') {
                (*mas)[level-1] = 'G';
            }
            else if ((*mas)[level-1] == 'G') {
                (*mas)[level-1] = 'T';
            }
        }
    }
    return 1;
}

bool by_pass(string *mas, int &level) {
    for (int j = level; (j > 0) && (((*mas)[j-1]) == 'T'); j--) {
        (*mas)[level-1] = 'A';
        level--;
    }
    if (level == 0) {
        return 0;
    }
    if ((*mas)[level-1] != 'T') {
        if ((*mas)[level-1] == 'A') {
            (*mas)[level-1] = 'C';
        }
        else if ((*mas)[level-1] == 'C') {
            (*mas)[level-1] = 'G';
        }
        else if ((*mas)[level-1] == 'G') {
            (*mas)[level-1] = 'T';
        }
    }
    return 1;
}

int XEM(string pat, string pat2, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (pat[i] != pat2[i]) {
            res++;
        }
    }
    return res;
}


void median_str(int l, string* mas, int t, string* res) {
    string pattern;
    int total_dist = 0;
    for (int i = 0; i < l; i++) {
        pattern.append("A");
    }
    int n = mas[0].size();
    int best_dist = l*t;
    int i = 1;
    bool flag = 1;
    while (flag) {
        if (i <= l-1) {
            int min_rast = i;
            total_dist = 0;
            for (int k = 0; k < t; k++) {
                for (int j = 0; j < n - l + 1; j++) {
                    int rast = XEM(pattern, mas[k].substr(j, i), i);
                    if (min_rast > rast) {
                        min_rast = rast;
                    }
                }
                total_dist += min_rast;
                min_rast = i;
            }

            if (total_dist > best_dist) {
                flag = by_pass(&pattern, i);
            }
            else {
                flag = next_vertex(&pattern, i, l);
            }
        }
        else {
            int min_rast = i;
            total_dist = 0;
            for (int k = 0; k < t; k++) {
                for (int j = 0; j < n - l + 1; j++) {
                    int rast = XEM(pattern, mas[k].substr(j, i), i);
                    if (min_rast >= rast) {
                        min_rast = rast;
                    }
                }
                total_dist += min_rast;
                min_rast = i;
            }
            if (total_dist < best_dist) {
                *res = pattern;
                best_dist = total_dist;
            }
            flag = next_vertex(&pattern, i, l);
        }
    }
}


int main() {
    string input_string;
    int l;

    std::ifstream file;
    file.open("input.txt", std::ios::out);
    file >> input_string;
    l = input_string[0] - '0';
    string* buffer = new string[1000];
    int i = 0;
    while (!file.eof()) {
        file >> buffer[i];
        i++;
    }
    string* pat = new string[i];
    for (int j = 0; j < i; j++) {
        pat[j] = buffer[j];
    }
    delete[] buffer;
    string res;
    file.close();
    median_str(l, pat, i, &res);
    std::ofstream fout;
    fout.open("output.txt");
    fout << res;
    fout.close();
    delete[] pat;
    return 0;
}