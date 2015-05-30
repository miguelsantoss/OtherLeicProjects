/** @version $Id: Paste.java,v 1.6 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Paste command.
 */
public class Paste extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public Paste(CalcSheet receiver) {
		super(MenuEntry.PASTE, receiver);
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
			_receiver.paste(gama);
		}
	}
}