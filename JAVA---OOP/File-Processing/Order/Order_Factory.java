package Order;
import filesprocessing.NotValidNameException;
import filesprocessing.ToolBox;

public class Order_Factory {

    /**
     * represents the abs order name
     */
    private final static String abs_order="abs";

    /**
     * represents the all filter name
     */
    private final static String type_order="type";

    /**
     * represents the all filter name
     */
    private final static String size_order="size";

    /**
     * represents the reverse suffix for a filter
     */
    private final static String Reverse="REVERSE";

    /**
     * Filter factory.Receives a string which represents the Filter
     * line in a commands file,and converts it into a Filter object
     * of the corresponding type
     * @param line The line from commands file
     * @return the appropriate Filter type object
     * @throws NotValidNameException in case of invalid input
     */

    public static Order OrderFactory(String line){
        //for the given line,creates an array of strings to
        // separate between values and commands
        String[] elements_in_line = ToolBox.toStringArray(line);

        switch(elements_in_line[0]){
        //in each line checks for the reverse suffix,
        // and if it exists,returns the reversed order

            case(abs_order):
                if(elements_in_line.length>1) {
                    if (elements_in_line[1].equals(Reverse)) {
                        return new abs(true);
                    }
                }
                return new abs(false);

            case(size_order):
                if(elements_in_line.length>1) {
                    if (elements_in_line[1].equals(Reverse)) {
                        return new size(true);
                    }
                }
                return new size(false);

            case(type_order):
                if(elements_in_line.length>1) {
                    if (elements_in_line[1].equals(Reverse)) {
                        return new type(true);
                    }
                }
                return new type(false);
        }

        throw new NotValidNameException();
    }
}
