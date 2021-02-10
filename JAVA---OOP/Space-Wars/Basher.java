import java.awt.Image;
import oop.ex2.*;

public class Basher extends SpaceShip {

    /** if closest ship is in this distance or lower,the basher will attempt to turn on it's shields */
    private static final double shields_distance=0.19;

    public void doAction(SpaceWars game) {
        if (is_shield_on()) {
            turn_shield_off();
        }

        movement(game);

        activate_shields(game);

        increase_energy();
    }

        /**
         * Gets the image of this ship. This method should return the image of the
         * ship with or without the shield. This will be displayed on the GUI at
         * the end of the round.
         *
         * @return the image of this ship.
         */

    public Image getImage(){
        if(is_shield_on()){
            return GameGUI.ENEMY_SPACESHIP_IMAGE;
        }
        return GameGUI.ENEMY_SPACESHIP_IMAGE_SHIELD;
    }

    /**
     *This method is called once in a round.It is responsible for the movement of the
     * Aggressive ship.
     *
     * @param game the game object to which this ship belongs.
     */

    private void movement(SpaceWars game){
        //checks angle to nearest ship and turns accordingly,also if distance from nearest ship is less then 0.19,will
        //turn shields on
        double angle = getPhysics().angleTo(game.getClosestShipTo(this).getPhysics());
        if (angle > 0) {
            getPhysics().move(true, 1);
        } else {
            if (angle < 0) {
                getPhysics().move(true, -1);
            } else {
                getPhysics().move(true, 0);
            }
        }
    }

    /**
     *This method is called once per round.It determines whether or not the Basher will
     * activate its shields
     */

    private void activate_shields(SpaceWars game){
        double distance = game.getClosestShipTo(this).getPhysics().distanceFrom(getPhysics());
        if (distance <= shields_distance) {
            shieldOn();
        }
    }

}

