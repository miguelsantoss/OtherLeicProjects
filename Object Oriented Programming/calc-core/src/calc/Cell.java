package calc;

import java.io.Serializable;

public class Cell implements Serializable  {
	private int _line;
	private int _column;
	private Content _content = null;
	
	public Cell(int line, int column){
		_line = line;
		_column = column;
	}
	public Cell(int line, int column, Content content) {
		this(line, column);
		_content = content;
	}
	public Cell(Content content) {
		this(0,0);
		_content = content; 
	}
	public int getLine() { return _line; }
	public int getColumn() { return _column; }
	public Content getContent() { return _content; }
	public int getValue() throws NullPointerException {
		return _content.getValue();
	}
	public void setContent(Content content) { _content = content; }
	public String showContent() { if(_content == null) { return ""; } return _content.showValue(); }
	public String showCell() { return Integer.toString(_line) + ";" + Integer.toString(_column) + "|"; }
	@Override
	public boolean equals(Object o) {
		if (o instanceof Cell) {
			Cell c = (Cell) o;
			return (this.getLine() == c.getLine()) && (this.getColumn() == c.getColumn());
		}
		return false;
	}
}
