package Filter;
import java.io.File;

public class Not implements Filter {
    private Filter filter;

    public Not(Filter filter){
        this.filter=filter;
    }

    /**
     * sets filter's functionality to return the opposite value for a given filter
     * with a given file
     * @param f the file which the original filter receives
     * @return true if filter returns false,false otherwise
     */

    @Override
    public boolean isPass(File f) {
        return !filter.isPass(f);
    }
}
