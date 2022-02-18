#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int CURRENT_LINE = 1 ; 

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
	char *str = "NonTwoOperator";
	
	//Evaluates if a and b are TO expressions by comparing the two simultaneously
	if(a == '=' && b == '='){
		str = "Operator_EqualsTo";
		return str;
	}
 	else if(a == '!' && b == '='){
		str = "Operator_NotEqualsTo";
		return str;
	}
	else if(a == '<' && b == '='){
		str = "Operator_LessEqual";
		return str;
	}
	else if(a == '>' && b == '='){
		str = "Operator_GreaterEqual";
		return str;
	}
	else if(a == '+' && b == '='){
		str = "Operator_PlusEqual";
		return str;
	}
	else if(a == '-' && b == '='){
		str = "Operator_MinusEqual";
		return str;
	}
	else if(a == '*' && b == '='){
		str = "Operator_MultiplyEqual";
		return str;
	}
	else if(a == '/' && b == '='){
		str = "Operator_DivideEqual";
		return str;
	}
	else if(a == '%' && b == '='){
		str = "Operator_ModuleEqual";
		return str;
	}
	else if(a == '~' && b == '/'){
		str = "Operator_IntegerDivision";
		return str;
	}
	else if(a == '*' && b == '*'){
		str = "Operator_Exponent";
		return str;
	}
	else if(a == '+' && b == '+'){
		str = "Operator_Increment";
		return str;
	}
	else if(a == '-' && b == '-'){
		str = "Operator_Decrement";
		return str;
	}
	else if(a == '|' && b == '|'){
		str = "Operator_LogicalOR";
		return str;
	}
	else if(a == '&' && b == '&'){
		str = "Operator_LogicalAND";
		return str;
	}
		
	if(!strcmp(str, "NonTwoOperator")){//bug comes from here
		if (b == '+')
			return "Operator_Plus";
		else if (b == '-')
			return "Operator_Minus";
		else if (b == '*')
			return "Operator_Multiply";
		else if (b == '/')
			return "Operator_Divide";
		else if (b == '>')
			return "Operator_Greaterthan";
		else if (b == '<')
			return "Operator_Lessthan";
		else if (b == '=')
			return "Operator_Equals";
		else if (b == '%')
			return "Operator_Modulo";
		else if (b == '!')
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
				str1[i] = str[i+1];//has bug with space
				i += 1;
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

bool isSingleComment(int n){
	if(n == 1)
		return (true);
	return false;
}

bool isMultiComment(int m){
	if(m == 1)
		return (true);
	return false;
}

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
    int left = 0, right = 0, n=0, m=0;
    int len = strlen(str);
    //const char* value;
    //
    FILE *dest_fp;
    dest_fp = fopen("results.mul","w");
    
// 	printf("Token\tLexeme\n\n");
    while (right <= len && left <= right) {
                
        if (isDelimiter(str[right]) == "NonDelimiter")
            right++;
		        
        if (isDelimiter(str[right]) != "NonDelimiter" && left == right) {
        	if(isDelimiter(str[right]) != "OtherSymbol"){
        		printf("%s '%c'\n", isDelimiter(str[right]), str[right]);
            	fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isDelimiter(str[right]));
			}

			else if(str[right]=='/' && str[right-1]=='/')
				n=1;
			
			else if(str[right]=='*' && str[right-1]=='/')
				m=1;
				
				//Takes two consecutive characters and send them to isTOExpression 
            else if (isOperator(str[right-1],str[right]) != "NonOperator") {
                printf("%s\n", isOperator(str[right-1],str[right]));
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isOperator(str[right-1],str[right]));
            }
            
            else if(isChemOperator(str[right]) != "NonChemOperator") {
            	printf("%s '%c'\n", isChemOperator(str[right]), str[right]);
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], isChemOperator(str[right]));
            }
 			else if(str[right]=='\n')
 				n=0;
 			else if(str[right]=='/' && str[right-1]=='*'){
 					printf("End of a comment\n");
 					m=0;
			 }
 				
 			
            right++;
            left = right;
        } else if (isDelimiter(str[right]) != "NonDelimiter" && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
 
 			if (isSingleComment(n) == true)
                printf("COMMENT '%s'\n", subStr);
            
            else if (isMultiComment(m) == true
					&& isDelimiter(str[right - 1]) == "NonDelimiter")
                printf("COMMENT '%s'\n", subStr);
            
            else if (isKeyword(subStr) == true) { 
                printf("KEYWORD '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "KEYWORD");
            }

            else if (isBoolean(subStr) == true) { 
                printf("BOOLEAN '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "BOOLEAN");
            }
 
            else if (isInteger(subStr) == true)
                printf("INTEGER '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "INTEGER");
 
            else if (isRealNumber(subStr) == true)
                printf("REAL NUMBER '%s'\n", subStr);

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == "NonDelimiter"
					 && isChemOperator(str[right - 1]) == "NonChemOperator"
					 && isMultiComment(m) == false) {
                printf("IDENTIFIER '%s'\n", subStr);
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "IDENTIFIER");
            }
            
            else if (isString(subStr) != "NonString")
                printf("STRING '%s'\n", isString(subStr));
                fprintf(dest_fp,"%d %d %s %s\n",CURRENT_LINE,right, subStr, "String");

            
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
                fprintf(dest_fp,"%d %d %c %s\n",CURRENT_LINE,right,str[right], subStr, "INVALID");
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
    bool DEBUG = false ;

    // DEBUG Mode: Just for minor line tests
    if (DEBUG) {

        char str[100] = "INT .a_nt = ~[H^20] >= .1;\n~H + FLOAT %2a \"longsussy\" \'c\' TRUE false //Thisisacomment\n";//has a bug with H^20 & two operator characters
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
