#ifndef Soundex_h
#define Soundex_h

#include <string>
#include <unordered_map>
#include <cctype>

class Soundex
{
public:
   static const size_t MaxCodeLength = 4;

// START:encode
   std::string encode(const std::string& word) const {
// START_HIGHLIGHT
      return zeroPad(upperFront(head(word)) + encodedDigits(tail(word)));
// END_HIGHLIGHT
   }
// END:encode

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
         if (isComplete(encoding)) break;
         if (encodedDigit(letter) != lastDigit(encoding))
            encoding += encodedDigit(letter);
      }
      return encoding;
   }
// END:encodedDigits

   std::string lastDigit(const std::string& encoding) const {
      if (encoding.empty()) return "";
      return std::string(1, encoding.back());
   }

   bool isComplete (const std::string& encoding) const {
      return encoding.length() == MaxCodeLength - 1; 
   }

public:
   std::string encodedDigit(char letter) const {
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
   }

private:
   std::string zeroPad(const std::string& word) const {
      auto zerosNeeded = MaxCodeLength - word.length();
      return word + std::string(zerosNeeded, '0');
   }
// START:encode

// START_HIGHLIGHT
   std::string upperFront(const std::string& string) const {
      return std::string(1, 
            std::toupper(static_cast<unsigned char>(string.front())));
   }
// END_HIGHLIGHT
// END:encode
};
// END:Soundex

#endif
