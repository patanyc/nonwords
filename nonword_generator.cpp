// nonword_generator.cpp
// Developed by the Pataphysical Society of New York - https://patanyc.org
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <iomanip>

// Adjust this constant to change the maximum word length the program can handle
const int MAX_WORD_LENGTH = 7;

// Adjust this constant to change the number of threads used for processing
// By default, it uses the number of hardware threads available
const int NUM_THREADS = std::thread::hardware_concurrency();

std::unordered_set<std::string> loadDictionary(const std::string& filename, int maxLength) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        if (word.length() <= maxLength) {
            dictionary.insert(word);
        }
    }
    return dictionary;
}

void generateAndCheckCombinations(const std::string& prefix, int k, const std::unordered_set<std::string>& dictionary, 
                                  std::ofstream& outFile, std::atomic<long long>& nonWordCount, std::mutex& fileMutex,
                                  std::atomic<long long>& progressCounter) {
    if (k == 0) {
        progressCounter++;
        if (dictionary.find(prefix) == dictionary.end()) {
            {
                std::lock_guard<std::mutex> lock(fileMutex);
                outFile << prefix << '\n';
            }
            ++nonWordCount;
        }
        return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
        generateAndCheckCombinations(prefix + c, k - 1, dictionary, outFile, nonWordCount, fileMutex, progressCounter);
    }
}

void threadFunction(int wordLength, char startChar, const std::unordered_set<std::string>& dictionary, 
                    std::ofstream& outFile, std::atomic<long long>& nonWordCount, std::mutex& fileMutex,
                    std::atomic<long long>& progressCounter) {
    std::string prefix(1, startChar);
    generateAndCheckCombinations(prefix, wordLength - 1, dictionary, outFile, nonWordCount, fileMutex, progressCounter);
}

void displayProgress(int wordLength, std::atomic<long long>& progressCounter, std::atomic<bool>& finished) {
    long long totalCombinations = std::pow(26, wordLength);
    while (!finished) {
        long long current = progressCounter.load();
        double percentage = (current * 100.0) / totalCombinations;
        std::cout << "\rProgress: " << std::fixed << std::setprecision(2) << percentage << "% (" << current << "/" << totalCombinations << ")" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void generateNonWords(int wordLength, const std::unordered_set<std::string>& dictionary, std::ofstream& outFile, bool singleFile) {
    auto start = std::chrono::high_resolution_clock::now();

    std::atomic<long long> nonWordCount(0);
    std::atomic<long long> progressCounter(0);
    std::mutex fileMutex;

    std::vector<std::thread> threads;
    std::cout << "Generating " << wordLength << "-letter non-words using " << NUM_THREADS << " threads..." << std::endl;

    std::atomic<bool> finished(false);
    std::thread progressThread(displayProgress, wordLength, std::ref(progressCounter), std::ref(finished));

    for (char c = 'a'; c <= 'z'; ++c) {
        threads.emplace_back(threadFunction, wordLength, c, std::ref(dictionary), std::ref(outFile), std::ref(nonWordCount), std::ref(fileMutex), std::ref(progressCounter));
        if (threads.size() == NUM_THREADS || c == 'z') {
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }
    }

    finished = true;
    progressThread.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nFound " << nonWordCount << " non-words of length " << wordLength << "." << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds." << std::endl;

    if (!singleFile) {
        outFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <min_length> <max_length> [single_file]" << std::endl;
        return 1;
    }

    // Parse command-line arguments
    // Adjust these values when running the program to change the range of word lengths
    int minLength = std::stoi(argv[1]);  // Minimum word length to generate
    int maxLength = std::stoi(argv[2]);  // Maximum word length to generate

    // Determine if output should be written to a single file
    // Add 'single_file' as the third argument when running the program to enable this option
    bool singleFile = (argc == 4 && std::string(argv[3]) == "single_file");

    // Validate input range
    if (minLength < 1 || maxLength > MAX_WORD_LENGTH || minLength > maxLength) {
        std::cerr << "Invalid length range. Must be between 1 and " << MAX_WORD_LENGTH << "." << std::endl;
        return 1;
    }

    // Load dictionary
    // Ensure your dictionary file is named "words.txt" and is in the same directory as the executable
    std::unordered_set<std::string> dictionary = loadDictionary("words.txt", maxLength);
    std::cout << "Dictionary loaded with " << dictionary.size() << " words up to " << maxLength << " letters." << std::endl;

    std::ofstream outFile;
    if (singleFile) {
        // If single file output is selected, all results will be written to "nonwords_all.txt"
        outFile.open("nonwords_all.txt", std::ios::out | std::ios::binary);
    }

    // Generate non-words for each length in the specified range
    for (int length = minLength; length <= maxLength; ++length) {
        if (!singleFile) {
            // If separate files are used, each length will have its own output file
            outFile.open("nonwords_" + std::to_string(length) + "letter.txt", std::ios::out | std::ios::binary);
        }
        generateNonWords(length, dictionary, outFile, singleFile);
    }

    if (singleFile) {
        outFile.close();
    }

    return 0;
}
// Never not except when so; if thus, not or, but and! &&&
