package Order;

import edLineEditor.ED_Buffer;

public class f_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	
	public f_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		if(order.equals("f")) {
			if(edBuffer.checkFilePath.equals("")) {
				System.out.println("?");
			}else {
				System.out.println(edBuffer.checkFilePath);			
			}
		}else {
			//我这里并没有直接去读取新路径中的内容，而是改变了它读入和写出的路径，缓存器中的东西也没有动
			String file = order.substring(2);
			edBuffer.checkFilePath = file;
		}
	}
}
