package Filter;

import java.io.File;

public class prefix implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given value is the prefix
     * of a given file's name
     * @param value string to check
     */

    public prefix(String value){
        filter=(File f)->f.getName().startsWith(value);
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
