package Filter;

import java.io.File;

public class all implements Filter {
    /**
     * instance of the object to return in order to maintain the singleton
     * design pattern
     */

    private static all singleton;

    private all(){}

    /**
     * A filter that returns true for any given file
     * @param f the file to check
     * @return true
     */

    @Override
    public boolean isPass(File f) {
        return true;
    }

    /**
     * method that gets the single instance of the object that exists
     * @return the singleton object of this type
     */

    public static all get_instance(){
        if (singleton==null){
            singleton=new all();
        }

        return singleton;
    }
}
