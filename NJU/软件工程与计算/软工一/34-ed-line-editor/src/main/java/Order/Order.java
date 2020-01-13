package Order;
/**
 * 可以改个继承，我没用什么接口特性
 */

import edLineEditor.EDLineEditor;

public interface Order{
	String defaultName = "";
	EDLineEditor ed = null;
	
	public void perform();
}
