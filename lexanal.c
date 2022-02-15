#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global Variables
int CURRENT_LINE = 1 ; 
int CURRENT_STATE_NUMBER = 0;

int CURRENT_LEFT_COUNT = 0;
int CURRENT_RIGHT_COUNT = 0;

char CURRENT_LETTER = '0';
char CURRENT_STRING[100];

bool CURRENT_WORD_IS_IDENTIFIER = false;

FILE *fptr;
FILE *dest_fp;

void perform_transition(char* string, char current, int number);
void accept_and_print( char *string, char *keyword_formed);
void characters_perform_transition(char *string, char state_character, int next_state);


// Returns 'true' if the character is a DELIMITER.
const char* isDelimiter(char ch)
{
  if (ch == ';') 
    return "Delimiter_Semicolon";
  else if (ch == '(')
    return "Delimiter_ParenLeft";
  else if (ch == ')')
    return "Delimiter_ParenRight";
  else if (ch == '{')  
    return "Delimiter_BracesLeft";
  else if (ch == '}')
    return "Delimiter_BracesRight";
  else if (ch == ' ') 
    return "OtherSymbol";
  else if (ch == '\n') 
    return "OtherSymbol";
  else if (ch == '[')
    return "OtherSymbol";
  else if (ch == ']')
    return "OtherSymbol";
  else if (ch == '+')
    return "OtherSymbol";
  else if (ch == '-')
    return "OtherSymbol";
  else if (ch == '*')
    return "OtherSymbol";
  else if (ch == '/')
    return "OtherSymbol";
  else if (ch == ',')
    return "OtherSymbol";
  else if (ch == '>')
    return "OtherSymbol";
  else if (ch == '<')
    return "OtherSymbol";
  else if (ch == '=')
    return "OtherSymbol";
  else if (ch == '!')
    return "OtherSymbol";
  else if (ch == '%')
    return "OtherSymbol";
  return "NonDelimiter";
}

//Returns string if one/two chars are Operators
 const char* isOperator(char left, char right){
  char a = left;
  char b = right;
  
  //Evaluates if a and b are TO expressions by comparing the two simultaneously
  if(a == '=' && b == '=')
    return "Operator_EqualsTo";
  else if(a == '!' && b == '=')
    return "Operator_NotEqualsTo";
  else if(a == '<' && b == '=')
    return "Operator_LessEqual";
  else if(a == '>' && b == '=')
    return "Operator_GreaterEqual";
  else if(a == '+' && b == '=')
    return "Operator_PlusEqual";
  else if(a == '-' && b == '=')
    return "Operator_MinusEqual";
  else if(a == '*' && b == '=')
    return "Operator_MultiplyEqual";
  else if(a == '/' && b == '=')
    return "Operator_DivideEqual";
  else if(a == '%' && b == '=')
    return "Operator_ModuleEqual";
  else if(a == '~' && b == '/')
    return "Operator_IntegerDivision";
  else if(a == '*' && b == '*')
    return "Operator_Exponent";
  else if(a == '+' && b == '+')
    return "Operator_Increment";
  else if(a == '-' && b == '-')
    return "Operator_Decrement";
  else if(a == '|' && b == '|')
    return "Operator_LogicalOR";
  else if(a == '&' && b == '&')
    return "Operator_LogicalAND";
    
  if(b != '+' && b != '-' && b != '*' && b != '/' && b != '>' 
    && b != '<' && b != '=' && b != '%' && b != '!'){//bug comes from here
    if (a == '+')
      return "Operator_Plus";
    else if (a == '-')
      return "Operator_Minus";
    else if (a == '*')
      return "Operator_Multiply";
    else if (a == '/')
      return "Operator_Divide";
    else if (a == '>')
      return "Operator_Greaterthan";
    else if (a == '<')
      return "Operator_Lessthan";
    else if (a == '=')
      return "Operator_Equals";
    else if (a == '%')
      return "Operator_Modulo";
    else if (a == '!')
      return "Operator_NotEqual";
  }
  
  return "NonOperator"; 
} 
 
// Returns 'true' if the character is an CHEMICAL OPERATOR.
const char* isChemOperator(char ch){
  
    if (ch == '~')
      return "ChemOperator_tilde";  
  else if (ch == '^')
    return "ChemOperator_carat";
  else if (ch == '[') 
    return "ChemOperator_BracketLeft";
  else if (ch ==']')
    return "ChemOperator_BracketRight";
    return "NonChemOperator";
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) != "NonDelimiter" ||
    str[0] == '"' || str[0] == '\'')
        return (false);
    return (true);
}

// Returns 'true' if the string is an STRING.
bool isString(char* str)
{
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[0] == '"' && str[i] == '"')
            return (true);
    }
    return (false);
}

// Returns 'true' if the string is an CPMMENT.
bool isComment(char* str)
{
    int i,  len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[0] == '/*' && str[i] == '*/')
            return (true);
    }
    return (false);
}

// Returns 'true' if the string is an CHARACTER.
bool isChar(char* str)
{
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[0] == '\'' && str[i] == '\'')
            return (true);
    }
    return (false);
}
 
// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{

    if (   !strcmp(str, "IF")           || !strcmp(str, "ELSE") 
        || !strcmp(str, "WHILE")        || !strcmp(str, "DO") 
        || !strcmp(str, "BREAK")        || !strcmp(str, "CONTINUE") 
        || !strcmp(str, "DOUBLE")       || !strcmp(str, "FLOAT")
        || !strcmp(str, "RETURN")       || !strcmp(str, "CHAR")
        || !strcmp(str, "CASE")         || !strcmp(str, "BOOL") 
        || !strcmp(str, "SIEZEOF")      || !strcmp(str, "LONG")
        || !strcmp(str, "SHORT")        || !strcmp(str, "TYPEDEF")
        || !strcmp(str, "SWITCH")       || !strcmp(str, "UNSIGNED")
        || !strcmp(str, "VOID")         || !strcmp(str, "STATIC")
        || !strcmp(str, "STRUCT")       || !strcmp(str, "GOTO")
        || !strcmp(str, "CONST")        || !strcmp(str, "DEFAULT")      
        || !strcmp(str, "INT")          || !strcmp(str, "FOR")          
        || !strcmp(str, "PRINTF")       || !strcmp(str, "SIGNED")       
        || !strcmp(str, "SCANF")        || !strcmp(str, "STRING")       
        || !strcmp(str, "TRUE")         || !strcmp(str, "FALSE")
        || !strcmp(str, "MAIN")         || !strcmp(str, "printchel")    
        || !strcmp(str, "impcomp")      || !strcmp(str, "pcm")          
        || !strcmp(str, "react"))
        return (true);
    return (false);
}
 
// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str)
{
    int i, len = strlen(str);
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}
 
// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;
 
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}
 
// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
 
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
 
// Parsing the input STRING.
void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);
    //const char* value;
    //
    FILE *dest_fp;
    dest_fp = fopen("results.mul","w");
 
    while (right <= len && left <= right) {

        if (isDelimiter(str[right]) == "NonDelimiter")
            right++;

        if (isDelimiter(str[right]) != "NonDelimiter" && left == right) {
          if(isDelimiter(str[right]) != "OtherSymbol"){
            printf("%s\n", isDelimiter(str[right]));
              fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
      }
        //Takes two consecutive characters and send them to isTOExpression 
            else if (isOperator(str[right-1],str[right]) != "NonOperator") {
                printf("%s\n", isOperator(str[right-1],str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isOperator(str[right-1],str[right]));
            }

            else if(isChemOperator(str[right]) != "NonChemOperator") {
              printf("%s\n", isChemOperator(str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isChemOperator(str[right]));
            }
 
            right++;
            left = right;
        } else if (isDelimiter(str[right]) != "NonDelimiter" && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
 
            if (isKeyword(subStr) == true) { 
                printf("KEYWORD '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "KEYWORD");
            }
 
            else if (isInteger(subStr) == true)
                printf("INTEGER '%s'\n", subStr);
 
            else if (isRealNumber(subStr) == true)
                printf("REAL NUMBER '%s'\n", subStr);

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == "NonDelimiter"
           && isChemOperator(str[right - 1]) == "NonChemOperator") {
                printf("IDENTIFIER '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "IDENTIFIER");
            }

            else if (isString(subStr) == true)
                printf("STRING '%s'\n", subStr);

            else if (isComment(subStr) == true)
                printf("COMMENT '%s'\n", subStr);

            else if (isChar(subStr) == true)
                printf("CHARACTER '%s'\n", subStr);

            else if (validIdentifier(subStr) == true
           && isChemOperator(str[right - 1]) != "NonChemOperator") {
                printf("%s\n", isChemOperator(str[right - 1]));
                fprintf(dest_fp,"%d %d %s\n",CURRENT_LINE,right, isChemOperator(str[right-1]));
           }

            else if (validIdentifier(subStr) == false
                  && isDelimiter(str[right - 1]) == "NonDelimiter")
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }

    CURRENT_LINE++;
    return;
}

void perform_transition(char *string, char state_character, int next_state)
{
    printf("Run Transition : %d\n",next_state);

    if ((state_character == string[CURRENT_RIGHT_COUNT])) {
        CURRENT_STATE_NUMBER = next_state; 
        CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
        CURRENT_WORD_IS_IDENTIFIER = false;
    }

    return;
}

void characters_perform_transition(char *string, char state_character, int next_state) 
{
    if (state_character == string[CURRENT_RIGHT_COUNT]) {
        CURRENT_STATE_NUMBER = next_state; 
        CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
        CURRENT_WORD_IS_IDENTIFIER = false;

    }
    else if (string[CURRENT_RIGHT_COUNT] == ' ')
        printf("Whitespace, ignore for now \n");

    else {
        // Head to identifier state if not possible
        CURRENT_STATE_NUMBER = 0 ;
        CURRENT_WORD_IS_IDENTIFIER = true;
    }

    return;

}

void accept_and_print( char *string, char *keyword_formed)
{
    char otherString[CURRENT_RIGHT_COUNT+1]; // note 6, not 5, there's one there for the null terminator
    strcpy(otherString,subString(string,CURRENT_LEFT_COUNT, CURRENT_RIGHT_COUNT));
    otherString[CURRENT_RIGHT_COUNT+1] = '\0'; // place the null terminator

    printf("%s - %s\n",keyword_formed,otherString);

    CURRENT_LEFT_COUNT = CURRENT_RIGHT_COUNT;
    CURRENT_STATE_NUMBER = 0;

    CURRENT_WORD_IS_IDENTIFIER = false;

    return;

    // Head to identifier state again if not possible
}

void FA_parse (char *string )
{
  int len = strlen(string);
  //const char* value;
  //

  while(CURRENT_RIGHT_COUNT <= len && CURRENT_LEFT_COUNT <= CURRENT_RIGHT_COUNT) {
      printf("%c - %d\n",CURRENT_LETTER,CURRENT_STATE_NUMBER);


      switch(CURRENT_STATE_NUMBER) {
          case 0:
              /*perform_transition(string,'+', 1);*/
              perform_transition(string,'-',2);
              perform_transition(string,'*',3);
              perform_transition(string,'/',4);
              perform_transition(string,'%',5);
              perform_transition(string,'~',6);
              perform_transition(string,'*',7);
              perform_transition(string,'B',16);
              perform_transition(string,'C',24);
              perform_transition(string,'D',10);
              perform_transition(string,'E',11);
              perform_transition(string,'F',12);
              perform_transition(string,'G',13);
              /*perform_transition(string,'I',14);*/
              /*perform_transition(string,'L',15);*/
              /*perform_transition(string,'P',16);*/
              /*perform_transition(string,'R',17);*/
              /*perform_transition(string,'S',18);*/
              /*perform_transition(string,'U',19);*/
              /*perform_transition(string,'W',20);*/
              /*perform_transition(string,'i',21);*/
              /*perform_transition(string,'p',22);*/

              if (CURRENT_WORD_IS_IDENTIFIER && (CURRENT_LETTER != ' ')) {
                  // perform regex check to ensure string is a VALID Identifier
                  perform_transition(string,CURRENT_LETTER,0);
              }
              else if (CURRENT_WORD_IS_IDENTIFIER) {
                  perform_transition(string,CURRENT_LETTER,1);
              }

              CURRENT_RIGHT_COUNT++;
              break;
        // case for identifier
        case 1:
              accept_and_print(string, "IDENTIFIER");
              break;

              /*printf("\nEnd State for +");*/
        case 16:
              characters_perform_transition(string, 'R',17);
              characters_perform_transition(string,'O',21);

              CURRENT_RIGHT_COUNT++;
              break;
        case 17:
              characters_perform_transition(string, 'E',18);

              CURRENT_RIGHT_COUNT++;
              break;
        case 18:
              characters_perform_transition(string,'A',19);

              CURRENT_RIGHT_COUNT++;
              break;
        case 19:
              characters_perform_transition(string,'K',20);

              CURRENT_RIGHT_COUNT++;
              break;
        case 20:
              accept_and_print(string,"KEYWORD_BREAK");

              CURRENT_RIGHT_COUNT++;
              break;
        case 21:
              characters_perform_transition(string,'O',22);

              CURRENT_RIGHT_COUNT++;
              break;
        case 22:
              characters_perform_transition(string,'L',23);

              CURRENT_RIGHT_COUNT++;
              break;
        case 23:
              accept_and_print(string,"KEYWORD_BOOL");

              CURRENT_RIGHT_COUNT++;
              break;
        case 24:
              characters_perform_transition(string,'A',25);
              /*characters_perform_transition(*/
              CURRENT_RIGHT_COUNT++;
              break;
        case 25:
              characters_perform_transition(string,'S',26);
              CURRENT_RIGHT_COUNT++;
              break;
        case 26:
              characters_perform_transition(string,'E',27);
              CURRENT_RIGHT_COUNT++;
              break;
        case 27:
              accept_and_print(string,"KEYWORD_CASE");




        /*case 2:*/
              /*printf("Do Something 2");*/
        /*case 3:*/
              /*printf("Do Something");*/
        /*case 4:*/
              /*printf("Do Something");*/
        /*case 5:*/
              /*printf("Do Something");*/
        /*case 6:*/
              /*printf("Do Something");*/
        case 8:
              printf("The Current State is 8");
              CURRENT_RIGHT_COUNT++;

    }

  }

}

// DRIVER FUNCTION
int main()
{
     // maximum length of string is 100 here
     // Global Variables 
    bool DEBUG = true ;

    dest_fp = fopen("results.mul","w");

    // DEBUG Mode: Just for minor line tests
    if (DEBUG) {
        char str[100] = "BOOL z ";//has a bug with H^20 & two operator characters

        /*CURRENT_STRING = str;*/

        FA_parse(str); // calling the parse function
    }
    // DEBUG-OFF Mode: Accepts an entire file and converts it all into another file containing lexeme tokens.
    else {
        char line[100] ;
        size_t len = 0 ;

        ssize_t read;
        char *val;


        fptr = fopen("file.mul","r");

        if (fptr == NULL) {
            printf("Can't Open File");
            return 0 ;
        }

        while (val = fgets(line,100, fptr)) {
            parse(val);
        }

        fclose(fptr);
    }

    return (0);
}
