package Filter;

import java.io.File;

public class between implements Filter {
    private Filter filter;

    /**
     *  sets filter's functionality to check if a given file's size is between two given
     *  values
     * @param value1 value the represents min of range
     * @param value2 value the represents max of range
     */

    between(double value1,double value2){
        if(value1>value2 || value1<0 || value2<0){
            throw new BadValuesException();
        }

        filter=(File f)->(double)f.length()/1024>=value1 && (double)f.length()/1024<=value2;
    }

    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
