import static org . junit . Assert .*;
import oop.ex3.spaceship.*;
import org.junit.Before;
import org.junit.Test;
import java.util.Map;

public class LockerTest implements StorageUnitTestInterface {
    /**
     * locker which will reset in each test
     */
    private static Locker locker;

    /**
     * LongTermStorage instance used to reset long term inventory
     */
    private static LongTermStorage lts=new LongTermStorage();

    /**
     * item of type "baseball bat"
     */
    private static final Item bat=ItemFactory.createSingleItem("baseball bat");

    /**
     * item of type "helmet,size 1"
     */
    private static final Item helmet1 =ItemFactory.createSingleItem("helmet, size 1");

    /**
     * item of type "helmet,size 3"
     */
    private static final Item helmet3 =ItemFactory.createSingleItem("helmet, size 3");

    /**
     * item of type "spores engine"
     */
    private static final Item spores_engine =ItemFactory.createSingleItem("spores engine");

    /**
     * item of type "football"
     */
    private static final Item football =ItemFactory.createSingleItem("football");

    /**
     * method that is performed before each test.
     * It initializes the Locker and resets the long term storage
     */

    @Before
    public void initialize(){
        locker=new Locker(500);
        lts.resetInventory();
    }

    /**
     * Test for the addItem method
     */

    @Test
    public void add_item_test(){
        assertEquals(locker.addItem(bat,250),1);
        //since 20 percent are occupied,should not allow anymore
        // baseball bats to be added
        assertEquals(locker.addItem(bat,150),-1);
        locker.removeItem(bat,5);

        //the case of n is negative
        assertEquals(locker.addItem(helmet1,-3),-1);

        //max bats that can be added directly to the locker (return code 0)
        assertEquals(locker.addItem(bat,5),0);
    }

    /**
     * Test for the getItemCount method
     */

    @Test
    public void item_count_test(){
        locker.addItem(spores_engine,50);
        assertEquals(locker.getItemCount(spores_engine.getType()),10);
        assertEquals(locker.getItemCount(bat.getType()),0);
        locker.removeItem(spores_engine,3);

        //count after removing
        assertEquals(locker.getItemCount(spores_engine.getType()),7);

}

    /**
     * Test for the removeItem method
     */

    @Test
    public void removeItem_test(){
        locker.addItem(spores_engine,5);

        //n is bigger than actual item amount in locker
        assertEquals(locker.removeItem(spores_engine,6),-1);
        assertEquals(locker.removeItem(spores_engine,2),0);

        //n is negative
        assertEquals(locker.removeItem(spores_engine,-2),-1);
    }

    /**
     * Test for the getInventory method
     */

    @Test
    public void get_inventory_test(){
        locker.addItem(spores_engine,2);
        locker.addItem(football,4);
        locker.addItem(helmet3,2);
        Map map=locker.getInventory();
        // checks amount in map object for each item
        assertEquals(map.get(spores_engine.getType()),2);
        assertEquals(map.get(football.getType()),4);
        assertEquals(map.get(helmet3.getType()),2);

        //adding a bat should fail,therefore bat count should be 0
        //and there should be no bat key in the map object
        locker.addItem(bat,1);
        assertFalse(map.containsKey(bat.getType()));

    }

    /**
     * Test for the getCapacity and getAvailableCapacity methods
     */

    @Test
    public void test_getCapacity(){
        assertEquals(locker.getCapacity(),500);
        locker.addItem(football,4);
        locker.addItem(helmet3,2);
        assertEquals(locker.getAvailableCapacity(),474);

        //after increment in amount,football will occupy more
        // than 50 percent of locker storage,therefore the suitable
        // amount should be moved to the long term storage.
        locker.addItem(football,68);
        assertEquals(locker.getAvailableCapacity(),390);
    }

    /**
     * Test for the functionality that prevents item of types football
     * and baseball bat to exist in the same locker
     */

    @Test
    public void football_and_bat(){
        locker.addItem(bat,5);
        assertEquals(locker.addItem(football,1),-2);
        locker.removeItem(bat,5);
        assertEquals(locker.addItem(football,1),0);
        assertEquals(locker.addItem(bat,1),-2);
    }

    /**
     * Test for the case where locker capacity is 0
     */

    @Test
    public void null_locker_capacity(){
        //checks for the case in which locker capacity is 0
        locker=new Locker(0);
        assertEquals(locker.addItem(bat,1),-1);
    }
}
