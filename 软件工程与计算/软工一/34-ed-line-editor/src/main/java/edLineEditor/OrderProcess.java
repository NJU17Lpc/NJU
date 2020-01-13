package edLineEditor;
/**
 * 这里的正则你到时候随便调调，
 * 我最后也稍微看下
 * 可以吧这些公用的commonPattern等直接放到里面，这样代码长得就不一样
 */

import Order.*;

public class OrderProcess {
	Order specificOrder = null;

	public void process(String orderItem, ED_Buffer edBuffer) {

		String commonPattern = "(['][a-z]([+-]\\d+)?,?|/\\w+/,?|[?]\\w+[?],?|[^a-zA-Z]+,?){0,2}";
		String specialPattern = "(/[[^/?]]*/[[^/?]*]?|[?][^/?]+[?][[^/?]*]?){0,2}";
		String specialAddress = "([/?]\\w+[+/?]+[+-]\\d+,?){0,2}";

		if (orderItem.matches(commonPattern + "z.*")) {

			specificOrder = new z_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches("f\\s*.*")) {

			specificOrder = new f_Order(orderItem, edBuffer);
			specificOrder.perform();
		} else if (orderItem.matches(commonPattern + "a")) {

			specificOrder = new a_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "i")) {

			specificOrder = new i_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "c")||orderItem.matches(specialAddress+"c")
				||orderItem.matches(specialPattern+"c")) {

			specificOrder = new c_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "d")||orderItem.matches(specialAddress+"d")
				||orderItem.matches(specialPattern+"d")) {

			specificOrder = new d_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "p") || (orderItem.matches(specialAddress + "p")) ||
				orderItem.matches(specialPattern + "p")) {

			specificOrder = new p_Order(orderItem, edBuffer);
			specificOrder.perform();
		} else if (orderItem.matches(commonPattern + "\\=")) {

			specificOrder = new equal_Order(orderItem, edBuffer);
			specificOrder.perform();
		} else if (orderItem.matches(commonPattern + "w.*")) {

			specificOrder = new w_Order(orderItem, edBuffer);
			specificOrder.perform();
		} else if (orderItem.matches(commonPattern + "W.*")) {

			specificOrder = new w_upperCase_Order(orderItem, edBuffer);
			specificOrder.perform();
		} else if (orderItem.matches(commonPattern + "t" + commonPattern) || orderItem.matches(specialPattern + "t" + commonPattern)
				|| orderItem.matches(commonPattern + "t" + specialPattern) || orderItem.matches(commonPattern + "t" + specialAddress)) {
			specificOrder = new t_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "m" + commonPattern) || orderItem.matches(specialPattern + "m" + commonPattern)
				|| orderItem.matches(commonPattern + "m" + specialPattern)) {
			specificOrder = new m_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "j") || orderItem.matches(specialAddress + "j")) {
			specificOrder = new j_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(commonPattern + "s.*")) {
			specificOrder = new s_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else if (orderItem.matches(specialPattern + "s.*")) {
			specificOrder = new s_Order(orderItem, edBuffer);
			specificOrder.perform();

		} else {
				System.out.println(orderItem + " has no match");
			}
		}
	}

