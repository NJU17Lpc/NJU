package edLineEditor;

import java.util.ArrayList;


/**
 * 
 * textContent为缓存器，保存每次修改后的内容
 * defaultLocation为默认地址，每次操作后需要与这个地址交互一下
 * 这个是对文本读取最重要的地方
 * @author 刘鹏程12138
 *
 */
public class ED_Buffer {
	protected TextOriginData textOriginData = null;
	public ArrayList<String> lastContent = new ArrayList<>();

	public ArrayList<String> textContent = null;
	public int defaultLocation = 0;
	
	public boolean hasFlushed = false;
	public ArrayList<String> tempTXTContent = new ArrayList<>();
	public String checkFilePath = "";
	
	public ED_Buffer(String filePath) {
		this.textOriginData = new TextOriginData(filePath);
		this.checkFilePath = filePath;
	}
	
	public ED_Buffer() {
		textContent = new ArrayList<>();
	}
	
	public void readTextOriginData() {
		textContent = textOriginData.getOriginData();
		defaultLocation = textContent.size();
	}
	
	public void flushTextContentData(ArrayList<String> RealTxtContent, boolean appendable) {//已经设置好默认地址，追加写入
		textOriginData.modifyTextData(RealTxtContent, appendable);
		hasFlushed = true;
	}
	
	public void flushTextContentData(ArrayList<String> RealTxtContent, String filePath) {//覆盖写入
		TextOriginData newTextOriginData = new TextOriginData(filePath);
		newTextOriginData.modifyTextData(RealTxtContent);
		hasFlushed = true;
	}
	
	public void flushTextContentData(ArrayList<String> RealTxtContent, String filePath, boolean appendable) {//追加写入
		TextOriginData newTextOriginData = new TextOriginData(filePath);
		newTextOriginData.modifyTextData(RealTxtContent, appendable);
		hasFlushed = true;
	}

	public void cleanTempTXTContent() {
		tempTXTContent = new ArrayList<>();
	}

	public ArrayList<String> previousContentCopy() {
		ArrayList<String> temp = new ArrayList<>();
		for(String str:textContent){
			temp.add(str);
		}
		return temp;
	}

	public void uploadLastContent(){
		lastContent = new ArrayList<>();
		for(String str:textContent){
			lastContent.add(str);
		}
	}
}
