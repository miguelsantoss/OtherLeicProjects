/** @version $Id: Calc.java,v 1.8 2013-11-30 13:58:36 ist175551 Exp $ */
package calc.textui;

import static ist.po.ui.Dialog.IO;

import java.io.IOException;

import calc.SheetManager;
import calc.UnknownDataException;

/**
 * Class that represents the spreadsheet's textual interface.
 */
public class Calc {
  /**
   * @param args
   */
	@SuppressWarnings("nls")
	 public static void main(String[] args) throws IOException {
		SheetManager manager = new SheetManager();
		String datafile = System.getProperty("import");
		if (datafile != null) {
			try {
			manager.readInputFile(datafile);
			} catch (UnknownDataException e) {
				IO.println("Ficheiro de import errado");
			}
		}
		calc.textui.main.MenuBuilder.menuFor(manager);
		IO.closeDown();
	}
}
