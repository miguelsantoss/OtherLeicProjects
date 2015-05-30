/** @version $Id: ShowFunctions.java,v 1.5 2013-12-03 11:37:24 ist175551 Exp $ */
package calc.textui.search;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;
import calc.SearchFunction;

/**
 * Class for searching functions.
 */
public class ShowFunctions extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public ShowFunctions(CalcSheet receiver) {
		super(MenuEntry.SEARCH_FUNCTIONS, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
               String search = IO.readString(Message.searchFunction());
		IO.println(_receiver.search(new SearchFunction(), search));
        }

}
