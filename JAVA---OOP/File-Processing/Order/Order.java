package Order;
import java.io.File;
import java.util.Comparator;

public interface Order extends Comparator<File> {
    public int compare(File f1, File f2);

    public boolean get_reverse();
}
