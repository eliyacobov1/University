import java.util.Comparator;
import oop.ex3.searchengine.*;

public class ByStarRating implements Comparator <Hotel> {
    /**
     * A comparator which compares two hotels by their star rating.If star
     * rating is equal,will compare by alphabetical order of their property names
     * @param h1 first hotel object
     * @param h2 second hotel object (the to compare with)
     * @return a negative integer, zero, or a positive integer as h1
     * is less than, equal to, or greater than h2 (in accordance to the comparision parameters).
     */

    @Override
    public int compare(Hotel h1,Hotel h2) {
        //if ratings are different,compare by them
        if(h1.getStarRating()!=h2.getStarRating()) {
            return Integer.valueOf(h1.getStarRating()).compareTo(h2.getStarRating());
        }

        //else compare by property names (in alphabetical order)
        return h1.getPropertyName().compareTo(h2.getPropertyName());
    }
}