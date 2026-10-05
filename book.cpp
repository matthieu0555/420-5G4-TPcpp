#include "book.h"

using namespace std;

// premier constructeur
Book::Book() {

}

// deuxieme constructeur
Book::Book(const string& title, const string& author, const string& isbn) {
    Book::setTitle(title);
    Book::setAuthor(author);
    Book::setISBN(isbn);
}

// getters

string Book::getTitle() const {
    return Book::title;
}

string Book::getAuthor() const {
    return Book::author;
}

string Book::getISBN() const {
    return Book::isbn;
}

bool Book::getAvailability() const {
    return Book::isAvailable;
}

string Book::getBorrowerId() const {
    return Book::borrowerId;
}

// setters

void Book::setTitle(const string& title) {
    this->title = title;
}

void Book::setAuthor(const string& author) {
    this->author = author;
}

void Book::setISBN(const string& isbn) {
    this->isbn = isbn;
}

void Book::setAvailability(const bool available) {
    this->isAvailable = available;
}

void Book::setBorrowerId(const string& borrowerId) {
    this->borrowerId = borrowerId;
}

