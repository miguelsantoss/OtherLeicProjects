/** @version $Id: ShowValues.java,v 1.3 2013-12-02 13:39:14 ist175551 Exp $ */
package calc.textui.search;

import java.io.IOException;

import static ist.po.ui.Dialog.IO;
import ist.po.ui.Command;
import ist.po.ui.DialogException;

import calc.CalcSheet;
import calc.SearchValue;

/**
 * Class for searching values.
 */
public class ShowValues extends Command<CalcSheet> {
	/**
	 * @param receiver
	 */
	public ShowValues(CalcSheet receiver) {
		super(MenuEntry.SEARCH_VALUES, receiver);
	}

	/**
	 * @see ist.po.ui.Command#execute()
	 */
	@Override
        public final void execute() throws DialogException, IOException {
		String search = IO.readString(Message.searchValue());
		IO.println(_receiver.search(new SearchValue(), search));
        }

}
