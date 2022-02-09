#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int CURRENT_LINE = 1 ; 

// Returns 'true' if the character is a DELIMITER.
const char* isDelimiter(char ch)
{
    if (ch == ' ') 
		return "Delimiter_Blankspace";
	else if (ch == ';') 
		return "Delimiter_Semicolon";
	else if (ch == '(')
		return "Delimiter_ParenLeft";
	else if (ch == ')')
		return "Delimiter_ParenRight";
    else if (ch == '[')
		return "Delimiter_BracketLeft";
	else if (ch == ']')
		return "Delimiter_BracketRight";
	else if (ch == '{')  
		return "Delimiter_BracesLeft";
	else if (ch == '}')
		return "Delimiter_BracesRight";
	else if (ch == '+')
		return "Delimiter";
	else if (ch == '-')
		return "Delimiter";
	else if (ch == '*')
		return "Delimiter";
	else if (ch == '/')
		return "Delimiter";
	else if (ch == ',')
		return "Delimiter";
	else if (ch == '>')
		return "Delimiter";
	else if (ch == '<')
		return "Delimiter";
	else if (ch == '=')
		return "Delimiter";
  return "Not a Delimiter";
}

//Returns string if two chars are TO Expressions
 const char* isTOExpression(char left, char right){
 	char a = left;
	char b = right;
	
	//Evaluates if a and b are TO expressions by comparing the two simultaneously
	 if(a == '=' && b == '=')
 		return "Equal to Operator";
 	else if(a == '!' && b == '=')
	 	return "Not equal to operator";
	else if(a == '<' && b == '=')
		return "Less than or equal to operator";
	else if(a == '>' && b == '=')
		return "Greater than or equal to operator";
	return "Not a TO Expression";	
} 

//edit this
// Returns 'true' if the character is an OPERATOR.
const char* isOperator(char ch)
{
    if (ch == '+')
		return "Operator_plus";
	else if (ch == '-')
		return "Operator_minus";
	else if (ch == '*')
		return "Operator_multiply";
	else if (ch == '/')
        return "Operator_divide";
	else if (ch == '>')
		return "Operator_greaterthan";
	else if (ch == '<') 
		return "Operator_lessthan";
	else if (ch == '=')
        return "Operator_equals";
    return "Not an Operator";
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
		return "ChemOperaror_BracketRight";
    return "Not a ChemOperator";
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) != "Not a Delimiter")
        return (false);
    return (true);
}
 
// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{

    if (   !strcmp(str, "IF")           || !strcmp(str, "ELSE") 
        || !strcmp(str, "WHILE")        || !strcmp(str, "DO") 
        || !strcmp(str, "BREAK")        || !strcmp(str, "CONTINUE") 
        || !strcmp(str, "DOUBLE")       || !strcmp(str, "FLOAT")
        || !strcmp(str, "RETURN")       || !strcmp(str, "CHAR")
        || !strcmp(str, "CASE")         || !strcmp(str, "CHAR")
        || !strcmp(str, "SIEZEOF")      || !strcmp(str, "LONG")
        || !strcmp(str, "SHORT")        || !strcmp(str, "TYPEDEF")
        || !strcmp(str, "SWITCH")       || !strcmp(str, "UNSIGNED")
        || !strcmp(str, "VOID")         || !strcmp(str, "STATIC")
        || !strcmp(str, "STRUCT")       || !strcmp(str, "GOTO")
        || !strcmp(str, "CONST")        || !strcmp(str, "GOTO")
        || !strcmp(str, "DEFAULT")      || !strcmp(str, "INT")
        || !strcmp(str, "FOR")          || !strcmp(str, "PRINTF")
        || !strcmp(str, "SIGNED")       || !strcmp(str, "SCANF")
        || !strcmp(str, "STRING")       || !strcmp(str, "INT")
        || !strcmp(str, "printchel")    || !strcmp(str, "impcomp")
        || !strcmp(str, "pcm")          || !strcmp(str, "react"))
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
                
        if (isDelimiter(str[right]) == "Not a Delimiter")
            right++;
            
        //Takes two consecutive characters and send them to isTOExpression 
		if (isTOExpression(str[left],str[right]) != "Not a TO Expression")
            printf("TO EXPRESSION '%s'\n", isTOExpression(str[right-1],str[right]));
		        
        if (isDelimiter(str[right]) != "Not a Delimiter" && left == right) {
        	printf("%s\n", isDelimiter(str[right]));
            fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
            
            
          
            if (isOperator(str[right]) != "Not an Operator") {
                printf("%s\n", isOperator(str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isOperator(str[right]));
            }
            else if(isChemOperator(str[right]) != "Not a ChemOperator") {
            	printf("%s\n", isChemOperator(str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isChemOperator(str[right]));
            }
 
            right++;
            left = right;
        } else if (isDelimiter(str[right]) != "Not a Delimiter" && left != right
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
                     && isDelimiter(str[right - 1]) == "Not a Delimiter"
					 && isChemOperator(str[right - 1]) == "Not a ChemOperator") {
                printf("IDENTIFIER '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "IDENTIFIER");
            }
            
           else if (validIdentifier(subStr) == true
					 && isChemOperator(str[right - 1]) != "Not a ChemOperator") {
                printf("%s\n", isChemOperator(str[right - 1]));
                fprintf(dest_fp,"%d %d %s\n",CURRENT_LINE,right, isChemOperator(str[right-1]));
           }

            else if (validIdentifier(subStr) == false
                	&& isDelimiter(str[right - 1]) == "Not a Delimiter")
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }

    CURRENT_LINE++;
    return;
}

// DRIVER FUNCTION
int main()
{
     // maximum length of string is 100 here
     // Global Variables 
    bool DEBUG = true ;

    // DEBUG Mode: Just for minor line tests
    if (DEBUG) {
        char str[100] = ">=";//has a bug with other delimiters and identifiers where they also appear along with the display of TO

        parse(str); // calling the parse function
    }
    // DEBUG-OFF Mode: Accepts an entire file and converts it all into another file containing lexeme tokens.
    else {
        char line[100] ;
        size_t len = 0 ;
        FILE *fptr;
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