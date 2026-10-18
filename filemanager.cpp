#include <fstream>
#include <iostream>
#include <filesystem>
#include "filemanager.h"

using namespace std;

// Constructor
FileManager::FileManager(const string &booksFile, const string &usersFile)
    : booksFileName(booksFile), usersFileName(usersFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library &library)
{
    if (booksFileName.empty() || usersFileName.empty())
    {
        cout << "Erreur : Impossible de sauvegarder, car le nom d'un des fichier de sauvegarde est vide\n";
        return false;
    }
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library &library)
{
    bool booksLoaded = loadBooksFromFile(library);
    bool usersLoaded = loadUsersFromFile(library);
    return booksLoaded || usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library &library)
{
    ofstream file(booksFileName);
    if (!file.is_open())
    {
        cout << "Erreur : Impossible d'ouvrir " << booksFileName << " en écriture.\n";
        return false;
    }

    auto books = library.getAllBooks();
    for (Book *book : books)
    {
        file << book->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library &library)
{
    ofstream file(usersFileName);
    if (!file.is_open())
    {
        cout << "Erreur : Impossible d'ouvrir " << usersFileName << " en écriture.\n";
        return false;
    }

    auto users = library.getAllUsers();
    for (User *user : users)
    {
        file << user->toFileFormat() << "\n";
    }

    file.close();
    return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library &library)
{
    ifstream file(booksFileName);
    if (!file.is_open())
    {
        cout << "Aucun fichier de livres existant trouvé. Démarrage avec une bibliothèque vide.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            Book book;
            book.fromFileFormat(line);
            library.addBook(book);
            count++;
        }
    }

    file.close();
    cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library &library)
{
    ifstream file(usersFileName);
    if (!file.is_open())
    {
        cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans utilisateurs enregistrés.\n";
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line))
    {
        if (!line.empty())
        {
            User user;
            user.fromFileFormat(line);
            library.addUser(user);
            count++;
        }
    }

    file.close();
    cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
    return true;
}

void FileManager::logActivity(const string& action, const string& details) {
    if (booksFileName.empty() || usersFileName.empty()) {
        //cout << "Erreur : Écriture du journal impossible, car les fichier book.txt et users.txt sont vide\n";
        //  J'ai fais expres de laisser la fonction sans truc car le message était répétitif.
        return;   //pas de -d, donc pas de journal
    }

    filesystem::path chemin = filesystem::path(booksFileName).parent_path() / "journal.log";
    ofstream file(chemin, ios::app);

     if (!file.is_open()) { // Es que le fichier est ouvert?
        cout << "Erreur : Impossible d'ouvrir le journal " << chemin << ".\n";
        return;
    }

    
    time_t maintenant = time(nullptr);
    char horodatage[20];
    strftime(horodatage, sizeof(horodatage), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    file << horodatage << " - [" << action << "] " << details << "\n";
}


// Check if file exists
bool FileManager::fileExists(const string &filename)
{
    ifstream file(filename);
    return file.good();
}


// Create backup
void FileManager::createBackup()
{
    if (booksFileName.empty() || usersFileName.empty())
    {
        cout << "Erreur : sauvegarde impossible, aucun répertoire de données (--data-dir) n'a été spécifié.\n";
    }
    else
    {
        if (fileExists(booksFileName))
        {
            filesystem::copy_file(booksFileName, booksFileName + ".backup", filesystem::copy_options::overwrite_existing);
        }

        if (fileExists(usersFileName))
        {
            filesystem::copy_file(usersFileName, usersFileName + ".backup", filesystem::copy_options::overwrite_existing);
        }

        cout << "Fichiers de sauvegarde créés.\n";
    }
}