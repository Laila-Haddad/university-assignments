package nodes;

public class blockNode extends treeNode {

	@Override
	public Object execute() {
//		System.out.println("hiiiiii from block node");
for (treeNode c : children) {
	c.execute();
}
		return null;
	}

}
