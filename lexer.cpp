#include <string>
#include <fstream>

std::ifstream sourceFile;

enum Token
{
  // end of file
  token_eof = -1,

  // commands
  token_def = -2,
  token_extern = -3,

  // primary
  token_identifier = -4,
  token_number = -5
};

std::string identifierStr; // name of recognized identifer token
double numVal; // name of recognized number

int getToken()
{
  static char lastChar = ' ';

  // omit space, tab, newline, cr, etc.
  while (std::isspace(lastChar)) {
    sourceFile >> std::noskipws >> lastChar;
  }

  // meet an alpha-numeric
  if (std::isalpha(lastChar)) {
    identifierStr = lastChar;
    do {
      sourceFile >> std::noskipws >> lastChar;
      if (std::isalnum(lastChar)) identifierStr += lastChar;
      else break;
    }
    while (true);

    return (identifierStr == "def") ? token_def :
                                      ((identifierStr == "extern") ?
                                         token_extern : token_identifier);
  }

  // meen a digit or '.'
  std::string numStr("");
  while (std::isdigit(lastChar) || lastChar == '.') {
    numStr += lastChar;
    sourceFile >> std::noskipws >> lastChar;
  }
  if (numStr != "") {
    numVal = std::stod(numStr);
    return token_number;
  }

  // meet a comment
  if (lastChar == '#') {
    do {
      auto nextChar = sourceFile.peek();
      if (nextChar == std::ifstream::traits_type::eof()) {
        return token_eof;
      }
      else {
        sourceFile >> std::noskipws >> lastChar;
      }
    }
    while (lastChar != '\n' && lastChar != '\r');
  }

  auto thisChar = lastChar;
  sourceFile >> std::noskipws >> lastChar;
  return thisChar;
}
