import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;
import java.util.Stack;

public class MulParser {

    // Root of the syntax tree
    private TreeNode root;

    /**
     * Creates a parser, with the given files to operate on.
     * @param neededFiles the needed files, where:
     *                    (0) - the symbol table file
     *                    (1) - the syntax tree file
     */
    public MulParser(File[] neededFiles) {
        // Attempt to create a Scanner for the symbol table file
        try {
            scannerSymbolTable = new Scanner(neededFiles[0]);
        } catch (FileNotFoundException e) {
            // Output a cannot open file message if not opened
            System.out.println(
                    "Error: cannot open file with name: " +
                            neededFiles[0].getName());
            System.exit(1);
        }
        // Attempt to create a PrintWriter for the syntax tree file
        try {
            printerSyntaxTree = new PrintWriter(neededFiles[1]);
        } catch (FileNotFoundException e) {
            // Output a cannot open file message if not opened
            System.out.println(
                    "Error: cannot open syntax tree file with name: " +
                            neededFiles[1].getName());
            System.exit(1);
        }

        // Initialize linked list of tokens
        tokens = new LinkedList<>();
    }

    LinkedList<Token> tokens;
    ListIterator<Token> tokenPointer;
    // Scanner for the symbol table file
    Scanner scannerSymbolTable;
    // PrintWriter for the syntax tree file
    PrintWriter printerSyntaxTree;

    /**
     * Reads the specified symbol table file line by line, and extracts
     * the tokens into a linked list.
     */
    public void initializeSymbols() {
        Token.Type[] tokenTypeValues = Token.Type.values();

        // Clear the token list
        tokens.clear();

        // Read each line of the symbol table file
        while(scannerSymbolTable.hasNextLine()) {
            String[] line = scannerSymbolTable.nextLine().split("@");

            // Read the line and column number
            int lineNumber = Integer.parseInt(line[0]);
            int columnNumber = Integer.parseInt(line[1]);
            // Read the lexeme
            String lexeme = line[2];
            // Read the token type
            int type = Integer.parseInt(line[3]);

            // Create the token
            Token token = new Token(
                    lineNumber,
                    columnNumber,
                    lexeme,
                    tokenTypeValues[type]);
            tokens.add(token);
        }

        // Start iterator at first symbol
        tokenPointer = tokens.listIterator();
    }

    /**
     * Starts the syntax analyzer phase with the given files.
     */
    public void start() {
        mulProg();

        // Output to console
        System.out.println(TreeNode.recursiveStringify(root, 0, true));
        // Output to syntax tree file
        printerSyntaxTree.print(TreeNode.recursiveStringify(root, 0, false));

        // Close stuff
        scannerSymbolTable.close();
        printerSyntaxTree.close();
    }

    /* START OF PRODUCTION RULES */
    private boolean mulProg() {
        root = new TreeNode(TreeNode.Type.MUL_PROG, "MUL_PROG");

        assertMatch(Token.Type.INT);
        assertMatch(Token.Type.MAIN);
        assertMatch(Token.Type.PAREN_LEFT);
        assertMatch(Token.Type.PAREN_RIGHT);
        assertMatch(Token.Type.BRACES_LEFT);
        body(root);
        assertMatch(Token.Type.BRACES_RIGHT);
        assertMatch(Token.Type.RETURN);
        assertMatch(Token.Type.INTEGER_LITERAL);
        assertMatch(Token.Type.SEMICOLON);

        return true;
    }

    private boolean body(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode bodyNode = new TreeNode(TreeNode.Type.BODY, "BODY");

        // Attempt to parse a statement
        if(statements(bodyNode)) {
            while(statements(bodyNode));
            parent.addChild(bodyNode);
            return true;
        }

        // If parsing a statement failed, backtrack then return false
        else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean statements(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode statementsNode = new TreeNode(TreeNode.Type.STATEMENTS, "STATEMENTS");

        if(decStatement(statementsNode) ||
                inStatement(statementsNode) ||
                assStatement(statementsNode, true) ||
                outStatement(statementsNode) ||
                conStatement(statementsNode) ||
                iteStatement(statementsNode)) {
            /* while(decStatement(statementsNode) ||
                    inStatement(statementsNode) ||
                    assStatement(statementsNode, true) ||
                    outStatement(statementsNode) ||
                    conStatement(statementsNode) ||
                    iteStatement(statementsNode)); */
            parent.addChild(statementsNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);

            // EXTRA CHECKS that did not proceed in the recursive descent
            // If identifier, expect input statement or assignment (both with = operator)
            if (match(Token.Type.IDENTIFIER)) {
                if (!match(Token.Type.ASSIGNMENT)) {
                    Token currentToken = tokenPointer.next();
                    System.out.printf(
                            "In line %d:%d: syntax error, expected an input or assignment statement.\n",
                            currentToken.lineNumber(),
                            currentToken.columnNumber(),
                            currentToken.lexeme());
                    System.exit(1);
                }
            }
            // If not curly brace
            // Fallback, no valid statements were found
            else if(!match(Token.Type.BRACES_RIGHT)) {
                Token currentToken = tokenPointer.next();
                System.out.printf(
                        "In line %d:%d: syntax error, expected start of a statement.\n",
                        currentToken.lineNumber(),
                        currentToken.columnNumber());
                System.exit(1);
            }

            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean decStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode decStatementNode = new TreeNode(TreeNode.Type.DEC_STATEMENT, "DEC_STATEMENT");

        if(dataType(decStatementNode) &&
                (assStatement(decStatementNode, false) ||
                        identifier(decStatementNode))) {
            while(match(Token.Type.COMMA) &&
                    (assStatement(decStatementNode, false) ||
                        identifier(decStatementNode)));
            assertMatch(Token.Type.SEMICOLON);

            parent.addChild(decStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean assStatement(TreeNode parent, boolean hasSemicolon) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode assStatementNode = new TreeNode(TreeNode.Type.ASS_STATEMENT, "ASS_STATEMENT");

        if(identifier(assStatementNode) &&
           match(Token.Type.ASSIGNMENT)) {
            boolean proceed = expr(assStatementNode);

            if(hasSemicolon)
                assertMatch(Token.Type.SEMICOLON);

            if(proceed) {
                parent.addChild(assStatementNode);
                return true;
            } else {
                // Get the token
                Token currentToken = tokenPointer.next();
                // Output syntax error message
                System.out.printf(
                        "In line %d:%d: syntax error, invalid input statement. Expected expression but encountered %s.\n",
                        currentToken.lineNumber(),
                        currentToken.columnNumber(),
                        currentToken.lexeme());
                System.exit(1);
            }
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }

        return false;
    }

    private boolean inStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode inStatementNode = new TreeNode(TreeNode.Type.IN_STATEMENT, null);

        // Attempt to match input statement
        if(identifier(inStatementNode) &&
           match(Token.Type.ASSIGNMENT) &&
           match(Token.Type.SCANF)) {
            assertMatch(Token.Type.PAREN_LEFT);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.SEMICOLON);
            parent.addChild(inStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean outStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode outStatementNode = new TreeNode(TreeNode.Type.OUT_STATEMENT, null);

        // Attempt to match output statement
        if(match(Token.Type.PRINTF)) {
            assertMatch(Token.Type.PAREN_LEFT);
            // TODO: handle errors when out() fails
            out(outStatementNode);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.SEMICOLON);
            parent.addChild(outStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean out(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode outNode = new TreeNode(TreeNode.Type.OUT, null);

        // Attempt to match output
        if(expr(outNode)) {
            while(match(Token.Type.COMMA) && expr(outNode));
            parent.addChild(outNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean conStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode conStatementNode = new TreeNode(TreeNode.Type.CON_STATEMENT, null);

        if(ifStatement(conStatementNode) && elseIfStatements(conStatementNode) &&
           elseStatement(conStatementNode)) {
            parent.addChild(conStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean ifStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode ifStatementNode = new TreeNode(TreeNode.Type.IF_STATEMENT, null);

        if(match(Token.Type.IF)) {
            assertMatch(Token.Type.PAREN_LEFT);
            // TODO: Change to expression
            expr(ifStatementNode);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.BRACES_LEFT);
            // TODO: Handle errors for statements inside if
            body(ifStatementNode);
            assertMatch(Token.Type.BRACES_RIGHT);
            parent.addChild(ifStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean elseIfStatements(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode elseIfStatementsNode = new TreeNode(TreeNode.Type.ELSEIF_STATEMENTS, null);

        if(elseIfStatement(elseIfStatementsNode)) {
            while(elseIfStatement(elseIfStatementsNode));
            parent.addChild(elseIfStatementsNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return true;
        }
    }

    private boolean elseIfStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode elseIfStatementNode = new TreeNode(TreeNode.Type.ELSEIF_STATEMENT, null);

        if(match(Token.Type.ELSE) && match(Token.Type.IF)) {
            assertMatch(Token.Type.PAREN_LEFT);
            expr(elseIfStatementNode);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.BRACES_LEFT);
            // TODO: Handle errors for statements inside else if
            body(elseIfStatementNode);
            assertMatch(Token.Type.BRACES_RIGHT);
            parent.addChild(elseIfStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean elseStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode elseStatementNode = new TreeNode(TreeNode.Type.ELSE_STATEMENT, null);

        if(match(Token.Type.ELSE)) {
            assertMatch(Token.Type.BRACES_LEFT);
            // TODO: Handle errors for statements inside else
            body(elseStatementNode);
            assertMatch(Token.Type.BRACES_RIGHT);
            parent.addChild(elseStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return true;
        }
    }

    private boolean iteStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode iteStatementNode = new TreeNode(TreeNode.Type.ITE_STATEMENT, null);

        if(doWhileStatement(iteStatementNode) || whileStatement(iteStatementNode)) {
            parent.addChild(iteStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean doWhileStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode doWhileStatementNode = new TreeNode(TreeNode.Type.DO_WHILE_STATEMENT, null);

        if(match(Token.Type.DO)) {
            assertMatch(Token.Type.BRACES_LEFT);
            body(doWhileStatementNode);
            assertMatch(Token.Type.BRACES_RIGHT);
            assertMatch(Token.Type.WHILE);
            assertMatch(Token.Type.PAREN_LEFT);
            expr(doWhileStatementNode);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.SEMICOLON);

            parent.addChild(doWhileStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean whileStatement(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode whileStatementNode = new TreeNode(TreeNode.Type.WHILE_STATEMENT, null);

        if(match(Token.Type.WHILE)) {
            assertMatch(Token.Type.PAREN_LEFT);
            expr(whileStatementNode);
            assertMatch(Token.Type.PAREN_RIGHT);
            assertMatch(Token.Type.BRACES_LEFT);
            body(whileStatementNode);
            assertMatch(Token.Type.BRACES_RIGHT);

            parent.addChild(whileStatementNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean expr(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode exprNode = new TreeNode(TreeNode.Type.EXPR, null);

        Stack<TreeNode> operators = new Stack<>(),
                         operands = new Stack<>();

        operators.push(new TreeNode(TreeNode.Type.SENTINEL, null));

        if(expression(operators, operands)) {
            exprNode.addChild(operands.pop());
            parent.addChild(exprNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean expression(Stack<TreeNode> operators,
                               Stack<TreeNode> operands) {
        // Parse a single value
        singleVal(operators, operands);
        // Get next token
        Token currentToken = tokenPointer.next();
        while(currentToken.type().isBinary()) {
            TreeNode binaryNode = TreeNode.toBinary(currentToken.type());
            pushOperator(binaryNode, operators, operands);
            singleVal(operators, operands);
            currentToken = tokenPointer.next();
        }
        // Retract by one
        tokenPointer.previous();

        while(operators.peek().getType() != TreeNode.Type.SENTINEL)
            popOperator(operators, operands);

        return true;
    }

    private void pushOperator(TreeNode operatorNode,
                              Stack<TreeNode> operators,
                              Stack<TreeNode> operands) {
        while(isGreaterPrecedence(operators.peek().getType(), operatorNode.getType()))
            popOperator(operators, operands);
        operators.push(operatorNode);
    }

    private void popOperator(Stack<TreeNode> operators,
                             Stack<TreeNode> operands) {
        TreeNode operatorNode = operators.pop();
        // If unary, pop a single operand then attach
        if(operatorNode.getType().isUnary()) {
            TreeNode operand = operands.pop();
            operatorNode.addChild(operand);
            operands.push(operatorNode);
        }
        // Else if binary, pop two operands then attach
        else {
            TreeNode secondOperand = operands.pop(),
                     firstOperand = operands.pop();
            operatorNode.addChild(firstOperand);
            operatorNode.addChild(secondOperand);
            operands.push(operatorNode);
        }
    }

    private boolean isGreaterPrecedence(TreeNode.Type left,
                                        TreeNode.Type right) {
        if(left == TreeNode.Type.SENTINEL)
            return false;
        if(left.getPrecedence() == right.getPrecedence())
            return left.isLeftAssociative();
        return left.getPrecedence() < right.getPrecedence();
    }

    private boolean singleVal(Stack<TreeNode> operators,
                              Stack<TreeNode> operands) {

        TreeNode placeholderParent = new TreeNode(TreeNode.Type.SENTINEL, null);
        if(identifier(placeholderParent)) {
            operands.push(placeholderParent.getChildren().get(0));
            postfixUnary(operators, operands);
            return true;
        } else if(literal(placeholderParent)) {
            operands.push(placeholderParent.getChildren().get(0));
            postfixUnary(operators, operands);
            return true;
        } else if(match(Token.Type.PAREN_LEFT)) {
            operators.push(new TreeNode(TreeNode.Type.SENTINEL, null));
            expression(operators, operands);
            assertMatch(Token.Type.PAREN_RIGHT);
            operators.pop();
            postfixUnary(operators, operands);
            return true;
        } else {
            Token currentToken = tokenPointer.next();
            if(currentToken.type().isUnary()) {
                TreeNode unaryNode = TreeNode.toUnary(currentToken.type());
                pushOperator(unaryNode, operators, operands);
                singleVal(operators, operands);
                postfixUnary(operators, operands);
                return true;
            } else {
                // Output a syntax error message (PANIC MODE STILL)
                System.out.printf(
                        "In line %d:%d: syntax error, expected literal, identifier, unary operator but encountered %s.\n",
                        currentToken.lineNumber(),
                        currentToken.columnNumber(),
                        currentToken.lexeme());
                System.exit(1);
                return false;
            }
        }
    }

    private boolean postfixUnary(Stack<TreeNode> operators,
                                 Stack<TreeNode> operands) {
        int backtrackIndex = tokenPointer.nextIndex();

        Token currentToken = tokenPointer.next();
        if(currentToken.type() == Token.Type.INCREMENT ||
                currentToken.type() == Token.Type.DECREMENT) {
            TreeNode unaryNode = TreeNode.toPostfixUnary(currentToken.type());
            pushOperator(unaryNode, operators, operands);
            postfixUnary(operators, operands);
        } else {
            tokenPointer = tokens.listIterator(backtrackIndex);
        }

        return true;
    }

    private boolean dataType(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode dataTypeNode = new TreeNode(TreeNode.Type.DATA_TYPE, null);

        // Attempt to match a data type keyword
        if(match(Token.Type.INT) ||
           match(Token.Type.FLOAT) ||
           match(Token.Type.STRING) ||
           match(Token.Type.BOOL)) {
            // If matched, get the token
            tokenPointer.previous();
            Token token = tokenPointer.next();
            // Set the node value to "DATATYPE INT" for example
            dataTypeNode.setValue(token.lexeme());
            // Add to parent
            parent.addChild(dataTypeNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean identifier(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        TreeNode identifierNode = new TreeNode(TreeNode.Type.IDENTIFIER, null);

        // Get the next token
        Token currentToken = tokenPointer.next();

        // If token is identifier
        if(currentToken.type() == Token.Type.IDENTIFIER) {
            // Get the lexeme and attach to node string value
            identifierNode.setValue(currentToken.lexeme());
            // Add to parent
            parent.addChild(identifierNode);
            return true;
        } else {
            // Reset the iterator to the backtrack index
            tokenPointer = tokens.listIterator(backtrackIndex);
            return false;
        }
    }

    private boolean literal(TreeNode parent) {
        int backtrackIndex = tokenPointer.nextIndex();
        Token currentToken = tokenPointer.next();

        TreeNode literalNode = null;

        switch(currentToken.type()) {
            case INTEGER_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.INTEGER_LITERAL,
                        currentToken.lexeme());
                break;
            case REAL_NUMBER_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.REAL_NUMBER_LITERAL,
                        currentToken.lexeme());
                break;
            case STRING_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.STRING_LITERAL,
                        currentToken.lexeme());
                break;
            case CHARACTER_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.CHARACTER_LITERAL,
                        currentToken.lexeme());
                break;
            case TRUE_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.TRUE_LITERAL,
                        currentToken.lexeme());
                break;
            case FALSE_LITERAL:
                literalNode = new TreeNode(TreeNode.Type.FALSE_LITERAL,
                        currentToken.lexeme());
                break;
            default:
                // Reset the iterator to the backtrack index
                tokenPointer = tokens.listIterator(backtrackIndex);
                return false;
        }

        parent.addChild(literalNode);
        return true;
    }

    /**
     * Matches the current token against the expected token type.
     * @param expectedType the expected token
     * @return if matched or not
     */
    private boolean match(Token.Type expectedType) {
        // Get the current token
        Token currentToken = tokenPointer.next();
        // If it is the expected token, return true
        if(currentToken.type() == expectedType)
            return true;

        // If invalid, output syntax error
        else if(currentToken.type() == Token.Type.INVALID) {
            System.out.printf(
                    "In line %d:%d: syntax error, invalid token %s.\n",
                    currentToken.lineNumber(),
                    currentToken.columnNumber(),
                    currentToken.lexeme());
            System.exit(1);
            return false;
        }
        // Else, backtrack then return false
        else {
            // If not matched, backtrack the pointer
            tokenPointer.previous();
            return false;
        }
    }

    /**
     * Matches the current token against the expected token type.
     * Will output a syntax error if not matched.
     * @param expectedType the expected token
     * @return if matched or not
     */
    private boolean assertMatch(Token.Type expectedType) {
        // If the expected type did not match the current token
        if(!match(expectedType)) {
            // Get the token
            Token currentToken = tokenPointer.next();
            // Output a syntax error message (PANIC MODE STILL)
            System.out.printf(
                    "In line %d:%d: syntax error, expected %s but encountered %s.\n",
                    currentToken.lineNumber(),
                    currentToken.columnNumber(),
                    expectedType.lexeme(),
                    currentToken.lexeme());
            // Exit the program for now
            // TODO: transform into non-panic mode
            System.exit(1);
        }

        return true;
    }

    private static Scanner scannerStdin;
    private static File fileSymbolTable;
    private static File fileSyntaxTree;

    public static void main(String[] args) {
        // File instance for symbol table file
        fileSymbolTable = new File("output.mul");
        // File instance for syntax tree file
        fileSyntaxTree = new File("output.multree");

        // Create parser
        MulParser mulParser = new MulParser(new File[] { fileSymbolTable, fileSyntaxTree });
        mulParser.initializeSymbols();
        mulParser.start();
    }

}
