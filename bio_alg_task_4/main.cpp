#include <fstream>
#include <vector>

using std::string;

bool increment_pattern(string *pattern) {
    const unsigned long pattern_length = (*pattern).size();
    if ((*pattern)[0] == 'T') {
        (*pattern)[0] = 'A';
        int i = 1;
        while (((*pattern)[i] == 'T') && (i < pattern_length)) {
            (*pattern)[i] = 'A';
            i++;
        }

        if (i == pattern_length) return false;

        if ((*pattern)[i] == 'A') (*pattern)[i] = 'C';

        else if ((*pattern)[i] == 'C') (*pattern)[i] = 'G';

        else if ((*pattern)[i] == 'G') (*pattern)[i] = 'T';

        return true;
    }

    if ((*pattern)[0] == 'A') {
        (*pattern)[0] = 'C';
    }
    else if ((*pattern)[0] == 'C') {
        (*pattern)[0] = 'G';
    }
    else if ((*pattern)[0] == 'G') {
        (*pattern)[0] = 'T';
    }

    return true;
}

const unsigned long XEM(string pattern, string pattern2, const unsigned long &template_length) {
    unsigned long res = 0;

    for (int i = 0; i < template_length; i++) {
        if (pattern[i] != pattern2[i]) res++;
    }

    return res;
}


const string median_string_finder(const unsigned long &template_length, const std::vector<string> &consistency_DNA, const int &length) {
    string result;
    string pattern;
    unsigned long total_dist = 0;

    for (int i = 0; i < template_length; i++) {
        pattern.append("A");
    }

    const unsigned long n = consistency_DNA[0].size();
    unsigned long best_dist = template_length * length;
    bool flag = true;

    while (flag) {
        unsigned long distance = 0;
        unsigned long min_distance = template_length;

        for (int i(0); i < length; i++) {
            for (unsigned long j(0); j < n - template_length + 1; j++) {
                distance = XEM(pattern, consistency_DNA[i].substr(j, template_length), template_length);
                if (min_distance >= distance) {
                    min_distance = distance;
                }
            }
            total_dist += min_distance;
            min_distance = template_length;
        }
        if (best_dist >= total_dist) {
            best_dist = total_dist;
            result = pattern;
        }
        total_dist = 0;
        flag = increment_pattern(&pattern);
    }

    return result;
}

int main() {
    string input_string;
    std::vector<string> consistency_DNA;
    std::ifstream input_file;

    input_file.open("input.txt", std::ios::out);
    input_file >> input_string;
    const unsigned long template_length = std::stoul(input_string);

    string buffer;
    int i = 0;
    while (!input_file.eof()) {
        input_file >> buffer;
        consistency_DNA.push_back(buffer);
        i++;
    }
    input_file.close();

    const string total_result = median_string_finder(template_length, consistency_DNA, i);

    std::ofstream output_file;
    output_file.open("output.txt");
    output_file << total_result;
    output_file.close();

    return 0;
}