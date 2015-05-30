package calc;

public class UnknownDataException extends RuntimeException{
	public UnknownDataException () {}

	public UnknownDataException (String message){
		super (message);
        }

	public UnknownDataException (Throwable cause) {
		super (cause);
        }

	public UnknownDataException (String message, Throwable cause) {
		super (message, cause);
        }
}
