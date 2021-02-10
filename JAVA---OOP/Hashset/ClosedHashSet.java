public class ClosedHashSet extends SimpleHashSet {

    /**
     * variable that represents the current total number of objects in the set
     */
    private int elements_in_set;

    /**
     * the array that is being used as a basic database where values are stored
     */
    private String[] array;

    /**
     * A default constructor. Constructs a new, empty table with default
     * initial capacity (16), upper load factor (0.75) and lower load factor (0.25)
     */

    public ClosedHashSet(){
        super();
        this.elements_in_set=0;
        this.array=new String[INITIAL_CAPACITY];

        //put null for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++) {
            array[i] = null;
        }
    }

    /**
     * Constructs a new, empty table with the specified load factors,
     * and the default initial capacity (16)
     * @param upperLoadFactor  The upper load factor of the hash table
     * @param lowerLoadFactor  The lower load factor of the hash table
     */

    public ClosedHashSet(float upperLoadFactor, float lowerLoadFactor){
        super(upperLoadFactor,lowerLoadFactor);
        this.elements_in_set=0;
        this.array=new String[INITIAL_CAPACITY];

        //put null for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++) {
            array[i] = null;
        }
    }

    /**
     * Data constructor - builds the hash set by adding the elements one by one.
     * Duplicate values should be ignored. The new table has the default values
     * of initial capacity (16), upper load factor (0.75), and lower load factor (0.25)
     * @param data Values to add to the set
     */

    public ClosedHashSet(java.lang.String[] data){
        super();
        this.elements_in_set=0;
        this.array=new String[INITIAL_CAPACITY];

        //put null for each of the cells in the array
        for(int i=0;i<INITIAL_CAPACITY;i++) {
            array[i] = null;
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
        if (contains(newValue)) {
            return false;
        }
        //increase elements_in_set by one and check if after increment,a resize
        //to the set is needed.If so,wil resize the array.If a resize had occurred,
        //this would mean that the elements_in_set variable was set to zero prior to
        //the resize.Therefore,will add 1 to elements_in_set in that case.
        elements_in_set++;
        if(Resize(2.0)==1){
            elements_in_set++;
        }
        //iterates through the array using the Iterate helper method to find an available cell.
        //when finds one,inserts the value
        array[Iterate(1, newValue)] = newValue;

        //finally,returns true
        return true;
    }

    /**
     * Look for a specified value in the set.
     * @param searchVal Value to search for
     * @return True iff searchVal is found in the set
     */

    public boolean contains(java.lang.String searchVal){
        //uses helper method Iterate (see below) to check if the value is in the array
        return(Iterate(0,searchVal)!=-1);
    }

    /**
     * Remove the input element from the set
     * @param toDelete Value to delete
     * @return True iff toDelete is found and deleted
     */

    public boolean delete(java.lang.String toDelete){
        int index=Iterate(0,toDelete);
        //check if element is in the set (otherwise,index value will be -1)
        if(index!=-1){
            //deletes the elements and subtracts 1 from elements_in_cell
            array[index]=null;
            elements_in_set--;

            //checks if a resize of the array is necessary,and if so,performs a resize
            Resize(0.5);

            //finally,returns true
            return true;
        }
        //if element is not in the array,returns false
        return false;
    }

    /**
     * @return The number of elements currently in the set
     */

    public int size(){
        return elements_in_set;
    }

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
     * @return 1 if resize was made,-1 otherwise
     */

    private int Resize(double coefficient){
        //checks if the new load factor exceeds from the upper or lower load factors
        float current_factor=(float)size()/capacity();
        if((current_factor>getUpperLoadFactor() && coefficient == 2.0)||
                (((current_factor<getLowerLoadFactor()) || current_factor==0) &&
                        coefficient == 0.5  && capacity()>1)){
            //convert new size from double to int
            int new_size=(int)(capacity()*coefficient);

            //creates a new array double or half the size
            String[] array1=new String[new_size];

            //put null for each of the cells in the array
            for(int i=0;i<new_size;i++) {
                array1[i] = null;
            }
            //create a backup for the current array called original_array and
            // set the new array as the current table for the set in order to
            // rehash all the elements.also nullifies the elements_in_set variable
            String[] original_array=array;
            array=array1;
            elements_in_set=0;

            //rehash all elements in the set
            for(String element:original_array){
                if(element!=null) {
                    add(element);
                }
            }

            return 1;
        }
        return -1;
    }

    /**
     * Helper method that iterates through the array for one of two causes.
     * Either to make sure that an element is not in the set,or to find a proper
     * index to insert a new element.
     * @param condition @0-will check if element is in the list,@1-will look for an
     *                  index to insert a new element
     * @param element The element that is to be checked
     * @return @ condition=0: if item is in the array will return its index,-1 otherwise
     * @ condition=1: index location in the array into which the element can be added to
     */

    private int Iterate(int condition,String element){
        int index=clamp(element.hashCode());
        int i=0;
        //represents hash function value,increases with each failed search attempt
        int hash_searchVal=index;

        if(condition==0){
            //Iterate through the array according to the hash function quadratic probing
            //rule to try and find the element.If ended up at at value equal or bigger
            // than hash(e) value when i=0 for the second time,will break
            // out of the loop and return -1
            while(!((index + (i + i * i) / 2)>capacity()
                    && hash_searchVal>=index)) {
                if(array[hash_searchVal]!=null) {
                    if (array[hash_searchVal].hashCode() == element.hashCode()) {
                        return hash_searchVal;
                    }
                }
                i++;
                hash_searchVal = (index + (i + i * i) / 2) & (capacity()-1);
            }
            return -1;
        }
        else{
            //iterates through the array using the hash function to find an available cell.
            //when finds one,returns its index.
            while(array[hash_searchVal]!=null) {
                i++;
                hash_searchVal = (index + (i + i * i) / 2) & (capacity()-1);
            }
            return hash_searchVal;
        }
    }
}
