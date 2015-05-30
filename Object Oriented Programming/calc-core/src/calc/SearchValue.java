package calc;

public class SearchValue implements Search {
    public String visitADD(ADD c) {
        return Integer.toString(Integer.parseInt(c.getOper1().getContent().accept(this)) + Integer.parseInt(c.getOper2().getContent().accept(this)));
    }
    public String visitSUB(SUB c) {
        return Integer.toString(Integer.parseInt(c.getOper1().getContent().accept(this)) - Integer.parseInt(c.getOper2().getContent().accept(this)));
    }
    public String visitMUL(MUL c) {
        return Integer.toString(Integer.parseInt(c.getOper1().getContent().accept(this)) * Integer.parseInt(c.getOper2().getContent().accept(this)));
    }
    public String visitDIV(DIV c) {
        return Integer.toString(Integer.parseInt(c.getOper1().getContent().accept(this)) / Integer.parseInt(c.getOper2().getContent().accept(this)));
    }
    public String visitLiteral(Literal c) {
        return Integer.toString(c.getValue());
    }
    public String visitAVG(AVG c) {
        return Integer.toString(c.execute());
    }
    public String visitPRD(PRD c) {
        return Integer.toString(c.execute());
    }
    public String visitCellReference(CellReference c) {
	if (c.getCellReference().getContent() != null) {
	    return c.getCellReference().getContent().accept(this);
        }
        else {
	    return "";
	}
    }
}