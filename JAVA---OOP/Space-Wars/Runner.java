import java.awt.Image;
import oop.ex2.*;

public class Runner extends SpaceShip {

    /**
     * minimal angle that the nearest ship has to be in order to issue a teleport command
     */
    private static final double teleport_angle = 0.23;

    /**
     * minimal distance that the nearest ship has to be in order to issue a teleport command
     */
    private static final double teleport_distance = 0.25;

    /**
     * Does the actions of this ship for this round.
     * This is called once per round by the SpaceWars game driver.
     *
     * @param game the game object to which this ship belongs.
     */
    public void doAction(SpaceWars game) {
        //checks angle and distance of nearest ship.If they align with the criteria,will teleport
        double angle = game.getClosestShipTo(this).getPhysics().angleTo(getPhysics());
        double distance = game.getClosestShipTo(this).getPhysics().distanceFrom(getPhysics());
        if (Math.abs(angle) < teleport_angle && distance < teleport_distance) {
            teleport();
        }

        movement(game);

        increase_energy();
    }

    /**
     * Gets the image of this ship. This method should return the image of the
     * ship with or without the shield. This will be displayed on the GUI at
     * the end of the round.
     *
     * @return the image of this ship.
     */

    public Image getImage() {
        return GameGUI.ENEMY_SPACESHIP_IMAGE;
    }

    /**
     * This method is called once in a round.It is responsible for the movement of the
     * Aggressive ship.
     *
     * @param game the game object to which this ship belongs.
     */

    private void movement(SpaceWars game) {
        double angle1 = getPhysics().angleTo(game.getClosestShipTo(this).getPhysics());
        if (angle1 > 0) {
            getPhysics().move(true, -1);
        } else {
            if (angle1 < 0) {
                getPhysics().move(true, 1);
            } else {
                getPhysics().move(true, 1);
            }
        }

    }
}
