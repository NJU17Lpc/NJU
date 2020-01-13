package Order;

import edLineEditor.*;
import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class a_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	int address = 0;
	
	public a_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {

		String addressString = order.substring(0, order.length()-1);
		if(addressString.equals("")){
			address = edBuffer.defaultLocation-1;
		}else{
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent)[1]-1;
		}

		if(address>edBuffer.textContent.size()||address<-1){
			System.out.println("?");
		}else{

			int addAddress = address;
			int count=0;
			for(String s:edBuffer.tempTXTContent) {
				edBuffer.textContent.add(++address, s);
				count++;
			}
			edBuffer.cleanTempTXTContent();
			edBuffer.defaultLocation = address+1;//校准最后的默认地址
			edBuffer.hasFlushed = false;//设置edBuffer的缓存还没有flush上去

		}
	}

}
