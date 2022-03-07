/**
 * Data class for a token.
 */
public record Token(int lineNumber, int columnNumber, String lexeme, Type type) {

    public enum Type {
        // Delimiters
        SEMICOLON(";"),
        PAREN_LEFT("("),
        PAREN_RIGHT(")"),
        BRACES_LEFT("{"),
        BRACES_RIGHT("}"),
        COLON(":"),
        COMMA(","),
        OTHER_SYMBOL,
        NON_DELIMITER, // Extra flags for lexer

        // Operators
        EQUALS_TO("=="),
        NOT_EQUALS_TO("!="),
        LESS_EQUAL("<="),
        GREATER_EQUAL(">="),
        PLUS_EQUAL("+="),
        MINUS_EQUAL("-="),
        MULTIPLY_EQUAL("*="),
        DIVIDE_EQUAL("/="),
        MODULE_EQUAL("%="),
        INTEGER_DIVISION("//"),
        EXPONENT("**"),
        INCREMENT("++"),
        DECREMENT("--"),
        LOGICAL_OR("||"),
        LOGICAL_AND("&&"),
        NON_OPERATOR, // Extra flags for lexer

        // Single Operators
        PLUS("+"),
        MINUS("-"),
        MULTIPLY("*"),
        DIVIDE("/"),
        GREATER_THAN(">"),
        LESS_THAN("<"),
        ASSIGNMENT("="),
        MODULO("%"),
        NOT_EQUAL("!"),

        // Chemical Operators
        TILDE("~"),
        CARET("^"),
        BRACKET_LEFT("["),
        BRACKET_RIGHT("]"),
        NON_CHEM_OPERATOR, // Extra flags for lexer

        // Constants
        STRING_LITERAL("string literal"),
        CHARACTER_LITERAL("character literal"),
        REAL_NUMBER_LITERAL("real number literal"),
        INTEGER_LITERAL("integer literal"),
        // Boolean Constants
        TRUE_LITERAL("true"),
        FALSE_LITERAL("false"),

        NON_STRING,
        NON_CHARACTER,
        NON_BOOLEAN,

        // Keywords
        IF("IF"),
        ELSE("ELSE"),
        WHILE("WHILE"),
        DO("DO"),
        BREAK("BREAK"),
        CONTINUE("CONTINUE"),
        DOUBLE("DOUBLE"),
        FLOAT("FLOAT"),
        RETURN("RETURN"),
        CHAR("CHAR"),
        CASE("CASE"),
        BOOL("BOOL"),
        SIZEOF("SIZEOF"),
        LONG("LONG"),
        SHORT("SHORT"),
        TYPEDEF("TYPEDEF"),
        SWITCH("SWITCH"),
        UNSIGNED("UNSIGNED"),
        VOID("VOID"),
        STATIC("STATIC"),
        STRUCT("STRUCT"),
        GOTO("GOTO"),
        CONST("CONST"),
        DEFAULT("DEFAULT"),
        INT("INT"),
        FOR("FOR"),
        PRINTF("PRINTF"),
        SIGNED("SIGNED"),
        SCANF("SCANF"),
        STRING("STRING"),
        MAIN("MAIN"),
        PRINTCHEL("printchel"),
        IMCOMP("imcomp"),
        PCM("pcm"),
        REACT("react"),
        NON_KEYWORD, // Extra flags for lexer

        // Identifier
        IDENTIFIER,

        // Chemical Expression
        CHEMICAL_EXPRESSION,

        // Comments
        COMMENT,

        // Invalid
        INVALID;

        private String lexeme;
        Type() { this(null); }
        Type(String lexeme) { this.lexeme = lexeme; }
        public String lexeme() { return lexeme; }
    }
}
