/** @version $Id: New.java,v 1.8 2013-12-03 10:44:26 ist175551 Exp $ */
package calc.textui.main;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.SheetManager;

/**
 * Create a new spreadsheet.
 */
public class New extends Command<SheetManager> {

	/**
	 * @param receiver
	 */
	public New(SheetManager receiver) {
		super(MenuEntry.NEW, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
	public final void execute() throws DialogException, IOException {
		if(_receiver.isModified()) {
			String answer = IO.readString(Message.saveBeforeExit());
			if (answer.equals("s")) {
				String Filename = IO.readString(Message.newSaveAs());
				_receiver.saveAs(Filename);
			}
			else if (answer.equals("n")) {
				
			}
			else {
				throw new IOException("Resposta invalida");
			}
		}
		int lines = IO.readInteger(Message.linesRequest());
		int columns = IO.readInteger(Message.columnsRequest());
		_receiver.createCalcSheet(lines, columns);
	}
}
