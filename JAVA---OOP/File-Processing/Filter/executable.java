package Filter;
import java.io.File;

public class executable implements Filter {

    /**
     * instance of the object to return in order to maintain the singleton
     * design pattern
     */

    private static executable singleton;

    private executable(){}

    /**
     * A filter that checks if a file is executable
     * @param f the file to check
     * @return true if file is writable,false otherwise
     */

    @Override
    public boolean isPass(File f) {
        return f.canExecute();
    }

    public static executable get_instance(){
        if (singleton==null){
            singleton=new executable();
        }

        return singleton;
    }
}
