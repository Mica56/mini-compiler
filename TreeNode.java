import java.util.LinkedList;

/**
 * A syntax tree node. A node is modeled with
 * multiple children, so the resulting tree is
 * a general tree data structure.
 */
public class TreeNode {

    private Type type;
    private String value;
    private LinkedList<TreeNode> children;

    public TreeNode(Type type, String value) {
        this.type = type;
        this.value = value;
        children = new LinkedList<>();
    }

    public Type getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public final LinkedList<TreeNode> getChildren() {
        return children;
    }

    public void addChild(TreeNode node) {
        children.add(node);
    }

    @Override
    public String toString() {
        return recursiveStringify(this, 0);
    }

    private static String recursiveStringify(
            TreeNode current, int noOfIndents) {
        StringBuilder stringBuilder = new StringBuilder();
        for(int i = 0; i < noOfIndents; i++)
            stringBuilder.append("\t");

        // Special cases (NODE_TYPE VALUE) as output
        if(current.type == Type.DATA_TYPE ||
                current.type == Type.IDENTIFIER ||
                current.type == Type.CHARACTER_LITERAL ||
                current.type == Type.STRING_LITERAL ||
                current.type == Type.INTEGER_LITERAL ||
                current.type == Type.REAL_NUMBER_LITERAL ||
                current.type == Type.TRUE_LITERAL ||
                current.type == Type.FALSE_LITERAL)
            return stringBuilder.append(current.type)
                    .append(" ")
                    .append(current.value)
                    .append("\n")
                    .toString();

        // Regular case (NODE_TYPE) only
        stringBuilder.append(current.type)
                .append("\n");

        // Output each child recursively
        for(TreeNode child : current.children)
            stringBuilder.append(recursiveStringify(child, noOfIndents + 1));

        return stringBuilder.toString();
    }

    public enum Type {
        MUL_PROG,
        BODY,
        STATEMENTS,

        // Statements
        DEC_STATEMENT,
        IN_STATEMENT,
        OUT_STATEMENT, OUT,
        ASS_STATEMENT,
        CON_STATEMENT, IF_STATEMENT, ELSEIF_STATEMENTS, ELSEIF_STATEMENT, ELSE_STATEMENT,
        ITE_STATEMENT, DO_WHILE_STATEMENT, WHILE_STATEMENT,
        // CHEM_STATEMENT,

        // Expression (Operators)
        SENTINEL(false, 100, false),
        EXPR,

        EQUALS_TO(false, 7, true),
        NOT_EQUALS_TO(false, 7, true),
        LESS_EQUAL(false, 6, true),
        GREATER_EQUAL(false, 6, true),
        PLUS_EQUAL(false, 10, true),
        MINUS_EQUAL(false, 10, true),
        MULTIPLY_EQUAL(false, 10, true),
        DIVIDE_EQUAL(false, 10, true),
        MODULE_EQUAL(false, 10, true),
        INTEGER_DIVISION(false, 4, true),
        EXPONENT(true, 2, false),
        PREFIX_INCREMENT(true, 3, false),
        PREFIX_DECREMENT(true, 3, false),
        POSTFIX_INCREMENT(true, 1, true),
        POSTFIX_DECREMENT(true, 1, true),
        LOGICAL_OR(false, 9, true),
        LOGICAL_AND(false, 8, true),
        PLUS(false, 5, true),
        MINUS(false, 5, true),
        MULTIPLY(false, 4, true),
        DIVIDE(false, 4, true),
        GREATER_THAN(false, 6, true),
        LESS_THAN(false, 6, true),
        ASSIGNMENT(false, 10, true),
        MODULO(false, 4, true),
        NOT_EQUAL(true, 3, false),

        DATA_TYPE,
        STRING_LITERAL,
        CHARACTER_LITERAL,
        REAL_NUMBER_LITERAL,
        TRUE_LITERAL,
        FALSE_LITERAL,
        INTEGER_LITERAL,
        IDENTIFIER;

        private boolean unary;
        private int precedence;
        private boolean leftAssociative;
        // Default constructor for those that do not need the properties
        Type() { this(false, -1, false); }
        // Constructor for operator nodes
        Type(boolean unary, int precedence, boolean leftAssociative) {
            this.unary = unary;
            this.precedence = precedence;
            this.leftAssociative = leftAssociative;
        }
        public boolean isUnary() { return unary; }
        public int getPrecedence() { return precedence; }
        public boolean isLeftAssociative() { return leftAssociative; }
    }

    public static TreeNode toBinary(Token.Type type) {
        switch(type) {
            case EQUALS_TO: return new TreeNode(Type.EQUALS_TO, type.lexeme());
            case NOT_EQUALS_TO: return new TreeNode(Type.NOT_EQUALS_TO, type.lexeme());
            case LESS_EQUAL: return new TreeNode(Type.LESS_EQUAL, type.lexeme());
            case GREATER_EQUAL: return new TreeNode(Type.GREATER_EQUAL, type.lexeme());
            case PLUS_EQUAL: return new TreeNode(Type.PLUS_EQUAL, type.lexeme());
            case MINUS_EQUAL: return new TreeNode(Type.MINUS_EQUAL, type.lexeme());
            case MULTIPLY_EQUAL: return new TreeNode(Type.MULTIPLY_EQUAL, type.lexeme());
            case DIVIDE_EQUAL: return new TreeNode(Type.DIVIDE_EQUAL, type.lexeme());
            case MODULE_EQUAL: return new TreeNode(Type.MODULE_EQUAL, type.lexeme());
            case INTEGER_DIVISION: return new TreeNode(Type.INTEGER_DIVISION, type.lexeme());
            case EXPONENT: return new TreeNode(Type.EXPONENT, type.lexeme());
            case LOGICAL_OR: return new TreeNode(Type.LOGICAL_OR, type.lexeme());
            case LOGICAL_AND: return new TreeNode(Type.LOGICAL_AND, type.lexeme());
            case PLUS: return new TreeNode(Type.PLUS, type.lexeme());
            case MINUS: return new TreeNode(Type.MINUS, type.lexeme());
            case MULTIPLY: return new TreeNode(Type.MULTIPLY, type.lexeme());
            case DIVIDE: return new TreeNode(Type.DIVIDE, type.lexeme());
            case GREATER_THAN: return new TreeNode(Type.GREATER_THAN, type.lexeme());
            case LESS_THAN: return new TreeNode(Type.LESS_THAN, type.lexeme());
            case ASSIGNMENT: return new TreeNode(Type.ASSIGNMENT, type.lexeme());
            case MODULO: return new TreeNode(Type.MODULO, type.lexeme());
            default: return null;
        }
    }

    public static TreeNode toUnary(Token.Type type) {
        switch(type) {
            case INCREMENT: return new TreeNode(Type.PREFIX_INCREMENT, type.lexeme());
            case DECREMENT: return new TreeNode(Type.PREFIX_DECREMENT, type.lexeme());
            case NOT_EQUAL: return new TreeNode(Type.NOT_EQUAL, type.lexeme());
            default: return null;
        }
    }

    public static TreeNode toPostfixUnary(Token.Type type) {
        switch(type) {
            case INCREMENT: return new TreeNode(Type.POSTFIX_INCREMENT, type.lexeme());
            case DECREMENT: return new TreeNode(Type.POSTFIX_DECREMENT, type.lexeme());
            default: return null;
        }
    }
}
