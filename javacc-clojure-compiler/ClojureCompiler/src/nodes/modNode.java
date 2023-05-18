package nodes;

public class modNode extends treeNode {

	@Override
	public Object execute() {
//		System.out.println("hiiiiii from mod node");
String varName=(String)children.get(0).execute();
if(varNode.variables.containsKey(varName))
{
	//must use casting function here . only accepted type is int rn
	
	int v=(int)varNode.variables.get(varName);
	String op=(String)children.get(1).execute();
	int n=(int)children.get(2).execute();
	if(op.equals("++")) v++;
	else if (op.equals("--")) v--;
	else if (op.equals("-")) v=v-n;
	else if (op.equals("+")) v=v+n;
	
varNode.variables.put(varName, v);
//System.out.println("hiiiiii from mod node variables is"+assignNode.variables);

}else 		System.out.println("undifiend variable");

		return null;
	}

}
