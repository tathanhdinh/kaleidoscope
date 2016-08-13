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
  int lastChar = ' ';

  // omit space, tab, newline, cr, etc.
  while (std::isspace(lastChar)) {
    sourceFile >> std::noskipws >> lastChar;
  }
}
