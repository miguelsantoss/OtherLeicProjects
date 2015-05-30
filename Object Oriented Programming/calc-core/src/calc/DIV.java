package calc;

public class DIV extends BinaryFunction {
	public DIV(Cell cell1, Cell cell2) { super(cell1, cell2, "DIV"); }
	public DIV(Cell cell1, int value) { super(cell1, value, "DIV"); }
	public DIV(int value, Cell cell2) { super(value, cell2, "DIV"); }
	public DIV(int value1, int value2) { super(value1, value2, "DIV"); }
	public DIV(DIV a) { super(a); }
	@Override
	public Content clone() { return new DIV(this); }
	@Override
	public String accept(Search v) { return v.visitDIV(this); }
	@Override
	public int execute() {
		return getOper1().getValue() / getOper2().getValue();
	}
} 