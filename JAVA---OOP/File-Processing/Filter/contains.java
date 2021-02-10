package Filter;

import java.io.File;

public class contains implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given file's name contains
     * a given value
     * @param value string to compare name to
     */

    public contains(String value){
        filter=(File f)->f.getName().contains(value);
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
