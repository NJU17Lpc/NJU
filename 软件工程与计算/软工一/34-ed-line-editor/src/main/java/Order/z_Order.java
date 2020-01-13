package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class z_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";

	public z_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {

		int startPosition = edBuffer.defaultLocation-1;
		int endPosition = edBuffer.textContent.size()-1;
		ArrayList<String> newFileContent = edBuffer.textContent;

		String n = getPara_n(order);
		int length_of_n = n.length();
		if(length_of_n != 0) {//z后面有数字匹配
			String addressString = order.substring(0, order.length()-1-length_of_n);
			if(addressString.length()!=0) {			
				startPosition = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, newFileContent)[1]-1;
				endPosition = startPosition + Integer.valueOf(n);
				if(endPosition>=edBuffer.textContent.size()){
					endPosition = edBuffer.textContent.size()-1;
				}
			}else{
				startPosition = edBuffer.defaultLocation-1+1;
				endPosition = startPosition + Integer.valueOf(n);
				if(endPosition>=edBuffer.textContent.size()){
					endPosition = edBuffer.textContent.size()-1;
				}
			}


		}else {
			if(order.length()==1){//指令只有一个z
				startPosition = edBuffer.defaultLocation-1+1;
				endPosition = edBuffer.textContent.size()-1;
			}else{
				startPosition = FindAddtress.getAddress(order.substring(0,order.length()-1), edBuffer.defaultLocation, newFileContent)[1]-1;
				endPosition = edBuffer.textContent.size() - 1;
			}

		}

		if(startPosition<0||endPosition>=edBuffer.textContent.size()||startPosition>endPosition){
			System.out.println("?");
		}else{
			for(int i=startPosition; i<=endPosition; i++) {
				System.out.println(edBuffer.textContent.get(i));
			}
			edBuffer.defaultLocation = endPosition+1;//校准最后的默认地址
		}

	}
	
	protected String getPara_n(String order) {
		Pattern pattern = Pattern.compile("z\\d+");
		Matcher matcher = pattern.matcher(order);
		if(matcher.find()) {
			return matcher.group().substring(1);
		}else {
			return "";
		}	
	}

}
