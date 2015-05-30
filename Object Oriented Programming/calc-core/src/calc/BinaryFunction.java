package calc;

public abstract class BinaryFunction extends Function {
	public BinaryFunction (Cell cell1, Cell cell2, String name) {
		super(cell1, cell2, name);
	}
	public BinaryFunction (Cell cell, int value, String name) {
		super(cell, value, name);
	}
	public BinaryFunction (int value, Cell cell, String name) {
		super(value, cell, name);
	}
	public BinaryFunction (int value1, int value2, String name) {
		super(value1, value2, name);
	}
	public BinaryFunction (BinaryFunction a) { super(a); }
	public abstract int execute();
	@Override
	public int getValue() { return this.execute(); }
	@Override
	public String showValue() {
		Cell oper_1 = getOper1();
		Cell oper_2 = getOper2();
		if (this.getName().equals("ADD") || this.getName().equals("SUB") || this.getName().equals("MUL") || this.getName().equals("DIV")) {
			if ((oper_1.getLine()) != 0 && (oper_2.getLine() != 0)) {
				return ("" + Integer.toString(this.getValue()) + "=" + this.getName() + "(" + oper_1.getLine() + ";" + oper_1.getColumn() + "," + oper_2.getLine() + ";" + oper_2.getColumn() + ")");
			}
			else if ((oper_1.getLine()) == 0 && (oper_2.getLine() == 0)) {
				return ("" + Integer.toString(this.getValue()) + "=" + this.getName() + "(" + oper_1.getContent().getValue() + "," + oper_2.getContent().getValue() + ")");
			}
			else if (oper_1.getLine() == 0) {
				return ("" + Integer.toString(this.getValue()) + "=" + this.getName() + "(" + oper_1.getContent().getValue() + "," + oper_2.getLine() + ";" + oper_2.getColumn() + ")"); 
			}
			else if (oper_2.getLine() == 0) {
				return ("" + Integer.toString(this.getValue()) + "=" + this.getName() + "(" + oper_1.getLine() + ";" + oper_1.getColumn() + "," + oper_2.getContent().getValue() + ")");
			}
		}
		else {
			return ("" + Integer.toString(this.getValue()) + "=" + this.getName() + "(" + oper_1.getLine() + ";" + oper_1.getColumn() + "," + oper_2.getLine() + ";" + oper_2.getColumn() + ")");
		}
		return null;
	}
}
	
