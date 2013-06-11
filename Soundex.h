#ifndef Soundex_h
#define Soundex_h

#include <string>
// START_HIGHLIGHT
#include <unordered_map>
// ...
// END_HIGHLIGHT

// START:Soundex
class Soundex
{
public:
   static const size_t MaxCodeLength = 4;

   std::string encode(const std::string& word) const {
      return zeroPad(head(word) + encodedDigits(word));
   }

private:
   std::string head(const std::string& word) const {
      return word.substr(0, 1);
   }

   std::string encodedDigits(const std::string& word) const {
      if (word.length() > 1) return encodedDigit(word[1]);
      return "";
   }

   static std::unordered_map<char, std::string> createTestMap() {
	   auto map = std::unordered_map<char, std::string>();
	   map['b'] = "1";
	   map['c'] = "2";
	   map['d'] = "3";

	   return map;
   }

// START:encodedDigits
   std::string encodedDigit(char letter) const {
// START_HIGHLIGHT
	  const std::unordered_map<char,std::string> encodings = createTestMap();

      return encodings.find(letter)->second;
// END_HIGHLIGHT
   }
// END:encodedDigits

   std::string zeroPad(const std::string& word) const {
      auto zerosNeeded = MaxCodeLength - word.length();
      return word + std::string(zerosNeeded, '0');
   }
};
// END:Soundex

#endif
