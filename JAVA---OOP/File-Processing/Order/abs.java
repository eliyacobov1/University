package Order;

import java.io.File;

public class abs implements Order {

    /**
     * variable that indicates if a reverse of the array that
     * is sorted by this order is necessary
     */
    private boolean reverse_indicator;

    public abs(boolean value){
        this.reverse_indicator=value;
    }

    /**
     * compares two files by their absolute name
     * @param f1 first file
     * @param f2 second file
     * @return the value {@code 0} if the first file's name is equal to
     *      this second; a value less than {@code 0} if the first file's name
     *      is lexicographically less than the second; and a
     *      value greater than {@code 0} if the first file's name
     *      lexicographically greater than the second
     */

    @Override
    public int compare(File f1, File f2) {
        return (f1.getAbsolutePath().compareTo(f2.getAbsolutePath()));
    }

    @Override
    public boolean get_reverse() {
        return reverse_indicator;
    }
}
