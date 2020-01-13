package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class equal_Order implements Order {
	ED_Buffer edBuffer = null;
	String order="";
	
	int[] address = {0,0};
	
	public equal_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		String addressString = order.substring(0, order.length()-1);
		int address = 0;
		if(addressString.equals("")) {
			address = edBuffer.textContent.size()-1;
		}else {			
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent)[1]-1;
		}

		if(address>=edBuffer.textContent.size()||address<0){
			System.out.println("?");
		}else{
			System.out.println(address+1);//题目要求的打印内容
		}
		
	}
}
