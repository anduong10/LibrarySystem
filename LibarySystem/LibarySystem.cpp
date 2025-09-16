#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

const int ISBN_LENGTH = 13;
const int MIN_YEAR = 1900;
const int MAX_YEAR = 2024;
const string BOOKS_FILE = "books.txt";

struct Book {
    string Title;
    string Author;
    string ISBN;
    int yearPublished;
};

class Library {
public:
    vector<Book> books;

    static bool CompareByTitle(const Book& a, const Book& b) {
        return a.Title < b.Title;
    }

    static bool CompareByAuthor(const Book& a, const Book& b) {
        return a.Author < b.Author;
    }

    static bool CompareByISBN(const Book& a, const Book& b) {
        return a.ISBN < b.ISBN;
    }

    void addBook() {
        string title, author, isbn;
        int year;

        cin.ignore();

        while (true) {
            cout << "Enter title: ";
            getline(cin, title);

            cout << "Enter author: ";
            getline(cin, author);

            cout << "Enter ISBN (" << ISBN_LENGTH << " digits): ";
            getline(cin, isbn);

            cout << "Enter year published: ";
            cin >> year;

            if (isbn.length() != ISBN_LENGTH || year < MIN_YEAR || year > MAX_YEAR) {
                cout << "Invalid ISBN or year. Try again." << endl;
                continue;
            } else {
                break;
            }
        }

        books.push_back({title, author, isbn, year});

        ofstream file(BOOKS_FILE, ios::app);
        if (file.is_open()) {
            file << title << "," << author << "," << isbn << "," << year << "\n";
            file.close();
            cout << "Book added." << endl;
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void importBooks() {
        ifstream file(BOOKS_FILE);
        if (!file.is_open()) {
            cout << "Could not open file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            int commaCount = count(line.begin(), line.end(), ',');
            if (commaCount == 3) {
                cout << "Correct format: " << line << endl;
            } else {
                cout << "Incorrect format: " << line << endl;
            }
        }

        file.close();
    }


    void searchByTitle() {
        string title;
        cout << "Enter the title to search for: ";
        cin >> title;

        for (const Book& book : books) {
            if (book.Title == title) {
                cout << "Found: " << book.Title << " by " << book.Author
                     << ", ISBN: " << book.ISBN
                     << ", Year: " << book.yearPublished << endl;
                return;
            }
        }
        cout << "Title not found." << endl;
    }

    void searchByAuthor() {
        string author;
        cout << "Enter the author to search for: ";
        cin >> author;

        for (const Book& book : books) {
            if (book.Author == author) {
                cout << "Found: " << book.Title << " by " << book.Author
                     << ", ISBN: " << book.ISBN
                     << ", Year: " << book.yearPublished << endl;
                return;
            }
        }
        cout << "Author not found." << endl;
    }

    void searchByISBN() {
        string isbn;
        cout << "Enter the ISBN to search for: ";
        cin >> isbn;

        for (const Book& book : books) {
            if (book.ISBN == isbn) {
                cout << "Found: " << book.Title << " by " << book.Author
                     << ", ISBN: " << book.ISBN
                     << ", Year: " << book.yearPublished << endl;
                return;
            }
        }
        cout << "ISBN not found." << endl;
    }

    void sortByTitle() {
        sort(books.begin(), books.end(), CompareByTitle);
        cout << "Sorted Books by Title:" << endl;
        for (const Book& book : books) {
            cout << book.Title << " by " << book.Author
                 << ", ISBN: " << book.ISBN
                 << ", Year: " << book.yearPublished << endl;
        }
    }

    void sortByAuthor() {
        sort(books.begin(), books.end(), CompareByAuthor);
        cout << "Sorted Books by Author:" << endl;
        for (const Book& book : books) {
            cout << book.Author << " - Title: " << book.Title
                 << ", ISBN: " << book.ISBN
                 << ", Year: " << book.yearPublished << endl;
        }
    }

    void sortByISBN() {
        sort(books.begin(), books.end(), CompareByISBN);
        cout << "Sorted Books by ISBN:" << endl;
        for (const Book& book : books) {
            cout << book.ISBN << " - Title: " << book.Title
                 << ", Author: " << book.Author
                 << ", Year: " << book.yearPublished << endl;
        }
    }
};

int main() {
    Library lib;

    while (true){
        string option;
        cout <<"Type in 1 for importing a text file" << endl;
        cout << "Type in 2 for creating new text file" << endl;
        cout << "Type in 3 for searching for book by title" << endl;
        cout << "Type in 4 for searching for a book by Author" << endl;
        cout << "Type in 5 for searching for book by ISBN" << endl;
        cout << "Type in 6 for sorting book by title" << endl;
        cout << "Type in 7 for sorting a book by author" << endl;
        cout << "Type in 8 for sorting a book by ISBN" << endl;
        cout << "Type in 9 to quit" << endl;
        cin >> option;

        if (option == "1") {
            lib.importBooks();
        }
        else if (option == "2") {
            lib.addBook();
        }
        else if (option == "3") {
            lib.searchByTitle();
        }
        else if (option == "4") {
            lib.searchByAuthor();
        }
        else if (option == "5") {
            lib.searchByISBN();
        }
        else if (option == "6") {
            lib.sortByTitle();
        }
        else if (option == "7") {
            lib.sortByAuthor();
        }
        else if (option == "8") {
            lib.sortByISBN();
        }
        else if (option == "9") {
            cout << "Quitting..." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
