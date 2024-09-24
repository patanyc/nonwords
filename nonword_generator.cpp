//nonword generator by the Pataphysical Society of New York
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>

void generateCombinations(std::string prefix, int k, std::vector<std::string>& result) {
    if (k == 0) {
        result.push_back(prefix);
        return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        generateCombinations(prefix + c, k - 1, result);
    }
}

std::unordered_set<std::string> loadDictionary(const std::string& filename) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        if (word.length() == 5) {
            dictionary.insert(word);
        }
    }
    return dictionary;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::unordered_set<std::string> dictionary = loadDictionary("words.txt");
    std::cout << "Dictionary loaded with " << dictionary.size() << " 5-letter words." << std::endl;

    std::vector<std::string> combinations;
    generateCombinations("", 5, combinations);
    std::cout << "Generated " << combinations.size() << " combinations." << std::endl;

    std::ofstream outFile("nonwords.txt");
    int nonWordCount = 0;
    for (const auto& word : combinations) {
        if (dictionary.find(word) == dictionary.end()) {
            outFile << word << std::endl;
            nonWordCount++;
        }
    }
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Found " << nonWordCount << " non-words." << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds." << std::endl;

    return 0;
}