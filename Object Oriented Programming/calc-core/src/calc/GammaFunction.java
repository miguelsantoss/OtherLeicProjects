package calc;

import java.util.ArrayList;

public abstract class GammaFunction extends Function {
	private ArrayList<Content> _listElements;
	public GammaFunction(Cell cell1, Cell cell2, String name, ArrayList<Content> listElements) { super(cell1,cell2, name); _listElements = listElements; }
	public GammaFunction(GammaFunction a) {
		super(a);
		a._listElements = new ArrayList<Content>();
		for(Content i: this._listElements) {
			a._listElements.add(i.clone());
		}			
	}
	public ArrayList<Content> getContentGamma() { return _listElements; }
	@Override
	public String showValue() {
		return "" + this.getValue() + "=" +  this.getName() + "(" + Integer.toString(this.getOper1().getLine()) + ";" + Integer.toString(this.getOper1().getColumn()) + ":" + Integer.toString(this.getOper2().getLine()) + ";" + Integer.toString(this.getOper2().getColumn()) + ")"; 
	}
	@Override
	public String accept(Search v) {return ""; /*FIX dis */}
}
	
