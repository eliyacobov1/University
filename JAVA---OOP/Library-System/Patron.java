@SuppressWarnings("WeakerAccess")
public class Patron {
    // class
    String FirstName;
    String LastName;
    int comicTendency;
    int dramaticTendency;
    int educationalTendency;
    int EnjoymentThreshold;
    int id;
    int NumBooksBorrowed;

    Patron(String patronFirstName, String patronLastName, int comicTendency
            , int dramaticTendency, int educationalTendency, int patronEnjoymentThreshold){
        //creates a new patron with the given data
        this.FirstName=patronFirstName;
        this.comicTendency=comicTendency;
        this.LastName=patronLastName;
        this.dramaticTendency=dramaticTendency;
        this.educationalTendency=educationalTendency;
        this.EnjoymentThreshold=patronEnjoymentThreshold;
        this.NumBooksBorrowed=0;
        this.id=0;
    }

    int getBookScore(Book book) {
        //Returns the literary value this patron assigns to the given book.
        return (book.getComicValue()*comicTendency+book.getDramaticValue()*dramaticTendency
                +book.getEducationalValue()*educationalTendency);
    }

    String stringRepresentation() {
        //Returns a string representation of the patron,
        //which is a sequence of its first and last name, separated by a single white space.
        return (FirstName+" "+LastName);
    }

    boolean willEnjoyBook(Book book) {
        //Returns true of this patron will enjoy the given book, false otherwise.
        return(getBookScore(book)>=EnjoymentThreshold);
    }

    int getPatronId() {
        //return id of the patron
        return id;
    }

    void setPatronId(int patronId) {
        //return id of the book
        id=patronId;
    }

    void take_another_book(){
        //adds another book to the number of borrowed book by the patron
        NumBooksBorrowed++;
    }

    void return_book(){
        //returns a book by decreasing the number of books borrowed by 1(for this specific patron)
        NumBooksBorrowed--;
    }

}
