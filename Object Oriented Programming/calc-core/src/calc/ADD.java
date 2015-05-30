package calc;

public class ADD extends BinaryFunction {
	public ADD(Cell cell1, Cell cell2) { super(cell1, cell2, "ADD"); }
	public ADD(Cell cell, int value) { super(cell, value, "ADD"); }
	public ADD(int value, Cell cell) { super(value, cell, "ADD"); }
	public ADD(int value1, int value2) { super(value1, value2, "ADD"); }
	public ADD(ADD a) { super (a); }
	@Override
	public Content clone() { return new ADD(this); }
	public String accept(Search v) { return v.visitADD(this); }
	@Override
	public int execute() {
		return getOper1().getValue() + getOper2().getValue();
	}
} 





