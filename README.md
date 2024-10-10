# Nonword Generator and Text Analyzer

This project, developed by The Pataphysical Society of New York (https://patanyc.org), consists of a Nonword Generator and a Text Analyzer. These tools are designed to aid research into the nature of uselessness. Example datasets and texts for analysis are also included. Findings from this research are published at https://patanyc.org/nonwords.

## Nonword Generator

### Features

- Generates nonwords of specified lengths (from 1 to 7 letters by default)
- Multithreaded for maximizing performance
- Progress indicator for real-time status
- Option to generate nonwords of a single length or a range of lengths
- Option to output to separate files for each length or a single combined file

### Requirements

- C++11 compatible compiler
- A dictionary file named `words.txt` in the same directory as the executable

### Compilation

Compile the program using the following command:

```
g++ -std=c++11 -pthread nonword_generator.cpp -o nonword_generator
```

### Usage

Run the program with two or three command-line arguments:

```
./nonword_generator <min_length> <max_length> [single_file]
```

Examples:
- To generate 5-letter nonwords in a separate file: `./nonword_generator 5 5`
- To generate nonwords from 3 to 6 letters in separate files: `./nonword_generator 3 6`
- To generate nonwords from 1 to 7 letters in a single file: `./nonword_generator 1 7 single_file`

### Output

By default, the program creates separate files for each word length, named `nonwords_Xletter.txt`. If the `single_file` option is used, all nonwords are written to `nonwords_all.txt`.

## Text Analyzer

The `text_analyzer.py` script is designed to analyze large text files, including the output of the nonword generator or other examplars.

### Features

- Calculates the exact word count in the file
- Counts the number of unique words
- Determines the file size in bytes
- Measures and displays the script's runtime

### Requirements

- Python 3.x

### Usage

1. Save the script as `text_analyzer.py`.

2. Run the script from the command line:

   ```
   python text_analyzer.py path/to/your/large_file.txt
   ```

3. The script will process the file and display the results.

## Additional Resources

- Sample outputs: Research quality datasets of English language nonwords, listed by length (1 to 5 letters), are included in this repository.
- Analysis findings: A complete analysis of the research findings is available at https://patanyc.org/nonwords.html.
- Classic example texts: Several large English texts referred to in the analysis are included for reference.

## Performance and Storage

- The number of possible nonword combinations grows exponentially with word length. Be prepared for long processing times and large output files for longer word lengths.
- 7-letter nonwords can result in a file size of approximately 64GB.

## Customization

The nonword generator can be customized by adjusting parameters in the code, such as maximum word length, number of threads, and dictionary file location.

## Acknowledgements

The English wordlist used as the default is derived from https://github.com/dwyl/english-words/blob/master/words_alpha.txt and is freely licensable for all uses.

## Contributing

Pataphysics researchers, academics, and laypersons are welcome to contact the authors via the website linked below.

## License

This project is open-source and available under the MIT License.

## Contact

For more information, visit https://patanyc.org

Never not except when so; if thus, not or but and!

&&&
