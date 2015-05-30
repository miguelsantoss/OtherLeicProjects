/** @version $Id: Show.java,v 1.9 2013-12-02 13:39:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Show cells command.
 */
public class EmptyGamma extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public EmptyGamma(CalcSheet receiver) {
		super(MenuEntry.EMPTYGAMMA, receiver);
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
			IO.println(Integer.toString(_receiver.IsEmptyGamma(gamma)));
		}
	}
}
