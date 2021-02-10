package Filter;
import filesprocessing.TypeIException;

public class BadParameterException extends TypeIException {/**
     * a typeI exception that is thrown is case a value that is not "YES"
     * or "NO" matched with one of the following filters: "hidden", "executable",
     * ,"writable".
     * one of the filters constructors
     */

     BadParameterException(){
        super();
     }
}

