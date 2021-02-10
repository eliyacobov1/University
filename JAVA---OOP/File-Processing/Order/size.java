package Order;
import java.io.File;
public class size implements Order {

    /**
     * variable that indicates if a reverse of the array that
     * is sorted by this order is necessary
     */
    private boolean reverse_indicator ;

    public size(boolean value){
        this.reverse_indicator=value;
    }

    /**
     * compares two files by their size
     * @param f1 first file
     * @param f2 second file
     * @return the value {@code 0} if the first file's size is equal to
     *      this second; a value less than {@code 0} if the first file's size
     *      is lexicographically less than the second; and a
     *      value greater than {@code 0} if the first file's size
     *      lexicographically greater than the second
     */

    @Override
    public int compare(File f1, File f2) {
        //first check if type comparison is not identical.If it is,compare by absolute name.
        double comparison=f1.length()-f2.length();

        if(comparison!=0){
            if (comparison>1){
                return 1;
            }
            else{
                return -1;
            }
        }

        else{
            return f1.getAbsolutePath().compareTo(f2.getAbsolutePath());
        }
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
