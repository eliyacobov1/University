package Filter;
import filesprocessing.TypeIException;

/**
 * a typeI exception that is thrown is case of bad range in the between
 * filter constructor or in case negative numeric values are received for
 * one of the filters constructors
 */

class BadValuesException extends TypeIException {
    BadValuesException(){
        super();
    }
}
