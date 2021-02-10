import java.util.LinkedList;

public class OpenHashSet extends SimpleHashSet{

    /**
     * variable that represents the current total number of objects in the set
     */
    private int elements_in_set;

    /**
     * the array that is being used as a basic database where values are stored
     */
    private Custom_List[] array;

    /**
     * A default constructor. Constructs a new, empty table with default
     * initial capacity (16), upper load factor (0.75) and lower load factor (0.25)
     */

    public OpenHashSet(){
        super();
        this.elements_in_set=0;
        this.array=new Custom_List[INITIAL_CAPACITY];

        //initialize a new List for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++){
            array[i]=new Custom_List();
        }
    }

    /**
     * Constructs a new, empty table with the specified load factors,
     * and the default initial capacity (16)
     * @param upperLoadFactor  The upper load factor of the hash table
     * @param lowerLoadFactor  The lower load factor of the hash table
     */

    public OpenHashSet(float upperLoadFactor, float lowerLoadFactor){
        super(upperLoadFactor,lowerLoadFactor);
        this.elements_in_set=0;
        this.array=new Custom_List[INITIAL_CAPACITY];

        //initialize a new List for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++){
            array[i]=new Custom_List();
        }
    }

    /**
     * Data constructor - builds the hash set by adding the elements one by one.
     * Duplicate values should be ignored. The new table has the default values
     * of initial capacity (16), upper load factor (0.75), and lower load factor (0.25)
     * @param data Values to add to the set
     */

    public OpenHashSet(java.lang.String[] data){
        super();
        this.elements_in_set=0;
        this.array=new Custom_List[INITIAL_CAPACITY];

        //initialize a new List for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++){
            array[i]=new Custom_List();
        }

        for(String element:data){
            add(element);
        }
    }

    /**
     * Add a specified element to the set if it's not already in it
     * @param newValue New value to add to the set
     * @return False iff newValue already exists in the set
     */

    public boolean add(java.lang.String newValue){
        //if element is already in the set,returns false
        if(contains(newValue)){
            return false;
        }
        int index=clamp(newValue.hashCode());

        //adds the element to the set in the appropriate array cell and increases
        // element_in_set by 1
        array[index].add(newValue);
        elements_in_set++;

        //checks if a resize of the array is necessary
        Resize( 2.0);

        //finally, returns true
        return true;
    }

    /**
     * Look for a specified value in the set.
     * @param searchVal Value to search for
     * @return True iff searchVal is found in the set
     */

    public boolean contains(java.lang.String searchVal){
        //represents the List in the array to which the value
        //will be inserted according to its hashcode.
        int index=clamp(searchVal.hashCode());

        //represents the List in the specific index which we got above
        LinkedList<String> Hash_List=array[index].getLinkedList();

        //look trough the LinkedList to check if the element is already in the set
        //if so,will return true
        for (String element : Hash_List) {
            if (searchVal.hashCode() == element.hashCode()) {
                return true;
            }
        }
        //if item is not found,returns false
        return false;
        }

    /**
     * Remove the input element from the set
     * @param toDelete Value to delete
     * @return True iff toDelete is found and deleted
     */

    public boolean delete(java.lang.String toDelete){
        //if element is not in the set,returns false
        if(!contains(toDelete)){
            return false;
        }
        //deletes the element
        int index=clamp(toDelete.hashCode());
        array[index].delete(toDelete);

        //subtracts 1 from elements_in_set
        elements_in_set--;

        //checks if a resize of the array is necessary
        Resize(0.5);

        //finally, returns true
        return true;
    }

    /**
     * @return The number of elements currently in the set
     */

    public int size(){ return elements_in_set; }

    /**
     * implementation of the abstract capacity method in class SimpleHashSet
     * @return The current capacity (number of cells) of the table
     */

    public int capacity(){
        return array.length;
    }

    /**
     * Checks if  there's a deviation from the upper or lower load factors.
     * If there is, will resize and double the array's capacity
     */

    private void Resize(double coefficient){
        //checks if the new load factor exceeds from the upper or lower load factors
        float current_factor=(float)size()/capacity();
        if(((current_factor>getUpperLoadFactor() || current_factor>1) && coefficient == 2.0)||
                ((current_factor<getLowerLoadFactor()&& coefficient == 0.5 || current_factor==0)
                        && capacity()>1)){
            //convert new size from double to int
            int new_size=(int)(capacity()*coefficient);

            //creates a new array double or half the size
            Custom_List[] array1=new Custom_List[new_size];

            //initialize a new List for each of the cells in the array
            for(int i=0;i<new_size;i++){
                array1[i]=new Custom_List();
            }
            //create a backup for the current array called original_array and
            // set the new array as the current table for the set in order to
            // rehash all the elements
            Custom_List[] original_array=array;
            array=array1;
            elements_in_set=0;

            //rehash all elements in the set
            for(Custom_List list:original_array){
                for(String element:list.getLinkedList()){
                    add(element);
                }
            }
        }
    }
}
