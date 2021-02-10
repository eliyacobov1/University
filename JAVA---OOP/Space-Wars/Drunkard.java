import java.awt.Image;
import oop.ex2.*;
import java.util.Random;

public class Drunkard extends SpaceShip {

    /**
     *  The random generator used for initialization of the values for the
     * movement,shooting and shield methods.
     */
     private static Random randomGenerator = new Random();

    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */

    public void doAction(SpaceWars game) {
        increase_shot_timer();
        teleport_decider();

        movement();

        shoot(game);

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
     *This method is called once per round.It is responsible for the movement of the
     * Drunkard ship,it is done by using random values each time the method is called.
     */

    private void movement(){
        boolean accelerate=randomGenerator.nextBoolean();
        int direction=randomGenerator.nextInt(2)-1;
        getPhysics().move(accelerate,direction);
    }

    /**
     *This method is called once per round.It determines whether or not the Drunkard will
     * commence a fire command.
     *
     * @param game the game object to which this ship belongs.
     */

    private void shoot(SpaceWars game){
        boolean shoot=randomGenerator.nextBoolean();
        if (shoot){
            fire(game);
        }
    }

    /**
     *This method is called once per round.It determines whether or not the Drunkard will
     * teleport.
     */

    private void teleport_decider(){
        boolean teleport=randomGenerator.nextBoolean();
        if (teleport){
            teleport();
        }
    }
}
