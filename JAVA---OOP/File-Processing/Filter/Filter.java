package Filter;
import java.io.File;

/**
 * interface class that represents a filter
 */

public interface Filter {
    /**
     * Method that checks if a file meets the filter's conditions
     * @param f the file to check
     * @return true if conditions are met,false otherwise
     */

    public boolean isPass(File f);
}
