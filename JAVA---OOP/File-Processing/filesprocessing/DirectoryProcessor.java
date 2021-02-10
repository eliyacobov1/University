package filesprocessing;
import java.util.ArrayList;

public class DirectoryProcessor {

    private static final String illegal_num_arg="ERROR: illegal number of arguments";

    public static void main(String[] args){

        if (args.length !=2){
            System.err.println(illegal_num_arg);
            throw new TypeIIException();
        }

        try{
            String SourceDir=args[0];
            String CommandsFile=args[1];

            ArrayList<Section> Section_list= File_Parsing.parse_file(CommandsFile);

            for(Section section:Section_list){
                section.Print_Section_Content(SourceDir);
            }
        }
        catch (TypeIIException err){
            System.err.println(err.getMessage());
        }
    }
}
