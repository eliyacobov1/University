import java.util.Comparator;
import oop.ex3.searchengine.*;

public class By_prox implements Comparator <Hotel> {

    /**
     * represents the latitude of a certain geographic
     * location
     */
    private final double latitude;

    /**
     * represents the longitude of a certain geographic
     * location
     */
    private final double longitude;

    By_prox(double latitude,double longitude) {
        this.latitude=latitude;
        this.longitude=longitude;
    }

    /**
     * A comparator which compares two hotels by their their distance from the geographic
     * location that is represented by the latitude and longitude instances.If distance
     * is equal,will compare by number of POI (where the smaller number calls for the bigger object)
     *
     * @param h1 first hotel object
     * @param h2 second hotel object (to compare with)
     * @return a negative integer, zero, or a positive integer as h1
     * is less than, equal to, or greater than h2 (in accordance to the comparision parameters).
     */

    @Override
    public int compare(Hotel h1,Hotel h2) {
        //set the distance of each hotel from the geographic point constructed of the
        //longitude and latitude data-members in 2 different variables
        double first_hotel_distance=Math.sqrt(Math.pow((h1.getLatitude()-latitude),2)
                +Math.pow((h1.getLongitude()-longitude),2));

        double second_hotel_distance=Math.sqrt(Math.pow((h2.getLatitude()-latitude),2)
                +Math.pow((h2.getLongitude()-longitude),2));

        //if distances are different,compare by them
        if(first_hotel_distance!=second_hotel_distance){
            return Double.compare(first_hotel_distance,second_hotel_distance);
        }
        //else sort by the number of points of interest
        return Integer.valueOf(h2.getNumPOI()).compareTo(h1.getNumPOI());

    }
}

