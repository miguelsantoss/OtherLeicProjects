package calc;

public class SearchFunction implements Search {
    
    public String visitADD(ADD c) {
        return c.getName();
    }
    public String visitSUB(SUB c) {
        return c.getName();
    }
    public String visitMUL(MUL c) {
	return c.getName();   
    }
    public String visitDIV(DIV c) {
	return c.getName();
    }
    public String visitAVG(AVG c) {
	return c.getName();
    }
    public String visitPRD(PRD c) {
	return c.getName();
    }
    public String visitLiteral(Literal c) {
        return "Literal";
    }
    public String visitCellReference(CellReference c) {
        return "Reference";
    }
}