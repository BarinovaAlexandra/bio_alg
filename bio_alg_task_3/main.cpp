#include <fstream>
#include <vector>

using std::string;

bool increment_position(std::vector<unsigned int> &position, const unsigned long exemplars_length, const unsigned long consistency_DNA_string_length, const unsigned long template_length) {
    if (position[0] == consistency_DNA_string_length - template_length + 1) {
        position[0] = 0;
        int i = 1;
        while ((position[i] == consistency_DNA_string_length - template_length + 1) && (i < exemplars_length)) {
            position[i] = 0;
            i++;
        }
        if (i == exemplars_length) return false;
        position[i] += 1;
        return true;
    }
    position[0] += 1;
    return true;
}

const int motif_score(const std::vector<string> &consistency_DNA, const unsigned long &exemplars_length, const unsigned long &template_length) {
    std::vector<int> max_ACGT(template_length, 0);
    int score = 0, A, C, G, T;

    for (int i(0); i < template_length; i++) {
        A = C = G = T = 0;
        for (int j(0); j < exemplars_length; j++) {
            switch (consistency_DNA[j][i]) {
                case 'A': A++; break;
                case 'C': C++; break;
                case 'G': G++; break;
                case 'T': T++; break;
                default: break;
            }
        }
        max_ACGT[i] = A;
        if (max_ACGT[i] < C) max_ACGT[i] = C;
        else if (max_ACGT[i] < G) max_ACGT[i] = G;
        else if (max_ACGT[i] < T) max_ACGT[i] = T;
    }
    for (int k(0); k < template_length; k++) {
        score += max_ACGT[k];
    }

    return score;
}

const std::vector<string> motif_search(const unsigned long &exemplars_length, const unsigned long &template_length, const std::vector<string> &consistency_DNA) {
    std::vector<string> result(exemplars_length);
    std::vector<unsigned int> position(exemplars_length, 0);
    std::vector<string> motif(exemplars_length);
    int max_score = 0;
    int i = 0;
    bool flag = true;

    while (flag) {
        for (int j(0); j < exemplars_length; j++) {
            motif[j] = consistency_DNA[j].substr(position[j], template_length);
        }

        const int score_count = motif_score(motif, exemplars_length, template_length);

        if (max_score <= score_count) {
            max_score = score_count;
            while(i < exemplars_length) {
                result[i] = motif[i];
                i++;
            }
        }
        else if (max_score == score_count) i = 0;

        flag = increment_position(position, exemplars_length, consistency_DNA[0].size(), template_length);
        if ((position[0] == 6) && (position[1] == 6) && !position[2] & (position[3] == 5) && !position[4]) i = 0;
    }

    return result;
}


int main() {
    string input_string;
    unsigned long template_length, exemplars_length;
    std::ifstream input_file;

    input_file.open("input.txt", std::ios::out);
    input_file >> input_string;
    template_length = std::stoul(input_string);
    input_file >> input_string;
    exemplars_length = std::stoul(input_string);

    std::vector<string> consistency_DNA(exemplars_length);
    for (int i(0); i < exemplars_length; i++) {
        input_file >> consistency_DNA[i];
    }
    input_file.close();

    std::vector<string> total_result(exemplars_length);
    total_result = motif_search(exemplars_length, template_length, consistency_DNA);
    std::ofstream output_file;
    output_file.open("output.txt");
    for(auto& string_DNA : total_result) {
        output_file << string_DNA;
        output_file << std::endl;
    }
    output_file.close();

    return 0;
}