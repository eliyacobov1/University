package filesprocessing;
import Filter.Filter;
import Order.Order;
import java.io.File;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

class Section {
    /**
     * Represents the Filter of a section
     */
    private Filter filter;

    /**
     * Represents the Order of a section
     */
    private Order order;

    /**
     * Represents an error message for when there is a problem in
     * accessing the source directory
     */
    private final static String SourceDir_error="ERROR: an Error occurred while reading the " +
            "Source directory";

    /**
     * Represents the list of errors that are related
     * to this sections lines in the command file
     */
    private ArrayList<String> Error_list;

    Section(Filter filter, Order order){
        this.filter=filter;
        this.order=order;
        this.Error_list=new ArrayList<>();
    }

    /**
     * method that sets a new filter for this section
     * @param new_filter the filter to be set
     */
    void set_filter(Filter new_filter){
        filter=new_filter;
    }

    /**
     * method that sets a new order for this section
     * @param new_order the filter to be set
     */
    void set_order(Order new_order){
        order=new_order;
    }

    /**
     * method that adds an error to the list of errors for
     * this section's lines
     * @param error the error to be added to the list
     */
    void add_error(String error){
        Error_list.add(error);
    }

    /**
     * method prints files in a given directory after filtering and ordering them
     * with a certain section's Filter and Order instances.Will also print the errors
     * from error list tha are realted to this section,prior to printing the file names.
     * @param SourceDir the directory in which the files are located
     */

    void Print_Section_Content(String SourceDir){
        try {
            ArrayList<File> file_list=new ArrayList<>();
            Path path = Paths.get(SourceDir);
            DirectoryStream<Path> stream = Files.newDirectoryStream(path);

            //build the file list using the FILTER instance of this section
            //(also make sure to add only files and not directories)
            for (Path path1 : stream){
                File file=path1.toFile();
                if(filter.isPass(file) && file.isFile()){
                    file_list.add(file);
                }
            }

            //convert list to array and use the custom sorting method
            //to sort the files using the ORDER object of this section
            File[] array=file_list.toArray(new File[0]);
            ToolBox.quicksort(array,0,array.length-1,order);

            if(order.get_reverse()){
                file_list=new ArrayList<>(Arrays.asList(array));
                Collections.reverse(file_list);
                array=file_list.toArray(new File[0]);
            }

            //first,print errors in section
            for(String error:Error_list){
                System.err.println(error);
            }

            //prints all filtered and ordered file names
            for(File file:array){
                System.out.println(file.getName());
            }
        }

        catch(IOException err){
            throw new TypeIIException(SourceDir_error,err);
        }
    }
}
