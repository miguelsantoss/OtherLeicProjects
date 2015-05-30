package calc;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.regex.Pattern;

/**
 * CalcSheets have cells, which contain contents and may interact with each
 * others.
 */

public class CalcSheet implements Serializable {
    /** CalcSheet's number of lines. */
	private int _lines;
    
    /** CalcSheet's number of columns. */
	private int _columns;
    
    /** A boolean to keep track if the file is modified since the last time 
     *      it was saved.
     */
	private boolean _modified = true;
    
    /** CalcSheet's name. */
	private String _fileName = "";
    
    /** CalcSheet has a collection of cells. */
	private ArrayList<Cell> _cellCollection = null;

    
    /** CutBuffer has a collection of contents. */
	private ArrayList<Cell> _cutBuffer = null;
	private String _cutBufferDirection = "";
    
    /**
     * Create a CalcSheet.
     *
     *@param lines
     *          initial lines for the CalcSheet.
     *
     *@param columns
     *          initial columns for the CalcSheet.
     *
     */
	public CalcSheet(int lines, int columns) {
        _lines = lines;
        _columns = columns;
        _cellCollection = new ArrayList<Cell> (lines * columns);
        fillArray();
    }
    
    /**
     * @return the number of lines of the CalcSheet.
     */
	public int getLines() {
        return _lines;
    }
    
    /**
     * @return the number of columns of the CalcSheet.
     */
	public int getColumns() {
        return _columns;
    }
    
    /**
     * @return the boolean to check if the CalcSheet was modified.
     */
	public boolean getModifiedState() {
        return _modified;
    }
    
    /**
     * @return the name of the CalcSheet.
     */
	public String getFileName() {
        return _fileName;
    }
    /**
     * @return the cell collection array.
     */
	public ArrayList<Cell> getCellscollection() {
        return _cellCollection;
    }
    
    /**
     * @param name
     *          the CalcSheet's new name.
     */
	public void setFileName(String name) {
		_fileName = name;
    }
    
    /**
     * @param line
     *          target cell's line.
     *
     * @param column
     *          target cell's column.
     *
     * @return the cell with the specific coordinates in the array of cells.
     */
	public Cell getCell(int line, int column) {
		int position = givePosition(line, column);
		if (_cellCollection.get(position) != null) {
			return _cellCollection.get(position);
		}
		else {
			return this.insertCell(line, column);
		}
	}
    
    /**
     * @param state
     *          the CalcSheet's new state.
     */
	public void setModified(boolean state) {
        _modified = state;
    }
	
    /**
     * @param cell
     *          the target cell.
     *
     * @return true if the target cell is already in the CalcSheet's cells
     *         collection, false if it isn't.
     */
	private boolean isThere(Cell cell) {
		boolean is;
		try{
			is = _cellCollection.get(givePosition(cell)).equals(cell);
		} catch (NullPointerException e) {
			is = false;
		}
		return is;
	}
    
    /**
     * @param cell
     *          the target cell.
     *
     * @return the position in which the cell is in the cells collection.
     */
	private int givePosition(Cell cell) {
		return (((cell.getLine() - 1) * this.getColumns()) + cell.getColumn());
	}
    
	private int givePosition(int line, int column) {
		return (((line-1)*this.getColumns()) + column);
	}
	
    /**
     * Create and register a cell without specific sontent.
     *
     * @param line
     *          the target line.
     *
     * @param column
     *          the target column.
     * 
     * @return the cell associated to the specific coordinates in the array
     *          of cells.
     */
	public Cell insertCell(int line, int column) {
		Cell cell = new Cell(line, column);
		if (!isThere(cell)) { 
			_cellCollection.add(givePosition(cell), cell);
			setModified(true);
			return _cellCollection.get(givePosition(cell));
		}
		else {
			return _cellCollection.get(givePosition(cell));
		}
	}
	
    
    /**
     * Create and register a cell with specific sontent.
     *
     * @param line
     *          the target line.
     *
     * @param column
     *          the target column.
     *
     * @param content
     *          the specific content for the cell.
     *
     * @return the cell associated to the specific coordinates in the array
     *          of cells and the specific content given in parametres.
     */
	public Cell insertCell(int line, int column, Content content) {
		Cell cell = new Cell(line, column, content);
		if (!isThere(cell)) { 
			_cellCollection.add(givePosition(cell), cell); 
			setModified(true);
			return _cellCollection.get(givePosition(cell));
		}
		else {
			cell = _cellCollection.get(givePosition(cell));
			cell.setContent(content);
			return cell;
		}
		
	}
	
    /**
     * Receives a type of search and the target and finds it in the array of
     *  cells.
     *
     * @param typeofSearch
     *          the type of search the user wants to do.
     *
     * @param target
     *          the string we want to match.
     *
     * @return the string containing all the matches and respective values.
     */
	public String search(Search typeOfSearch, String target) {
		String result = "";
		Cell cell;
		int line = 1;
		int column = 1;
		for ( ; line < this.getLines(); line++) {
			for ( ; column < this.getColumns(); column++) {
				cell = this.getCell(line, column);	
				if (cell.getContent() != null) {
					if ((cell.getContent().accept(typeOfSearch)).equals(target)) {
						result += cell.showCell() + cell.showContent() + "\n";
					}
				}
			}
			column = 1;
		}
		if (result.length() > 0 && result.charAt(result.length()-1)=='\n') {
			result = result.substring(0, result.length()-1);	
		}
		return result;
	}
	
    /**
     * Used to fill the array of cells with null pointers so that we can work
     *     with the size we want.
     */
	private void fillArray() {
		for(int i = 0; i < (_lines*_columns); i++) {
			_cellCollection.add(null);
		}
	}
	 
    /**
     * Show as a String each cell and specific content in the range of a
     *      gamma.
     *
     * @param gamma
     *          the target gamma.
     *
     * @return an array of Strings containing all the cells and respective
     *         content in the range of the target gamma.
     */
	public String show(Gamma gamma) throws NullPointerException {
		String toShow = "";
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		if (gamma.getDirection().equals("")) {
			toShow += this.getCell(lines, columns).showCell() + this.getCell(lines, columns).showContent();
		}
		else if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++) {
				toShow += this.getCell(lines, columns).showCell() + this.getCell(lines, columns).showContent() + "\n";
			}
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++) {
				toShow += this.getCell(lines, columns).showCell() + this.getCell(lines, columns).showContent() + "\n";
			}
		}
		if (toShow.length() > 0 && toShow.charAt(toShow.length()-1)=='\n') {
			toShow = toShow.substring(0, toShow.length()-1);	
		}
		return toShow;
	}
	
    /**
     * Parses the input to identify the target gamma.
     *
     * @param input
     *          target gamma.
     *
     * @return a string with each cells' coordinates and contents.
     */
	public String show(String input) {
		Gamma gamma = parseGamma(input);
		return show(gamma);
	}

    /**
     * Copy the content of each cell from the range of the gamma to the
     * CutBuffer.
     *
     * @param input
     *          the target gamma.
     */
	public void copy(String input) {
		Gamma gamma = parseGamma(input);
		_cutBuffer = new ArrayList<Cell>(gamma.getSize());
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		int bufferLine = 1;
		int bufferColumn = 1;
		if (gamma.getDirection().equals("")) {
			try{
			_cutBuffer.add(new Cell(bufferLine, bufferColumn,this.getCell(lines, columns).getContent()));
			} catch (NullPointerException e) {
				_cutBuffer.add(new Cell(bufferLine, bufferColumn));
			}
			_cutBufferDirection = "";
		}
		if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++, bufferLine++) {
				try{
				_cutBuffer.add(new Cell(bufferLine, bufferColumn,this.getCell(lines, columns).getContent()));
				} catch (NullPointerException e) {
					_cutBuffer.add(new Cell(bufferLine, bufferColumn));
				}
			}
			_cutBufferDirection = "vertical";
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++, bufferColumn++) {
				try{
				_cutBuffer.add(new Cell(bufferLine, bufferColumn,this.getCell(lines, columns).getContent()));
				} catch (NullPointerException e) {
					_cutBuffer.add(new Cell(bufferLine, bufferColumn));
				}
			}
			_cutBufferDirection = "horizontal";
		}
	}
	
    /**
     * Copy the content of each cell from the range of the gamma to the
     * an array of Contents.
     *
     * @param gamma
     *          the target gamma.
     *
     * @return the array filled with the target contents.
     */
	public ArrayList<Content> copyContents(Gamma gamma) {
		ArrayList<Content> contents = new ArrayList<Content>(gamma.getSize());
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		if (gamma.getDirection().equals("")) {
			contents.add(_cellCollection.get(givePosition(lines, columns)).getContent().clone());
		}
		else if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++) {
				contents.add(_cellCollection.get(givePosition(lines, columns)).getContent().clone());
			}
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++) {
				contents.add(_cellCollection.get(givePosition(lines, columns)).getContent().clone());
			}
		}
		return contents;
	}
    
    /**
     * Delete the content of each cell from the range of the gamma.
     *
     * @param input
     *          the target gamma.
     */
	public void deleteContent(String input) {
		Gamma gamma = parseGamma(input);
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		if (gamma.getDirection().equals("")) {
			this.getCell(lines, columns).setContent(null);
		}
		if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++) {
				this.getCell(lines, columns).setContent(null);
			}
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++) {
				this.getCell(lines, columns).setContent(null);
			}
		}
	}
    
    /**
     * Copy the content of each cell from the range of the gamma to the
     * CutBuffer and then delete all the content from each cell from the
     * range of the gamma.
     *
     * @see CalcSheet#copy(Gamma)
     *
     * @see CalcSheet#deleteContent(Gamma)
     *
     * @param gamma
     *          the target gamma.
     */
	public void cut(String gamma) {
		copy(gamma);
		deleteContent(gamma);
		setModified(true);
	}
    
    /**
     * Sets the content of each cell from the range of the gamma to the
     * CutBuffer.
     *
     * @param gamma
     *          the target gamma.
     */
	public void paste(String input) {
		Gamma gamma = parseGamma(input);
		int index = 0;
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		if (gamma.getDirection().equals("")) {
			System.out.println(_cutBufferDirection);
			if (_cutBufferDirection.equals("vertical")) {
				for (; lines <= linesMax; lines++, index++) {
					this.getCell(lines, columns).setContent(_cutBuffer.get(index).getContent());
				}
			}
			else if (_cutBufferDirection.equals("horizontal")) {
				for (; columns <= columnsMax; columns++, index++) {
					this.getCell(lines, columns).setContent(_cutBuffer.get(index).getContent());
				}
			}
			else {
				this.getCell(lines, columns).setContent(_cutBuffer.get(index).getContent());
			}
		}
		if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++, index++) {
				this.getCell(lines, columns).setContent(_cutBuffer.get(index).getContent());
			}
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++, index++) {
				this.getCell(lines, columns).setContent(_cutBuffer.get(index).getContent());
			}
		}
	}
    
    /**
     * Show as a String the contents in the CutBuffer.
     *
     * @return the array of Strings with each content as a String.
     */ 
	public String showCutBuffer() {
		String toShow = "";
		int stringIndex = 0;
		if (_cutBuffer != null) {
			for(int i = 0; i <= _cutBuffer.size() - 1; i++, stringIndex++) {
				toShow += Integer.toString(_cutBuffer.get(i).getLine()) + ";" + Integer.toString(_cutBuffer.get(i).getColumn()) + "|" + _cutBuffer.get(i).showContent() + "\n"; 
			}
			if (toShow.length() > 0 && toShow.charAt(toShow.length()-1)=='\n') {
				toShow = toShow.substring(0, toShow.length()-1);	
			}
		}
		return toShow;
	} 

	
    /**
     * Split the input in the coordinates of the gamma.
     *
     * @param input
     *          the target gamma.
     *
     * @return a gamma with the given coordinates after the parse of the input.  
     */
	public Gamma parseGamma(String input) {
		String[] split = input.replace(":",";").split(";");
		try {
			return new Gamma(this.insertCell(Integer.parseInt(split[0]), Integer.parseInt(split[1])), this.insertCell(Integer.parseInt(split[2]), Integer.parseInt(split[3])));
		} catch (ArrayIndexOutOfBoundsException oneCell) {
			return new Gamma(this.insertCell(Integer.parseInt(split[0]), Integer.parseInt(split[1])), this.insertCell(Integer.parseInt(split[0]), Integer.parseInt(split[1])));
		}
	}

    /**
     * Confirm if the gamma is in range of the CalcSheet.
     *
     * @param gamma
     *          the target gamma.
     *
     * @return boolean if the gamma is inside the CalcSheet.
     */
	public boolean confirmRange(String gamma) {
		String[] test = gamma.replace(":",";").split(";");
		for(String i:test) {
			if (Integer.parseInt(i) <= 0) {
				return false;
			}
		}
		try {
			if ((Integer.parseInt(test[0]) != Integer.parseInt(test[2])) && (Integer.parseInt(test[1]) != Integer.parseInt(test[3]))) {
				return false;
			}
			return ((Integer.parseInt(test[0]) <= this.getLines()) && (Integer.parseInt(test[2]) <= this.getLines()) && (Integer.parseInt(test[1]) <= this.getColumns()) && (Integer.parseInt(test[3]) <= this.getColumns()));
		} catch (ArrayIndexOutOfBoundsException oneCell) {
			return ((Integer.parseInt(test[0]) <= this.getLines()) && (Integer.parseInt(test[1]) <= this.getColumns())); }	
	}
    
    /**
     * Insert in each cell of a gamma a specific content.
     *
     * @param gamma
     *          the target gamma.
     *
     * @param content
     *          the specific content.
     */
	public void insertGamma(String gammaString, String contentString) {
		Gamma gamma = parseGamma(gammaString);
		Content content = parseContent(contentString);
		int lines = gamma.getBeginningLine();
		int columns = gamma.getBeginningColumn();
		int linesMax = gamma.getEndLine();
		int columnsMax = gamma.getEndColumn();
		if (gamma.getDirection().equals("")) {
			this.insertCell(lines, columns, content);
		}
		if (gamma.getDirection().equals("vertical")) {
			for (; lines<=linesMax ; lines++) {
				this.insertCell(lines, columns, content);
			}
		}
		else if (gamma.getDirection().equals("horizontal")) {
			for(; columns <= columnsMax ; columns++) {
				this.insertCell(lines, columns, content);
			}
		}
	 }
	 
    /**
     * Split the input in the content it represents, parsing by the patterns
     *  Matcher and Pattern.
     *
     * @param input
     *          the target content.
     *
     * @return the content as an instance.
     */
	public Content parseContent(String input) throws UnknownDataException {
		input.replace("=", "");
		Pattern cell = Pattern.compile("(\\d)+;(\\d)+");
		Pattern functionADD = Pattern.compile("ADD\\((((\\d)+;(\\d)+)|((\\d)+)),(((\\d)+;(\\d)+)|((\\d)+))\\)");
		Pattern functionSUB = Pattern.compile("SUB\\((((\\d)+;(\\d)+)|((\\d)+)),(((\\d)+;(\\d)+)|((\\d)+))\\)");
		Pattern functionDIV = Pattern.compile("DIV\\((((\\d)+;(\\d)+)|((\\d)+)),(((\\d)+;(\\d)+)|((\\d)+))\\)");
		Pattern functionMUL = Pattern.compile("MUL\\((((\\d)+;(\\d)+)|((\\d)+)),(((\\d)+;(\\d)+)|((\\d)+))\\)");
		Pattern functionAVG = Pattern.compile("AVG\\((\\d)+;(\\d)+:(\\d)+;(\\d)+\\)");
		Pattern functionPRD = Pattern.compile("PRD\\((\\d)+;(\\d)+:(\\d)+;(\\d)+\\)");
		Pattern literal = Pattern.compile("(\\d)+");
		if (functionADD.matcher(input).matches()) {
			return contentFunctionADD(input);
		}
		else if (functionSUB.matcher(input).matches()) {
			return contentFunctionSUB(input);
		}
		else if (functionDIV.matcher(input).matches()) {
			return contentFunctionDIV(input);
		}
		else if (functionMUL.matcher(input).matches()) {
			return contentFunctionMUL(input);
		}
		else if (functionPRD.matcher(input).matches()) {
			return contentFunctionPRD(input);
		}
		else if (functionAVG.matcher(input).matches()) {
			return contentFunctionAVG(input);
		}
		else if (cell.matcher(input).matches()) {
			return contentCellReference(input);
		}
		else if (literal.matcher(input).matches()) {
			return contentLiteral(input);
		}
		else {
			throw new UnknownDataException(input);
		}
	}
	
    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionADD(String content) {
		String[] cellContent = content.replace("ADD(","").replace(")","").split(",");
		String secondArgumentDetails[];
		if (cellContent[0].contains(";")) { 
			String firstArgumentDetails[] = cellContent[0].split(";");
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new ADD(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new ADD(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), Integer.parseInt(cellContent[1]));
			}		
		}
		else {
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new ADD(Integer.parseInt(cellContent[0]), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new ADD(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1]));
			}
		}
	}
    
    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionSUB(String content) {
		String[] cellContent = content.replace("SUB(","").replace(")","").split(",");
		String secondArgumentDetails[];
		if (cellContent[0].contains(";")) { 
			String firstArgumentDetails[] = cellContent[0].split(";");
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new SUB(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new SUB(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), Integer.parseInt(cellContent[1]));
			}		
		}
		else {
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new SUB(Integer.parseInt(cellContent[0]), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new SUB(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1]));
			}
		}
	}

    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionMUL(String content) {
		String[] cellContent = content.replace("MUL(","").replace(")","").split(",");
		String secondArgumentDetails[];
		if (cellContent[0].contains(";")) { 
			String firstArgumentDetails[] = cellContent[0].split(";");
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new MUL(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new MUL(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), Integer.parseInt(cellContent[1]));
			}		
		}
		else {
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new MUL(Integer.parseInt(cellContent[0]), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new MUL(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1]));
			}
		}
	}
    
    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionDIV(String content) {
		String[] cellContent = content.replace("DIV(","").replace(")","").split(",");
		String secondArgumentDetails[];
		if (cellContent[0].contains(";")) { 
			String firstArgumentDetails[] = cellContent[0].split(";");
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new DIV(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new DIV(this.insertCell(Integer.parseInt(firstArgumentDetails[0]),Integer.parseInt(firstArgumentDetails[1])), Integer.parseInt(cellContent[1]));
			}		
		}
		else {
			if (cellContent[1].contains(";")) {
				secondArgumentDetails = cellContent[1].split(";");
				return new DIV(Integer.parseInt(cellContent[0]), this.insertCell(Integer.parseInt(secondArgumentDetails[0]),Integer.parseInt(secondArgumentDetails[1])));
			}
			else {
				return new DIV(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1]));
			}
		}
	}

    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionAVG(String content) {
		String[] cellContent = content.replace("AVG(","").replace(")","").replace(":",";").split(";");
		return new AVG(this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.copyContents(new Gamma(this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])))));
	}

    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentFunctionPRD(String content) {
		String[] cellContent = content.replace("PRD(","").replace(")","").replace(":",";").split(";");
		return new PRD(this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.copyContents(new Gamma(this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])), this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])))));
	}
	
    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentLiteral(String content) {
		return new Literal(Integer.parseInt(content));
	}
	
    /**
     * @param content
     *          the target content
     *
     * @return an instance of the chosen Content's subclass.
     */
	private Content contentCellReference(String content) {
		String[] cellContent = content.split(";");
		return new CellReference(this.insertCell(Integer.parseInt(cellContent[0]),Integer.parseInt(cellContent[1])));
	}
}