#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum TokenType
{
  // Delimiters
  SEMICOLON,
  PAREN_LEFT,
  PAREN_RIGHT,
  BRACES_LEFT,
  BRACES_RIGHT,
  COLON,
  COMMA,
  OTHER_SYMBOL,
  NON_DELIMITER, // Extra flags for lexer

  // Operators
  EQUALS_TO,
  NOT_EQUALS_TO,
  LESS_EQUAL,
  GREATER_EQUAL,
  PLUS_EQUAL,
  MINUS_EQUAL,
  MULTIPLY_EQUAL,
  DIVIDE_EQUAL,
  MODULE_EQUAL,
  INTEGER_DIVISION,
  EXPONENT,
  INCREMENT,
  DECREMENT,
  LOGICAL_OR,
  LOGICAL_AND,
  NON_OPERATOR, // Extra flags for lexer

  // Single Operators
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  GREATER_THAN,
  LESS_THAN,
  ASSIGNMENT,
  MODULO,
  NOT_EQUAL,

  // Chemical Operators
  TILDE,
  CARET,
  BRACKET_LEFT,
  BRACKET_RIGHT,
  NON_CHEM_OPERATOR, // Extra flags for lexer

  // Constants
  STRING_LITERAL,
  CHARACTER_LITERAL,
  REAL_NUMBER_LITERAL,
  INTEGER_LITERAL,
  // Boolean Constants
  TRUE_LITERAL,
  FALSE_LITERAL,

  NON_STRING,
  NON_CHARACTER,
  NON_BOOLEAN,

  // Keywords
  IF,
  ELSE,
  WHILE,
  DO,
  BREAK,
  CONTINUE,
  DOUBLE,
  FLOAT,
  RETURN,
  CHAR,
  CASE,
  BOOL,
  SIZEOF,
  LONG,
  SHORT,
  TYPEDEF,
  SWITCH,
  UNSIGNED,
  VOID,
  STATIC,
  STRUCT,
  GOTO,
  CONST,
  DEFAULT,
  INT,
  FOR,
  PRINTF,
  SIGNED,
  SCANF,
  STRING,
  MAIN,
  PRINTCHEL,
  IMCOMP,
  PCM,
  REACT,
  NON_KEYWORD, // Extra flags for lexer

  // Identifier
  IDENTIFIER,

  // Chemical Expression
  CHEMICAL_EXPRESSION,

  // Comments
  COMMENT,

  // Invalid
  INVALID,
};

int CURRENT_LINE = 1;
int right = 0;

FILE *dest_fp;

// Returns string if the character is a DELIMITER.
enum TokenType isDelimiter(char ch)
{
  if (ch == ';')
    return SEMICOLON;
  else if (ch == '(')
    return PAREN_LEFT;
  else if (ch == ')')
    return PAREN_RIGHT;
  else if (ch == '{')
    return BRACES_LEFT;
  else if (ch == '}')
    return BRACES_RIGHT;
  else if (ch == ':')
    return COLON;
  else if (ch == ',')
    return COMMA;
  else if (ch == ' ')
    return OTHER_SYMBOL;
  else if (ch == '\n')
    return OTHER_SYMBOL;
  else if (ch == '\t')
    return OTHER_SYMBOL;
  else if (ch == '\v')
    return OTHER_SYMBOL;
  else if (ch == '|')
    return OTHER_SYMBOL;
  else if (ch == '[')
    return OTHER_SYMBOL;
  else if (ch == ']')
    return OTHER_SYMBOL;
  else if (ch == '+')
    return OTHER_SYMBOL;
  else if (ch == '-')
    return OTHER_SYMBOL;
  else if (ch == '*')
    return OTHER_SYMBOL;
  else if (ch == '/')
    return OTHER_SYMBOL;
  else if (ch == ',')
    return OTHER_SYMBOL;
  else if (ch == '>')
    return OTHER_SYMBOL;
  else if (ch == '<')
    return OTHER_SYMBOL;
  else if (ch == '=')
    return OTHER_SYMBOL;
  else if (ch == '!')
    return OTHER_SYMBOL;
  else if (ch == '%')
    return OTHER_SYMBOL;
  else if (ch == '&')
    return OTHER_SYMBOL;
  else if (ch == '~')
    return OTHER_SYMBOL;
  return NON_DELIMITER;
}

// Returns string if one/two chars are Operators
enum TokenType isDoubleOperator(char left, char right)
{
  char a = left;
  char b = right;

  // Evaluates if a and b are TO expressions by comparing the two simultaneously
  if (a == '=' && b == '=')
    return EQUALS_TO;
  else if (a == '!' && b == '=')
    return NOT_EQUALS_TO;
  else if (a == '<' && b == '=')
    return LESS_EQUAL;
  else if (a == '>' && b == '=')
    return GREATER_EQUAL;
  else if (a == '+' && b == '=')
    return PLUS_EQUAL;
  else if (a == '-' && b == '=')
    return MINUS_EQUAL;
  else if (a == '*' && b == '=')
    return MULTIPLY_EQUAL;
  else if (a == '/' && b == '=')
    return DIVIDE_EQUAL;
  else if (a == '%' && b == '=')
    return MODULE_EQUAL;
  else if (a == '~' && b == '/')
    return INTEGER_DIVISION;
  else if (a == '*' && b == '*')
    return EXPONENT;
  else if (a == '+' && b == '+')
    return INCREMENT;
  else if (a == '-' && b == '-')
    return DECREMENT;
  else if (a == '|' && b == '|')
    return LOGICAL_OR;
  else if (a == '&' && b == '&')
    return LOGICAL_AND;

  return NON_OPERATOR;
}

enum TokenType isSingleOperator(char right)
{
  char a = right;

  if (a == '+')
    return PLUS;
  else if (a == '-')
    return MINUS;
  else if (a == '*')
    return MULTIPLY;
  else if (a == '/')
    return DIVIDE;
  else if (a == '>')
    return GREATER_THAN;
  else if (a == '<')
    return LESS_THAN;
  else if (a == '=')
    return ASSIGNMENT;
  else if (a == '%')
    return MODULO;
  else if (a == '!')
    return NOT_EQUAL;

  return NON_OPERATOR;
}

// Returns string if a character is a CHEMICAL OPERATOR.
enum TokenType isChemOperator(char ch)
{

  if (ch == '~')
    return TILDE;
  else if (ch == '^')
    return CARET;
  else if (ch == '[')
    return BRACKET_LEFT;
  else if (ch == ']')
    return BRACKET_RIGHT;
  return NON_CHEM_OPERATOR;
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char *str)
{
  int i, len = strlen(str);
  if (len == 0)
    return (false);
  if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
      str[0] == '3' || str[0] == '4' || str[0] == '5' ||
      str[0] == '6' || str[0] == '7' || str[0] == '8' ||
      str[0] == '9' || isDelimiter(str[0]) != NON_DELIMITER ||
      str[0] == 'A' || str[0] == 'B' || str[0] == 'C' ||
      str[0] == 'D' || str[0] == 'E' || str[0] == 'F' ||
      str[0] == 'G' || str[0] == 'H' || str[0] == 'I' ||
      str[0] == 'J' || str[0] == 'K' || str[0] == 'L' ||
      str[0] == 'M' || str[0] == 'N' || str[0] == 'O' ||
      str[0] == 'P' || str[0] == 'Q' || str[0] == 'R' ||
      str[0] == 'S' || str[0] == 'T' || str[0] == 'U' ||
      str[0] == 'V' || str[0] == 'W' || str[0] == 'X' ||
      str[0] == 'Y' || str[0] == 'Z' || str[0] == '~' ||
      str[0] == '"' || str[0] == '\'' || str[0] == '_')
    return (false);
  for (i = 1; i <= len; i++)
  {
    if (str[i] == ' ' || str[i] == '~' || str[i] == '^' ||
        str[i] == '&' || str[i] == '|')
      return (false);
  }
  if (str[len - 1] == '"' || str[len - 1] == '\'')
    return (false);

  return (true);
}

// Returns string if it is a STRING.
const char *isString(char *str)
{
  int i = 0, f = 0, l = 0, len = strlen(str);

  if (len == 0)
    return "NonString";
  for (i = 0; i < len; i++)
  {
    if (str[0] == '"' && str[i] == '"')
    {
      while (str[f] == '"')
      {
        f += 1;
      }
      l = len - 1;
      while (str[l] == '"')
      {
        l -= 1;
      }
      len = l - f;
      char *str1 = (char *)malloc(len);
      while (i < len + 1)
      {
        str1[i] = str[i + 1]; // has bug with ' '
        i += 1;
      }
      str1[i] = '\0';
      return str1;
    }
  }
  return "NonString";
}

// Returns string if it is a CHARACTER.
const char *isChar(char *str)
{
  int i, len = strlen(str);
  char *ch = (char *)malloc(len);

  if (len == 0)
    return "NonCharacter";
  if (str[0] == '\'' && str[2] == '\'')
  {
    ch[0] = str[1];
    ch[1] = '\0';
    return ch;
  }
  return "NonCharacter";
}

// Returns 'true' if the string is an CPMMENT.
bool isSingleComment(int n)
{
  if (n == 1)
    return (true);
  return (false);
}

bool isMultiComment(int m)
{
  if (m == 1)
    return (true);
  return (false);
}

// Returns 'true' if string is a Boolean value.
enum TokenType isBoolean(char *str)
{
  if (strcmp(str, "TRUE") == 0)
    return TRUE_LITERAL;
  else if (strcmp(str, "FALSE") == 0)
    return FALSE_LITERAL;
  return NON_BOOLEAN;
}

// Returns 'true' if the string is a KEYWORD.
enum TokenType isKeyword(char *str)
{
  if (strcmp(str, "IF") == 0)
    return IF;
  else if (strcmp(str, "ELSE") == 0)
    return ELSE;
  else if (strcmp(str, "WHILE") == 0)
    return WHILE;
  else if (strcmp(str, "DO") == 0)
    return DO;
  else if (strcmp(str, "BREAK") == 0)
    return BREAK;
  else if (strcmp(str, "CONTINUE") == 0)
    return CONTINUE;
  else if (strcmp(str, "DOUBLE") == 0)
    return DOUBLE;
  else if (strcmp(str, "FLOAT") == 0)
    return FLOAT;
  else if (strcmp(str, "RETURN") == 0)
    return RETURN;
  else if (strcmp(str, "CHAR") == 0)
    return CHAR;
  else if (strcmp(str, "CASE") == 0)
    return CASE;
  else if (strcmp(str, "BOOL") == 0)
    return BOOL;
  else if (strcmp(str, "SIZEOF") == 0)
    return SIZEOF;
  else if (strcmp(str, "LONG") == 0)
    return LONG;
  else if (strcmp(str, "SHORT") == 0)
    return SHORT;
  else if (strcmp(str, "TYPEDEF") == 0)
    return TYPEDEF;
  else if (strcmp(str, "SWITCH") == 0)
    return SWITCH;
  else if (strcmp(str, "UNSIGNED") == 0)
    return UNSIGNED;
  else if (strcmp(str, "VOID") == 0)
    return VOID;
  else if (strcmp(str, "STATIC") == 0)
    return STATIC;
  else if (strcmp(str, "STRUCT") == 0)
    return STRUCT;
  else if (strcmp(str, "GOTO") == 0)
    return GOTO;
  else if (strcmp(str, "CONST") == 0)
    return CONST;
  else if (strcmp(str, "DEFAULT") == 0)
    return DEFAULT;
  else if (strcmp(str, "INT") == 0)
    return INT;
  else if (strcmp(str, "FOR") == 0)
    return FOR;
  else if (strcmp(str, "PRINTF") == 0)
    return PRINTF;
  else if (strcmp(str, "SIGNED") == 0)
    return SIGNED;
  else if (strcmp(str, "SCANF") == 0)
    return SCANF;
  else if (strcmp(str, "STRING") == 0)
    return STRING;
  else if (strcmp(str, "MAIN") == 0)
    return MAIN;
  else if (strcmp(str, "printchel") == 0)
    return PRINTCHEL;
  else if (strcmp(str, "imcomp") == 0)
    return IMCOMP;
  else if (strcmp(str, "pcm") == 0)
    return PCM;
  else if (strcmp(str, "react") == 0)
    return REACT;
  return NON_KEYWORD;
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char *str)
{
  int i, len = strlen(str);

  if (len == 0)
    return (false);
  for (i = 0; i < len; i++)
  {
    if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
      return (false);
  }
  return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char *str)
{
  int i, len = strlen(str);
  bool hasDecimal = false;

  if (len == 0)
    return (false);
  for (i = 0; i < len; i++)
  {
    if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
        (str[i] == '-' && i > 0))
      return (false);
    if (str[i] == '.')
      hasDecimal = true;
  }
  return (hasDecimal);
}

// Returns 'true' if the string is a CHEMICAL EXPRESSION
bool isChemExpression(int num)
{
  if (num == 1)
    return (true);
  return (false);
}

// Extracts the SUBSTRING.
char *subString(char *str, int left, int right)
{
  int i;
  char *subStr = (char *)malloc(
      sizeof(char) * (right - left + 2));

  for (i = left; i <= right; i++)
    subStr[i - left] = str[i];
  subStr[right - left + 1] = '\0';
  return (subStr);
}

// Parsing the input STRING.
void parse(char *str)
{
  int left = 0, FoundSingleLineComment = 0, FoundMultiLineComment = 0, ChemOperatorFound = 0;
  right = 0;
  int len = strlen(str);
  // const char* value;

  while (right <= len && left <= right)
  {

    if (isDelimiter(str[right]) == NON_DELIMITER)
      right++;

    if (isDelimiter(str[right]) != NON_DELIMITER && left == right)
    {
      if (isDelimiter(str[right]) != OTHER_SYMBOL)
      {
        fprintf(dest_fp, "%d:%d:%c:%d\n", CURRENT_LINE, right, str[right], isDelimiter(str[right]));
        printf("%d %8d %8c %8d\n", CURRENT_LINE, right, str[right], isDelimiter(str[right]));
      }

      else if (str[right] == '/' && str[right - 1] == '/')
        FoundSingleLineComment = 1;

      else if (str[right] == '*' && str[right - 1] == '/')
        FoundMultiLineComment = 1;

      // Takes two consecutive characters and send them to isOperator
      else if (isDoubleOperator(str[right], str[right + 1]) != NON_OPERATOR)
      {
        char lexeme[3];
        lexeme[0] = str[right];
        lexeme[1] = str[right + 1];

        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, lexeme, isDoubleOperator(str[right], str[right + 1]));
        printf("%d %8d %8d\n", CURRENT_LINE, right, isDoubleOperator(str[right], str[right + 1]));
        right++; // extra skip since two operators were taken
      }
      else if (isChemOperator(str[right]) != NON_CHEM_OPERATOR)
      {
        fprintf(dest_fp, "%d:%d:%c:%d\n", CURRENT_LINE, right, str[right], isChemOperator(str[right]));
        printf("%d %8d %8d\n", CURRENT_LINE, right, isChemOperator(str[right]));
        ChemOperatorFound = 1;
      }
      else if (isSingleOperator(str[right]) != NON_OPERATOR)
      {
        fprintf(dest_fp, "%d:%d:%c:%d\n", CURRENT_LINE, right, str[right], isSingleOperator(str[right]));
        printf("%d %8d %8d\n", CURRENT_LINE, right, isSingleOperator(str[right]));
      }

      else if (str[right] == '\n')
      {
        FoundSingleLineComment = 0;
        /*while(isalpha(CURRENT_LETTER) || (CURRENT_LETTER == '_')) {*/
        /*CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];*/
        /*CURRENT_RIGHT_COUNT++;*/
        /*}*/
      }
      else if (str[right] == '/' && str[right - 1] == '*')
      {
        FoundMultiLineComment = 0;
      }
      else if (str[right] == ' ' || str[right] == '\n')
      {
        ChemOperatorFound = 0;
      }

      right++;
      left = right;
    }
    else if (isDelimiter(str[right]) != NON_DELIMITER && left != right || (right == len && left != right))
    {
      char *subStr = subString(str, left, right - 1);

      if (isSingleComment(FoundSingleLineComment) == true)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, COMMENT);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, COMMENT);
      }

      else if (isMultiComment(FoundMultiLineComment) == true)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, COMMENT);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, COMMENT);
      }

      else if (isKeyword(subStr) != NON_KEYWORD)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, isKeyword(subStr));
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, isKeyword(subStr));
      }

      else if (isBoolean(subStr) != NON_BOOLEAN)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, isBoolean(subStr));
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, isBoolean(subStr));
      }

      else if (isInteger(subStr) == true)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, INTEGER_LITERAL);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, INTEGER_LITERAL);
      }

      else if (isRealNumber(subStr) == true)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, REAL_NUMBER_LITERAL);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, REAL_NUMBER_LITERAL);
      }

      else if (isChar(subStr) != "NonCharacter")
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, isChar(subStr), CHARACTER_LITERAL);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, isChar(subStr), CHARACTER_LITERAL);
      }

      else if (isString(subStr) != "NonString")
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, isString(subStr), STRING_LITERAL);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, isString(subStr), STRING_LITERAL);
      }

      else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == NON_DELIMITER && isChemOperator(str[right - 1]) == NON_CHEM_OPERATOR)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, IDENTIFIER);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, IDENTIFIER);
      }

      else if (isChemExpression(ChemOperatorFound) == true)
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, CHEMICAL_EXPRESSION);
        printf("%d %8d %8s %8d\n", CURRENT_LINE, right, subStr, CHEMICAL_EXPRESSION);
      }

      else
      {
        fprintf(dest_fp, "%d:%d:%s:%d\n", CURRENT_LINE, right, subStr, INVALID);
        printf("'%s' IS INVALID\n", subStr);
      }

      left = right;
    }
  }

  CURRENT_LINE++;
  return;
}

int endsWith(char *str, char *end)
{
  size_t slen = strlen(str);
  size_t elen = strlen(end);
  if (slen < elen)
    return 0;
  return (strcmp(&(str[slen - elen]), end) == 0);
}

// DRIVER FUNCTION
int main(int argc, char *argv[])
{
  // maximum length of string is 100 here
  // Global Variables
  bool DEBUG = false;

  // DEBUG Mode: Just for minor line tests
  if (DEBUG)
  {
    char line[100];
    size_t len = 0;
    FILE *fptr;
    ssize_t read;
    char *val;

    fptr = fopen("file.mul", "r");
    dest_fp = fopen("output.mul", "w");

    if (fptr == NULL)
    {
      printf("Can't Open File");
      return 0;
    }

    while (val = fgets(line, 100, fptr))
    {
      if (val[0] != '\n')
      {
        parse(val);
      }
      else
      {
        CURRENT_LINE++;
      }
    }

    fclose(fptr);
  }
  // DEBUG-OFF Mode: Accepts an entire file and converts it all into another file containing lexeme tokens.
  else
  {
    char line[100];
    size_t len = 0;
    FILE *fptr;
    ssize_t read;
    char *val;

    if (argc < 2)
    {
      printf("Error: no given files.\n");
      printf("Usage is: gcc lexical.out filename.mul\n");
      exit(EXIT_FAILURE);
    }

    if (!endsWith(argv[1], ".mul"))
    {
      printf("Error: invalid file with name %s. It must have a"
             " format of name.mul\n",
             argv[1]);
      exit(EXIT_FAILURE);
    }

    fptr = fopen(argv[1], "r");
    dest_fp = fopen("output.mul", "w");

    if (fptr == NULL)
    {
      printf("Failed to Open File. Terminating Program.");
      return 0;
    }

    while (val = fgets(line, 100, fptr))
    {
      if (val[0] != '\n')
      {
        parse(val);
      }
      else
      {
        CURRENT_LINE++;
      }
    }

    fclose(fptr);
  }

  fclose(dest_fp);
  return (0);
}
