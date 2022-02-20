#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int CURRENT_LINE = 1 ; 
int right = 0 ;

FILE *dest_fp;

// Returns string if the character is a DELIMITER.
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
    else if (ch == ':') 
    return "Delimiter_Colon";
  else if (ch == ',') 
    return "Delimiter_Comma";
  else if (ch == ' ') 
    return "OtherSymbol";
  else if (ch == '\n') 
    return "OtherSymbol";
  else if (ch == '\t') 
    return "OtherSymbol";
  else if (ch == '\v') 
    return "OtherSymbol";
  else if (ch == '|') 
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
  else if (ch == '&')
    return "OtherSymbol";
  else if (ch == '~')
    return "OtherSymbol";
  else if (ch == '^')
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
 
// Returns string if a character is a CHEMICAL OPERATOR.
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
    int i, len = strlen(str);
    if (len == 0)
        return (false);
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) != "NonDelimiter" ||
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
    for (i = 1; i <= len; i++) {
      if(str[i] == ' ' || str[i] == '~' || str[i] == '^' ||
        str[i] == '&' || str[i] == '|')
        return (false);
    }
    if(str[len-1] == '"' || str[len-1] == '\'')
        return (false);

  return (true);
}

// Returns string if it is a STRING.
const char* isString(char* str){
    int i = 0, f = 0, l = 0, len = strlen(str);

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
            while(i < len+1){
                str1[i] = str[i+1];//has bug with ' '
                i += 1;
            }
            str1[i]='\0';
            return str1;
        }
    }
    return "NonString";
}

// Returns 'true' if the string is an CPMMENT.
bool isSingleComment(int n)
{
   if(n==1)
       return (true);
    return (false);
}

bool isMultiComment(int m)
{
   if(m==1)
        return (true);
    return (false);
}

// Returns 'true' if the string is an CHARACTER.
const char* isChar(char* str){
    int i, len = strlen(str);
    char *ch = (char*)malloc(len);
    if (len == 0)
        return "NonCharacter";
    if (str[0] == '\'' && str[2] == '\''){
        ch[0] = str[1];
        ch[1] = '\0';

        return ch;
    }
    return "NonCharacter";
}

//Returns 'true' if string is a Boolean value.
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
        || !strcmp(str, "CONST")        || !strcmp(str, "DEFAULT")      
        || !strcmp(str, "INT")      || !strcmp(str, "FOR")          
        || !strcmp(str, "PRINTF")   || !strcmp(str, "SIGNED")       
        || !strcmp(str, "SCANF")    || !strcmp(str, "STRING")       
        || !strcmp(str, "MAIN")     || !strcmp(str, "printchel")    
        || !strcmp(str, "imcomp")    || !strcmp(str, "pcm")          
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

//Returns string if it is a CHEMICAL ELEMENT
const char* isChemElem(char* str)
{
    if (!strcmp(str, "H"))
        return "ChemElem_Hydrogen";
    else if (!strcmp(str, "He"))
    	return "ChemElem_Helium";
    else if (!strcmp(str, "Li"))
    	return "ChemElem_Lithium";
    else if (!strcmp(str, "Be"))
    	return "ChemElem_Beryllium";
    else if (!strcmp(str, "B"))
    	return "ChemElem_Boron";
    else if (!strcmp(str, "C"))
    	return "ChemElem_Carbon";
    else if (!strcmp(str, "N"))
    	return "ChemElem_Nitrogen";
    else if (!strcmp(str, "O"))
    	return "ChemElem_Oxygen";
    else if (!strcmp(str, "F"))
    	return "ChemElem_Fluorine";
    else if (!strcmp(str, "Ne"))
    	return "ChemElem_Neon";
    else if (!strcmp(str, "Na"))
    	return "ChemElem_Sodium";
    else if (!strcmp(str, "Mg"))
    	return "ChemElem_Magnesium";
    else if (!strcmp(str, "Al"))
    	return "ChemElem_Aluminum";
    else if (!strcmp(str, "Si"))
    	return "ChemElem_Silicon";
    else if (!strcmp(str, "P"))
    	return "ChemElem_Phosphorous";
    else if (!strcmp(str, "S"))
    	return "ChemElem_Sulfur";
    else if (!strcmp(str, "Cl"))
    	return "ChemElem_Chlorine";
    else if (!strcmp(str, "Ar"))
    	return "ChemElem_Argon";
    else if (!strcmp(str, "K"))
    	return "ChemElem_Potassium";
    else if (!strcmp(str, "Ca"))
    	return "ChemElem_Calcium";
    else if (!strcmp(str, "Sc"))
    	return "ChemElem_Scandium";
    else if (!strcmp(str, "Ti"))
    	return "ChemElem_Titanium";
    else if (!strcmp(str, "V"))
    	return "ChemElem_Vanadium";
    else if (!strcmp(str, "Cr"))
    	return "ChemElem_Chromium";
    else if (!strcmp(str, "Mn"))
    	return "ChemElem_Manganese";
    else if (!strcmp(str, "Fe"))
    	return "ChemElem_Iron";
    else if (!strcmp(str, "Co"))
    	return "ChemElem_Cobalt";
    else if (!strcmp(str, "Ni"))
    	return "ChemElem_Nickel";
    else if (!strcmp(str, "Cu"))
    	return "ChemElem_Copper";
    else if (!strcmp(str, "Zn"))
    	return "ChemElem_Zinc";
    else if (!strcmp(str, "Ga"))
    	return "ChemElem_Gallium";
    else if (!strcmp(str, "Ge"))
    	return "ChemElem_Germanium";
    else if (!strcmp(str, "As"))
    	return "ChemElem_Arsenic";
    else if (!strcmp(str, "Se"))
    	return "ChemElem_Selenium";
    else if (!strcmp(str, "Br"))
    	return "ChemElem_Bromine";
    else if (!strcmp(str, "Kr"))
    	return "ChemElem_Krypton";
    else if (!strcmp(str, "Rb"))
    	return "ChemElem_Rubidium";
    else if (!strcmp(str, "Sr"))
    	return "ChemElem_Strontium";
    else if (!strcmp(str, "Y"))
    	return "ChemElem_Yttrium";
    else if (!strcmp(str, "Zr"))
    	return "ChemElem_Zirconium";
    
    return "NonChemElem";
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
    int left = 0, FoundSingleLineComment=0, FoundMultiLineComment=0;
    right = 0;
    int len = strlen(str);
    //const char* value;


    while (right <= len && left <= right) {

        if (isDelimiter(str[right]) == "NonDelimiter")
            right++;

        if (isDelimiter(str[right]) != "NonDelimiter" && left == right) {
          if(isDelimiter(str[right]) != "OtherSymbol"){
            /*printf("%s\n", isDelimiter(str[right]));*/
            fprintf(dest_fp,"%d %8d %8c %8s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
            printf("%d %8d %8c %8s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
          }
          
          else if(str[right]=='/' && str[right-1]=='/')
				    FoundSingleLineComment=1;
				
			    else if(str[right]=='*' && str[right-1]=='/')
				    FoundMultiLineComment=1;
          
          //Takes two consecutive characters and send them to isOperator
            else if (isOperator(str[right-1],str[right]) != "NonOperator") {
                /*printf("%s\n", isOperator(str[right-1],str[right]));*/
                fprintf(dest_fp,"%d %8d %8c %8s\n",CURRENT_LINE,right,' ', isOperator(str[right-1],str[right]));
                printf("%d %8d %8s\n",CURRENT_LINE,right, isOperator(str[right-1],str[right]));
            }

            else if(isChemOperator(str[right]) != "NonChemOperator") {
                /*printf("%s\n", isChemOperator(str[right]));*/
                fprintf(dest_fp,"%d %8d %8c %8s\n",CURRENT_LINE,right,' ', isOperator(str[right-1],str[right]));
                printf("%d %8d %8s\n",CURRENT_LINE,right, isOperator(str[right-1],str[right]));
            }
            else if(str[right]=='\n')
 				      FoundSingleLineComment=0;
 			      else if(str[right]=='/' && str[right-1]=='*')
				      FoundMultiLineComment=0;
				
            right++;
            left = right;
        } else if (isDelimiter(str[right]) != "NonDelimiter" && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isSingleComment(FoundSingleLineComment) == true){
              fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "COMMENT");
              printf("%d %d '%s' %s\n",CURRENT_LINE,right, subStr, "COMMENT");
            }
            
            else if (isMultiComment(FoundMultiLineComment) == true){
            	fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "COMMENT");
            	printf("%d %d '%s' %s\n",CURRENT_LINE,right, subStr, "COMMENT");
			      }

            else if (isKeyword(subStr) == true) {
                fprintf(dest_fp,"%d %8d %8s %8s\n",CURRENT_LINE,right, subStr, "KEYWORD");
                printf("%d %8d %8s %8s\n",CURRENT_LINE,right, subStr, "KEYWORD");
            }
			
            else if (isBoolean(subStr) == true) { 
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "BOOLEAN");
                printf("%d %d '%s' %s\n",CURRENT_LINE,right, subStr, "BOOLEAN");
            }

            else if (isInteger(subStr) == true) {
                fprintf(dest_fp,"%d %8d %8s %8s\n",CURRENT_LINE,right, subStr, "INTEGER");
                printf("%d %8d %8s %8s\n",CURRENT_LINE,right, subStr, "INTEGER");
            }

            else if (isRealNumber(subStr) == true) {
                printf("REAL NUMBER '%s'\n", subStr);
                fprintf(dest_fp,"%d %8d %8s %8s\n",CURRENT_LINE,right, subStr, "REAL NUMBER");
            }

            else if (isRealNumber(subStr) == true){
            	fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "REAL NUMBER");
            	printf("%d %d %s %s\n",CURRENT_LINE,right, subStr, "REAL NUMBER");
			      }

            else if (isChar(subStr) != "NonCharacter"){
              fprintf(dest_fp,"%d %d '%s' %s\n",CURRENT_LINE,right, isChar(subStr), "CHARACTER");
              printf("%d %d '%s' %s\n",CURRENT_LINE,right, isChar(subStr), "CHARACTER");
            }
                
            else if (isString(subStr) != "NonString"){
            	fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, isString(subStr), "STRING");
            	printf("%d %d '%s' %s\n",CURRENT_LINE,right, isString(subStr), "STRING");
			      }
            
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == "NonDelimiter"
           			 && isChemOperator(str[right - 1]) == "NonChemOperator") {
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "IDENTIFIER");
                printf("%d %d '%s' %s\n",CURRENT_LINE,right, subStr, "IDENTIFIER");
            }

            else if (isChemElem(subStr) != "NonChemElem") {
                fprintf(dest_fp,"%d %d %s\n",CURRENT_LINE,right, isChemElem(subStr), "CHEMICAL ELEMENT");
                printf("%d %d %s\n",CURRENT_LINE,right, isChemElem(subStr), "CHEMICAL ELEMENT");

           }

            else
                printf("'%s' IS INVALID\n", subStr);
            left = right;
        }
    }

    CURRENT_LINE++;
    return;
}

int endsWith (char *str, char *end) {
    size_t slen = strlen (str);
    size_t elen = strlen (end);
    if (slen < elen)
        return 0;
    return (strcmp (&(str[slen-elen]), end) == 0);
}

// DRIVER FUNCTION
int main(int argc, char *argv[])
{
     // maximum length of string is 100 here
     // Global Variables 
    bool DEBUG = true ;

    // DEBUG Mode: Just for minor line tests
    if (DEBUG) {
        char line[100] ;
        size_t len = 0 ;
        FILE *fptr;
        ssize_t read;
        char *val;


        fptr = fopen("file.mul","r");
        dest_fp = fopen("output.mul","w");

        if (fptr == NULL) {
            printf("Can't Open File");
            return 0 ;
        }

        while (val = fgets(line,100, fptr)) {
            if (val[0] != '\n') {
                parse(val);
            }
            else {
                CURRENT_LINE++;
            }
        }

        fclose(fptr);
    }
    // DEBUG-OFF Mode: Accepts an entire file and converts it all into another file containing lexeme tokens.
    else {
        char line[100] ;
        size_t len = 0 ;
        FILE *fptr;
        ssize_t read;
        char *val;

        if (argc < 2) {
            printf("Error: no given files.\n");
            printf("Usage is: gcc lexical.out filename.mul\n");
            exit(EXIT_FAILURE);
        }

        if(!endsWith(argv[1],".mul")) {
            printf("Error: invalid file with name %s. It must have a"
                " format of name.mul\n", argv[1]);
            exit(EXIT_FAILURE);
        }



        fptr = fopen(argv[1],"r");
        dest_fp = fopen("output.mul","w");


        if (fptr == NULL) {
            printf("Failed to Open File. Terminating Program.");
            return 0 ;
        }

        while (val = fgets(line,100, fptr)) {
            if (val[0] != '\n') {
                parse(val);
            }
            else {
                CURRENT_LINE++;
            }
        }

        fclose(fptr);
    }

    fclose(dest_fp);
    return (0);
}
