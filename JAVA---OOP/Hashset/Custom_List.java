import java.util.LinkedList;

public class Custom_List implements SimpleSet {

    /**
     * LinkedList variable for composition purposes
     */
    private LinkedList<String> LinkedList;

    public Custom_List() {
        this.LinkedList = new LinkedList<String>();
    }

    /**
     * Add a specified element to the LinkedList of the List
     * if it's not already in it
     * @param newValue New value to add to the LinkedList
     * @return true when newValue is added
     */

    public boolean add(java.lang.String newValue){
        return LinkedList.add(newValue);
    }

    /**
     * Look for a specified value in the LinkedList of the List
     * @param searchVal Value to search for
     * @return True iff searchVal is found in the set,otherwise False
     */

    public boolean contains(java.lang.String searchVal){
        return LinkedList.contains(searchVal);
    }

    /**
     * Remove the input element from the LinkedList of the List
     * @param toDelete Value to delete
     * @return True iff toDelete is found and deleted
     */

    public boolean delete(java.lang.String toDelete){
        return LinkedList.remove(toDelete);
    }

    /**
     * @return The number of elements currently in the LinkedList of the List
     */
    public int size(){
        return LinkedList.size();
    }

    /**
     * Gets the LinkedList variable of this List instance
     * @return The LinkedList variable of this List instance
     */
    LinkedList<String> getLinkedList(){
        return LinkedList;
    }

    boolean isEmpty(){
        return LinkedList.isEmpty();
    }
}
