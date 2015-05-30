package calc;

public class Literal extends Content {
	private int _value;
	public Literal(int value) { _value = value; }
	public Literal(Literal a) { this._value = a._value; }
	@Override
	public int getValue() { return _value; }
	@Override
	public Content clone() { return new Literal(this); }
	@Override
	public String showValue() {
		return Integer.toString(_value);
	}
	@Override
	public String accept(Search v) { return v.visitLiteral(this); }
}
