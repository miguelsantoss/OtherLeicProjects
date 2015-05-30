/** @version $Id: MenuBuilder.java,v 1.3 2013-11-15 01:20:43 ist175551 Exp $ */
package calc.textui.search;

import ist.po.ui.Command;
import ist.po.ui.Menu;

import calc.CalcSheet;

/**
 * Menu builder for search operations.
 */
public class MenuBuilder {

	/**
	 * FIXME: commands may have one or more receivers
	 */
	public static void menuFor(CalcSheet receiver) {
		Menu menu = new Menu(MenuEntry.TITLE, new Command<?>[] {
				new ShowValues(receiver),
				new ShowFunctions(receiver) });
		menu.open();
	}
}

