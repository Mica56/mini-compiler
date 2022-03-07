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

    public void addChild(TreeNode node) {
        children.add(node);
    }

    // TODO: Create a node flattener toString() method

    // TODO: Create node types
    public enum Type {

    }
}
