#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//check if this is okay @Jessie
// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

//edit this
// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}
 
// Returns 'true' if the character is an CHEMICAL OPERATOR.
bool isChemOperator(char ch)
{
    if (ch == '~' || ch == '^' || ch == '[' ||
        ch == ']')
        return (true);
    return (false);
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
 
//edit this 
//We don't have the ff. keywords: continue, sizeof, short, typedef, void, static, and struct
// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{
    if (!strcmp(str, "IF") || !strcmp(str, "ELSE") ||
	    !strcmp(str, "BREAK") || !strcmp(str, "CASE") ||
	 	!strcmp(str, "CHAR") || !strcmp(str, "CONST") ||
	 	!strcmp(str, "DEFAULT"	) || !strcmp(str, "FLOAT") ||
	 	!strcmp(str, "DOUBLE") || !strcmp(str, "DO") ||
	 	!strcmp(str, "FOR") || !strcmp(str, "GOTO") ||
	 	!strcmp(str, "INT") || !strcmp(str, "LONG") ||
	 	!strcmp(str, "PRINTF") || !strcmp(str, "RETURN") ||
	 	!strcmp(str, "SIGNED") || !strcmp(str, "SCANF") ||
	 	!strcmp(str, "STRING") || !strcmp(str, "SWITCH") ||
	 	!strcmp(str, "UNSIGNED") || !strcmp(str, "WHILE") ||
	 	!strcmp(str, "printchel") || !strcmp(str, "imcomp") ||
	 	!strcmp(str, "pcm") || !strcmp(str, "react"))
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
 
    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;
 
        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true)
                printf("'%c' IS AN OPERATOR\n", str[right]);
            else if(isChemOperator(str[right]) == true)
            	printf("'%c' IS A CHEMICAL OPERATOR\n", str[right]);
 
            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
 
            if (isKeyword(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);
 
            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);
 
            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);
            
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false
					 && isChemOperator(str[right - 1]) == false)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            
           else if (validIdentifier(subStr) == true
					 && isChemOperator(str[right - 1]) == true)
                printf("'%s' IS A CHEMICAL OPERATOR\n", subStr);

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
    char str[100] = "int .a_nt += 1 + m1 + ~[H^2O]";//has a bug with H^20
 
    parse(str); // calling the parse function
 
    return (0);
}
