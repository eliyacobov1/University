package filesprocessing;
import Filter.Filter_Factory;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class ToolBox {

    // a class with methods that are being used on multiple types of
    //modules

    /**
     * method that separates the lines given in a commands file
     * into different elements (without the hash tags)
     * @param line line from file
     * @return String array containing all the elements from the line
     */

    public static String[] toStringArray(String line) {

        ArrayList<String> elements_in_line =
                new ArrayList<>(Arrays.asList(line.split("#")));

        return elements_in_line.toArray(new String[0]);
    }

    /**
     * method that returns a file's extension.It does so by finding
     * the last dot in it's name and returning the substring that is
     * found after that dot.In case there are no dots,returns an empty string
     * @param fileName the name of the file
     * @return the extension of the file name
     */

    public static String get_extension(String fileName) {
        int lastIndexDot = fileName.lastIndexOf('.');
        if (lastIndexDot != -1 && lastIndexDot != 0) {
            return fileName.substring(lastIndexDot, fileName.length());
        } else {
            return "";
        }
    }

    /**
     * quick sort function that sorts a given array of Files using
     * the provided Comparator
     * @param array the array to sort
     * @param comparator the comparator that is used to compare files
     */

    static void quicksort(File[] array ,int begin,int end, Comparator<File> comparator){
        if(begin<end){
            int pivot=partition(array,begin,end,comparator);

            quicksort(array,begin,pivot-1,comparator);
            quicksort(array,pivot+1,end,comparator);
        }
    }

    /**
     * helper method for quick sort
     * @param array the array to sort
     * @param begin start index
     * @param end end index
     * @param comparator comparator that is used to compare files
     */
    private static int partition(File[] array, int begin, int end, Comparator<File> comparator) {
        File pivot=array[end];
        int counter=begin;

        for (int i = begin; i < end; i++) {
            if (comparator.compare(array[i], pivot) <= 0) {
                File temp = array[counter];
                array[counter] = array[i];
                array[i] = temp;
                counter++;
            }
        }

            File temp=array[counter];
            array[counter]=pivot;
            array[end]=temp;

            return counter;
        }

    /**
     * method that checks if a certain FILTER line exceeds the maximum
     * number of elements that it can hold according to the restrictions.
     * also checks validity of the negate suffix in case the size of the
     * line implies of it's existence.Also checks that the minimum number
     * of elements according to the restrictions is present in the line
     * @param line String array with the elements of the line
     * @param max_num_elements maximum possible legal size of the line
     * @param min_elements minimum number of elements in line
     * @return true if line is valid,false otherwise
     */
    public static boolean line_validity(String[] line,int max_num_elements,int min_elements){
        if(line.length>max_num_elements){
            return false;
        }

        if(line.length==max_num_elements){
            if(!line[max_num_elements-1].equals(Filter_Factory.negate))
                return false;
        }

        return(line.length>=min_elements);


    }
}
