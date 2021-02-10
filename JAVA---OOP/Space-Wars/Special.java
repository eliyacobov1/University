import java.awt.Image;
import oop.ex2.*;

public class Special extends SpaceShip  {
    /**
     * minimal angle that the nearest ship has to be in order to issue a teleport command
     */
    private static final double teleport_angle = 0.23;

    /**
     * minimal distance that the nearest ship has to be in order to issue a teleport command
     */
    private static final double teleport_distance = 0.25;

    /** minimal angle that the nearest ship angle */
    private static final double shoot_angle=0.21;

    /** if closest ship is in this distance or lower,the Special ship will attempt to turn on it's shields */
    private static final double shields_distance=0.19;

    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */

    public void doAction(SpaceWars game) {
        increase_shot_timer();

        teleport_decider(game);

        movement(game);

        activate_shields(game);

        double angle=getPhysics().angleTo(game.getClosestShipTo(this).getPhysics());
        if (Math.abs(angle)<shoot_angle){
            fire(game);
        }

        increase_energy();
        increase_energy();
        increase_energy();
        increase_energy();
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
            return GameGUI.SPACESHIP_IMAGE_SHIELD;
        }
        return GameGUI.SPACESHIP_IMAGE;
    }

    /**
     *This method is called once in a round.It is responsible for the movement of the
     * Aggressive ship.
     *
     * @param game the game object to which this ship belongs.
     */

    private void movement(SpaceWars game){
        double angle=getPhysics().angleTo(game.getClosestShipTo(this).getPhysics());
        if(angle>0){
            getPhysics().move(true,1);
        }
        else{
            if(angle<0){
                getPhysics().move(true,-1);
            }
            else{
                getPhysics().move(true,0);
            }
        }
    }

    /**
     *This method is called once per round.It determines whether or not the special ship will
     * teleport.
     */

    private void teleport_decider(SpaceWars game){
        double angle = game.getClosestShipTo(this).getPhysics().angleTo(getPhysics());
        double distance = game.getClosestShipTo(this).getPhysics().distanceFrom(getPhysics());
        if (Math.abs(angle) < teleport_angle && distance < teleport_distance) {
            teleport();
        }
    }

    /**
     *This method is called once per round.It determines whether or not the Special ship will
     * activate its shields
     */

    private void activate_shields(SpaceWars game){
        double distance = game.getClosestShipTo(this).getPhysics().distanceFrom(getPhysics());
        if (distance <= shields_distance) {
            shieldOn();
        }
    }
}
