@SuppressWarnings("WeakerAccess")
public class Library {

    int maxBookCapacity;
    int maxBorrowedBooks;
    int maxPatronCapacity;
    Book[] book_list;
    Patron[] patron_list;
    int patron_count;
    int book_count;

    Library(int maxBookCapacity, int maxBorrowedBooks, int maxPatronCapacity){
        //creates a new library with the given data
        this.maxBookCapacity=maxBookCapacity;
        this.maxBorrowedBooks=maxBorrowedBooks;
        this.maxPatronCapacity=maxPatronCapacity;
        this.book_list=new Book[maxBookCapacity];
        this.patron_list=new Patron[maxPatronCapacity];
        this.patron_count=0;
        this.book_count=0;
    }

    int	addBookToLibrary(Book book) {
        //Adds the given book to this library, if there is place available, and it isn't already in the library.
        //if successful returns book id else returns -1
        //see if the library is not full and if can add more books
        //if there is an attempt to add an existing book,returns the id of the book without adding another copy
        for (Book b : book_list) {
            //first checks if book is already in the list,if so,returns its id without adding another copy
            if (b == book) {
                return b.getBookId();
            }
        }
        if (book_count < maxBookCapacity) {
            //else,adds book to the list after checking that there is room
            book_list[book_count] = book;
            book_count++;
            book.setBookId(book_count);
            return book.getBookId();

        } else {
            return -1;
        }
    }

    boolean	borrowBook(int bookId, int patronId) {
        //Marks the book with the given id number as borrowed by the patron with the given patron id
        // , if this book is available, the given patron isn't already
        // borrowing the maximal number of books allowed, and if the patron will enjoy this book.
        if (isPatronIdValid(patronId) && isBookIdValid(bookId)) {
            Patron p = patron_list[patronId - 1];
            Book b = book_list[bookId - 1];
            if (p.NumBooksBorrowed < maxBorrowedBooks) {
                if (b.getPatronId() == -1 && p.willEnjoyBook(b)) {
                    b.setBorrowerId(patronId);
                    p.take_another_book();
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }

        } else {
            return false;
        }
    }

    int	getBookId(Book book) {
        //Returns the non-negative id number of the given book if he is owned by this library, -1 otherwise
        return book.getBookId();
    }

    int getPatronId(Patron patron) {
        //Returns the non-negative id number of the given patron if he is registered to this library, -1 otherwise.
        return patron.getPatronId();
    }

    boolean	isBookAvailable(int bookId) {
        //Returns true if the book with the given id is available, false otherwise.
        //checks if book exists in list and then if it is owned by a certain patron.
        // if not,it will considered as available
        if (book_count >= bookId) {
            return (book_list[bookId - 1].getPatronId() == -1);
        }
        else{
            return false;
        }
    }

    boolean	isBookIdValid(int bookId) {
        //Returns true if the given number is an id of some book in the library, false otherwise.
        return (book_count >= bookId && bookId>0);
    }

    boolean	isPatronIdValid(int patronId) {
        //Returns true if the given number is an id of a patron in the library, false otherwise.
        return (patron_count >= patronId && patronId>0);
    }

    int	registerPatronToLibrary(Patron patron) {
        //Registers the given Patron to this library, if there is a spot available.
        //returns a non-negative id number for the patron if there was a spot and the patron was
        // successfully registered, -1 otherwise.
        for (Patron p : patron_list) {
            //first checks if patron is already in the list,if so,returns -1 without adding him again
            if (p == patron) {
                return p.getPatronId();
            }
        }

        if(patron_count<maxPatronCapacity){
            patron_list[patron_count]=patron;
            patron_count++;
            patron.setPatronId(patron_count);
            return patron.getPatronId();
        }
        else {
            return -1;
        }
    }

    void returnBook(int bookId) {
        //Return the given book by setting the patron_id to 0
        //finds the patron to which the book belonged to and subtracts 1 from the number of books he has
        //first checks for the case in which the book is already available and has no owner
        if (book_list[bookId-1].getPatronId()!=-1){
            int patronId = book_list[bookId - 1].getPatronId();
            patron_list[patronId - 1].return_book();
            //sets borrower id as 0 (which is the number representing the absence of an owner)
            book_list[bookId - 1].setBorrowerId(-1);
        }
    }

    Book suggestBookToPatron(int patronId) {
        //Suggest the patron with the given id the book he will enjoy the most,
        // out of all available books he will enjoy, if any such exist.If patronId does not
        //belong to the library,will return a null book.If max level of enjoyment is equal for numerous
        //books,returns the last one in the list with that level of enjoyment (also true for 0 book score)
        //first checks if patron id is valid
        if(!isPatronIdValid(patronId)){
            return null;
        }
        int max_enjoyment = 0;
        Patron p1 = patron_list[patronId-1];
        Book b1=null;
        if (p1 == null) {
            return b1;
            }
        //checks all available books to check max level of enjoyment using the variable defined above
        for(Book b:book_list){
            if (p1.getBookScore(b)>=max_enjoyment && p1.willEnjoyBook(b)
                    && b.getPatronId()==-1){
                max_enjoyment=p1.getBookScore(b);
                b1=b;
            }
        }
        return b1;

    }
}
