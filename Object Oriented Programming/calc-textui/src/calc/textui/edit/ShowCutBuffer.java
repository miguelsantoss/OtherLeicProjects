/** @version $Id: ShowCutBuffer.java,v 1.5 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;

/**
 * Show cut buffer command.
 */
public class ShowCutBuffer extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public ShowCutBuffer(CalcSheet receiver) {
		super(MenuEntry.SHOW_CUT_BUFFER, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		 IO.println(_receiver.showCutBuffer()); 
	}
}
