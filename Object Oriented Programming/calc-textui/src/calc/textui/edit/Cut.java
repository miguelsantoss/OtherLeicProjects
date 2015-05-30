/** @version $Id: Cut.java,v 1.6 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Cut command.
 */
public class Cut extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public Cut(CalcSheet receiver) {
		super(MenuEntry.CUT, receiver);
	}

	/** 
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		String gamma = IO.readString(Message.addressRequest());
		if (!_receiver.confirmRange(gamma)) {
			throw new InvalidCellRange(gamma);
		}
		else {
			_receiver.cut(gamma);
		}
	}
}