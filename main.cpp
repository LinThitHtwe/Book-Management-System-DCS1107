#include <iostream>
#include <fstream>
#include <iomanip>
// #include <stdlib.h>

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
void DisplayLoginSuccessfulBanner();
void DisplayBackToMenuBanner();
void DisplayProgramQuitBanner();
void DisplayAdminMenu();
void AddBook();
void DisplayBooks();
void DisplayLogoutSuccessfulBanner();
int getLatestBookID();

main()
{
    int choice;
    bool isLogin = false, shouldQuitProgram = false;
    displayWelcomeBanner();
    while (!shouldQuitProgram)
    {

        displayOptionsMenu();
        do
        {
            cout << "Please enter your choice (0, 1, 2 or 3): ";
            cin >> choice;

            if (choice != 0 && choice != 1 && choice != 2 && choice != 3)
            {
                cout << "Invalid choice. Please try again." << endl;
            }
            else if (choice == 3)
            {
                shouldQuitProgram = true;
                system("cls");
                DisplayProgramQuitBanner();
                break;
            }
            else
            {
                isLogin = true;
            }
        } while (choice != 0 && choice != 1 && choice != 2 && choice != 3);

        while (isLogin)
        {
            system("cls");
            DisplayLoginSuccessfulBanner();
            DisplayAdminMenu();
            do
            {
                cout << "Please enter your choice (0, 1, 2 or 3): ";
                cin >> choice;

                if (choice != 0 && choice != 1 && choice != 2 && choice != 3)
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 0 && choice != 1 && choice != 2 && choice != 3);
            cout << endl;
            system("cls");

            // Display Book
            if (choice == 0)
            {
                DisplayBooks();
                DisplayBackToMenuBanner();
                do
                {
                    cin >> choice;

                    if (choice != 0 && choice != 1 && choice != 2)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 0 && choice != 1 && choice != 2);
                system("cls");
            }
            // Add Book
            else if (choice == 1)
            {
                AddBook();
                DisplayBackToMenuBanner();
                do
                {
                    cin >> choice;

                    if (choice != 0 && choice != 1 && choice != 2)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 0 && choice != 1 && choice != 2);
                system("cls");
            }

            else if (choice == 3)
            {
                isLogin = false;
                DisplayLogoutSuccessfulBanner();
                break;
            }
        }
    }
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

void DisplayLoginSuccessfulBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                   L O G I N   S U C C E S S F U L                ||" << endl;
    cout << "||                          W E L C O M E !                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayLogoutSuccessfulBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                   L O G O U T   S U C C E S S F U L              ||" << endl;
    cout << "||                          W E L C O M E !                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayProgramQuitBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||               P R O G R A M   S U C C E S S F U L L Y            ||" << endl;
    cout << "||                           Q U I T !                              ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void displayOptionsMenu()
{
    cout << "============================= MENU ===================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Login                                                       ||" << endl;
    cout << "||  [1] Sign Up                                                     ||" << endl;
    cout << "||  [2] Forget Password                                             ||" << endl;
    cout << "||  [3] Quit Program                                                ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayAdminMenu()
{
    cout << "========================== ADMIN MENU ================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Book Lists                                                  ||" << endl;
    cout << "||  [1] Add Book                                                    ||" << endl;
    cout << "||  [2] Sales Report                                                ||" << endl;
    cout << "||  [3] Logout Program                                              ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayBackToMenuBanner()
{
    cout << "\n";
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "======================================================================+" << endl;
    ;
    cout << "Enter your choice: ";
}

void DisplayBooks()
{
    struct Book books[100];
    int i = 0;
    ifstream read;

    read.open("books.txt");

    if (read.fail())
    {
        cout << "Error opening books file." << endl;
        return;
    }

    while (!read.eof())
    {
        read >> books[i].id;
        read.ignore();
        read.getline(books[i].title, 100);
        read.getline(books[i].author, 100);

        read >> books[i].quantity;
        read >> books[i].price;
        read.ignore();

        i++;
    }
    cout << "============================= BOOK LIST ===============================" << endl;
    cout
        << setw(6) << "ID"
        << setw(25) << "Title"
        << setw(20) << "Author"
        << setw(10) << "Qty"
        << setw(10) << "Price" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        cout
            << setw(6) << books[j].id
            << setw(25) << books[j].title
            << setw(20) << books[j].author
            << setw(10) << books[j].quantity
            << fixed << setprecision(2)
            << setw(10) << books[j].price << endl;
    }

    cout << "-----------------------------------------------------------------------" << endl
         << endl;
}

void AddBook()
{
    ofstream write;
    struct Book book;
    ifstream read;
    read.open("books.txt");

    cout << "============================= ADD BOOK ===============================" << endl;

    //    do
    //    {
    //        cout << "Enter book ID: ";
    //        cin >> book.id;
    //        if (book.id < 0)
    //        {
    //            cout << "Invalid input. Please enter a positive integer for book ID." << endl;
    //        }
    //    } while (book.id < 1);

    book.id = getLatestBookID() + 1;

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

    bool isFileEmpty = read.peek() == EOF;

    if (!isFileEmpty)
    {
        write << "\n";
    }

    write << book.id << "\n"
          << book.title << "\n"
          << book.author << "\n"
          << book.quantity << "\n"
          << book.price;

    write.close();

    cout << "Book added successfully!" << endl;
}

int getLatestBookID()
{
    ifstream read("books.txt");
    Book book;
    int latestId = 1;

    while (read >> book.id)
    {
        read.ignore();
        read.getline(book.title, 100);
        read.getline(book.author, 100);
        read >> book.quantity;
        read >> book.price;
        read.ignore();

        latestId = book.id;
    }

    read.close();
    return latestId;
}