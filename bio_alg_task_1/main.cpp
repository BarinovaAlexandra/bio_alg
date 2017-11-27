#include <fstream>
//#include <string>

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

int main() {
    string inputString;
    string requiredPattern;

    std::ifstream inputFile;
    inputFile.open("input.txt", std::ios::out);
    inputFile >> inputString;
    inputFile >> requiredPattern;
    inputFile.close();

    int sum = patternCoincidenceCount(inputString, requiredPattern);

    std::ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << sum;
    outputFile.close();

    return 0;
}