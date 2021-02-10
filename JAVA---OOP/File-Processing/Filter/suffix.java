package Filter;

import java.io.File;

public class suffix implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given value is the suffix
     * of a given file's name
     * @param value string to check
     */

    public suffix(String value){
        filter=(File f)->f.getName().endsWith(value);
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
