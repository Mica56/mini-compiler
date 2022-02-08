#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Returns a string stating what the delimiter is
const char* isDelimiter(char ch)
{
	char intro[] = "DELIMITER IS";
	
	switch(ch){
		case ',': return strncat(intro,"COMMA",5);
		case ';': return strncat(intro,"SEMICOLON",9);
		case '(': return strncat(intro,"PARENTHESIS_LEFT",16);
		case ')': return strncat(intro,"PARENTHESIS_RIGHT",17);
		case '[': return strncat(intro,"BRACKET_LEFT",12);
		case ']': return strncat(intro,"BRACKET_RIGHT",13);
		case '{': return strncat(intro,"CURLY_BRACKET_LEFT",18);
		case '}': return strncat(intro,"CURLY_BRACKET_RIGHT",19);
		default: return NULL;
	}
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
        str[0] == '9' || isDelimiter(str[0]) == true) 
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
 
    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;
 
        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) != "Not an Operator")
                printf("%s\n", isOperator(str[right]));
            else if(isChemOperator(str[right]) != "Not a ChemOperator")
            	printf("%s\n", isChemOperator(str[right]));
 
            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
 
            if (isKeyword(subStr) == true)
                printf("KEYWORD '%s'\n", subStr);
 
            else if (isInteger(subStr) == true)
                printf("INTEGER '%s'\n", subStr);
 
            else if (isRealNumber(subStr) == true)
                printf("REAL NUMBER '%s'\n", subStr);
            
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false
					 && isChemOperator(str[right - 1]) == "Not a ChemOperator")
                printf("IDENTIFIER '%s'\n", subStr);
            
           else if (validIdentifier(subStr) == true
					 && isChemOperator(str[right - 1]) != "Not a ChemOperator")
                printf("%s\n", isChemOperator(str[right - 1]));

            else if (validIdentifier(subStr) == false
                	&& isDelimiter(str[right - 1]) == false)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }
    return;
}
 
// DRIVER FUNCTION
int main()
{
     // maximum length of string is 100 here
    char str[100] = "INT .a_nt += 1 + m1 + ~[H^2O]";//has a bug with H^20
 
    parse(str); // calling the parse function
 
    return (0);
}
