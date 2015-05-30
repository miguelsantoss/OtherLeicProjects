package calc;

public abstract class Function extends Content {
	private String _name;
	private Cell _oper_1;
	private Cell _oper_2;
	public Function (Cell cell1, Cell cell2, String name) {
		
		_oper_1 = cell1;
		_oper_2 = cell2;
		_name = name;
	}
	public Function (Cell cell, int value, String name) {
		_oper_1 = cell;
		_oper_2 = new Cell(new Literal(value));
		_name = name;
	}
	public Function (int value, Cell cell, String name) {
		_oper_1 = new Cell(new Literal(value));
		_oper_2 = cell;
		_name = name;
	}
	public Function (int value1, int value2, String name) {
		_oper_1 = new Cell(new Literal(value1));
		_oper_2 = new Cell(new Literal(value2));
		_name = name;
	}
	public Function (Function a) {
		this._oper_1 = a._oper_1;
		this._oper_2 = a._oper_2;
		this._name = a._name;
	}
	public Cell getOper1() { return _oper_1; }
	public Cell getOper2() { return _oper_2; }
	public String getName() { return _name; }
	public abstract int execute();
	@Override
	public int getValue() { return this.execute(); }
	public abstract String showValue();
}
	
