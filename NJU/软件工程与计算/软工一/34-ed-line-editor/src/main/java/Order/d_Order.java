package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class d_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";

	int[] address = {0,0};
	int startPositon = 0;
	int endPosition = 0;
	
	public d_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		String addressString = order.substring(0, order.length()-1);
		if(addressString.equals("")){
			startPositon = edBuffer.defaultLocation-1;
			endPosition = edBuffer.defaultLocation-1;
		}else {
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent);
			startPositon = address[0] - 1;
			endPosition = address[1] - 1;
		}

		if(startPositon<0||endPosition>=edBuffer.textContent.size()||startPositon>endPosition){
			System.out.println("?");
		}else{
			for(int i=endPosition; i>=startPositon; i--) {
				edBuffer.textContent.remove(i);
			}
			//如果删除后，此时的startPosition还有内容，位置就是startPosition;如果已经没有内容了，位置就startPosition-1
			edBuffer.defaultLocation = (startPositon<=edBuffer.textContent.size()-1)?startPositon+1:startPositon;;//校准最后的默认地址

		}
	}

}
