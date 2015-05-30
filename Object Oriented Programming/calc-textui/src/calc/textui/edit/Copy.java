/** @version $Id: Copy.java,v 1.6 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Copy command.
 */
public class Copy extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public Copy(CalcSheet receiver) {
		super(MenuEntry.COPY, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
	public final void execute() throws DialogException, IOException, InvalidCellRange {
		String gama = IO.readString(Message.addressRequest());
		if (!_receiver.confirmRange(gama)) {
			throw new InvalidCellRange(gama);
		}
		else {
			_receiver.copy(gama);
		}
	}
}
