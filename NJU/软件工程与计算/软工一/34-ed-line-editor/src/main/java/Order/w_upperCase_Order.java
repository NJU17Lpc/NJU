package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class w_upperCase_Order implements Order{
	ED_Buffer edBuffer = null;
	String order="";
	int[] address = {0,0};

	public w_upperCase_Order(String order, ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}

	public void perform() {
		String processOrder = getFile(order);
		int startPosition = 0;
		int endPosition = 0;
		ArrayList<String> tempList = new ArrayList<>();

		if(processOrder.equals("W")) {
			//如果参数file不指定，则使用默认文件名代替参数file
			//当没有默认文件名时，参数file必须指定，否则打印'?'
			if(edBuffer.checkFilePath.equals("")) {
				System.out.println("?");
			}else {
				//找出需要保存的行，放到临时的arraylist里面，方便调用edBuffer的方法flush上去
				if(order.equals("W")) {
					startPosition = 0;
					endPosition = edBuffer.textContent.size()-1;
				}else {

					int[] address = FindAddtress.getAddress(order.substring(0, order.length()-1), edBuffer.defaultLocation, edBuffer.textContent);
					startPosition=address[0]-1;
					endPosition=address[1]-1;
				}

				if(startPosition<0||endPosition>=edBuffer.textContent.size()||startPosition>endPosition){
					System.out.println("?");
				}else{
					for(int i=startPosition; i<=endPosition; i++) {
						tempList.add(edBuffer.textContent.get(i));
					}
					edBuffer.flushTextContentData(tempList,true);
				}
			}

		}else {
			//这个file指定的文件不要通过edBuffer走，可能他就是想随便确定一个file
			//在edBuffer中创建人畜无害，即插即用的文件flush方法
			int length_of_w = processOrder.length();
			String tempString = order.substring(0,order.length()+1-length_of_w);

			if(tempString.equals("W")) {
				startPosition = 0;
				endPosition = edBuffer.textContent.size()-1;
			}else {
				int[] temp=FindAddtress.getAddress(tempString.substring(0,tempString.length()-1), edBuffer.defaultLocation, edBuffer.textContent);
				startPosition = temp[0]-1;
				endPosition = temp[1]-1;
			}

			if(startPosition<0||endPosition>=edBuffer.textContent.size()||startPosition>endPosition){
				System.out.println("?");
			}else{
				for(int i=startPosition; i<=endPosition; i++) {
					tempList.add(edBuffer.textContent.get(i));
				}
				edBuffer.flushTextContentData(tempList, processOrder.substring(2),true);
			}

		}

	}
	
	protected String getFile(String Order) {
		
		Pattern pattern = Pattern.compile("W\\s\\w+");
		Matcher matcher = pattern.matcher(order);
		if(matcher.find()) {
			return matcher.group();//能匹配到的话，返回w [file]
		}else {
			return "W";//匹配不到的话，返回w
		}	

	}
}
