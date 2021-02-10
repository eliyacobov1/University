import java.awt.Image;
import oop.ex2.*;

/**
 * The API spaceships need to implement for the SpaceWars game. 
 * It is your decision whether SpaceShip.java will be an interface, an abstract class,
 *  a base class for the other spaceships or any other option you will choose.
 *  
 * @author oop
 */
public class SpaceShip{

    /** The default max energy of a ship on reset,210 by default */
    private static final int max_energy_default=210;

    /** Amount of health that a ship has upon initialization,22 by default */
    private static final int default_health=22;

    /** The limit of energy units that a ship can posses  */
    private int max_energy;

    /** Amount of health point the the ship has */
    private int health;

    /** Amount of energy units the the ship has */
    private int energy;

    /** Boolean instance representing the ship's shields.True is for shields on and False for shield of */
    private boolean shield;

    /** shot time that counts to 7 rounds each time the spaceship shoots.By default it is 0 */
    private int shot_timer;

    /** physics instance that manages the location and speed of the spaceship */
    private SpaceShipPhysics physics;

    public SpaceShip(){
        this.physics=new SpaceShipPhysics();
        this.health=default_health;
        this.energy=190;
        this.max_energy=max_energy_default;
        this.shot_timer=0;
        this.shield=false;
    }

    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */
    public void doAction(SpaceWars game) {
        return;
    }

    /**
     * This method is called every time a collision with this ship occurs 
     */
    public void collidedWithAnotherShip(){
        if (shield) {
            energy = energy + 18;
            max_energy = max_energy + 18;
        }
        else{
            health-=1;
        }
    }

    /** 
     * This method is called whenever a ship has died. It resets the ship's 
     * attributes, and starts it at a new random position.
     */
    public void reset(){
        this.physics=new SpaceShipPhysics();
        this.health=22;
        this.energy=190;
        this.max_energy=210;
        this.shot_timer=0;
        this.shield=false;
    }

    /**
     * Checks if this ship is dead.
     * 
     * @return true if the ship is dead. false otherwise.
     */
    public boolean isDead() {
        return (health<=0);
    }

    /**
     * Gets the physics object that controls this ship.
     * 
     * @return the physics object that controls the ship.
     */
    public SpaceShipPhysics getPhysics() {
        return physics;
    }

    /**
     * This method is called by the SpaceWars game object when ever this ship
     * gets hit by a shot.
     */
    public void gotHit() {
        if (!shield) {
            health-=1;
            max_energy-=10;
            if (energy>max_energy){
                energy=max_energy;
            }
        }
    }

    /**
            * Gets the image of this ship. This method should return the image of the
     * ship with or without the shield. This will be displayed on the GUI at
     * the end of the round.
     *
             * @return the image of this ship.
     */
    public Image getImage(){
        return null;
    }

    /**
     * Attempts to fire a shot.
     * 
     * @param game the game object.
     */
    public void fire(SpaceWars game) {
        if (energy >= 19 && shot_timer==0) {
            game.addShot(physics);
            energy = energy - 19;
            shot_timer=1;
        }

        /**
         * Attempts to turn on the shield.
         */
    }
    public void shieldOn () {
        if(energy>=3){
            shield=true;
            energy-=3;
        }

    }

    /**
     * Attempts to teleport.
     */
    public void teleport(){
        if (energy >= 140) {
            physics = new SpaceShipPhysics();
            energy=energy-140;
        }
    }

    /**
     * Increases current energy level by 1 it does exceed the max energy level of the ship.
     */
    public void increase_energy() {
        if(energy<max_energy){
            energy+=1;
        }
    }

    /**
     * checks shot timer of this ship (the count of rounds that were played since the last shot
     * was fired,if between 1-7 then the ship is not eligible to shoot yet).If between 1-7,will add 1 to it.
     * If 7 rounds had already passed,will put zero and thus enable the 'fire' method to commence.
     */

    public void increase_shot_timer(){
        if (shot_timer==7){
            shot_timer=0;
            return;
        }
        if (shot_timer>=1 && shot_timer<7 ){
            shot_timer+=1;
        }

    }
    /**
     * Checks shield is on.
     *
     * @return true if the shield is on. false otherwise.
     */
    public boolean is_shield_on(){
        return shield;
    }

    /**
     * Turns shield off if it is on.
     */
    public void turn_shield_off(){
        shield=false;
    }


}
