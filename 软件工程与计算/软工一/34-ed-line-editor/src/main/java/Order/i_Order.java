package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class i_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	int address = 0;

	public i_Order(String order,  ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		//把新加入的文本    放在指定行的前面
		edBuffer.uploadLastContent();
		String addressString = order.substring(0, order.length()-1);
		if(addressString.equals("")) {
			address = edBuffer.defaultLocation-1;
		}else {			
			address = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent)[1]-1;//保证是指定位置的前一行
		}

		if(address>edBuffer.textContent.size()||address<-1){//i的位置有疑问
			System.out.println("?");
		}else{
			int insertAddress = address;
			int insertCount = 0;
			if(address==-1){
				address++;
			}
			for(String s:edBuffer.tempTXTContent) {
				edBuffer.textContent.add(address++, s);
				insertCount++;
			}

			edBuffer.cleanTempTXTContent();
			edBuffer.defaultLocation = address;//校准最后的默认地址
			edBuffer.hasFlushed = false;//设置edBuffer的缓存还没有flush上去
		}
	}

}
