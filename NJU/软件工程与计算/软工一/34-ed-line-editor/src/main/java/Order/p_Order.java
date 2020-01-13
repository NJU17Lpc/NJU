package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class p_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	
	int[] address = {0,0};
	int startPositon = 0;
	int endPosition = 0;
	
	public p_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		
		String addressString = order.substring(0, order.length()-1);
		if(addressString.equals("")){
			startPositon = edBuffer.defaultLocation-1;
			endPosition = edBuffer.defaultLocation-1;
		}else{
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent);
			startPositon = address[0]-1;//返回的地址是跟着文本的行数来的，如果要修改arraylist内容，需要把对应的行数对着-1
			endPosition = address[1]-1;
		}

		if(startPositon>endPosition||endPosition>=edBuffer.textContent.size()||startPositon<0){
			System.out.println("?");
		}else{
			for(int i=startPositon; i<=endPosition; i++) {
				System.out.println(edBuffer.textContent.get(i));
			}
			edBuffer.defaultLocation = endPosition+1;//校准最后的默认地址
		}

	}
}
