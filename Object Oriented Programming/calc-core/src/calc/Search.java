package calc;

public interface Search {
    String visitADD(ADD c);
    String visitSUB(SUB c);
    String visitMUL(MUL c);
    String visitDIV(DIV c);
    String visitAVG(AVG c);
    String visitPRD(PRD c);
    String visitLiteral(Literal c);
    String visitCellReference(CellReference c);
}