package filesprocessing;
import Filter.Filter_Factory;
import Filter.all;
import Order.Order_Factory;
import Order.abs;
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;


class File_Parsing {

    /**
     * Represents the error that is to be presented in case of a missing
     * Filter sub-section
     */
    private static final String filter_subsection_error="ERROR: FILTER Subsection missing";

    /**
     * Represents the error that is to be presented in case of a missing
     * Order sub-section
     */
    private static final String order_subsection_error="ERROR: ORDER Subsection missing";

    /**
     * Represents the name of a Filter sub-section
     */
    private static final String Filter_line="FILTER";

    /**
     * Represents the name of an Order sub-section
     */
    private static final String Order_line="ORDER";

    /**
     * Represents the error that is to be presented in case of a problem
     * that is caused while trying to access the commands file
     */
    private static final String CommandsFile_read_error="ERROR: could not read Commands File";

    /**
     * Represents the error that is to be presented in case of a TypeI Exception
     */
    private static final String TypeI_error="Warning in line ";


    static ArrayList<Section> parse_file(String CommandsFile) {
        ArrayList<Section> section_list=new ArrayList<>();

        try {
            Scanner scan = new Scanner(new FileReader(CommandsFile));

            int i = 1;

            //if file is empty,return an empty list of sections
            if(!scan.hasNextLine()){
                return section_list;
            }

            String line=scan.nextLine();

            if (!line.equals(Filter_line)) {
                throw new TypeIIException(filter_subsection_error);
            }

            while (scan.hasNextLine()) {
                //Check if sub-section name is valid.
                // If not,will throw type II exception
                if (!line.equals(Filter_line)) {
                    throw new TypeIIException(filter_subsection_error);
                }

                Section section=new Section(all.get_instance(),new abs(false));

                i++;

                    try {
                        //try and set the Filter to the one described in the subsection.
                        //if not valid,catch type I Exception and add error to section
                        section.set_filter(Filter_Factory.FilterFactory(scan.nextLine()));
                    } catch (TypeIException err) {
                        section.add_error(TypeI_error + i);
                    }

                    i++;

                    //Check if sub-section name is valid,and if section has a
                    // next line.If not,will throw the appropriate exception
                    if(scan.hasNextLine()) {
                        if (!scan.nextLine().equals(Order_line)) {
                            throw new TypeIIException(order_subsection_error);
                        }
                    }
                    else{
                        throw new TypeIIException(order_subsection_error);
                    }


                    //check if section has a next line.If not,add section
                    //with the default abs order
                    if(scan.hasNextLine()) {
                        line = scan.nextLine();
                    }
                    else{
                        section_list.add(section);
                        line="";
                        break;
                    }

                    if (!line.equals(Filter_line)) {
                        try {
                            i++;
                            //try and set the Order to the one described in the subsection.
                            //if not valid,catch type I Exception and add error to section
                            section.set_order(Order_Factory.OrderFactory(line));
                        } catch (TypeIException err){
                            section.add_error(TypeI_error + i);
                        }

                        if(scan.hasNextLine()) {
                            line = scan.nextLine();
                        }
                    }
                    section_list.add(section);
                    i++;
                }
            scan.close();

            //If file ends at the beginning of a new FILTER subsection,return
            //Type II Exception
            if(line.equals(Filter_line)){
                throw new TypeIIException(filter_subsection_error);
            }

            return section_list;
            }
        //catch Exception that is thrown in case the commands file is
        //not found or can't be accessed
        catch (FileNotFoundException err){
            throw new TypeIIException(CommandsFile_read_error,err);
        }
    }
}
