package Filter;
import filesprocessing.NotValidNameException;
import filesprocessing.ToolBox;

public class Filter_Factory {

    /**
     * represents the word "YES"
     */
    private final static String yes="YES";

    /**
     * represents the word "NO"
     */
    private final static String no="NO";

    /**
     * represents the negation suffix for a filter
     */
    public final static String negate="NOT";

    /**
     * represents the all filter name
     */
    private final static String all_filter="all";

    /**
     * represents the executable filter name
     */
    private final static String executable_filter="executable";

    /**
     * represents the writable filter name
     */
    private final static String writable_filter="writable";

    /**
     * represents the hidden filter name
     */
    private final static String hidden_filter="hidden";

    /**
     * represents the between filter name
     */
    private final static String between_filter="between";

    /**
     * represents the contains filter name
     */
    private final static String contains_filter="contains";

    /**
     * represents the file filter name
     */
    private final static String file_filter="file";

    /**
     * represents the greater_than filter name
     */
    private final static String greater_than_filter="greater_than";

    /**
     * represents the smaller_than filter name
     */
    private final static String smaller_than_filter="smaller_than";

    /**
     * represents the prefix filter name
     */
    private final static String prefix_filter="prefix";

    /**
     * represents the suffix filter name
     */
    private final static String suffix_filter="suffix";

    /**
     * Filter factory.Receives a string which represents the Filter
     * line in a commands file,and converts it into a Filter object
     * of the corresponding type
     * @param line The line from commands file
     * @return the appropriate Filter type object
     * @throws filesprocessing.TypeIException in case of invalid input
     */

    public static Filter FilterFactory(String line) {
        //for the given line,creates an array of strings to
        // separate between values and commands
        String[] elements_in_line = ToolBox.toStringArray(line);

        //elements_in_line[0] represents the first word in
        // line which is the filter name
        switch (elements_in_line[0]) {

            case (all_filter):
                if(!ToolBox.line_validity(elements_in_line,2,1)){
                    throw new BadParameterException();
                }

                if (line.contains(negate)) {
                    return new Not(all.get_instance());
                } else {
                    return all.get_instance();
                }

            case (executable_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }
                //if elements_in_line is not longer than 1 in length,this
                //means that there is no proper value for this filter
                if (line.contains(negate)) {
                    if (check_parameter(elements_in_line[1])) {
                        return new Not(executable.get_instance());
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return executable.get_instance();
                    }
                } else {
                    if (check_parameter(elements_in_line[1])) {
                        return executable.get_instance();
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return new Not(executable.get_instance());
                    }
                }

            case (writable_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                //if elements_in_line is not longer than 1 in length,this
                //means that there is no proper value for this filter
                if (line.contains(negate)) {
                    if (check_parameter(elements_in_line[1])) {
                        return new Not(writable.get_instance());
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return writable.get_instance();
                    }
                } else {
                    if (check_parameter(elements_in_line[1])) {
                        return writable.get_instance();
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return new Not(writable.get_instance());
                    }
                }

            case (hidden_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                //if elements_in_line is not longer than 1 in length,this
                //means that there is no proper value for this filter
                if (line.contains(negate)) {
                    if (check_parameter(elements_in_line[1])) {
                        return new Not(hidden.get_instance());
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return hidden.get_instance();
                    }
                } else {
                    if (check_parameter(elements_in_line[1])) {
                        return hidden.get_instance();
                    }
                    if (!check_parameter(elements_in_line[1])) {
                        return new Not(hidden.get_instance());
                    }
                }

            case (between_filter):
                between filter = new between(Double.valueOf(elements_in_line[1])
                        , Double.valueOf(elements_in_line[2]));

                if(!ToolBox.line_validity(elements_in_line,4,3)){
                    throw new BadParameterException();
                }
                if(line.contains(negate)) {
                        return new Not(filter);
                        }
                return filter;

            case (contains_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                if (line.contains(negate)) {
                    return new Not(new contains(elements_in_line[1]));
                }

                return new contains(elements_in_line[1]);

            case (file_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                if (line.contains(negate)) {
                    return new Not(new file(elements_in_line[1]));
                }
                return new file(elements_in_line[1]);

            case (greater_than_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                greater_than filter1 = new greater_than(Double.valueOf(elements_in_line[1]));
                if (line.contains(negate)) {
                    return new Not(filter1);
                } else {
                    return filter1;
                }

            case (smaller_than_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                smaller_than filter2 = new smaller_than(Double.valueOf(elements_in_line[1]));
                if (line.contains(negate)) {
                    return new Not(filter2);
                } else {
                    return filter2;
                }


            case (prefix_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                prefix filter3 = new prefix(elements_in_line[1]);
                if (line.contains(negate)) {
                    return new Not(filter3);
                }

                return filter3;

            case (suffix_filter):
                if(!ToolBox.line_validity(elements_in_line,3,2)){
                    throw new BadParameterException();
                }

                suffix filter4 = new suffix(elements_in_line[1]);
                if (line.contains(negate)) {
                    return new Not(filter4);
                }
                return filter4;
        }
            throw new NotValidNameException();
        }

    /**
     * check if parameter for specific types of filters is valid
     * (equals "YES" or "NO")
     * @param value the parameter to check
     * @return true if parameter is "YES", false if it is "NO"
     * @throws BadParameterException if parameter is neither of the above values
     */

    private static boolean check_parameter(String value){
        if(value.equals(yes)){
            return true;
        }

        if(value.equals(no)){
            return false;
        }

        throw new BadParameterException();
    }
}
