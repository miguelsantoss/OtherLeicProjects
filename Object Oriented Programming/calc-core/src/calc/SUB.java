package calc;

public class SUB extends BinaryFunction {
	public SUB(Cell cell1, Cell cell2) { super(cell1, cell2, "SUB"); }
	public SUB(Cell cell1, int value) { super(cell1, value, "SUB"); }
	public SUB(int value, Cell cell2) { super(value, cell2, "SUB"); }
	public SUB(int value1, int value2) { super(value1, value2, "SUB"); }
	public SUB(SUB a) { super(a); }
	@Override
	public Content clone() { return new SUB(this); }
	@Override
	public String accept(Search v) { return v.visitSUB(this); }
	@Override
	public int execute() {
		return getOper1().getValue() - getOper2().getValue();
	}
} 


