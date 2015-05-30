/** @version $Id: MenuOpenEdit.java,v 1.8 2013-11-28 19:20:10 ist175551 Exp $ */
package calc.textui.main;

import ist.po.ui.Command;
import ist.po.ui.ValidityPredicate;

import calc.SheetManager;

/**
 * Open edit menu.
 */
public class MenuOpenEdit extends Command<SheetManager> {

	/**
	 * @param receiver
	 *	   the target Sheet Manager
	 */
	public MenuOpenEdit(SheetManager receiver) {
		super(MenuEntry.MENU_CALC, receiver, new ValidityPredicate<SheetManager>(receiver) {
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
		calc.textui.edit.MenuBuilder.menuFor(_receiver.getSheet());
	}
}