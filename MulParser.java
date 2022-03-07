import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

/**
 * A parser for the MUL programming language.
 * Modeled as a Backtracking Recursive Descent parser.
 */
public class MulParser {

    // File manipulators
    // Scanner for the symbol table file
    private Scanner scannerSymbolTable;
    // PrintWriter for the syntax tree file
    private PrintWriter printerSyntaxTree;

    // List of Tokens
    private LinkedList<Token> tokenLinkedList;
    // Pointer to the current token
    private ListIterator<Token> tokenListIterator;

    /**
     * Creates a parser, with the given files to operate on.
     * @param fileSymbolTable the symbol table file
     * @param fileSyntaxTree the syntax tree file
     */
    public MulParser(File fileSymbolTable, File fileSyntaxTree) {
        // Attempt to create a Scanner for the symbol table file
        try {
            scannerSymbolTable = new Scanner(fileSymbolTable);
        } catch (FileNotFoundException e) {
            // Output a cannot open file message if not opened
            System.out.println(
                    "Error: cannot open file with name: " +
                            fileSymbolTable.getName());
            System.exit(1);
        }
        // Attempt to create a PrintWriter for the syntax tree file
        try {
            printerSyntaxTree = new PrintWriter(fileSyntaxTree);
        } catch (FileNotFoundException e) {
            // Output a cannot open file message if not opened
            System.out.println(
                    "Error: cannot open syntax tree file with name: " +
                            fileSyntaxTree.getName());
            System.exit(1);
        }

        // Initialize linked list of tokens
        tokenLinkedList = new LinkedList<>();
    }

    /**
     * Reads the specified symbol table file line by line, and extracts
     * the tokens into a linked list.
     */
    public void initializeSymbols() {
        Token.Type[] tokenTypeValues = Token.Type.values();

        // Clear the token list
        tokenLinkedList.clear();

        // Read each line of the symbol table file
        while(scannerSymbolTable.hasNextLine()) {
            String[] line = scannerSymbolTable.nextLine().split(":");

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
            // Add the token to the list
            tokenLinkedList.add(token);
        }

        System.out.println("read");
    }

    /* START OF PRODUCTION RULES */
    private boolean mulProg(TreeNode parent) {
        return true;
    }

    private boolean body(TreeNode parent) {
        return true;
    }

    private boolean statement(TreeNode parent) {
        return true;
    }

    private boolean inputStatement(TreeNode parent) {
        return true;
    }

    private boolean outputStatement(TreeNode parent) {
        return true;
    }

    private boolean assignmentStatement(TreeNode parent) {
        return true;
    }

    private boolean conditionalStatement(TreeNode parent) {
        return true;
    }

    private boolean ifStatement(TreeNode parent) {
        return true;
    }

    private boolean elseIfStatement(TreeNode parent) {
        return true;
    }

    private boolean elseStatement(TreeNode parent) {
        return true;
    }

    private boolean iterativeStatement(TreeNode parent) {
        return true;
    }

    /**
     * Matches the current token against the expected token type.
     * @param expectedType the expected token
     * @return if matched or not
     */
    private boolean match(Token.Type expectedType) {
        // Get the current token
        Token currentToken = tokenListIterator.next();
        // If it is the expected token, return true
        if(currentToken.type() == expectedType)
            return true;
        // Else, backtrack then return false
        else {
            // If not matched, backtrack the pointer
            tokenListIterator.previous();
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
            Token currentToken = tokenListIterator.next();
            // Output a syntax error message (PANIC MODE STILL)
            System.out.printf(
                    "In line %d:%d: syntax error, expected %s but encountered %s.",
                    currentToken.lineNumber(),
                    currentToken.columnNumber(),
                    tokenListIterator.next().lexeme());
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
        scannerStdin = new Scanner(System.in);

        // Prompt for symbol table file name
        System.out.print("Enter symbol table file name >> ");
        String symbolTableFilename = scannerStdin.next();

        // File instance for symbol table file
        fileSymbolTable = new File(symbolTableFilename);
        // File instance for syntax tree file
        fileSyntaxTree = new File(symbolTableFilename.split("\\.")[0]);

        // Create parser
        MulParser mulParser = new MulParser(fileSymbolTable, fileSyntaxTree);
        mulParser.initializeSymbols();
    }

}
