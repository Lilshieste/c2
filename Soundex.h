#ifndef Soundex_h
#define Soundex_h

#include <string>
#include <unordered_map>

class Soundex
{
public:
   static const size_t MaxCodeLength = 4;

   std::string encode(const std::string& word) const {
      return zeroPad(head(word) + encodedDigits(tail(word)));
   }

private:
   std::string head(const std::string& word) const {
      return word.substr(0, 1);
   }
   
   std::string tail(const std::string& word) const {
      return word.substr(1);
   }

// START:encodedDigits
   std::string encodedDigits(const std::string& word) const {
      std::string encoding;
      for (auto letter: word) {
// START_HIGHLIGHT
         if (isComplete(encoding)) break;
// END_HIGHLIGHT
         encoding += encodedDigit(letter);
      }
      return encoding;
   }

// START_HIGHLIGHT
   bool isComplete (const std::string& encoding) const {
      return encoding.length() == MaxCodeLength - 1; 
   }
// END_HIGHLIGHT
// END:encodedDigits

// START:encodedDigit
// START_HIGHLIGHT
public:
// END_HIGHLIGHT
   std::string encodedDigit(char letter) const {
      // ...
// END:encodedDigit
      auto encodings = std::unordered_map<char, std::string>();
      encodings['b'] = encodings['f'] = encodings['p'] = encodings['v'] = "1";
      encodings['c'] = encodings['g'] = encodings['j'] = encodings['k'] = encodings['q'] = 
                       encodings['s'] = encodings['x'] = encodings['z'] = "2";
      encodings['d'] = encodings['t'] = "3";
      encodings['l'] = "4";
      encodings['m'] = encodings['n'] = "5";
      encodings['r'] = "6";
      auto it = encodings.find(letter);
      return it == encodings.end() ? "" : it->second;
// START:encodedDigit
   }

// START_HIGHLIGHT
private:
// END_HIGHLIGHT
   // ...
// END:encodedDigit
   std::string zeroPad(const std::string& word) const {
      auto zerosNeeded = MaxCodeLength - word.length();
      return word + std::string(zerosNeeded, '0');
   }
};
// END:Soundex

#endif
