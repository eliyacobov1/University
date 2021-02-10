import java.util.HashSet;
import java.util.LinkedList;
import java.util.TreeSet;

public class SimpleSetPerformanceAnalyzer {

    /**
     * represents the array index that contains a OpenHashSet
     */
    private int OpenSet=0;

    /**
     * represents the array index that contains a ClosedHashSet
     */
    private int ClosedSet=1;

    /**
     * represents the array index that contains a TreeSet
     */
    private int Tree=2;

    /**
     * represents the array index that contains a LinkedList
     */
    private int Linked=3;

    /**
     * represents the array index that contains a HashSet
     */
    private int Hash=4;

    /**
     * represents a string that is used in the analyzing process
     */
    private String string_to_test1="hi";

    /**
     * represents a string that is used in the analyzing process
     */
    private String string_to_test2="-13170890158";

    /**
     * represents a string that is used in the analyzing process
     */
    private String string_to_test3="23";

    /**
     * represents the array in which all of the data structures reside
     */
    private static SimpleSet[] Array_Of_Sets=new SimpleSet[5];



    public static void main(String[] args){
        SimpleSetPerformanceAnalyzer analyzer=new SimpleSetPerformanceAnalyzer();

        for(int i=0;i<5;i++){
            analyzer.test1(i);
        }

        for(int i=0;i<5;i++){
            analyzer.test2(i);
        }

        for(int i=0;i<5;i++){
            analyzer.test3(i);
        }

        for(int i=0;i<5;i++){
            analyzer.test4(i);
        }

        for(int i=0;i<5;i++){
            analyzer.test5(i);
        }

        for(int i=0;i<5;i++){
            analyzer.test6(i);
        }
    }

    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test1(int i){
        System.out.println("Test number 1 (Add data1.txt)");
        String[] data1=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data1.txt");
        switch (i) {
            case 0:
            long timeBefore = System.nanoTime();
            Array_Of_Sets[0]=new OpenHashSet(Ex4Utils.file2array
                    ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
            long difference = System.nanoTime() - timeBefore;

            System.out.println("For data structure OpenHashset "+
                     "the time is " + difference / 1000000);
            return;


            case 1:
            timeBefore = System.nanoTime();
            Array_Of_Sets[0]=new ClosedHashSet(Ex4Utils.file2array
                    ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
            difference = System.nanoTime() - timeBefore;

            System.out.println("For data structure ClosedHashset "+
                    "the time is " + difference / 1000000);
            return;

            case 2:
                Array_Of_Sets[2]=new CollectionFacadeSet(new TreeSet<String>());
                timeBefore = System.nanoTime();
                for(String string:data1){
                    Array_Of_Sets[2].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset "+
                        "the time is " + difference / 1000000);
                return;

            case 3:
                Array_Of_Sets[3]=new CollectionFacadeSet(new LinkedList<String>());
                timeBefore = System.nanoTime();
                for(String string:data1){
                    Array_Of_Sets[3].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist "+
                        "the time is " + difference / 1000000);
                return;

            case 4:
                Array_Of_Sets[4]=new CollectionFacadeSet(new HashSet<String>());
                timeBefore = System.nanoTime();
                for(String string:data1){
                    Array_Of_Sets[4].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Hashset "+
                        "the time is " + difference / 1000000);
                return;
        }
    }

    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test2(int i){
        System.out.println("Test number 2 (Add data2.txt)");
        String[] data=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data2.txt");
        switch (i) {
            case 0:
                long timeBefore = System.nanoTime();
                Array_Of_Sets[0] = new OpenHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                long difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure OpenHashset " +
                        "the time is " + difference / 1000000);
                return;


            case 1:
                timeBefore = System.nanoTime();
                Array_Of_Sets[0] = new ClosedHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure ClosedHashset " +
                        "the time is " + difference / 1000000);
                return;

            case 2:
                Array_Of_Sets[2] = new CollectionFacadeSet(new TreeSet<String>());
                timeBefore = System.nanoTime();
                for (String string : data) {
                    Array_Of_Sets[2].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset " +
                        "the time is " + difference / 1000000);
                return;

            case 3:
                Array_Of_Sets[3] = new CollectionFacadeSet(new LinkedList<String>());
                timeBefore = System.nanoTime();
                for (String string : data) {
                    Array_Of_Sets[3].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist " +
                        "the time is " + difference / 1000000);
                return;

            case 4:
                Array_Of_Sets[4] = new CollectionFacadeSet(new HashSet<String>());
                timeBefore = System.nanoTime();
                for (String string : data) {
                    Array_Of_Sets[4].add(string);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Hashset " +
                        "the time is " + difference / 1000000);
                return;
        }
        }

    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test3(int i){
        System.out.println("Test number 3 (Contains hi in data1.txt)");
        String[] data1=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data1.txt");
        switch (i) {
            case 0:
                Array_Of_Sets[0]=new OpenHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test1);
                }
                long timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test1);
                }
                long difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure OpenHashset "+
                        "the time is " + difference/70000 );
                return;

            case 1:
                Array_Of_Sets[1]=new ClosedHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test1);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure ClosedHashset "+
                        "the time is " + difference / 70000);
                return;

            case 2:
                Array_Of_Sets[2]=new CollectionFacadeSet(new TreeSet<String>());
                for(String string:data1){
                    Array_Of_Sets[2].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test1);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset "+
                        "the time is " + difference / 70000);
                return;

            case 3:
                Array_Of_Sets[3]=new CollectionFacadeSet(new LinkedList<String>());
                for(String string:data1){
                    Array_Of_Sets[3].add(string);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<700;j++){
                    Array_Of_Sets[3].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist "+
                        "the time is " + difference / 700);
                return;

            case 4:
                Array_Of_Sets[4]=new CollectionFacadeSet(new HashSet<String>());
                for(String string:data1){
                Array_Of_Sets[4].add(string);
            }
            for (int j=0;j<70000;j++){
                Array_Of_Sets[4].contains(string_to_test1);
            }
            timeBefore = System.nanoTime();
            for (int j=0;j<70000;j++){
                Array_Of_Sets[4].contains(string_to_test1);
            }
            difference = System.nanoTime() - timeBefore;

            System.out.println("For data structure Hashset "+
                    "the time is " + difference / 70000);
            return;
            }
        }


    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test4(int i){
        System.out.println("Test number 4 (Contains 1317089015)");
        String[] data1=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data1.txt");
        switch (i) {
            case 0:
                Array_Of_Sets[0]=new OpenHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test2);
                }
                long timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test2);
                }
                long difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure OpenHashset "+
                        "the time is " + difference/70000 );
                return;


            case 1:
                Array_Of_Sets[1]=new ClosedHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data1.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test2);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test2);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure ClosedHashset "+
                        "the time is " + difference / 70000);
                return;

            case 2:
                Array_Of_Sets[2]=new CollectionFacadeSet(new TreeSet<String>());
                for(String string:data1){
                    Array_Of_Sets[2].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test2);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test2);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset "+
                        "the time is " + difference / 70000);
                return;

            case 3:
                Array_Of_Sets[3]=new CollectionFacadeSet(new LinkedList<String>());
                for(String string:data1){
                    Array_Of_Sets[3].add(string);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<700;j++){
                    Array_Of_Sets[3].contains(string_to_test2);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist "+
                        "the time is " + difference / 700);
                return;

            case 4:
                Array_Of_Sets[4]=new CollectionFacadeSet(new HashSet<String>());
                for(String string:data1){
                    Array_Of_Sets[4].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test2);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test2);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Hashset "+
                        "the time is " + difference / 70000);
                return;
            }
        }


    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test5(int i){
        System.out.println("Test number 5 (Contains 23)");
        String[] data1=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data2.txt");
        switch (i) {
            case 0:
                Array_Of_Sets[0]=new OpenHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test3);
                }
                long timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test3);
                }
                long difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure OpenHashset "+
                        "the time is " + difference/70000 );
                return;


            case 1:
                Array_Of_Sets[1]=new ClosedHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test3);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test3);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure ClosedHashset "+
                        "the time is " + difference / 70000);
                return;

            case 2:
                Array_Of_Sets[2]=new CollectionFacadeSet(new TreeSet<String>());
                for(String string:data1){
                    Array_Of_Sets[2].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test3);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test3);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset "+
                        "the time is " + difference / 70000);
                return;

            case 3:
                Array_Of_Sets[3]=new CollectionFacadeSet(new LinkedList<String>());
                for(String string:data1){
                    Array_Of_Sets[3].add(string);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<700;j++){
                    Array_Of_Sets[3].contains(string_to_test3);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist "+
                        "the time is " + difference / 700);
                return;

            case 4:
                Array_Of_Sets[4]=new CollectionFacadeSet(new HashSet<String>());
                for(String string:data1){
                    Array_Of_Sets[4].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test3);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test3);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Hashset "+
                        "the time is " + difference / 70000);
                return;
        }
        }

    /**
     * perform i'th test for time measurement analysis (whereas i is the number next to
     * the word test in the method's name)
     * @param i the number that represents the data structure to perform the test on
     * openhashset=1,closedhashset=2,Treeset=3,linkedlist=4,Hashset=5
     */

    private void test6(int i){
        System.out.println("Test number 6 (Contains hi in data2.txt)");
        String[] data1=Ex4Utils.file2array("C:/Users/Eli/IdeaProjects/School/src/data2.txt");
        switch (i) {
            case 0:
                Array_Of_Sets[0]=new OpenHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test1);
                }
                long timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[0].contains(string_to_test1);
                }
                long difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure OpenHashset "+
                        "the time is " + difference/70000 );
                return;


            case 1:
                Array_Of_Sets[1]=new ClosedHashSet(Ex4Utils.file2array
                        ("C:/Users/Eli/IdeaProjects/School/src/data2.txt"));
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test1);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[1].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure ClosedHashset "+
                        "the time is " + difference / 70000);
                return;

            case 2:
                Array_Of_Sets[2]=new CollectionFacadeSet(new TreeSet<String>());
                for(String string:data1){
                    Array_Of_Sets[2].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test1);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[2].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Treeset "+
                        "the time is " + difference / 70000);
                return;

            case 3:
                Array_Of_Sets[3]=new CollectionFacadeSet(new LinkedList<String>());
                for(String string:data1){
                    Array_Of_Sets[3].add(string);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<700;j++){
                    Array_Of_Sets[3].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Linkedlist "+
                        "the time is " + difference / 700);
                return;

            case 4:
                Array_Of_Sets[4]=new CollectionFacadeSet(new HashSet<String>());
                for(String string:data1){
                    Array_Of_Sets[4].add(string);
                }
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test1);
                }
                timeBefore = System.nanoTime();
                for (int j=0;j<70000;j++){
                    Array_Of_Sets[4].contains(string_to_test1);
                }
                difference = System.nanoTime() - timeBefore;

                System.out.println("For data structure Hashset "+
                        "the time is " + difference / 70000);
                return;
        }
        }
}
