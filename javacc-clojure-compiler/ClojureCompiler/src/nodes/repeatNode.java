package nodes;

public class repeatNode extends treeNode{
	
	public repeatNode() {}
	
	@Override
	public Object execute() {
		int num = (int)children.get(0).execute();
		
		for(int i=0; i < num; i++) {
		   System.out.println(children.get(1).execute().toString());
		}
    
		return null;
	}
}
