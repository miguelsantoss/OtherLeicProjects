/** @version $Id: MenuBuilder.java,v 1.6 2013-11-27 20:10:13 ist175551 Exp $ */
package calc.textui.main;

import ist.po.ui.Command;
import ist.po.ui.Menu;
import calc.SheetManager;

/**
 * Menu builder for the main menu.
 */
public abstract class MenuBuilder {

	/**
	 * @param manager
	 */
	public static void menuFor(SheetManager manager) {
		Menu menu = new Menu(MenuEntry.TITLE, new Command<?>[] {
				new New(manager),
				new Open(manager),
				new Save(manager),
				new SaveAs(manager),
				new MenuOpenEdit(manager),
				new MenuOpenSearch(manager),
                                });
		menu.open();
	}

}
