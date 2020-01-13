package Order;

import edLineEditor.ED_Buffer;
import edLineEditor.FindAddtress;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class s_Order implements Order{
	ED_Buffer edBuffer = null;
	
	String order="";
	int address = 0;
	public static String lastOrder = "";
	
	public s_Order(String order,  ED_Buffer edBuffer) {
		this.order = order;
		this.edBuffer = edBuffer;
	}
	
	public void perform() {

		edBuffer.uploadLastContent();
		if(order.substring(order.length()-1).equals("g")) {
			end_with_g_special(order);
		}else if(order.substring(order.length()-1).equals("s")) {
			end_with_s();
		}else if(order.substring(order.length()-1).equals("/")) {
			end_with_symbol_special(order);
		}else {
			end_with_count_special(order);
		}
	}


	protected void end_with_g_special(String order){


		lastOrder = order;
		String[] orderString = order.split("");
		int symbolCount = 0;
		String after_s = "";
		String wholeString = "";
		String str1 = "";
		String str2 = "";
		int[] address = {0,0};
		int startPosition = 0;
		int endPosition = 0;
		for(int i=orderString.length-1; i>=0; i--){
			after_s = orderString[i]+after_s;
			if(orderString[i].equals("/")){
				symbolCount++;
			}
			if(symbolCount==3){
				break;
			}
		}
		wholeString = "s"+after_s;
		String strString = after_s.substring(1,after_s.length()-2);
		if(strString.substring(0,1).equals("/")){
			str1 = "";
			str2 = strString.substring(1);
		}else if(strString.substring(strString.length()-1,strString.length()).equals("/")){
			str1 = strString.substring(0,strString.length()-1);
			str2 = "";
		}else{
			str1 = strString.split("/")[0];
			str2 = strString.split("/")[1];
		}

		if(order.substring(0, order.length()-wholeString.length()).equals("")) {
			address[0] = edBuffer.defaultLocation;
			address[1] = edBuffer.defaultLocation;
		}else {
			address = FindAddtress.getAddress(order.substring(0, order.length()-wholeString.length()), edBuffer.defaultLocation, edBuffer.textContent);
		}
		startPosition = address[0]-1;
		endPosition = address[1]-1;


		if(startPosition<0||endPosition>=edBuffer.textContent.size()||startPosition>endPosition){
			System.out.println("?");
		}else{
			for(int i=startPosition; i<=endPosition; i++) {
				Pattern pattern = Pattern.compile(str1);
				Matcher matcher = pattern.matcher(edBuffer.textContent.get(i));
				if(matcher.find()) {//确保默认行是最后一个被修改的行
					edBuffer.defaultLocation = i+1;
				}
				edBuffer.textContent.set(i, matcher.replaceAll(str2));
			}
			checkHasChange();
		}

	}
	protected void checkHasChange(){

		boolean hasOneChange = false;
		for(int i=0; i<edBuffer.textContent.size(); i++){
			if(!edBuffer.textContent.get(i).equals(edBuffer.lastContent.get(i))){
				hasOneChange = true;
				break;
			}
		}
		if(!hasOneChange){
			System.out.println("?");
		}
	}


	protected void end_with_s() {
		if(lastOrder.equals("")){
			System.out.println("?");
		}else{
			s_Order s = new s_Order(lastOrder, edBuffer);
			s.perform();
		}
	}

	protected void end_with_count_special(String order){

		Pattern pattern = Pattern.compile("(\\d+)$");
		//Pattern pattern = Pattern.compile("/(\\w+/\\w+)/$|/\\s*[0-9a-zA-Z.:]*\\s*/\\s*[0-9a-zA-Z.:]*\\s*/(\\d+)$");
		Matcher matcher = pattern.matcher(order);
		String countString = "";
		if(matcher.find()){
			countString = matcher.group(1);
		}

		lastOrder = order;
		String[] orderString = order.split("");
		int symbolCount = 0;
		String after_s = "";
		String wholeString = "";
		String str1 = "";
		String str2 = "";

		int[] address = {0,0};
		int startPosition = 0;
		int endPosition = 0;
		for(int i=orderString.length-1; i>=0; i--){
			after_s = orderString[i]+after_s;
			if(orderString[i].equals("/")){
				symbolCount++;
			}
			if(symbolCount==3){
				break;
			}
		}
		wholeString = "s"+after_s;
		String strString = after_s.substring(1,after_s.length()-countString.length()-1);
		if(strString.substring(0,1).equals("/")){
			str1 = "";
			str2 = strString.substring(1);
		}else if(strString.substring(strString.length()-1,strString.length()).equals("/")){
			str1 = strString.substring(0,strString.length()-1);
			str2 = "";
		}else{
			str1 = strString.split("/")[0];
			str2 = strString.split("/")[1];
		}


		if(order.substring(0, order.length()-wholeString.length()).equals("")) {
			address[0] = edBuffer.defaultLocation;
			address[1] = edBuffer.defaultLocation;
		}else {
			address = FindAddtress.getAddress(order.substring(0, order.length()-wholeString.length()), edBuffer.defaultLocation, edBuffer.textContent);
		}
		startPosition = address[0]-1;
		endPosition = address[1]-1;

		if(startPosition<0||endPosition>=edBuffer.textContent.size()) {
			System.out.println("?");
		}else{
			int count = Integer.valueOf(countString);
			for (int i = startPosition; i <= endPosition; i++) {
				pattern = Pattern.compile(str1);
				matcher = pattern.matcher(edBuffer.textContent.get(i));
				int num = 0;

				String tempContent = edBuffer.textContent.get(i);
				String content = edBuffer.textContent.get(i);
				String temp = "";

				while (matcher.find()) {
					if (num == count) {
						break;
					} else {
						tempContent = tempContent.replaceFirst(".*?" + str1, "");
						num++;
					}
				}

				if (num == count) {
					//tempContent = str2+tempContent;
					temp = content.substring(0, content.length() - tempContent.length() - str1.length()) + str2 + tempContent;
					edBuffer.textContent.set(i, temp);
					edBuffer.defaultLocation = i + 1;
				}
			}
			checkHasChange();

		}
	}


	protected void end_with_symbol_special(String order) {
		lastOrder = order;
		String[] orderString = order.split("");
		int symbolCount = 0;
		String after_s = "";
		String wholeString = "";
		String str1 = "";
		String str2 = "";
		int[] address = {0, 0};
		int startPosition = 0;
		int endPosition = 0;
		for (int i = orderString.length - 1; i >= 0; i--) {
			after_s = orderString[i] + after_s;
			if (orderString[i].equals("/")) {
				symbolCount++;
			}
			if (symbolCount == 3) {
				break;
			}
		}
		wholeString = after_s;
		String strString = after_s.substring(1, after_s.length() - 1);
		if (strString.substring(0, 1).equals("/")) {
			str1 = "";
			str2 = strString.substring(1);
		} else if (strString.substring(strString.length() - 1, strString.length()).equals("/")) {
			str1 = strString.substring(0, strString.length() - 1);
			str2 = "";
		} else {
			str1 = strString.split("/")[0];
			str2 = strString.split("/")[1];
		}

		if (order.substring(0, order.length() - wholeString.length()-1).equals("")) {
			address[0] = edBuffer.defaultLocation;
			address[1] = edBuffer.defaultLocation;
		} else {
			address = FindAddtress.getAddress(order.substring(0, order.length() - wholeString.length() - 1), edBuffer.defaultLocation, edBuffer.textContent);
		}
		startPosition = address[0] - 1;
		endPosition = address[1] - 1;

		if (startPosition < 0 || endPosition >= edBuffer.textContent.size() || startPosition > endPosition) {
			System.out.println("?");
		} else {
			for (int i = startPosition; i <= endPosition; i++) {
				Pattern pattern = Pattern.compile(str1);
				Matcher matcher = pattern.matcher(edBuffer.textContent.get(i));
				if (matcher.find()) {
					edBuffer.defaultLocation = i + 1;
					edBuffer.textContent.set(i, matcher.replaceFirst(str2));
				}

			}
			checkHasChange();
		}
	}
}
