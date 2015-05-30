package calc;

import java.io.Serializable;

public abstract class Content implements Serializable {
	public abstract int getValue();
	public abstract String showValue();
	public abstract String accept(Search v);
	public abstract Content clone();
}
