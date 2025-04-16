#include <iostream>
#include <fstream>

using namespace std;

#define BOOK_FILE "books.txt"

struct Book
{
    char title[100], author[100];
    int id, quantity;
    double price;
};

void displayWelcomeBanner();
void displayOptionsMenu();
void AddBook();
// void DisplayBooks();

main()
{

    int choice;
    displayWelcomeBanner();
    displayOptionsMenu();
    do
    {
        cout << "Please enter your choice (0, 1, or 2): ";
        cin >> choice;

        if (choice != 0 && choice != 1 && choice != 2)
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0 && choice != 1 && choice != 2);

    AddBook();

    // DisplayBooks();
}

void displayWelcomeBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                          W E L C O M E !                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void displayOptionsMenu()
{
    int choice;

    cout << "============================= MENU ===================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Login                                                       ||" << endl;
    cout << "||  [1] Sign Up                                                     ||" << endl;
    cout << "||  [2] Forget Password                                             ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

// void DisplayBooks()
// {
//     struct Book books[100];
//     int i = 0, j;
//     ifstream read;

//     read.open("books.txt");

//     while (!read.eof())
//     {
//         read >> books[i].id;
//         read >> books[i].title;
//         read >> books[i].author;
//         read >> books[i].quantity;
//         read >> books[i].price;

//         i++;
//     }

//     int size = i;

//     cout << "============================= BOOK LIST ===============================" << endl;
//     cout << "ID\tTitle\t\tAuthor\t\tQuantity\tPrice" << endl;
//     cout << "----------------------------------------------------------------------" << endl;

//     for (j = 0; j < 2; j++)
//     {
//         cout << books[j].id << "\t"
//              << books[j].title << "\t"
//              << books[j].author << "\t"
//              << books[j].quantity << "\t\t"
//              << books[j].price << endl;
//     }

//     read.close();
// }

void AddBook()
{
    ofstream write;
    struct Book book;

    cout << "============================= ADD BOOK ===============================" << endl;

    do
    {
        cout << "Enter book ID: ";
        cin >> book.id;
        if (book.id < 0)
        {
            cout << "Invalid input. Please enter a positive integer for book ID." << endl;
            cin.clear();
        }
    } while (book.id < 1);

    do
    {
        cout << "Enter book title: ";
        cin.ignore();
        cin.getline(book.title, 100);
        if (book.title[0] == '\0')
        {
            cout << "Title cannot be empty." << endl;
        }
    } while (book.title[0] == '\0');

    do
    {
        cout << "Enter book author: ";
        cin.getline(book.author, 100);
        if (book.author[0] == '\0')
        {
            cout << "Author name cannot be empty." << endl;
        }
    } while (book.author[0] == '\0');

    do
    {
        cout << "Enter book quantity: ";
        cin >> book.quantity;
        if (book.quantity < 1)
        {
            cout << "Invalid input. Please enter a non-negative integer for quantity." << endl;
        }
    } while (book.quantity < 1);

    do
    {
        cout << "Enter book price: ";
        cin >> book.price;
        if (book.price < 1)
        {
            cout << "Invalid input. Please enter a non-negative number for price." << endl;
        }
    } while (book.price < 1);

    write.open(BOOK_FILE, ios::app);

    write << book.id << "\t" << book.title << "\t"
          << book.author << "\t" << book.quantity << "\t"
          << book.price << endl;
    write.close();

    cout << "Book added successfully!" << endl;
}

int getLatestBookID()
{
    ifstream read;
    read.open("books.txt");

    return 1001;
}