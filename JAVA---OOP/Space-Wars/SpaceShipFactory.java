import oop.ex2.*;

public class SpaceShipFactory {
    /** variable that is set to true if a human is added to the array of ships*/
    private static boolean is_human_in_array=false;

    /**
     * Gets a array of strings and returns an array of spaceships according to the
     * following corresponding values:
     * "h" - Human controlled ship (controlled by the user),can only add one of this ship type.
     * "r" - Runner: a ship that tries to avoid all other ships.
     * "b" - Basher: a ship that deliberately tries to collide with other ships.
     * "a" - Aggressive: a ship that tries to pursue other ships and fire at them.
     * "d" - Drunkard: a ship with a drunken pilot that moves in random directions,
     * and also shoots and teleports in a random manner
     * "s" - Special: a ship that combines the behaviours of the Aggressive ship
     * (pursues and shoots other ships),the Runner ship (by teleporting when the
     * nearest enemy ship is at a certain angle and distance),and the basher ship (by activating shields
     * when the nearest ship as at a certain distance).Also,the special ship energy unit count increases
     * by 5 in each round (instead of the usual single unit increment)
     * @param args the array of String's which represent the desired ships to be put in the game
     * @return the array of fitting spaceships that is used by the "spacewars" class to initiate the game.
     */

    public static SpaceShip[] createSpaceShips(String[] args) {
        SpaceShip[] spaceship_array=new SpaceShip[args.length];
        for(int i=0;i<args.length;i++){
            if(args[i].charAt(0)=='a'){
                spaceship_array[i]=new Aggressive();
            }

            if(args[i].charAt(0)=='r'){
                spaceship_array[i]=new Runner();
            }

            if(args[i].charAt(0)=='b'){
                spaceship_array[i]=new Basher();
            }

            if(args[i].charAt(0)=='d'){
                spaceship_array[i]=new Drunkard();
            }

            if(args[i].charAt(0)=='s'){
                spaceship_array[i]=new Special();
            }

            if(args[i].charAt(0)=='h'){
                if(is_human_in_array){
                    throw new IllegalArgumentException("only one human spaceship can be added to the game");
                }
                else {
                    spaceship_array[i] = new Human();
                    is_human_in_array = true;
                }
            }
        }
        return spaceship_array;
    }
}
