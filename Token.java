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
        EQUALS_TO("==", false, true),
        NOT_EQUALS_TO("!=", false, true),
        LESS_EQUAL("<=", false, true),
        GREATER_EQUAL(">=", false, true),
        PLUS_EQUAL("+=", false, true),
        MINUS_EQUAL("-=", false, true),
        MULTIPLY_EQUAL("*=", false, true),
        DIVIDE_EQUAL("/=", false, true),
        MODULE_EQUAL("%=", false, true),
        INTEGER_DIVISION("//", false, true),
        EXPONENT("**", false, true),
        INCREMENT("++", true, false),
        DECREMENT("--", true, false),
        LOGICAL_OR("||", false, true),
        LOGICAL_AND("&&", false, true),
        NON_OPERATOR, // Extra flags for lexer

        // Single Operators
        PLUS("+", false, true),
        MINUS("-", false, true),
        MULTIPLY("*", false, true),
        DIVIDE("/", false, true),
        GREATER_THAN(">", false, true),
        LESS_THAN("<", false, true),
        ASSIGNMENT("=", false, true),
        MODULO("%", false, true),
        NOT_EQUAL("!", true, false),

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
        private boolean unary;
        private boolean binary;
        Type() { this(null, false, false); }
        Type(String lexeme) { this(lexeme, false, false); }
        Type(String lexeme, boolean unary, boolean binary) {
            this.lexeme = lexeme;
            this.unary = unary;
            this.binary = binary;
        }
        public String lexeme() { return lexeme; }
        public boolean isUnary() { return unary; }
        public boolean isBinary() { return binary; }
    }
}
