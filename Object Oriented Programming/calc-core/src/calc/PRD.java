package calc;

import java.util.ArrayList;

public class PRD extends GammaFunction {
	public PRD(Cell cell1, Cell cell2, ArrayList<Content> listValues) { super(cell1, cell2, "PRD", listValues); }
	public PRD(PRD a) { super(a); }
	@Override
	public Content clone() { return new PRD(this); }
	@Override
	public int execute() {
		ArrayList<Content> listValues = getContentGamma();
		int result = 1;
		for(Content content: listValues) {
			result *= content.getValue();
		}
		return result;
	}
}
