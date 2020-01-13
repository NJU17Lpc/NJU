package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

public class j_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	
	private int[] PreviousAddress = {0,0};
	private int previousStartPosition = 0;
	private int previousEndPosition = 0;

	public j_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {
		edBuffer.uploadLastContent();

		if(order.equals("j")) {
			PreviousAddress[0] = edBuffer.defaultLocation;
			PreviousAddress[1] = edBuffer.defaultLocation+1;			
		}else {			
			String addressString = order.substring(0,order.length()-1);
			PreviousAddress = FindAddtress.getAddress(addressString, edBuffer.defaultLocation, edBuffer.textContent);
		}
		
		previousStartPosition = PreviousAddress[0] - 1;
		previousEndPosition = PreviousAddress[1] - 1;

		if(previousStartPosition<0||previousEndPosition>=edBuffer.textContent.size()
				||previousStartPosition>previousEndPosition){
			System.out.println("?");
		}else if(previousStartPosition==previousEndPosition){
			//j指令指定一行，对文本不进行操作，也不算对文本做任何改动。同时，当前行也不变。
		}else{
			String temp = "";
			for(int i=previousStartPosition; i<=previousEndPosition; i++) {
				temp += edBuffer.textContent.get(i);
			}

			for(int i=previousEndPosition; i>=previousStartPosition; i--) {
				edBuffer.textContent.remove(i);
			}
			edBuffer.textContent.add(previousStartPosition, temp);
			edBuffer.defaultLocation = previousStartPosition+1;


		}

	}
}
