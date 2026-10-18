#include <iostream>
#include <algorithm>

#include "library.h"

using namespace std;
#include <limits>

// Constructor
Library::Library() {}

// Add book to library
void Library::addBook(const Book &book)
{
    books.push_back(make_unique<Book>(book));
}

// Remove book from library
bool Library::removeBook(const string &isbn)
{
    auto it = find_if(books.begin(), books.end(),
                      [&isbn](const unique_ptr<Book> &book)
                      {
                          return book->getISBN() == isbn;
                      });

    if (it != books.end())
    {
        books.erase(it);
        return true;
    }
    return false;
}

// Find book by ISBN
Book *Library::findBookByISBN(const string &isbn)
{
    auto it = find_if(books.begin(), books.end(),
                      [&isbn](const unique_ptr<Book> &book)
                      {
                          return book->getISBN() == isbn;
                      });

    return (it != books.end()) ? it->get() : nullptr;
}

// Search books by title (case-insensitive partial match)
vector<Book *> Library::searchBooksByTitle(const string &title)
{
    vector<Book *> results;
    string lowerTitle = title;
    transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

    for (auto &book : books)
    {
        string bookTitle = book->getTitle();
        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);

        if (bookTitle.find(lowerTitle) != string::npos)
        {
            results.push_back(book.get());
        }
    }
    return results;
}

// Search books by author (case-insensitive partial match)
vector<Book *> Library::searchBooksByAuthor(const string &author)
{
    vector<Book *> results;
    string lowerAuthor = author;
    transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);

    for (auto &book : books)
    {
        string bookAuthor = book->getAuthor();
        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);

        if (bookAuthor.find(lowerAuthor) != string::npos)
        {
            results.push_back(book.get());
        }
    }
    return results;
}

// Get all available books
vector<Book *> Library::getAvailableBooks()
{
    vector<Book *> available;
    for (auto &book : books)
    {
        if (book->getAvailability())
        {
            available.push_back(book.get());
        }
    }
    return available;
}

// Get all books
vector<Book *> Library::getAllBooks()
{
    vector<Book *> allBooks;
    for (auto &book : books)
    {
        allBooks.push_back(book.get());
    }
    return allBooks;
}

// Add user to library
void Library::addUser(const User &user)
{
    users.push_back(make_unique<User>(user));
}

string Library::generateUserId()
{
    int maxId = 0;
    string UserId = "USR";

    for (auto &user : users)
    {
        string id = user->getUserId();
        if (id.size() > 3 && id.substr(0, 3) == "USR")
        { // es que le id a plus que 3 caractere + verifie que les premiers 3 character sont USR
            string nombre = id.substr(3);

            int n = stoi(nombre);
            if (maxId < n)
            {
                maxId = n;
            }
        }
    }

    maxId++;

    if (maxId < 10)
    {
        UserId.append("00" + to_string(maxId));
    }
    else if (maxId < 100)
    {
        UserId.append("0" + to_string(maxId));
    }
    else
    {
        UserId.append(to_string(maxId));
    }

    return UserId;
}

// Find user by ID
User *Library::findUserById(const string &userId)
{
    auto it = find_if(users.begin(), users.end(),
                      [&userId](const unique_ptr<User> &user)
                      {
                          return user->getUserId() == userId;
                      });

    return (it != users.end()) ? it->get() : nullptr;
}

// Get all users
vector<User *> Library::getAllUsers()
{
    vector<User *> allUsers;
    for (auto &user : users)
    {
        allUsers.push_back(user.get());
    }
    return allUsers;
}

// Check out book
bool Library::checkOutBook(const string &isbn, const string &userId)
{
    Book *book = findBookByISBN(isbn);
    User *user = findUserById(userId);

    if (book && user && book->getAvailability())
    {
        book->checkOut(user->getUserId());
        user->borrowBook(isbn);
        return true;
    }
    return false;
}

// Return book
bool Library::returnBook(const string &isbn)
{
    Book *book = findBookByISBN(isbn);

    if (book && !book->getAvailability())
    {
        // Find the user who borrowed this book
        for (auto &user : users)
        {
            if (user->hasBorrowedBook(isbn))
            {
                user->returnBook(isbn);
                break;
            }
        }
        book->returnBook();
        return true;
    }
    return false;
}

// Display all books
void Library::displayAllBooks()
{
    if (books.empty())
    {
        cout << "Aucun livre dans la bibliothèque.\n";
        return;
    }

    vector<Book *> livres = Library::getAllBooks();
    int choix = -1;

    while (choix != 1 && choix != 2) {
        cout << "Trier les livres par auteur ou par titre?" << endl;
        cout << "Choix 1: Titre" << endl;
        cout << "Choix 2: Auteur" << endl;
    
        if (!(cin >> choix)) { //Protection comme dans le main (code copier collé du main.cpp dans la boucle)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choix = -1;
          }
    }

    if (choix == 1)
    {
            sort(livres.begin(), livres.end(), [](Book *a, Book *b)
             { return a->getTitle() < b->getTitle(); });
    } else {

        sort(livres.begin(), livres.end(), [](Book *a, Book *b)
            { if (a->getAuthor() != b->getAuthor()) {
             return a->getAuthor() < b->getAuthor();
         }
         return a->getTitle() < b->getTitle(); //Si les auteurs ont le meme nom, jvais trier par titre
            });
    }

    cout << "\n=== TOUS LES LIVRES TRIÉ PAR " << (choix == 1 ? "TITRE" : "AUTEUR") << " ===\n";
    for (size_t i = 0; i < livres.size(); ++i)
    {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << livres[i]->toString() << "\n";
        cout << "-------------------------\n";
    }
}

// Display available books
void Library::displayAvailableBooks()
{
    auto available = getAvailableBooks();

    if (available.empty())
    {
        cout << "Aucun livre disponible pour emprunt.\n";
        return;
    }

    cout << "\n=== LIVRES DISPONIBLES ===\n";
    for (size_t i = 0; i < available.size(); ++i)
    {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << available[i]->toString() << "\n";
        cout << "---------------------------\n";
    }
}

// Display all users
void Library::displayAllUsers()
{
    if (users.empty())
    {
        cout << "Aucun utilisateur enregistré.\n";
        return;
    }

    cout << "\n=== TOUS LES UTILISATEURS ===\n";
    for (size_t i = 0; i < users.size(); ++i)
    {
        cout << "\nUtilisateur " << (i + 1) << " :\n";
        cout << users[i]->toString() << "\n";
        cout << "------------------------------\n";
    }
}

// Statistics
int Library::getTotalBooks() const { return books.size(); }
int Library::getAvailableBookCount() const
{
    return count_if(books.begin(), books.end(),
                    [](const unique_ptr<Book> &book)
                    {
                        return book->getAvailability();
                    });
}
int Library::getCheckedOutBookCount() const { return getTotalBooks() - getAvailableBookCount(); }