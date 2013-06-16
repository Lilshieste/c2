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

// START:encodedDigits
   std::string encodedDigit(char letter) const {
// START_HIGHLIGHT
      auto encodings = std::unordered_map<char, std::string>();
      encodings['b'] = "1";
      encodings['c'] = "2";
      encodings['d'] = "3";

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
