import oop.ex3.spaceship.*;
import java.util.HashMap;
import java.util.Map;

public class LongTermStorage extends StorageUnit {

    /**o
     * static variable that represents the total capacity f the long-term storage
     */
    private static final int capacity=1000;

    /**
     * static variable that represents the available capacity of the long-term storage
     */
    private static int available_capacity=1000;

    /**
     * static variable that holds the info regarding which items
     * are in the long term storage in in what quantities
     */
    private static Map <String,Integer> map=new HashMap<String, Integer>();

    public LongTermStorage(){ }

    /**
     * This method adds n Items of the given type to the long term storage unit
     *
     * @param item the item to add
     * @param n the number of items
     * @return 0 if the action is successful, -1 otherwise
     */

    public int addItem(Item item, int n) {

        //if n is negative,prints error and returns -1
        if(n<0){
            System.out.println("Error: Your request cannot" +
                    "be completed at this time.");
            return-1;
        }

        if(n>0) {
            //checks if there is available storage
            if (item.getVolume() * n <= available_capacity) {
                //checks if item is already in storage
                if (map.containsKey(item.getType())) {
                    map.put(item.getType(), map.get(item.getType())+n);
                } else {
                    map.put(item.getType(), n);
                }

                //subtracts amount from available capacity storage
                available_capacity-=item.getVolume()*n;
                return 0;

            } else {
                //if there is not enough space,returns -1 and prints informative error
                System.out.println("Error: Your request cannot be completed at this" +
                        "time. Problem: no room for n Items of type type");
                return -1;
            }
        }
        //if n==0,won't add any items and return 0
        return 0;
    }

    /**
     * This method resets the long-term storage’s inventory
     */

    public void resetInventory(){
        map.clear();
        available_capacity=1000;
}

    /**
     * This method removes n Items of the type type from the long term storage unit
     *
     * @param type the item's type
     * @return the number of suitable items in the locker
     */

    public int getItemCount(String type){

        if(!map.containsKey(type)){
            return 0;
        }

        return map.get(type);
    }

    /**
     * This method return a map of the long term storage unit inventory's current state
     *
     * @return a map of all the item types contained in the long term storage unit, and their
     * respective quantities
     */

    public Map<String, Integer> getInventory(){

        return map;
    }

    /**
     * get's the capacity of the locker
     *
     * @return Returns the long term storage unit total capacity
     */


    public int getCapacity(){
        return capacity;
    }

    /**
     * get's the available capacity of the storage
     *
     * @return Returns the long term storage unit available capacity
     */

    public int getAvailableCapacity(){

        return available_capacity;
    }
}
