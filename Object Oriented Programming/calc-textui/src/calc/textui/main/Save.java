/** @version $Id: Save.java,v 1.6 2013-11-28 19:20:10 ist175551 Exp $ */
package calc.textui.main;

import java.io.IOException;
import java.io.FileNotFoundException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;
import ist.po.ui.ValidityPredicate;

import calc.SheetManager;

/**
 * Command to save a file.
 */
public class Save extends Command<SheetManager> {

	/**
	 * @param receiver
	 */
	public Save(SheetManager receiver) {
		super(MenuEntry.SAVE, receiver, new ValidityPredicate<SheetManager>(receiver) {
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
		try {
			_receiver.save();
		} catch (FileNotFoundException file) {
			String Filename = IO.readString(Message.newSaveAs());
			_receiver.saveAs(Filename);
		}
			      
        }

}
