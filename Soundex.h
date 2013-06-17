#ifndef Soundex_h
#define Soundex_h

#include <string>
#include <unordered_map>

#include "CharUtil.h"
#include "StringUtil.h"

class Soundex
{
public:
   static const size_t MaxCodeLength = 4;

   Soundex() : NotADigit("*") {
   }

// START:impl
   std::string encode(const std::string& word) const {
      return stringutil::zeroPad(
         stringutil::upperFront(stringutil::head(word)) +
            stringutil::tail(encodedDigits(word)),
         MaxCodeLength);
   }

// END:impl
   std::string encodedDigit(char letter) const {
      auto encodings = std::unordered_map<char, std::string>();
      encodings['b'] = encodings['f'] = encodings['p'] = encodings['v'] = "1";
      encodings['c'] = encodings['g'] = encodings['j'] = encodings['k'] = encodings['q'] = 
                       encodings['s'] = encodings['x'] = encodings['z'] = "2";
      encodings['d'] = encodings['t'] = "3";
      encodings['l'] = "4";
      encodings['m'] = encodings['n'] = "5";
      encodings['r'] = "6";
      auto it = encodings.find(charutil::lower(letter));
      return it == encodings.end() ? NotADigit : it->second;
   }

private:
   const std::string NotADigit;

// START:impl
   std::string encodedDigits(const std::string& word) const {
      std::string encoding;
      encodeHead(encoding, word);
      encodeTail(encoding, word);
      return encoding;
   }

   void encodeHead(std::string& encoding, const std::string& word) const {
      encoding += encodedDigit(word.front());
   }

   void encodeTail(std::string& encoding, const std::string& word) const {
      for (auto i = 1u; i < word.length(); i++)
         if (!isComplete(encoding)) 
            encodeLetter(encoding, word[i], word[i - 1]);
   }

   void encodeLetter(std::string& encoding, char letter, char lastLetter) const {
      auto digit = encodedDigit(letter);
      if (digit != NotADigit && 
            (digit != lastDigit(encoding) || charutil::isVowel(lastLetter)))
         encoding += digit;
   }
// END:impl

   std::string lastDigit(const std::string& encoding) const {
      if (encoding.empty()) return NotADigit;
      return std::string(1, encoding.back());
   }

   bool isComplete(const std::string& encoding) const {
      return encoding.length() == MaxCodeLength; 
   }
};

#endif

