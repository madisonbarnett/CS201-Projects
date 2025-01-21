#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <map>
#include <chrono>

/* 
    Name: Madison Barnett
    Email: mtbarnett@crimson.ua.edu
    Course Section: Fall 2024 CS 201-002 
    Homework #: 1
    To Compile: g++ homework1.cpp
    To Run: ./a.exe filename.txt
*/

int main(int argc, char* argv[]) {
    if (argc != 2) {
        // Print error message if program is not run correctly
        std::cout << "Proper format is './a.exe filename.txt'" << std::endl;
        return 1;
    }
    std::string textFile = argv[1];
    //std::cout << textFile << std::endl;

    // Print error message if file does not open correctly
    std::ifstream infile(textFile);
    if (!infile) {
        std::cout << "Failed to open \"" << textFile << "\"" << std::endl;
        return 2;
    }

    // Start clock
    auto starttime = std::chrono::steady_clock::now();

    // Parse through text in input file, adding each string found to vector tokens
    int totalWordCount = 0;
    std::string text;
    std::vector<std::string> tokens;
    const std::regex delim("\\s+"); 
    while (infile >> text) {
      auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; word++) {
            tokens.push_back(*word);
            totalWordCount++;
        }
    }
    
    // Sort vector tokens, count the copies of each string found, add to multimap wordList which is sorted by count value in descending order
    std::multimap<int, std::string, std::greater<int>> wordList;
    int uniqueWordCount = 0;
    std::sort(tokens.begin(), tokens.end());
    int count = 1;
    for (int i=0; i<tokens.size() - 1; i++) {
        if (tokens[i] == tokens[i+1]) {
            count++;
        }
        else {
            wordList.insert({count, tokens[i]});
            uniqueWordCount++;
            count = 1;
        }
    }
    wordList.insert({count, tokens[tokens.size() - 1]});
    uniqueWordCount++;

    // Stop clock
	auto endtime = std::chrono::steady_clock::now();
	std::chrono::duration<double> timetaken = endtime - starttime;

    // Print words in descending frequency order with proper format
    for (auto i : wordList)
        std::cout << i.second << ": " << i.first << std::endl;
    
    std::cout << "Total unique words: " << uniqueWordCount << std::endl;
    //std::cout << "Total words: " << totalWordCount << std::endl;
    std::cout << "Total time taken: " << timetaken.count() << std::endl;

    return 0;
}
