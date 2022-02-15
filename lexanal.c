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
bool validIdentifier(char* str){
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) != "NonDelimiter" ||
    str[0] == '"' || str[0] == '\'')
        return (false);
    return (true);
}

// Returns 'true' if the string is an STRING.
const char* isString(char* str){
    int i = 0, f = 0, l = 0, x, len = strlen(str);
 	
    if (len == 0)
        return "NonString";
    for (i = 0; i < len; i++) {
        if (str[0] == '"' && str[i] == '"'){
        	while(str[f]=='"'){
				f += 1;
			}
			l = len - 1;
			while(str[l]=='"'){
				l -= 1;
			}
			len = l - f;
			char *str1 = (char*)malloc(len);
			while(i < len){
				str1[i] = str[f];//has bug with \n
				i += 1;
				f += 1;
			}
			str1[i] = '\0';
			return str1;
		}
    }
	
    return "NonString";
}

// Returns 'true' if the string is an CHARACTER.
const char* isChar(char* str){
    int i, len = strlen(str);
 	char *ch = (char*)malloc(len);
    if (len == 0)
        return (false);

    if (str[0] == '\'' && str[2] == '\''){
    	ch[0] = str[1];
    	ch[1] = '\0';
        return ch;
	}
    return "NonCharacter";
}

// Returns 'true' if the string is an CPMMENT.
//bool isComment(char* str)//have to formualte a proper logic for this
//{
//    int i,  len = strlen(str);
// 
//    if (len == 0)
//        return (false);
//    for (i = 0; i < len; i++) {
//        if (str[0] == '/*' && str[i] == '*/')
//            return (true);
//    }
//    return (false);
//}

bool isBoolean(char* str){
	if (!strcmp(str, "TRUE") || !strcmp(str, "FALSE")
		|| !strcmp(str, "true") || !strcmp(str, "false"))
		return (true);
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
        || !strcmp(str, "CONST")       	|| !strcmp(str, "DEFAULT")      
		|| !strcmp(str, "INT")			|| !strcmp(str, "FOR")          
		|| !strcmp(str, "PRINTF")		|| !strcmp(str, "SIGNED")       
		|| !strcmp(str, "SCANF")		|| !strcmp(str, "STRING")       
		|| !strcmp(str, "MAIN")			|| !strcmp(str, "printchel")    
		|| !strcmp(str, "impcomp")		|| !strcmp(str, "pcm")          
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
        		printf("%s '%c'\n", isDelimiter(str[right]), str[right]);
            	fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
			}
				//Takes two consecutive characters and send them to isTOExpression 
            else if (isOperator(str[right-1],str[right]) != "NonOperator") {
                printf("%s\n", isOperator(str[right-1],str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isOperator(str[right-1],str[right]));
            }

            else if(isChemOperator(str[right]) != "NonChemOperator") {
            	printf("%s '%c'\n", isChemOperator(str[right]), str[right]);
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
            
                        
            else if (isBoolean(subStr) == true) { 
                printf("BOOLEAN '%s'\n", subStr);
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
            
            else if (isString(subStr) != "NonString")
                printf("STRING '%s'\n", isString(subStr));

//            else if (isComment(subStr) == true)//doesn't work properly
//                printf("COMMENT '%s'\n", subStr);
            
			else if (isChar(subStr) != "NonCharacter")
                printf("CHARACTER '%s'\n", isChar(subStr));
            
            else if (validIdentifier(subStr) == true
					 && isChemOperator(str[right - 1]) != "NonChemOperator") {
                printf("%s '%c'\n", isChemOperator(str[right - 1]), str[right - 1]);
                fprintf(dest_fp,"%d %d %s\n",CURRENT_LINE,right, isChemOperator(str[right-1]));
           }

            else if (validIdentifier(subStr) == false

                	&& isDelimiter(str[right - 1]) == "NonDelimiter")
                printf("'%s' IS INVALID\n", subStr);
            left = right;
        }
    }

    CURRENT_LINE++;
    return;
}

void perform_transition(char *string, char state_character, int next_state)
{
    printf("Run Transition : %d %c\n",next_state, string[CURRENT_RIGHT_COUNT]);

    if ((state_character == string[CURRENT_RIGHT_COUNT])) {
        CURRENT_STATE_NUMBER = next_state; 
        CURRENT_RIGHT_COUNT++;
        CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
        CURRENT_WORD_IS_IDENTIFIER = false;
    }

    return;
}

void characters_perform_transition(char *string, char state_character, int next_state) 
{
    if (state_character == string[CURRENT_RIGHT_COUNT]) {
        CURRENT_STATE_NUMBER = next_state; 
        CURRENT_RIGHT_COUNT++;
        CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
        CURRENT_WORD_IS_IDENTIFIER = false;

    }
    else if (string[CURRENT_RIGHT_COUNT] == ' ')
        printf("Whitespace, ignore for now \n");

    else if (!CURRENT_WORD_IS_IDENTIFIER) {
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

    CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
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

  CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];

  while(CURRENT_RIGHT_COUNT <= len && CURRENT_LEFT_COUNT <= CURRENT_RIGHT_COUNT) {
      printf("%c - %d\n",CURRENT_LETTER,CURRENT_STATE_NUMBER);
      switch(CURRENT_STATE_NUMBER) {
          case 0:
              /*perform_transition(string,'+', 1);*/
              if (CURRENT_LETTER == '-')
                perform_transition(string,'-',2);
              else if (CURRENT_LETTER =='*')
                perform_transition(string,'*',3);
              else if (CURRENT_LETTER == '/')
                perform_transition(string,'/',4);
              else if (CURRENT_LETTER == '%')
                  perform_transition(string,'%',5);
              else if (CURRENT_LETTER == '~')
                  perform_transition(string,'~',6);
              else if (CURRENT_LETTER == '*')
                  perform_transition(string,'*',7);
              else if (CURRENT_LETTER == 'B')
                  perform_transition(string,'B',16);
              else if (CURRENT_LETTER == 'C')
                  perform_transition(string,'C',24);
              else if (CURRENT_LETTER == 'D')
                  perform_transition(string,'D',10);
              else if (CURRENT_LETTER == 'E')
                  perform_transition(string,'E',11);
              else if (CURRENT_LETTER == 'F')
                  perform_transition(string,'F',12);
              else if (CURRENT_LETTER == 'G')
                  perform_transition(string,'G',13);

              /*perform_transition(string,'I',14);*/
              /*perform_transition(string,'L',15);*/
              /*perform_transition(string,'P',16);*/
              /*perform_transition(string,'R',17);*/
              /*perform_transition(string,'S',18);*/
              /*perform_trans
            case 30: WORD_STATE(TRANSITION('_', 31));
            case 31: WORD_STATE(TRANSITION('d', 32));
            case 32: WORD_STATE(TRANSITION('e', 33));ition(string,'U',19);*/
              /*perform_transition(string,'W',20);*/
              /*perform_transition(string,'i',21);*/
              /*perform_transition(string,'p',22);*/
              else if (isalpha(CURRENT_LETTER) || (CURRENT_LETTER == '_')) {
                  // perform regex check to ensure string is a VALID Identifier
                  while(isalpha(CURRENT_LETTER) || (CURRENT_LETTER == '_')) {
                      CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
                      CURRENT_RIGHT_COUNT++;
                  }
                  accept_and_print(string, "IDENTIFIER");
              }
              else {
                  printf("WHITESPACE\n");
                  CURRENT_RIGHT_COUNT++;
                  CURRENT_LETTER = string[CURRENT_RIGHT_COUNT];
              }

              break;
        // case for identifier
        case 1:
              accept_and_print(string, "IDENTIFIER");
              break;

              /*printf("\nEnd State for +");*/
        case 16:
              if (CURRENT_LETTER == 'R')
                  characters_perform_transition(string, 'R',17);
              else if (CURRENT_LETTER == 'O')
                  characters_perform_transition(string,'O',21);
              break;
        case 17:
              characters_perform_transition(string, 'E',18);

              break;
        case 18:
              characters_perform_transition(string,'A',19);
              break;
        case 19:
              characters_perform_transition(string,'K',20);
              break;
        case 20:
              accept_and_print(string,"KEYWORD_BREAK");
              break;
        case 21:
              characters_perform_transition(string,'O',22);
              /*characters_perform_transition(string,*/


              break;
        case 22:
              characters_perform_transition(string,'L',23);

        /*case 31: WORD_STATE(TRANSITION('d', 32));*/
        /*case 32: WORD_STATE(TRANSITION('e', 33));*/

              break;
        case 23:
              accept_and_print(string,"KEYWORD_BOOL");
              break;
        case 24:
              if (CURRENT_LETTER == 'A')
                  characters_perform_transition(string,'A',25);
              else if (CURRENT_LETTER == 'H')
                  characters_perform_transition(string,'H',28);
              else if (CURRENT_LETTER == 'O')
                  characters_perform_transition(string,'O',31);

              break;
        case 25:
              characters_perform_transition(string,'S',26);
              break;
        case 26:
              characters_perform_transition(string,'E',27);

              break;
        case 27:
              accept_and_print(string,"KEYWORD_CASE");
        case 28:
              characters_perform_transition(string,'A',29);
              break;
        case 29:
              characters_perform_transition(string,'R',30);
        case 30:
              accept_and_print(string,"KEYWORD_CHAR");
              break;
        case 31:
              characters_perform_transition(string,'O',32);
              break;
        case 32:
              characters_perform_transition(string,'N',33);
              break;
        case 33:
              characters_perform_transition(string,'T',34);
              break;
        case 34:
              characters_perform_transition(string,'I',35);
              break;
        case 35:
              characters_perform_transition(string,'N',36);
              break;
        case 36:
              characters_perform_transition(string,'U',37);
              break;
        case 37:
              characters_perform_transition(string,'E',38);
              break;
        case 38:
              accept_and_print(string,"KEYWORD_CONTINUE");
              break;










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
    bool DEBUG = false ;

    dest_fp = fopen("results.mul","w");

    // DEBUG Mode: Just for minor line tests
    if (DEBUG) {
        char str[100] = "CONTINUE";//has a bug with H^20 & two operator characters

        /*CURRENT_STRING = str;*/

        FA_parse(str); // calling the parse function
    }
    // DEBUG-OFF Mode: Accepts an entire file and converts it all into another file containing lexeme tokens.
    else {
        size_t len = 0 ;

        ssize_t read;
        char *val;


        fptr = fopen("file.mul","r");

        if (fptr == NULL) {
            printf("Can't Open File");
            return 0 ;
        }

        while (val = fgets(CURRENT_STRING,100, fptr)) {

            CURRENT_LINE = 1 ; 
            CURRENT_STATE_NUMBER = 0;

            CURRENT_LEFT_COUNT = 0;
            CURRENT_RIGHT_COUNT = 0;

            CURRENT_LETTER = ' ';

            CURRENT_WORD_IS_IDENTIFIER = false;

            FA_parse(val);
        }

        fclose(fptr);
    }

    return (0);
}
