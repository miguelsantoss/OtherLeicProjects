package calc;

import java.io.*;
import java.io.Serializable;
import java.util.regex.Pattern;

public class SheetManager {
	private CalcSheet _sheet = null;
	public SheetManager() { }
	public boolean hasSheet() { if (_sheet == null) return false; return true; }
	public void save() throws IOException, FileNotFoundException {
		String file = _sheet.getFileName();
		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(file));
		out.writeObject(_sheet);
		out.close();
		_sheet.setModified(false);
	}
	public void saveAs(String file) throws IOException {
		_sheet.setFileName(file);
		save();
	}
	public void load(String file) throws IOException, ClassNotFoundException, FileNotFoundException {
		ObjectInputStream in = new ObjectInputStream(new FileInputStream(file));
		CalcSheet sheet = (CalcSheet)in.readObject();
		in.close();
		this.setSheet(sheet);
		_sheet.setModified(false);
	}
	
	public boolean isModified() {
		if (this.getSheet() != null) {
			return _sheet.getModifiedState();
		}
		else {
			return false;
		}
	}
	
	public CalcSheet getSheet() { return _sheet; }
	
	public void createCalcSheet(int lines, int columns) throws FileNotSavedException { 
		if ((this.getSheet() == null)||(!_sheet.getModifiedState())) {
			this.setSheet(new CalcSheet(lines, columns));
		}
		else {
			throw new FileNotSavedException();
		}
	}

	public void setSheet(CalcSheet sheet) { _sheet = sheet; }
	private int givePosition(Cell cell) {
		return (((cell.getLine() - 1) * this.getSheet().getColumns()) + cell.getColumn());
	}
	public void readInputFile(String file) throws IOException, UnknownDataException {
		BufferedReader reader = new BufferedReader(new FileReader(file));
		int lines = Integer.parseInt(reader.readLine().split("=")[1]);
		int columns = Integer.parseInt(reader.readLine().split("=")[1]);
		_sheet = new CalcSheet(lines, columns);
		String line;
		while ((line = reader.readLine()) != null) {
			String split[] = line.replace("=","").split("\\|");
			_sheet.insertGamma(split[0], split[1]);
		}
		reader.close();
	}
}