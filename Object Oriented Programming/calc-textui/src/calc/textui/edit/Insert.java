/** @version $Id: Insert.java,v 1.7 2013-12-01 15:58:44 ist175551 Exp $ */
package calc.textui.edit;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;
import calc.UnknownDataException;

import calc.CalcSheet;

/**
 * Insert command.
 */
public class Insert extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public Insert(CalcSheet receiver) {
		super(MenuEntry.INSERT, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		String gamma = IO.readString(Message.addressRequest());
		String content = IO.readString(Message.contentsRequest());
		try {
			if (!_receiver.confirmRange(gamma)) {
				throw new InvalidCellRange(gamma);
			}
			else {
				_receiver.insertGamma(gamma, content);
			}
		} catch (UnknownDataException e) {
			IO.println("Conteudo invalido");
		}
	}
}