import static org . junit . Assert .*;
import oop.ex3.searchengine.*;
import org.junit.BeforeClass;
import org.junit.Test;
import java.util.ArrayList;

public class BoopingSiteTest {

    /**
     * boopingsite static variable from which hotels are getting sorted
     */
    private static BoopingSite boopingSite;

    /**
     * a list of all cities of all hotels that are in the file hotel_dataset
     */
    private static ArrayList<String> city_list=new ArrayList<String>();

    /**
     * latitude to test the sorting methods with
     */
    private static double latitude=2003.1098;

    /**
     * latitude to test the sorting methods with
     */
    private static double longitude=197.7272;

    /**
     * a city that is not part of the hotel dataset for testing purposes
     */
    private static String city_NotInFile="Beer Sheva";


    /**
     * method that is performed before each test.
     * It initializes the Locker and resets the long term storage
     */

    @BeforeClass
    public static void initialize() {
        //initialize a boopingsite variable with the hotel_dataset data set
        boopingSite = new BoopingSite("hotels_dataset.txt");

        for (Hotel hotel : HotelDataset.getHotels("hotels_dataset.txt")) {

            //adds all cities in the file hotels_dataset to the list
            if (!city_list.contains(hotel.getCity())) {
                city_list.add(hotel.getCity());
            }
        }
    }

    /**
     * test for the getHotelsInCityByProximity method
     */

    @Test
    public void prox_city_test(){

        for(String city:city_list){

            //creates array of hotels that are in the city
            Hotel[] hotel_array=
                    boopingSite.getHotelsInCityByProximity(city,latitude,longitude);

            for(int i=1;i<hotel_array.length;i++){

                double prox_hotel1=Math.sqrt(Math.pow(hotel_array[i-1].getLatitude()-latitude,2)+
                        Math.pow(hotel_array[i-1].getLongitude()-longitude,2));

                double prox_hotel2=Math.sqrt(Math.pow(hotel_array[i].getLatitude()-latitude,2)+
                        Math.pow(hotel_array[i].getLongitude()-longitude,2));

                if(prox_hotel1!=prox_hotel2){

                    //asserts hotels are indeed from the city and are sorted by distance from the
                    //geographic point
                    assertEquals(hotel_array[i].getCity(),city);
                    assertEquals(hotel_array[i-1].getCity(),city);
                    assertTrue(prox_hotel2>prox_hotel1);
                }
                else{

                    //if rating is equal asserts rating is done by num of POI
                    //and also that both hotels are from the given city
                    assertEquals(hotel_array[i].getCity(),city);
                    assertEquals(hotel_array[i-1].getCity(),city);
                    assertTrue(hotel_array[i].getNumPOI()<=
                            hotel_array[i-1].getNumPOI());
                }
            }

        }
    }

    /**
     * test for the getHotelsInCityByRating method
     */

    @Test
    public void rating_test(){
        for(String city:city_list){
            
            //creates array of hotels that are in the city
            Hotel[] hotel_array=
                    boopingSite.getHotelsInCityByRating(city);

            for(int i=1;i<hotel_array.length;i++){
                if(hotel_array[i-1].getStarRating()!=hotel_array[i].getStarRating()){

                    //asserts hotels are indeed from the city and are sorted by rating
                    assertEquals(hotel_array[i].getCity(),city);
                    assertEquals(hotel_array[i-1].getCity(),city);
                    assertTrue(hotel_array[i].getStarRating()>
                            hotel_array[i-1].getStarRating());
                }
                else{

                    //if rating is equal asserts sorting is done by alphabetical order
                    //and also that both hotels are from the given city
                    assertEquals(hotel_array[i].getCity(),city);
                    assertEquals(hotel_array[i-1].getCity(),city);
                    assertTrue(hotel_array[i].getPropertyName().
                            compareTo(hotel_array[i-1].getPropertyName())>=0);
                }
            }

        }
    }

    /**
     * test for the getHotelsByProximity method
     */

    @Test
    public void prox_test(){

            Hotel[] hotel_array=
                    boopingSite.getHotelsByProximity(latitude,longitude);

            for(int i=1;i<hotel_array.length;i++){

                double prox_hotel1=Math.sqrt(Math.pow(hotel_array[i-1].getLatitude()-latitude,2)+
                        Math.pow(hotel_array[i-1].getLongitude()-longitude,2));

                double prox_hotel2=Math.sqrt(Math.pow(hotel_array[i].getLatitude()-latitude,2)+
                        Math.pow(hotel_array[i].getLongitude()-longitude,2));

                if(prox_hotel1!=prox_hotel2){

                    //asserts hotels are indeed sorted by distance from the
                    //geographic point
                    assertTrue(prox_hotel2>prox_hotel1);
                }
                else{

                    //if rating is equal asserts rating is done by num of POI
                    assertTrue(hotel_array[i].getNumPOI()<=
                            hotel_array[i-1].getNumPOI());
                }
            }

        }

    /**
     * Test to check if getHotelsInCityByRating and getHotelsInCityByProximity methods
     * return an empty hotel array when given a city that is not part of the boopingsite
     * data set
     */

    @Test
    public void City_NotInFile_test(){

        //asserts that methods return an empty hotel list for an illegal city input
        assertTrue(boopingSite.getHotelsInCityByProximity
                (city_NotInFile,latitude,longitude) instanceof Hotel[]);

        assertEquals(boopingSite.getHotelsInCityByProximity
                (city_NotInFile,latitude,longitude).length,0);

        assertTrue(boopingSite.getHotelsInCityByRating
                (city_NotInFile) instanceof Hotel[]);

        assertEquals(boopingSite.getHotelsInCityByRating
                (city_NotInFile).length,0);

    }
}


