package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

import java.util.ArrayList;

public class t_Order implements Order {
	ED_Buffer edBuffer = null;
	String order="";

	private int[] PreviousAddress = {0,0};
	private int previousStartPositon = 0;
	private int previousEndPosition = 0;

	private int[] LatterAddress = {0,0};
	private int latterStartPositon = 0;
	private int latterEndPosition = 0;
	
	public t_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {

		edBuffer.uploadLastContent();
		String testLastStr = "";
		if(order.length()==1) {
			testLastStr = "t";
		}else {
			testLastStr = order.substring(order.length()-1);
		}
		ArrayList<String> tempArrayList = new ArrayList<>();
		
		if(!testLastStr.equals("t")) {//最后一个字母不是t的话，说明后面有内容，就split
			String[] temp = getBetterSplilt(order);
			if(temp.length==1){//对应t前面为""，前面部分使用默认。后面部分是有地址的
				PreviousAddress[0] = edBuffer.defaultLocation;
				PreviousAddress[1] = edBuffer.defaultLocation;
				LatterAddress = FindAddtress.getAddress(temp[0], edBuffer.defaultLocation, edBuffer.textContent);
			}else{
				PreviousAddress = FindAddtress.getAddress(temp[0], edBuffer.defaultLocation, edBuffer.textContent);
				LatterAddress = FindAddtress.getAddress(temp[1], edBuffer.defaultLocation, edBuffer.textContent);
			}

		}else {//后面没有地址时
			if(order.length()==1) {//指令只有一个t，前后都是默认地址
				LatterAddress[0] = edBuffer.defaultLocation;
				LatterAddress[1] = edBuffer.defaultLocation;
				PreviousAddress = LatterAddress;
			}else {//处理前面的地址，后面使用默认地址
				PreviousAddress = FindAddtress.getAddress(order.substring(0, order.length()-1), edBuffer.defaultLocation, edBuffer.textContent);
				LatterAddress[0] = edBuffer.defaultLocation;
				LatterAddress[1] = edBuffer.defaultLocation;
			}		
		}
		
		previousStartPositon = PreviousAddress[0]-1;
		previousEndPosition = PreviousAddress[1]-1;
		
		latterStartPositon = LatterAddress[0] - 1;
		latterEndPosition = LatterAddress[1] - 1;

		int insertIndex = latterEndPosition;

		if(previousStartPositon<0||previousEndPosition>=edBuffer.textContent.size()
				||insertIndex<0||insertIndex>=edBuffer.textContent.size()
				||previousStartPositon>previousEndPosition){
			System.out.println("?");
		}else {
			for (int i = previousStartPositon; i <= previousEndPosition; i++) {
				tempArrayList.add(edBuffer.textContent.get(i));
			}

			for (int j = 0; j < tempArrayList.size(); j++) {
				edBuffer.textContent.add(++insertIndex, tempArrayList.get(j));
			}

			edBuffer.defaultLocation = insertIndex + 1;

		}
	}


	protected String[] getBetterSplilt(String order){
		String[] strList = order.split("");
		int specialCount = 0;
		String latterStr = "";
		for(int i=strList.length-1; i>=0; i--){
			if(strList[i].equals("/")||strList[i].equals("?")){
				specialCount++;
			}
			if(strList[i].equals("t")&&specialCount%2==0){
				break;
			}
			latterStr = strList[i]+latterStr;
		}
		String[] temp = {"",""};
		temp[0] = order.substring(0,order.length()-latterStr.length()-1);
		temp[1] = order.substring(order.length()-latterStr.length());
		return temp;
	}
}
