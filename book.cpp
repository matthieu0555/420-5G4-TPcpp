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
    if (this->isAvailable == false) {
        cout << "Le livre n'est pas disponible" << endl;
    } else if (!this->borrowerId.empty()) {
        std::cout << "Le livre est déja emprunté" << std::endl;
    } else {
        this->borrowerId = borrowerId;
        this->isAvailable = false;
    }
}

void Book::returnBook() {
    this->borrowerId = "";
    this->isAvailable = true;
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

    if (!this->borrowerId.empty()) {
        user = "|" + this->borrowerId;
    }

    return this->title + "|" + this->author  + "|" + this->isbn + "|" + isAvailable + user;
};

void Book::fromFileFormat(const string& line) {
    std::string delimiter = "|";

    int debutPosition = 0;
    int finPosition = line.find('|');
    std::string title = line.substr(debutPosition, finPosition - debutPosition); //2e argument = longeur plutot que position de fin

    debutPosition = finPosition + 1; //position apres le "|" trouvé
    finPosition = line.find(delimiter, debutPosition);
    std::string author = line.substr(debutPosition, finPosition - debutPosition);
    
    debutPosition = finPosition + 1; //position apres le "|" trouvé
    finPosition = line.find(delimiter, debutPosition);
    std::string isbn = line.substr(debutPosition, finPosition - debutPosition);

    debutPosition = finPosition + 1; //position apres le "|" trouvé
    finPosition = line.find(delimiter, debutPosition);
    std::string availability;

    if (finPosition == -1) {
        availability = line.substr(debutPosition);   // jusqu'à la fin
    } else {
        availability = line.substr(debutPosition, finPosition - debutPosition);
    }

    std::string userId = "";

    // -1 = pas d'emprunteur assigné
    if (finPosition != -1) {
        userId = line.substr(finPosition + 1);
    }

    setTitle(title);
    setAuthor(author);
    setISBN(isbn);
    setAvailability(availability == "1");
    setBorrowerId(userId);
}