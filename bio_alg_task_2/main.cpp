#include <fstream>

using std::string;

int patternCoincidenceCount(const string& inputString, const string& requiredPattern) {
    int sum = 0;

    if (inputString.empty() || requiredPattern.empty()) return 0;

    unsigned long int N = inputString.size();
    unsigned long int k = requiredPattern.size();

    for (unsigned long int i(0); i < N - k + 1; i++) {
        if (inputString.substr(i, k) == requiredPattern) {
            sum += 1;
        }
    }

    return sum;
}

bool commonContainWords(const string& inputString, unsigned long int k, string* commonSting) {
    if (inputString.empty() || k == 0) return false;

    unsigned long int N = inputString.size();
    auto* summaryCount = new int[N - k + 1];

    for (unsigned long int i = 0; i < N - k + 1; i++) {
        summaryCount[i] = patternCoincidenceCount(inputString, inputString.substr(i, k));
    }

    int maxCount = summaryCount[0];

    for (int j(1); j < N - k + 1; j++) {
        if (summaryCount[j] > maxCount) {
            maxCount = summaryCount[j];
        }
    }
    for (unsigned long int j(0); j < N - k + 1; j++) {
        if (summaryCount[j] == maxCount && !patternCoincidenceCount(*commonSting, inputString.substr(j, k))) {
            *commonSting += inputString.substr(j, k);
            *commonSting += ' ';
        }
    }

    return true;
}

int main() {
    unsigned long int n;
    string str;
    string pat;

    std::ifstream inputFile;
    inputFile.open("input.txt", std::ios::out);
    inputFile >> str;
    inputFile >> n;
    inputFile.close();

    commonContainWords(str, n, &pat);

    std::ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << pat;
    outputFile.close();

    return 0;
}