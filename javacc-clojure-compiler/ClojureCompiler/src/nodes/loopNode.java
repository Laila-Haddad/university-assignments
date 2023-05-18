package nodes;

public class loopNode extends treeNode  {
	
	@Override
	public Object execute() {
//		System.out.println("hiiiiii from loop node");
		children.get(0).execute();
		while((boolean)children.get(1).execute()) {
			children.get(2).execute();
			children.get(3).execute();
		}
     

return null;
}
	}
