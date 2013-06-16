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
      auto encodings = std::unordered_map<char, std::string>();
      encodings['b'] = encodings['f'] = encodings['p'] = encodings['v'] = "1";
         // ...
// END:encodedDigits
      encodings['c'] = encodings['g'] = encodings['j'] = encodings['k'] = encodings['q'] = 
                       encodings['s'] = encodings['x'] = encodings['z'] = "2";
      encodings['d'] = encodings['t'] = "3";
      encodings['l'] = "4";
      encodings['m'] = encodings['n'] = "5";
      encodings['r'] = "6";
// START:encodedDigits

// START_HIGHLIGHT
      auto it = encodings.find(letter);
      return it == encodings.end() ? "" : it->second;
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
