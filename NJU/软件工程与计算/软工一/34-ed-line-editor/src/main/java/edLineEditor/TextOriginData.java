package edLineEditor;

import java.io.*;
import java.util.ArrayList;

/**
 *
 * 这里是对原文本内容读取和新建读取的地方
 */
public class TextOriginData {

	protected String filePath = "";
	protected BufferedReader br;
	protected BufferedWriter bw;
	protected ArrayList<String> originData = new ArrayList<>();
	
	public ArrayList<String> getOriginData(){
		ArrayList<String> returnData = new ArrayList<>();
		for(String s:originData) {
			returnData.add(s);
		}
		return returnData;
	}
	
	public TextOriginData(String filePath) {
		this.filePath  = filePath;
		checkFileExistence(filePath);
		String line = null;
		try {
			br = new BufferedReader(new FileReader(filePath));
			while((line=br.readLine())!=null) {
				originData.add(line);
			}
			br.close();
		} catch (IOException e) {
			System.out.println("***文件读取失败***");
			e.printStackTrace();
		}
	}
	
	public void checkFileExistence(String filepath) {
		//System.out.println("in");
		File file = new File(filepath);
		if(!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				System.out.println("文件创建失败");
				e.printStackTrace();
			}
		}
	}
	
	public void modifyTextData(ArrayList<String> newContent) {
		
		try {
			bw = new BufferedWriter(new FileWriter(new File(filePath)));
			for(String s:newContent) {
				bw.write(s+System.getProperty("line.separator"));
			}
			bw.flush();
			bw.close();
		} catch (IOException e) {
			System.out.println("***文件写入失败***");
			e.printStackTrace();
		}
	}
	
	public void modifyTextData(ArrayList<String> newContent, boolean appendable) {
		
		try {
			bw = new BufferedWriter(new FileWriter(new File(filePath),true));
			for(String s:newContent) {
				bw.write(s+System.getProperty("line.separator"));
			}
			bw.flush();
			bw.close();
		} catch (IOException e) {
			System.out.println("***文件写入失败***");
			e.printStackTrace();
		}
	}
}
