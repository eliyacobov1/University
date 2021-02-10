import java.awt.Image;
import oop.ex2.*;

public class Human extends SpaceShip {
    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */

    public void doAction(SpaceWars game) {
        increase_shot_timer();
        if(is_shield_on() ){
            turn_shield_off();
        }
        if (game.getGUI().isTeleportPressed()){
            teleport();
        }

        movement(game);

        if (game.getGUI().isShieldsPressed()){
            shieldOn();
        }
        if (game.getGUI().isShotPressed()){
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
        if(is_shield_on()){
            return GameGUI.SPACESHIP_IMAGE_SHIELD;
        }
        return GameGUI.SPACESHIP_IMAGE;
    }

    /**
     *This method is called once in a round.It is responsible for the movement of the
     * ship.The movement is done with correlation to the input that is received from the user.
     */

    private void movement(SpaceWars game){
    //checks if user used acceleration button,if so,checks in which direction to move
    if(game.getGUI().isUpPressed()) {
        if (game.getGUI().isLeftPressed() && game.getGUI().isRightPressed()){
            getPhysics().move(true, 0);
        }
        else {
            if (game.getGUI().isLeftPressed()) {
                getPhysics().move(true, 1);
            } else {
                if (game.getGUI().isRightPressed()) {
                    getPhysics().move(true, -1);
                } else {
                    getPhysics().move(true, 0);
                }
            }
        }
    }
    //else will make the same movements only without accelerating
    else{
        if (game.getGUI().isLeftPressed() && game.getGUI().isRightPressed()){
            getPhysics().move(true, 0);
        }
        else {
            if (game.getGUI().isLeftPressed()) {
                getPhysics().move(false, 1);
            } else {
                if (game.getGUI().isRightPressed()) {
                    getPhysics().move(false, -1);
                } else {
                    getPhysics().move(false, 0);
                }
            }
        }
    }
    }
}
