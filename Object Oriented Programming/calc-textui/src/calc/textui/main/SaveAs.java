/** @version $Id: SaveAs.java,v 1.5 2013-11-28 19:20:10 ist175551 Exp $ */
package calc.textui.main;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;
import ist.po.ui.ValidityPredicate;

import calc.SheetManager;

/**
 * Command to save a file with a new name.
 */
public class SaveAs extends Command<SheetManager> {

	/**
	 * @param receiver
	 */
	public SaveAs(SheetManager receiver) {
		super(MenuEntry.SAVE_AS, receiver, new ValidityPredicate<SheetManager>(receiver) {
			public boolean isValid() {
				return _receiver.hasSheet();
			}
		});
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		String Filename = IO.readString(Message.saveAs());
		_receiver.saveAs(Filename);
        }

}
