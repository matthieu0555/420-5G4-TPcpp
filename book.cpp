#include "book.h"

#include <iostream>

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

// Methods

void Book::checkOut(const string& borrowerId) {
    if (this->borrowerId.empty()) {
        this->borrowerId = borrowerId;
    } else {
        std::cout << "Le livre est déja emprunté" << std::endl;
    }
}

void Book::returnBook() {
    this->borrowerId = "";
}

string Book::toString() const {
    return this->title;
};

string Book::toFileFormat() const {
    string isAvailable = "0";
    string user = "";

    if (this->isAvailable) {
        isAvailable = "1";
    }

    if (this->borrowerId.empty()) {
        user = "|" + this->borrowerId;
    }

    return this->title + "|" + this->author  + "|" + this->isbn + "|" + isAvailable + user;
};

void Book::fromFileFormat(const string& line) {
    std::string delimiter = "|";
    int pos = 0;
    std::string title = line.substr(pos, line.find(delimiter));
    pos = line.find(delimiter);
    std::string author = line.substr(pos, line.find(delimiter)); 
    pos = line.find(delimiter, pos); //commence a partir de la derniere position
    std::string isbn = line.substr(0, line.find(delimiter)); 
    pos = line.find(delimiter, pos); //commence a partir de la derniere position
    std::string availability = line.substr(0, line.find(delimiter)); 
    pos = line.find(delimiter, pos); //commence a partir de la derniere position
    std::string userId = line.substr(0, line.find(delimiter)); 
}