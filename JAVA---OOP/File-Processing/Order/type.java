package Order;
import filesprocessing.ToolBox;

import java.io.File;
public class type implements Order {

    /**
     * variable that indicates if a reverse of the array that
     * is sorted by this order is necessary
     */
    private boolean reverse_indicator;

    public type(boolean value){
        this.reverse_indicator=value;
    }

    /**
     * compares two files by their types
     * @param f1 first file
     * @param f2 second file
     * @return the value {@code 0} if the first file's type is equal to
     *      this second; a value less than {@code 0} if the first file's type
     *      is lexicographically less than the second; and a
     *      value greater than {@code 0} if the first file's type
     *      lexicographically greater than the second
     */

    @Override
    public int compare(File f1, File f2) {
        //first put file suffixes in new string variables.If there are
        //no dots,suffix will be considered as empty.
        String f1_type= ToolBox.get_extension(f1.getName());
        String f2_type= ToolBox.get_extension(f2.getName());

        //first check if type comparison is not identical.If it is,compare by absolute name.

        int comparison=f1_type.compareTo(f2_type);

        if(comparison!=0){
            return comparison;
        }

        return f1.getAbsolutePath().compareTo(f2.getAbsolutePath());

    }
    /**
     * returns the variable that indicates if a reverse of the array that
     * is sorted by this order is necessary
     * @return the reverse boolean indecator
     */

    @Override
    public boolean get_reverse() {
        return reverse_indicator;
    }

}
