public abstract class SimpleHashSet
        implements SimpleSet {

    /**
     * Describes the higher load factor of a newly created hash set
     */
    protected static float DEFAULT_HIGHER_CAPACITY=0.75f;

    /**
     *Describes the lower load factor of a newly created hash set
     */
    protected static float DEFAULT_LOWER_CAPACITY=0.25f;

    /**
     * Describes the capacity of a newly created hash set
     */
    protected static int INITIAL_CAPACITY=16;

    /**
     * represents the higher load factor of a SimpleHashSet instance
     */
    private float Higher_Factor;

    /**
     * represents the lower load factor of a SimpleHashSet instance
     */
    private float Lower_Factor;

    /**
     * the array that is being used as a basic database where values are stored
     */
    private Object[] array;

    /**
     * Constructs a new hash set with the default capacities given in
     * DEFAULT_LOWER_CAPACITY and DEFAULT_HIGHER_CAPACITY
     */
    public SimpleHashSet(){
        this.Higher_Factor=DEFAULT_HIGHER_CAPACITY;
        this.Lower_Factor=DEFAULT_LOWER_CAPACITY;
    }

    /**
     * Constructs a new hash set with capacity INITIAL_CAPACITY
     * @param upperLoadFactor the upper load factor before rehashing
     * @param lowerLoadFactor the lower load factor before rehashing
     */
    public SimpleHashSet(float upperLoadFactor, float lowerLoadFactor){
        this.Higher_Factor=upperLoadFactor;
        this.Lower_Factor=lowerLoadFactor;
    }

    /**
     * @return The current capacity (number of cells) of the table.
     */
    public abstract int capacity();

    /**
     * Clamps hashing indices to fit within the current table capacity
     * @param index the index before clamping
     * @return an index properly clamped
     */

    protected int clamp(int index)
    {
        return (index &(capacity()-1));

    }

    /**
     * @return The lower load factor of the table.
     */
    protected float getLowerLoadFactor(){
        return this.Lower_Factor;
    }

    /**
     * @return The Upper load factor of the table.
     */
    protected float getUpperLoadFactor(){
        return this.Higher_Factor;
    }
}
