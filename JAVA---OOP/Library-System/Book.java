@SuppressWarnings("WeakerAccess")
public class Book {

    String title;
    String author;
    int Publication;
    int ComicValue;
    int DramaticValue;
    int EducationalValue;
    Library library;
    int id;
    int patron_id;

    public Book(String bookTitle, String bookAuthor, int bookYearOfPublication, int bookComicValue, int bookDramaticValue
            ,int bookEducationalValue){
        //creates a new book with the given data
        this.title=bookTitle;
        this.author=bookAuthor;
        this.Publication=bookYearOfPublication;
        this.ComicValue=bookComicValue;
        this.DramaticValue=bookDramaticValue;
        this.EducationalValue=bookEducationalValue;
        this.patron_id=-1;
        this.id=-1;

    }

    int getCurrentBorrowerId(){
        // return current borrower id,if there is no borrower returns 0
            return patron_id;
    }

    int	getLiteraryValue() {
        //return literary value which is defined by the sum of all values of the book
        return (this.DramaticValue + this.EducationalValue + this.ComicValue);
    }

    void returnBook() {
        //Marks this book as returned,sets borrower id to -1
        patron_id=-1;
    }

    void setBorrowerId(int borrowerId){
        patron_id=borrowerId;
    }

    String	stringRepresentation(){
        //prints a string representation of the books traits
        return("["+title+","+author+","+Publication+','+getLiteraryValue()+']');
    }

    int getComicValue(){
        //return comic value of the book
        return ComicValue;
    }

    int getEducationalValue(){
        //return Educational value of the book
        return EducationalValue;
    }

    int getDramaticValue() {
        //return Educational value of the book
        return DramaticValue;
    }

    void setBookId(int bookId) {
        //return id of the book
        id=bookId;
    }

    int getBookId() {
        //return id of the book
        return id;
    }

    int getPatronId(){
        //return id of the book
        return patron_id;
    }

}
