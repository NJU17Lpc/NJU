package edLineEditor;

import Order.s_Order;

import java.util.Scanner;

/**
 * 接收用户控制台的输入，解析命令，根据命令参数做出相应处理。
 * 不需要任何提示输入，不要输出任何额外的内容。
 * 输出换行时，使用System.out.println()。或者换行符使用System.getProperty("line.separator")。
 * 
 * 待测方法为public static void main(String[] args)方法。args不传递参数，所有输入通过命令行进行。
 * 方便手动运行。
 * 
 * 说明：可以添加其他类和方法，但不要删除该文件，改动该方法名和参数，不要改动该文件包名和类名
 */

public class EDLineEditor {

	/**
	 *
	 * 这里是入口，我没有怎么重构，读起来判定条件多，主要是因为当时跟着测试用例走的，
	 * @param args
	 */
	public static void main(String[] args) {		
		ED_Buffer edBuffer = null;
		OrderProcess op = new OrderProcess();
		Scanner s = new Scanner(System.in);
		String firstLine = s.nextLine();

		String edBufferString = "";
		boolean isTxt = false;
		s_Order.lastOrder = "";

		if(firstLine.equals("ed")) {
			edBuffer = new ED_Buffer();
		}else if(firstLine.matches("ed\\s.+")) {
			edBuffer = new ED_Buffer(firstLine.substring(3));
			edBuffer.readTextOriginData();

		}

		while(s.hasNext()) {
			String input = s.nextLine();

			if(input.matches(".+[qQ]$")){
				System.out.println("?");
				continue;
			}else if(input.matches("^\\W+f$|^.+f\\s.*")){
				System.out.println("?");
				continue;
			}

			if (input.equals(".")) {
				isTxt = false;
				op.process(edBufferString, edBuffer);
				continue;
			}
			if (isTxt) {
				edBuffer.tempTXTContent.add(input);
				continue;
			}
			if (input.matches(".*[aic]$")) {
				if (aicAddressVaild(input, edBuffer)) {
					edBufferString = input;
					isTxt = true;
					continue;
				} else {
					System.out.println("?");
					continue;
				}
			}

			if(input.equals("Q")) {
				break;
			}else if(input.equals("q")) {
				if(s.hasNext()) {
					System.out.println("?");
					String temp = s.nextLine();					
					if(temp.equals("q")) {
						break;
					}
					op.process(temp, edBuffer);
					continue;
				}else {
					break;
				}
			}
			op.process(input, edBuffer);
			
		}
		s.close();
	}

	protected static boolean aicAddressVaild(String order, ED_Buffer edBuffer){
		if(order.substring(order.length()-1).equals("c")){
			if(edBuffer.textContent.size()==0){
				return false;
			}
			if(order.equals("c")){
				return true;
			}
			int[] address = FindAddtress.getAddress(order.substring(0,order.length()-1), edBuffer.defaultLocation, edBuffer.textContent);
			if(address[0]>address[1]||address[0]<=0||address[1]>edBuffer.textContent.size()){
				return false;
			}else {
				return  true;
			}
		}else{
			if(order.equals("a")||order.equals("i")){
				return true;
			}
			int address = FindAddtress.getAddress(order.substring(0,order.length()-1), edBuffer.defaultLocation, edBuffer.textContent)[1];
			if(address>edBuffer.textContent.size()||address<0){
				return false;
			}else{
				return true;
			}
		}

	}

}
