package Filter;
import java.io.File;

public class hidden implements Filter {

    /**
     * instance of the object to return in order to maintain the singleton
     * design pattern
     */

    private static hidden singleton;

    private hidden(){}

    /**
     * A filter that checks if a file is hidden
     * @param f the file to check
     * @return true if file is writable,false otherwise
     */

    @Override
    public boolean isPass(File f) {
        return f.isHidden();
    }

    /**
     * method that gets the single instance of the object that exists
     * @return the singleton object of this type
     */

    public static hidden get_instance(){
        if (singleton==null){
            singleton=new hidden();
        }

        return singleton;
    }
}
