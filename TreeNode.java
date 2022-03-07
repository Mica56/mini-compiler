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
                current.type == Type.IDENTIFIER)
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

    // TODO: Create a node flattener toString() method

    // TODO: Create node types
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

        DATA_TYPE,
        IDENTIFIER,
    }
}
