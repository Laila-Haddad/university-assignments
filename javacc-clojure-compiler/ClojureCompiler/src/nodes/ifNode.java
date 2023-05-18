package nodes;

public class ifNode extends treeNode {

	@Override
	public Object execute() {
//		System.out.println("hiiiiii from if node");
		

if((boolean)children.get(0).execute())
{
	children.get(1).execute();
}
		return null;
	}

}
