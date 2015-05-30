/** @version $Id: Delete.java,v 1.6 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Delete command.
 */
public class Delete extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public Delete(CalcSheet receiver) {
		super(MenuEntry.DELETE, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		String gama = IO.readString(Message.addressRequest());
		if (!_receiver.confirmRange(gama)) {
			throw new InvalidCellRange(gama);
		}
		else {
			_receiver.deleteContent(gama);
		}
	}
}
