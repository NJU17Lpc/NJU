package edLineEditor;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class FindAddtress {
	public static int[] getAddress(String addressString, int defaultLocation, ArrayList<String> textContent) {
		int[] result = {0,0};

			if(addressString.equals(".")) {
			result[0] = defaultLocation;
			result[1] = defaultLocation;
		}else if(addressString.equals("$")) {

			
			result[0] = textContent.size();
			result[1] = textContent.size();
		}else if(addressString.equals(",")) {
			
			//System.out.println("匹配 ,");			
			
			result[0] = 1;
			result[1] = textContent.size();
		}else if(addressString.equals(";")) {

			//System.out.println("匹配 ;");
			
			result[0] = defaultLocation;
			result[1] = textContent.size();
		}else if(addressString.matches("[/?][^/?]+[/?][+]\\d+")){
			//System.out.println("匹配 /str/+n");
			String[] temp=addressString.split("[+]");
			result[0] = getAddress(temp[0],defaultLocation,textContent)[0]+Integer.valueOf(temp[1]);

			result[1] = result[0];
		}else if(addressString.matches("[/?][^/?]+[/?][-]\\d+")){
			//System.out.println("匹配 /str/-n");
			String[] temp={"",""};
			Pattern pattern = Pattern.compile("([/?][^/?]+[/?])[-](\\d+)");
			Matcher matcher = pattern.matcher(addressString);
			if(matcher.find()){
				temp[0] = matcher.group(1);
				temp[1] = matcher.group(2);
			}
			result[0] = getAddress(temp[0],defaultLocation,textContent)[0]-Integer.valueOf(temp[1]);
			result[1] = result[0];
		}else if(addressString.matches("^\\.\\+\\d+$")) {
			
			//System.out.println("匹配 .+n");
			
			result[0] = defaultLocation + Integer.valueOf(addressString.substring(2));
			result[1] = defaultLocation + Integer.valueOf(addressString.substring(2));
			
		}else if(addressString.matches("^\\.\\-\\d+$")) {
			
			//System.out.println("匹配 .-n");
			
			result[0] = defaultLocation - Integer.valueOf(addressString.substring(2));
			result[1] = defaultLocation - Integer.valueOf(addressString.substring(2));
			
		}else if(addressString.matches("^\\$\\+\\d+$")) {
			
		//	System.out.println("匹配 $+n");
			
			result[0] = textContent.size() + Integer.valueOf(addressString.substring(2));
			result[1] = textContent.size() + Integer.valueOf(addressString.substring(2));
		}else if(addressString.matches("^\\$\\-\\d+$")) {
			
		//	System.out.println("匹配 $-n");
			
			result[0] = textContent.size() - Integer.valueOf(addressString.substring(2));
			result[1] = textContent.size() - Integer.valueOf(addressString.substring(2));
		}else if(addressString.matches("^\\d+\\+\\d+$")) {
			
		//	System.out.println("匹配 n+n");
			
			result[0] = Integer.valueOf(addressString.split("[+]")[0]) + Integer.valueOf(addressString.split("[+]")[1]);
			result[1] = result[0];
		}else if(addressString.matches("^\\d+\\-\\d+$")) {
			
			//System.out.println("匹配 n-n");
			
			result[0] = Integer.valueOf(addressString.split("-")[0]) - Integer.valueOf(addressString.split("-")[1]);
			result[1] = result[0];
		}else if(addressString.matches("^\\d+$")) {
			
			//System.out.println("匹配 n");
			
			result[0] = Integer.valueOf(addressString);
			result[1] = result[0];
		}else if(addressString.matches("^\\+\\d+$")) {
			
			//System.out.println("匹配 +n");
			
			result[0] = defaultLocation + Integer.valueOf(addressString.substring(1));
			result[1] = result[0];
		}else if(addressString.matches("^\\-\\d+$")) {
			
			//System.out.println("匹配 -n");
			
			result[0] = defaultLocation - Integer.valueOf(addressString.substring(1));
			result[1] = result[0];
		}else if(addressString.matches("^\\d+[,]\\d+$")) {

			String[] temp = addressString.split(",");

			result[0] = Integer.valueOf(temp[0]);
			result[1] = Integer.valueOf(temp[1]);
		}else if(addressString.matches("^/.+/$")) {
			
			//System.out.println("匹配 /str/");

			result[0] = getLatterAddress(textContent, defaultLocation, addressString.substring(1, addressString.length()-1));
			result[1] = result[0];
		}else if(addressString.matches("^[?].+[?]$")) {
			
			//System.out.println("匹配 ?str?");
			
			result[0] = getPreviousAddress(textContent, defaultLocation, addressString.substring(1, addressString.length()-1));
			result[1] = result[0];
		} else if(addressString.matches("^.+[,].+$")) {
			
			//System.out.println("匹配 _,_");
			
			String[] temp = addressString.split(",");
			String str = "";
			if(temp.length>=3){
				temp = SpecialAddress(addressString);
			}
			result[0] = getAddress(temp[0], defaultLocation, textContent)[0];
			result[1] = getAddress(temp[1], defaultLocation, textContent)[0];
		}else {

//			result[0] = defaultLocation;
//			result[1] = defaultLocation;
			result[0] = -10;
			result[1] = -10;
		}
		
		return result;
	}

	protected static String[] SpecialAddress(String specialAddress) {//不能够简单的split逗号了
		String[] result = {"",""};
		Pattern pattern = Pattern.compile("[?/][^?/]*[?/][^?/]*");
		Matcher matcher = pattern.matcher(specialAddress);
		int index = 0;
		while(matcher.find()){
			String tempStr = matcher.group();
			//System.out.println(tempStr);
			if(tempStr.substring(tempStr.length()-1).equals(",")){
				result[index] = tempStr.substring(0,tempStr.length()-1);
			}else{
				result[index] = tempStr;
			}
			index++;
		}

		return result;
	}

	protected static int getPreviousAddress(ArrayList<String> al, int startPosition, String target) {
		//其实不太好，我直接把最重要的  读取的文本缓存器  控制权  交给这个方法
		
		//不包括当前行，向下找，找到文本最后一行
		//如果向前匹配不到，就对整个ArrayList找一遍
		
		//System.out.println("in getPreviousAddress");
		//System.out.println("target:"+target);
		
		Pattern pattern = null;
		Matcher findTarget = null;
		for(int i=startPosition-2; i>=0; i--) {
			if(al.get(i).contains(target)){
				return i+1;
			}
		}
		//有必要的话，从文本开始行搜索到当前行
		return getPreviousOverallAddress(al, startPosition, target);
		
	}
	
	protected static int getLatterAddress(ArrayList<String> al, int startPosition, String target) {

		Pattern pattern = null;
		Matcher findTarget = null;
		for(int i=startPosition; i<al.size(); i++) {
			if(target.length()==1){
				target = "["+target+"]";
			}
			pattern = Pattern.compile(target);
			findTarget = pattern.matcher(al.get(i));
			if(findTarget.find()) {
				return i+1;
			}

		}
		//有必要的话，从文本末尾处返回到开头开始找
		return getLatterOverallAddress(al, startPosition, target);
	}
	
	protected static int getLatterOverallAddress(ArrayList<String> al, int startPosition, String target) {
		
		//System.out.println("in getLatterOverallAddress");
		
		Pattern pattern = null;
		Matcher findTarget = null;
		for(int i=0; i<=startPosition-1; i++) {
			pattern = Pattern.compile(target);
			findTarget = pattern.matcher(al.get(i));
			if(findTarget.find()) {
				return i+1;
			}
		}
//		System.out.println("?");
		return -10;
	}
	
	protected static int getPreviousOverallAddress(ArrayList<String> al, int startPosition, String target) {
		
		//System.out.println("in getPreviousOverallAddress");
		
		Pattern pattern = null;
		Matcher findTarget = null;
		for(int i=al.size()-1; i>=startPosition-1; i--) {
			pattern = Pattern.compile(target);
			findTarget = pattern.matcher(al.get(i));
			if(findTarget.find()) {
				return i+1;
			}
		}
//		System.out.println("?");
		return -10;
	}
	
	protected static int[] checkMaxSize(int num, int maxSize) {
		int[] result = new int[2];
		if(num>maxSize) {
			result[0] = maxSize;
			result[1] = maxSize;
		}else {
			result[0] = num;
			result[1] = num;
		}
		return result;
	}

}
