#include <iostream>
#include <vector>
#include <regex>

int main() {
   std::string text;
   std::vector<std::string> tokens;
   const std::regex delim("\\s+"); 

   while (std::cin >> text) {
      auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
      auto end = std::sregex_token_iterator();
      for (std::sregex_token_iterator word = begin; word != end; word++) {
         tokens.push_back(*word);
      }
   }

   for(const auto & str : tokens)
      std::cout << str << std::endl;

   return 0;
}