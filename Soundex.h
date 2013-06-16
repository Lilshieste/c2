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

// START:prefactor
   std::string encode(const std::string& word) const {
// START_HIGHLIGHT
      return zeroPad(head(word) + encodedDigits(tail(word)));
// END_HIGHLIGHT
   }

private:
   // ...
// END:prefactor
   std::string head(const std::string& word) const {
      return word.substr(0, 1);
   }
   
// START:prefactor
// START_HIGHLIGHT
   std::string tail(const std::string& word) const {
      return word.substr(1);
   }
// END_HIGHLIGHT

   std::string encodedDigits(const std::string& word) const {
// START_HIGHLIGHT
      if (word.empty()) return "";
      return encodedDigit(word.front());
// END_HIGHLIGHT
   }
// END:prefactor

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
