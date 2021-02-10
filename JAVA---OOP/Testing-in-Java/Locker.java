import oop.ex3.spaceship.*;
import java.util.HashMap;
import java.util.Map;

public class Locker extends StorageUnit{

    /**
     * an instance of the LongTermStorage class that enables access to this
     * class's static data
     */
    private static LongTermStorage lts=new LongTermStorage();

    /**
     * the number of units which represents the locker's capacity
     */
    private final int capacity;

    /**
     * variable that represents the available capacity of the locker
     */
    private int available_capacity;

    /**
     * the Map instance which holds the info regarding which items
     * are in the locker's storage in in what quantities
     */
    private Map <String,Integer> map;

    public Locker(int capacity) {
        this.capacity = capacity;
        this.map=new HashMap<String,Integer>();
        this.available_capacity=capacity;
    }

    /**
     * This method adds n Items of the given type to the locker
     *
     * @param item the item to add
     * @param n    the number of items
     * @return 0 if the action is successful,1 if moved item to
     * long term storage along the procedure,-2 if there is a request to put
     * a baseball bat and a football together,-1 otherwise
     */

    public int addItem(Item item, int n) {

        if(football_and_bat(item)==-2){
            return -2;
        }

        //condition to assert that n is positive
        if(n>0) {
            // checks if item type is legal

            if (!is_legal_type(item)) {
                return -1;
            }
            //will attempt to add the requested amount of items in dependency of
            //the current available locker storage,long term storage and volume and
            //amount of items

            //first checks if there is enough available storage
            if((item.getVolume()*n)<=available_capacity) {
                switch (attempt_to_add(item, n)) {
                    case 0:
                        return 0;

                    case 1:
                        System.out.println("Warning: Action successful, but has caused items to" +
                                " be moved to storage");
                        return 1;

                    case -1:
                        System.out.println("Error: Your request cannot be completed at this time." +
                                " Problem: no room for n∗ Items of type type");
                        return -1;
                }
            }
        }
        //if n is not positive,returns -1
        System.out.println("Error: Your request cannot" +
                "be completed at this time");
        return -1;
    }

    /**
     * This method removes n Items of the type type from the locker
     *
     * @param item the item to remove
     * @param n    the number of items
     * @return 0 if the action is successful, -1 otherwise
     */

    public int removeItem(Item item, int n) {

        //checks if n is negative,i  which case will print an
        // error and return -1
        if(n<0){
            System.out.println("Error: Your request cannot be completed at this time. Problem: cannot\n" +
                    "remove a negative number of items of type "+item.getType());
            return -1;
        }

        //first checks if item type is in the locker
        if(map.containsKey(item.getType())){

            int current_amount= map.get(item.getType());

            if(current_amount<n){
                //if the amount is smaller then n,prints error and returns -1
                System.out.println("Error: Your request cannot be completed at" +
                        "this time. Problem: the locker does not contain n items of type "+item.getType());
                return -1;
            }

            //checks if amount is bigger than n,if so,subtracts n from it
            if(current_amount>n){
                map.put(item.getType(),current_amount-n); }

            //if the amount is n,removes the item completely
            else{
                map.remove(item.getType()); }

            available_capacity+=item.getVolume()*n;
        }
        return 0;
    }

    /**
     * This method gets the current item count of the given item type
     *
     * @param type the item's type
     * @return the number of suitable items in the locker
     */

    public int getItemCount(String type) {
        if(!map.containsKey(type)){
            return 0;
        }

        return map.get(type);
    }

    /**
     * This method return a map of the locker's inventory current state
     *
     * @return a map of all the item types contained in the locker, and their
     * respective quantities
     */

    public Map<String, Integer> getInventory() {
        return map;
    }

    /**
     * get's the capacity of this locker
     *
     * @return Returns the locker’s total capacity
     */

    public int getCapacity() {
        return capacity;
    }

    /**
     * get's the  available capacity on this locker
     *
     * @return Returns the locker’s available capacity
     */

    public int getAvailableCapacity() {
        return available_capacity;
    }

    /**
     * This method checks if the item type and volume are legal with the help
     * of the ItemFactory class.
     *
     * @param item the given item for which we wanna check the type of
     * @return true if item is legal, false otherwise
     */

    private boolean is_legal_type(Item item){
        Item[] legal_item_list = ItemFactory.createAllLegalItems();
        //loop that checks if given item is of one the legal item types
        for (Item item1:legal_item_list) {
            if (item.getType().equals(item1.getType()) &&
                    item.getVolume()==(item1.getVolume())){
                return true;
            }
        }
        return false;
    }

    /**
     * This method checks if the item and requested amount can be added to the storage
     * and in which manner (only to the locker or a certain amount to the locker and the
     * rest to the long term storage)
     *
     * @param item the given item to add
     * @param n the amount of items to add
     * @return 0 if the action is successful,1 if moved item to
     * long term storage along the procedure, -1 otherwise
     */

    private int attempt_to_add(Item item,int n){
        //variable which contains the current available long term storage
        int long_term_storage=lts.getAvailableCapacity();

        int current_item_capacity=0;

        //checks if there are already items of this type in the locker
        if(map.containsKey(item.getType())) {
            current_item_capacity = map.get(item.getType()) * item.getVolume();
        }

            //calculates if the percentage of storage  that the items of this
            // type capitalize when adding the requested amount of additional
            // items exceeds 50
            if (current_item_capacity + n * item.getVolume() > (capacity * 0.5)) {

                //looks for an amount which suffices all the conditions that should
                // be met in order for the item to be transferred to the long term
                // storage and stored in the locker
                for (int i = n - 1; i > 0; i--) {

                    //variables that represents the volume that will be added to storage
                    //and to the locker upon multiplication with i
                    int add_to_locker=i * item.getVolume();
                    int add_to_storage=(n - i) * item.getVolume();

                    if ((current_item_capacity +add_to_locker) <= (capacity * 0.2) &&
                            (long_term_storage -add_to_storage) >=0 ) {

                        //increases number of items from this type in locker and long term
                        // storage by the fitting amount and returns 1
                        map.put(item.getType(), i);
                        lts.addItem(item, n - i);
                        available_capacity -= i * item.getVolume();
                        return 1;
                    }
                }
                //if can't sort the item between the locker and the long term storage,
                // will not add items and will return -1
                return -1;
            }
            //else,will add requested amount to the locker and will return 0

            //if current_item_capacity is 0,will create a new key and value
            if(current_item_capacity==0) { map.put(item.getType(), n); }

            //else,will add n to the existing value
            else{ map.put(item.getType(), map.get(item.getType()) + n); }
            available_capacity -= n * item.getVolume();
            return 0;
        }


    /**
     * method that checks if requested item and current locker capacity are
     * not potentially violating the restriction that forbids item of types
     * football and baseball bat to exist in the same locker
     * @return -2 if a violation occurs,0 otherwise
     */

    private int football_and_bat(Item item){
        //check if there item is of type football or baseball bat,
        //if so makes sure that there is no violation of a contradicting item
        if(item.getType().equals("football")){
            if (map.containsKey("baseball bat")){
                System.out.println("Error: Your request cannot be " +
                        "completed at this time. Problem: the locker " +
                        "cannot contain items of type "+item.getType()+
                        ", as it contains a contradicting item");

                return -2;
            }
        }

        if(item.getType().equals("baseball bat")){
            if (map.containsKey("football")){
                System.out.println("Error: Your request cannot be " +
                        "completed at this time. Problem: the locker " +
                        "cannot contain items of type "+item.getType()+
                        ", as it contains a contradicting item");

                return -2;
            }
        }
        return 0;
    }
}
