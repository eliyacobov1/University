package filesprocessing;

class TypeIIException extends RuntimeException {
    /**
     * type 2 exception thrown in the cases described in the instructions
     */

    TypeIIException(String message,Throwable err){
        super(message,err);
    }

    TypeIIException(String message){
        super(message);
    }

    TypeIIException(){
        super();
    }
}
