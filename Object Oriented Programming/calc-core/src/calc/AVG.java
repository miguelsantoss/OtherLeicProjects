package calc;

import java.util.ArrayList;

public class AVG extends GammaFunction {
	public AVG(Cell cell1, Cell cell2, ArrayList<Content> listValues) { super(cell1, cell2, "AVG", listValues); }
	public AVG(AVG a) { super(a); }
	@Override
	public Content clone() { return new AVG(this); }
	@Override
	public int execute() {
		ArrayList<Content> listValues = getContentGamma();
		int result = 0;
		int counter = 0;
		for(Content content: listValues) {
			result += content.getValue();
			counter++;
		}
		return result / counter;
	}
}
