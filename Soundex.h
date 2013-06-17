#ifndef Soundex_h
#define Soundex_h

#include <string>
#include <unordered_map>
#include <cctype>

class Soundex
{
public:
   static const size_t MaxCodeLength = 4;

   Soundex() : NotADigit("*") {
   }

// START:CombinesDupImpl
   std::string encode(const std::string& word) const {
// START_HIGHLIGHT
      return zeroPad(upperFront(head(word)) + tail(encodedDigits(word)));
// END_HIGHLIGHT
   }

// END:CombinesDupImpl
private:
   std::string head(const std::string& word) const {
      return word.substr(0, 1);
   }
   
   std::string tail(const std::string& word) const {
      return word.substr(1);
   }

   const std::string NotADigit;

// START:CombinesDupImpl
   std::string encodedDigits(const std::string& word) const {
      std::string encoding;

// START_HIGHLIGHT
      encoding += encodedDigit(word.front());
// END_HIGHLIGHT

// START_HIGHLIGHT
      for (auto letter: tail(word)) {
// END_HIGHLIGHT
         if (isComplete(encoding)) break;

         auto digit = encodedDigit(letter);
         if (digit != NotADigit && digit != lastDigit(encoding))
            encoding += digit;
      }
      return encoding;
   }

// END:CombinesDupImpl

   std::string lastDigit(const std::string& encoding) const {
      if (encoding.empty()) return NotADigit;
      return std::string(1, encoding.back());
   }

// START:CombinesDupImpl
   bool isComplete (const std::string& encoding) const {
// START_HIGHLIGHT
      return encoding.length() == MaxCodeLength; 
// END_HIGHLIGHT
   }
// END:CombinesDupImpl

public:
// START:encodedDigit
   std::string encodedDigit(char letter) const {
      auto encodings = std::unordered_map<char, std::string>();
      encodings['b'] = encodings['f'] = encodings['p'] = encodings['v'] = "1";
      encodings['c'] = encodings['g'] = encodings['j'] = encodings['k'] = encodings['q'] = 
                       encodings['s'] = encodings['x'] = encodings['z'] = "2";
      encodings['d'] = encodings['t'] = "3";
      encodings['l'] = "4";
      encodings['m'] = encodings['n'] = "5";
      encodings['r'] = "6";
      auto it = encodings.find(lower(letter));
      return it == encodings.end() ? NotADigit : it->second;
   }

private:
   char lower(char c) const {
      return std::tolower(static_cast<unsigned char>(c));
   }

   std::string zeroPad(const std::string& word) const {
      auto zerosNeeded = MaxCodeLength - word.length();
      return word + std::string(zerosNeeded, '0');
   }

   std::string upperFront(const std::string& string) const {
      return std::string(1, 
            std::toupper(static_cast<unsigned char>(string.front())));
   }
};

#endif

