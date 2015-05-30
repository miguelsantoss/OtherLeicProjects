/** @version $Id: MenuBuilder.java,v 1.4 2013-11-29 19:35:38 ist175551 Exp $ */
package calc.textui.edit;

import ist.po.ui.Command;
import ist.po.ui.Menu;

import calc.CalcSheet;

/**
 * Menu builder for edit operations.
 */
public class MenuBuilder {
	public static void menuFor(CalcSheet sheet) {
		Menu menu = new Menu(MenuEntry.TITLE, new Command<?>[] {
				new Show(sheet),
				new Insert(sheet),
				new Copy(sheet),
				new Delete(sheet),
				new Cut(sheet),
				new Paste(sheet),
				new ShowCutBuffer(sheet),
                new EmptyGamma(sheet),
                new Not5(sheet),
				});
		menu.open();
	}

}
