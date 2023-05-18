package nodes;

public class miniSwitchNode extends treeNode{

	private Object value;

	public miniSwitchNode (Object v) 
	{
		this.value = v;
	}

	public Object execute()
	{
		if (this.value.equals(children.get(0).execute()))
		{
			children.get(1).execute();
			return true;
		}
		return false;	
	}
}