/** @version $Id: MenuOpenSearch.java,v 1.5 2013-11-28 19:20:10 ist175551 Exp $ */
package calc.textui.main;

import ist.po.ui.Command;
import ist.po.ui.ValidityPredicate;

import calc.SheetManager;

/**
 * Open search menu.
 */
public class MenuOpenSearch extends Command<SheetManager> {

	/**
	 * @param receiver
	 */
	public MenuOpenSearch(SheetManager receiver) {
		super(MenuEntry.MENU_SEARCH, receiver, new ValidityPredicate<SheetManager>(receiver) {
			public boolean isValid() {
				return _receiver.hasSheet();
			}
		});
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
	public final void execute() {
		calc.textui.search.MenuBuilder.menuFor(_receiver.getSheet());
	}

}
