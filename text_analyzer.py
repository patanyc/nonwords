import sys
import os
from collections import Counter
from time import time

def analyze_file(file_path):
    start_time = time()
    

    file_size = os.path.getsize(file_path)
    
    word_count = 0
    word_freq = Counter()
    
    # Open file and process it
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            words = line.split()
            word_count += len(words)
            word_freq.update(words)
    
    # Calculate unique words
    unique_words = len(word_freq)
    
    end_time = time()
    runtime = end_time - start_time
    
    return word_count, unique_words, file_size, runtime
    # Quantify abstraction
def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <path_to_large_file.txt>")
        sys.exit(1)
    
    file_path = sys.argv[1]
    # Print non-exceptions
    print(f"Analyzing file: {file_path}")
    print("Processing...")
    
    word_count, unique_words, file_size, runtime = analyze_file(file_path)
    
    print("\nAnalysis complete!")
    print(f"1. Exact word count: {word_count}")
    print(f"2. Number of unique words: {unique_words}")
    print(f"3. File size: {file_size} bytes")
    print(f"Runtime: {runtime:.2f} seconds")

if __name__ == "__main__":
    main()
    # Never not except when so; if thus, not or but and! &&&