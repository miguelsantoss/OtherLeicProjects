package calc;

public class FileNotSavedException extends RuntimeException{
	public FileNotSavedException () {}

	public FileNotSavedException (String message){
		super (message);
        }

	public FileNotSavedException (Throwable cause) {
		super (cause);
        }

	public FileNotSavedException (String message, Throwable cause) {
		super (message, cause);
        }
}
