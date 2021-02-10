import static org . junit . Assert .*;
import oop.ex3.spaceship.*;
import org.junit.Before;
import org.junit.Test;
import java.util.Map;

public class LongTermTest implements StorageUnitTestInterface {

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
     * Test for the addItem method
     */

    @Before
    public void initialize(){
        lts.resetInventory();
    }

    @Test
    public void add_item_test(){
        assertEquals(lts.addItem(bat,200),0);

        //maximal of bats to be added (now the long term storage is full)
        assertEquals(lts.addItem(bat,300),0);

        //should return -1 since storage is full
        assertEquals(lts.addItem(football,1),-1);

        lts.resetInventory();

        //the case of n is negative
        assertEquals(lts.addItem(helmet1,-3),-1);

        //asserts that adding a football and a baseball bat is possible
        lts.addItem(bat,1);
        assertEquals(lts.addItem(football,1),0);
    }

    /**
     * Test for the getItemCount method
     */

    @Test
    public void item_count_test(){
        lts.addItem(spores_engine,50);
        assertEquals(lts.getItemCount(spores_engine.getType()),50);
        assertEquals(lts.getItemCount(bat.getType()),0);

        lts.resetInventory();

        //count after reset
        assertEquals(lts.getItemCount(spores_engine.getType()),0);

    }

    /**
     * Test for the getInventory method
     */

    @Test
    public void get_inventory_test(){
        lts.addItem(spores_engine,2);
        lts.addItem(football,4);
        lts.addItem(helmet3,2);

        Map map=lts.getInventory();

        // checks amount in map object for each item
        assertEquals(map.get(spores_engine.getType()),2);
        assertEquals(map.get(football.getType()),4);
        assertEquals(map.get(helmet3.getType()),2);

        lts.resetInventory();

        //no room for 505 bats so no bats should be added
        lts.addItem(bat,505);
        assertFalse(map.containsKey(bat.getType()));

    }

    /**
     * Test for the getCapacity and getAvailableCapacity methods
     */

    @Test
    public void test_getCapacity(){
        assertEquals(lts.getCapacity(),1000);
        lts.addItem(football,4);
        lts.addItem(helmet3,2);
        assertEquals(lts.getAvailableCapacity(),974);

        //no change should occur since there is no space for 250 items
        //at the given circumstances
        lts.addItem(football,250);
        assertEquals(lts.getAvailableCapacity(),974);
    }
}

