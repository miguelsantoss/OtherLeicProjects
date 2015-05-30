package calc;

import java.io.Serializable;

public class Gamma implements Serializable {
	private Cell _beginning;
	private Cell _end;
	private int _size;
	private String _direction = "";
	
	public Gamma(Cell cell1, Cell cell2) {
		_beginning = cell1;
		_end = cell2; 
		
		if(((cell1.getLine() - cell2.getLine()) == 0) && ((cell1.getColumn() - cell2.getColumn()) != 0)) {
			_direction = "horizontal";
		}
		else if(((cell1.getLine() - cell2.getLine()) != 0) && ((cell1.getColumn() - cell2.getColumn()) == 0)) {
			_direction = "vertical";
		}
		if (((cell1.getLine() - cell2.getLine()) == 0) && ((cell1.getColumn() - cell2.getColumn()) == 0)) {
			_direction = "";
		}
		_size = giveSize(_beginning, _end);
	}
	private int giveSize(Cell begin, Cell end) {
		return (end.getLine() - begin.getLine()) + (end.getColumn() - begin.getColumn());
	}
	public int getSize() { return _size; }
	public Cell getBeginning() { return _beginning; }
	public int getBeginningLine() { return _beginning.getLine(); }
	public int getBeginningColumn() { return _beginning.getColumn(); }
	public Cell getEnd() { return _end; }
	public int getEndLine() { return _end.getLine(); }
	public int getEndColumn() { return _end.getColumn(); }
	public String getDirection() { return _direction; }
	@Override
	public boolean equals (Object o) {
		if (o instanceof Gamma) {
			Gamma g = (Gamma) o;
			return ((this.getSize() == g.getSize()) && (this.getDirection() == (g.getDirection())));
		}	
		return false; 
	}
}	
