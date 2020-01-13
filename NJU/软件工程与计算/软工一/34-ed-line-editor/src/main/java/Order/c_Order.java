package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class c_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";

	int[] address = {0,0};
	int startPositon = 0;
	int endPosition = 0;
	
	public c_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		edBuffer.uploadLastContent();
		String addressString = order.substring(0, order.length()-1);
		if(addressString.equals("")){
			startPositon = edBuffer.defaultLocation-1;
			endPosition = edBuffer.defaultLocation-1;
		}else{
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent);
			startPositon = address[0]-1;
			endPosition = address[1]-1;
		}

		if(endPosition>=edBuffer.textContent.size()||startPositon<0||startPositon>endPosition){
			System.out.println("?");
		}else{

			for(int i=endPosition; i>=startPositon; i--) {
				edBuffer.textContent.remove(i);
			}

			int address = startPositon;
			int deleteCount = endPosition - startPositon + 1;
			int addCount = 0;
			for(String s:edBuffer.tempTXTContent) {
				edBuffer.textContent.add(address++, s);
				addCount++;
			}
			edBuffer.cleanTempTXTContent();
			edBuffer.defaultLocation = address;//校准最后的默认地址
			edBuffer.hasFlushed = false;//设置edBuffer的缓存还没有flush上去

		}

	}

	
}
