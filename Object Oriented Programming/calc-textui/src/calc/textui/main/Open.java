/** @version $Id: Open.java,v 1.7 2013-11-30 19:12:14 ist175551 Exp $ */
package calc.textui.main;

import java.io.IOException;
import java.io.FileNotFoundException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.SheetManager;


/**
 * Command to open a file.
 */
public class Open extends Command<SheetManager> {

	/**
	 * @param receiver
	 */
	public Open(SheetManager receiver) {
		super(MenuEntry.OPEN, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
            String Filename = IO.readString(Message.openFile());
            try {
                _receiver.load(Filename);
            } catch (FileNotFoundException file) { IO.println(Message.fileNotFound(Filename)); 
            } catch (ClassNotFoundException e) { IO.println("Erro a carregar ficheiro"); }
	}
}
