package Filter;
import java.io.File;

public class greater_than implements Filter {
    private Filter filter;

    /**
     * sets filter's functionality to check if a given file's size is bigger than a
     * given value (in k-bytes)
     * @param value number to compare size to
     */

    public greater_than(double value){
        if(value<0){
            throw new BadValuesException();
        }

        filter=(File f)->(double)f.length()/1024>value;
    }


    @Override
    public boolean isPass(File f) {
        return filter.isPass(f);
    }
}
