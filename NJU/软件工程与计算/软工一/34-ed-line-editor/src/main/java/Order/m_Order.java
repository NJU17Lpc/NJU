package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

import java.util.ArrayList;

public class m_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";

	private int[] PreviousAddress = {0,0};
	private int previousStartPositon = 0;
	private int previousEndPosition = 0;

	private int[] LatterAddress = {0,0};
	private int latterStartPositon = 0;
	private int latterEndPosition = 0;
	
	public m_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		edBuffer.uploadLastContent();
		String testLastStr = "";

		if(order.length()==1) {
			testLastStr = "m";
		}else {			
			testLastStr = order.substring(order.length()-1);
		}
		ArrayList<String> tempArrayList = new ArrayList<>();
		
		if(!testLastStr.equals("m")) {//最后一个字母不是m的话，说明后面有内容，就split
			String[] temp = getBetterSplit(order);
			if(temp.length==1){//对应t前面为""，前面部分使用默认。后面部分是有地址的
				PreviousAddress[0] = edBuffer.defaultLocation;
				PreviousAddress[1] = edBuffer.defaultLocation;
				LatterAddress = FindAddtress.getAddress(temp[0], edBuffer.defaultLocation, edBuffer.textContent);
			}else{
				PreviousAddress = FindAddtress.getAddress(temp[0], edBuffer.defaultLocation, edBuffer.textContent);
				LatterAddress = FindAddtress.getAddress(temp[1], edBuffer.defaultLocation, edBuffer.textContent);
			}
		}else {//后面没有地址时
			if(order.length()==1) {//指令只有一个m，前后都是默认地址
				LatterAddress[0] = edBuffer.defaultLocation;
				LatterAddress[1] = edBuffer.defaultLocation;
				PreviousAddress = LatterAddress;
			}else {//处理前面的地址，后面使用默认地址
				if(order.substring(0, order.length()-1).equals("")){
					PreviousAddress[0] = edBuffer.defaultLocation;
					PreviousAddress[1] = edBuffer.defaultLocation;
				}else{
					PreviousAddress = FindAddtress.getAddress(order.substring(0, order.length()-1), edBuffer.defaultLocation, edBuffer.textContent);
				}

				LatterAddress[0] = edBuffer.defaultLocation;
				LatterAddress[1] = edBuffer.defaultLocation;
			}		
		}
		
		previousStartPositon = PreviousAddress[0]-1;
		previousEndPosition = PreviousAddress[1]-1;
		
		latterStartPositon = LatterAddress[0] - 1;
		latterEndPosition = LatterAddress[1] - 1;

		int insertIndex = latterEndPosition;
		
		if(insertIndex<previousEndPosition && insertIndex>=previousStartPositon) {
			System.out.println("?");
		}else if(previousStartPositon<0||previousEndPosition>=edBuffer.textContent.size()
				||insertIndex<0||insertIndex>=edBuffer.textContent.size()
				||previousStartPositon>previousEndPosition){
			System.out.println("?");
		}else {
			for(int i=previousStartPositon; i<=previousEndPosition; i++) {				
				tempArrayList.add(edBuffer.textContent.get(i));
			}

			if(insertIndex >= previousEndPosition) {	//移动后插入的位置如果在移动前位置的后面，可以最后删除

				for(int i=0; i<tempArrayList.size(); i++) {
					edBuffer.textContent.add(++insertIndex, tempArrayList.get(i));
				}
				for(int i=previousEndPosition; i>=previousStartPositon; i--) {
					edBuffer.textContent.remove(i);
				}

			}else {//插入的位置在前面的话，也可以动态删除

				int deletePosition = previousStartPositon;
				for(int i=0; i<tempArrayList.size(); i++) {
					edBuffer.textContent.add(++insertIndex, tempArrayList.get(i));
					edBuffer.textContent.remove(deletePosition+tempArrayList.size());
				}
				insertIndex++;
			}

			edBuffer.defaultLocation = insertIndex;
		}

	}

	protected String[] getBetterSplit(String order){
		int specialSymbol = 0;
		String[] result = {"",""};
		String[] orderArray = order.split("");
		String previousString = "";
		String latterString = "";
		for(int i=orderArray.length-1; i>=0; i--){
			if(orderArray[i].equals("/")||orderArray[i].equals("?")){
				specialSymbol++;
			}
			if(specialSymbol%2==0&&orderArray[i].equals("m")){
				previousString = order.substring(0,i);
				latterString = order.substring(i+1);
			}
		}
		result[0] = previousString;
		result[1] = latterString;
		return  result;
	}
}
