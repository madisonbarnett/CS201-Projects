#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <chrono>

/*
    Name: Madison Barnett
    Email: mtbarnett@crimson.ua.edu
    Course Section: Fall 2024 CS 201-002 
    Homework #: 3
*/

int main(int argc, char *argv[]) {
	int i = 0;
	// check for correct command-line arguments
	if (argc != 3) {
	   std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
	   std::exit(-1);
	}

	// From sample file given
	std::string line, name;
	std::regex delim("/");
	std::ifstream dbfile(argv[1]);
	if (!dbfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[1] << std::endl;
	   std::exit(-1);
	}

	// Start clock
	auto starttime = std::chrono::steady_clock::now();

	// Two unordered maps track information from input
    std::string movieName;
	int totalMovies = 0;
    std::unordered_map<std::string, std::vector<std::string>> movieToActor;
    std::unordered_map<std::string, std::vector<std::string>> actorToMovie;
	while (std::getline(dbfile, line)) {
        // parse each line for tokens delimited by "/"
        auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        movieName = *begin; // Beginning of line is movie title
		if (!movieName.empty()) { // Ensure not an empty line
			totalMovies++; 
		}
	    ++begin;
    
        for (std::sregex_token_iterator word = begin; word != end; ++word) {
            movieToActor[movieName].push_back(*word); // movieToActor use movie name as key and add each actor to vector
            actorToMovie[*word].push_back(movieName); // Add current movie name to actorToMovie with current actor as the key
	    }
	}
	dbfile.close();
	std::cout << "***Done reading db file " << argv[1] << "***" << std::endl;

	auto endtimeStruct = std::chrono::steady_clock::now();
	std::chrono::duration<double> timetakenStruct = endtimeStruct - starttime; // Find time taken to build maps

	std::ifstream queryfile(argv[2]);
	if (!queryfile.is_open()) {
	   std::cout << "Unable to open file: " << argv[2] << std::endl;
	   std::exit(-1);
	}

	std::cout << "***Reading query file " << argv[2] << "***" << std::endl;
	while (std::getline(queryfile, name)) {
	   std::cout << name << ":" << std::endl;
	   if (movieToActor.count(name) != 0) { // Search for key in both maps and output result if found
			for (auto item : movieToActor[name]) {
				std::cout << item << std::endl;
			}
 	   }
	   else if (actorToMovie.count(name) != 0) {
			for (auto item : actorToMovie[name]) {
				std::cout << item << std::endl;
			}
	   }
	   else {
			std::cout << "Not Found" << std::endl; // If both .count returned 0, name wasn't in dbfile
	   }
	}
	queryfile.close();
	std::cout << "***Done reading query file " << argv[2] << "***" << std::endl;

	auto endtimeQuery = std::chrono::steady_clock::now();
	std::chrono::duration<double> timetakenQuery = endtimeQuery - endtimeStruct; // Find time taken for search and retrieval
	std::chrono::duration<double> timetakenTotal = endtimeQuery - starttime; // Find time taken total

	// Output information
	std::cout << "Total movies: " << totalMovies << std::endl;
	std::cout << "Time taken to build data structure: " << timetakenStruct.count() << std::endl;
	std::cout << "Time taken to search: " << timetakenQuery.count() << std::endl;
	std::cout << "Total time: " << timetakenTotal.count() << std::endl;

	return 0;
}
