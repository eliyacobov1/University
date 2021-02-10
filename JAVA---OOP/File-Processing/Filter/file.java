package Filter;

import java.io.File;

public class file implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given file's name is equal
     * to a given value
     * @param value string to compare name to
     */

    public file(String value){
        filter=(File f)->f.getName().equals(value);
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
