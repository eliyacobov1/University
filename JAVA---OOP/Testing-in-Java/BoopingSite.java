import oop.ex3.searchengine.*;
import java.util.*;

public class BoopingSite {

    /**
     * Represents the name of the Booping-site, which is
     * the name of the data set
     */
    private String name;

    public BoopingSite(String name){
        this.name=name;
    }


    /**
     * This method returns an array of hotels located in the given city
     * , sorted from the highest star-rating to the lowest
     *
     * @param city the name of the city
     * @return array of hotels that are in the city
     */

    public Hotel[] getHotelsInCityByRating(String city){
        //create an instance of the comparator that sorts by star-rating
        ByStarRating comp=new ByStarRating();

        return sort_hotels(comp,city);
    }

    /**
     * This method
     * returns an array of hotels, sorted according to their (euclidean)
     * distance from the given geographic location, in ascending order
     *
     * @param latitude number which represents the latitude at the given point
     * @param longitude number which represents the longitude at the given point
     * @return array of hotels in accordance to their proximity to the geographic
     * point,In case of illegal input, this method returns an empty array
     */

    public Hotel[] getHotelsByProximity(double latitude, double longitude){
        //create an instance of the comparator that sorts by distance from geographic location
        Comparator<Hotel> comp=new By_prox(latitude,longitude);

        return sort_hotels(comp,"");
    }

    /**
     * This method returns an array of hotels in the given city,sorted according to
     * their (euclidean) distance from the given geographic location, in ascending order
     *
     * @param latitude number which represents the latitude at the given point
     * @param longitude number which represents the longitude at the given point
     * @param city the name of the city
     * @return array of hotels in the city, in accordance to their proximity to the geographic
     * point,In case of illegal input, this method returns an empty array
     */

    public Hotel[] getHotelsInCityByProximity(String city, double latitude, double longitude){
        //create an instance of the comparator that sorts by distance from geographic location
        Comparator<Hotel> comp=new By_prox(latitude,longitude);

        return sort_hotels(comp,city);
    }

    /**
     * method that receives a comparator and a city and returns a sorted
     * array of hotels according to the requirements
     * @param comp the comparator which is used to sort the hotels
     * @return array of hotel sorted by the comparators conditions
     */

    private Hotel[] sort_hotels(Comparator<Hotel> comp,String city){
        Hotel[] hotel_array=HotelDataset.getHotels(name);
        ArrayList<Hotel> hotel_list=new ArrayList<Hotel>();

        if(!city.equals("")) {
            for (Hotel hotel : hotel_array) {
                if (hotel.getCity().equals(city)) {
                    hotel_list.add(hotel);
                }
            }
        }
        else{
            //empty city String indicates the usage of the getHotelsByProximity method,
            //in which case the sorting is done on all the hotels in the array
            // (and not on once that are in a specific city)
            Arrays.sort(hotel_array,comp);
            return hotel_array;
        }

        if(hotel_list.isEmpty()){
            Hotel[] hotel_array1={};
            return hotel_array1;
        }

        //sorts the list with the given comparator,than converts it into an array
        Collections.sort(hotel_list,comp);
        Hotel[] hotel1=new Hotel[hotel_list.size()];
        hotel_list.toArray(hotel1);

        return hotel1;

    }
}
