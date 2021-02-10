package Filter;

import java.io.File;

public class smaller_than implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given file's size is smaller than a
     * given value (in k-bytes)
     * @param value number to compare size to
     */

    public smaller_than(double value){
        if(value<0){
            throw new BadValuesException();
        }

        filter=(File f)->(double)f.length()/1024<value;
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
