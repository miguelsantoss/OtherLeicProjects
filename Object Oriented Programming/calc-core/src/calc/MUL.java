package calc;

public class MUL extends BinaryFunction {
	public MUL(Cell cell1, Cell cell2) { super(cell1, cell2, "MUL"); }
	public MUL(Cell cell1, int value) { super(cell1, value, "MUL"); }
	public MUL(int value, Cell cell2) { super(value, cell2, "MUL"); }
	public MUL(int value1, int value2) { super(value1, value2, "MUL"); }
	public MUL(MUL a) { super(a); }
	@Override
	public Content clone() { return new MUL(this); }
	@Override
	public int execute() {
		return getOper1().getValue() * getOper2().getValue();
	}
	@Override
	public String accept(Search v) { return v.visitMUL(this); }
} 