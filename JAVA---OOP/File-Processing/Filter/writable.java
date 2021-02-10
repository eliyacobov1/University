package Filter;
import java.io.File;

public class writable implements Filter {

    /**
     * instance of the object to return in order to maintain the singleton
     * design pattern
     */

    private static writable singleton;

    private writable(){}

    /**
     * A filter that checks if a file is writable
     * @param f the file to check
     * @return true if file is writable,false otherwise
     */

    @Override
    public boolean isPass(File f) {
        return f.canWrite();
    }

    public static writable get_instance(){
        if (singleton==null){
            singleton=new writable();
        }

        return singleton;
    }
}
