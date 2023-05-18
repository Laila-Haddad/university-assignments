package nodes;

public class intNode extends valueNode
{
	private int value;
	
	public intNode(String v)
	{
		this.value = Integer.parseInt(v);
	}
	
	public Object execute() 
	{
		return this.value;
	}
}