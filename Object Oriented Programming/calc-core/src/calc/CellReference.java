package calc;

public class CellReference extends Content {
	private Cell _reference;
	public CellReference(Cell cell) { _reference = cell; }
	public CellReference(CellReference a) { this._reference = a._reference; }
	public Cell getCellReference() { return _reference; }
	@Override
	public Content clone() { return new CellReference(this); }
	@Override
	public String accept(Search v) { return v.visitCellReference(this); }
	@Override
	public int getValue() { return _reference.getValue(); }
	@Override
	public String showValue() {
		try {
			return "" + Integer.toString(_reference.getValue()) + "=" + _reference.getLine() + ";" + _reference.getColumn();
		}
		catch (NullPointerException e) {
			return "#VALUE" + "=" + _reference.getLine() + ";" + _reference.getColumn();
		}
	} 
}
