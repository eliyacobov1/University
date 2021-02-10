import java.awt.Image;
import oop.ex2.*;

public class Aggressive extends SpaceShip {

    /** minimal angle that the nearest ship angle */
    private static final double shoot_angle=0.21;

    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */

    public void doAction(SpaceWars game) {
        increase_shot_timer();
        //checks angle to nearest ship and turns accordingly,also if angle from nearest ship is less then 0.21,will fire.
        movement(game);

        double angle=getPhysics().angleTo(game.getClosestShipTo(this).getPhysics());
        if (Math.abs(angle)<shoot_angle){
            fire(game);
        }
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
        return GameGUI.ENEMY_SPACESHIP_IMAGE;
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
}
