#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

#define BOOK_FILE "books.txt"
#define SALE_FILE "sales.txt"
#define SALE_REPORT_FILE "sales_report.txt"
#define MAX_BOOKS 100
#define MAX_SALES 100

struct Book
{
    char title[100], author[100];
    int id, quantity;
    double price;
};

struct Sale
{
    char title[100];
    int id, bookId, totalSold;
    double totalPrice;
};

void DisplayWelcomeBanner();
void DisplayOptionsMenu();
void DisplayLoginSuccessfulBanner();
void DisplayBackToMenuBanner();
void DisplayProgramQuitBanner();
void DisplayAdminMenu();
void AddBook();
void DisplayBooks();
void DisplayLogoutSuccessfulBanner();
void UpdateBookByID();
int GetLatestBookID();
void DisplaySalesReport();
void GenerateSalesReport();
void DisplayBackToMenuBannerSalesReport();
void DisplayLoading();

main()
{
    int choice;
    bool isLogin = false, shouldQuitProgram = false;
    DisplayWelcomeBanner();
    while (!shouldQuitProgram)
    {

        DisplayOptionsMenu();
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

        if (isLogin)
        {
            system("cls");
            DisplayLoginSuccessfulBanner();
        }

        while (isLogin)
        {

            DisplayAdminMenu();
            do
            {
                cout << "Please enter your choice (0, 1, 2, 3 or 4): ";
                cin >> choice;

                if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4)
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 0 && choice != 1 && choice != 2 && choice != 3  && choice != 4);
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

                    if (choice != 0)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 0);
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

                    if (choice != 0)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 0);
                system("cls");
            }
            // Update Book
            else if (choice == 2)
            {
                system("cls");
                UpdateBookByID();
                DisplayBackToMenuBanner();
                do
                {
                    cin >> choice;

                    if (choice != 0)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (choice != 0);
                system("cls");
            }
            // Display Sales Report
            else if (choice == 3)
            {
                system("cls");
                DisplaySalesReport();
                DisplayBackToMenuBannerSalesReport();
                do
                {
                    cin >> choice;

                    if (choice != 0 && choice != 1)
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }

                    if (choice == 1)
                    {
                        system("cls");
                        GenerateSalesReport();
                        DisplayBackToMenuBanner();
                        do
                        {
                            cin >> choice;

                            if (choice != 0)
                            {
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        } while (choice != 0);
                    }

                } while (choice != 0 && choice != 1);
                system("cls");
            }
            // Log out
            else if (choice == 4)
            {
                isLogin = false;
                DisplayLogoutSuccessfulBanner();
                break;
            }
        }
    }
}

void DisplayWelcomeBanner()
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

void DisplayOptionsMenu()
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
    cout << "||  [2] Update Book                                                 ||" << endl;
    cout << "||  [3] Sales Report                                                ||" << endl;
    cout << "||  [4] Logout Program                                              ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayBackToMenuBanner()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "======================================================================+" << endl;
    ;
    cout << "Enter your choice: ";
}

void DisplayBackToMenuBannerSalesReport()
{
    cout << "\n";
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                Press 1 to generate report                         ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "======================================================================+" << endl;
    ;
    cout << "Enter your choice: ";
}

void DisplayLoading()
{
    cout << endl << endl;
    cout << setw(50) << "==============================" << endl;
    cout << setw(50) << "||      L O A D I N G       ||" << endl;
    cout << setw(50) << "==============================" << endl;

	sleep(1);
	system("cls");
}

void DisplayBooks()
{
    struct Book books[MAX_BOOKS];
    int i = 0;
    ifstream read;
	
	DisplayLoading();
	
    read.open(BOOK_FILE);

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
        << setw(10) << "Quantity"
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

    book.id = GetLatestBookID() + 1;

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

void UpdateBookByID()
{
    Book books[MAX_BOOKS];
    int count = 0, targetId;
    bool found = false;
    ifstream read;

    cout << "============================= UPDATE BOOK ===============================" << endl;

    read.open(BOOK_FILE);

    if (read.fail())
    {
        cout << "Error opening books file." << endl;
        return;
    }

    while (!read.eof())
    {
        read >> books[count].id;
        read.ignore();
        read.getline(books[count].title, 100);
        read.getline(books[count].author, 100);

        read >> books[count].quantity;
        read >> books[count].price;
        read.ignore();

        count++;
    }
    read.close();

    cout << "Enter the Book ID to update: ";
    cin >> targetId;

    for (int i = 0; i < count; i++)
    {
        if (books[i].id == targetId)
        {
            found = true;
            cout << "\n=========================== CURRENT BOOK INFO ===========================" << endl;
            cout << left;
            cout << setw(12) << "ID:" << books[i].id << endl;
            cout << setw(12) << "Title:" << books[i].title << endl;
            cout << setw(12) << "Author:" << books[i].author << endl;
            cout << setw(12) << "Quantity:" << books[i].quantity << endl;
            cout << setw(12) << "Price:" << books[i].price << endl;
            cout << "============================================================================" << endl
                 << endl;
        }
        do
        {
            cout << "Enter book title to update: ";
            cin.ignore();
            cin.getline(books[i].title, 100);
            if (books[i].title[0] == '\0')
            {
                cout << "Title cannot be empty." << endl;
            }
        } while (books[i].title[0] == '\0');

        do
        {
            cout << "Enter book author to update: ";
            cin.getline(books[i].author, 100);
            if (books[i].author[0] == '\0')
            {
                cout << "Author name cannot be empty." << endl;
            }
        } while (books[i].author[0] == '\0');

        do
        {
            cout << "Enter book quantity to update: ";
            cin >> books[i].quantity;
            if (books[i].quantity < 1)
            {
                cout << "Invalid input. Please enter a non-negative integer for quantity." << endl;
            }
        } while (books[i].quantity < 1);

        do
        {
            cout << "Enter book price to update: ";
            cin >> books[i].price;
            if (books[i].price < 1)
            {
                cout << "Invalid input. Please enter a non-negative number for price." << endl;
            }
        } while (books[i].price < 1);

        break;
    }

    if (!found)
    {
        cout << "Book with ID " << targetId << " not found." << endl;
        return;
    }

    ofstream write;
    write.open(BOOK_FILE, ios::out);

    for (int i = 0; i < count; i++)
    {
        if (i != 0)
            write << "\n";
        write << books[i].id << "\n"
              << books[i].title << "\n"
              << books[i].author << "\n"
              << books[i].quantity << "\n"
              << books[i].price;
    }
    write.close();

    cout << "Book updated successfully!" << endl;
}

int GetLatestBookID()
{
    ifstream read(BOOK_FILE);
    Book book;
    int latestId = 0;

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

void DisplaySalesReport()
{
    struct Sale sales[MAX_SALES];
    int i = 0;
    double grandTotal = 0;
    ifstream read;

	DisplayLoading();

    read.open(SALE_FILE);

    if (read.fail())
    {
        cout << "Error opening sales file." << endl;
        return;
    }

    while (!read.eof() && i < MAX_SALES)
    {
        read >> sales[i].id;
        read.ignore();
        read.getline(sales[i].title, 100);
        read >> sales[i].bookId;
        read >> sales[i].totalSold;
        read >> sales[i].totalPrice;
        read.ignore();
        i++;
    }
    read.close();

    cout << "============================= SALES REPORT ==============================" << endl;
    cout
        << setw(6) << "ID"
        << setw(25) << "Title"
        << setw(12) << "Total Sold"
        << setw(12) << "Total (RM)" << endl;
    cout << "-------------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        cout
            << setw(6) << sales[j].id
            << setw(25) << sales[j].title
            << setw(12) << sales[j].totalSold
            << fixed << setprecision(2)
            << setw(12) << sales[j].totalPrice << endl;

        grandTotal += sales[j].totalPrice;
    }

    cout << "-------------------------------------------------------------------------" << endl
         << endl;

    cout << "-------------------------------------------------------------------------" << endl;
    cout << right << setw(66) << "Total Revenue: RM " << fixed << setprecision(2) << grandTotal << endl;
    cout << "=========================================================================" << endl;
}

void GenerateSalesReport()
{
    struct Sale sales[MAX_SALES];
    int i = 0;
    ifstream read;

    read.open(SALE_FILE);

    cout << endl << endl;
    cout << "==================================================================" << endl;
    cout << "||      G E N E R A T I N G      R E P O R T     F I L E        ||" << endl;
    cout << "==================================================================" << endl;

    if (read.fail())
    {
        cout << "Error opening sales file." << endl;
        return;
    }

    while (!read.eof() && i < MAX_SALES)
    {
        read >> sales[i].id;
        read.ignore();
        read.getline(sales[i].title, 100);
        read >> sales[i].bookId;
        read >> sales[i].totalSold;
        read >> sales[i].totalPrice;
        read.ignore();
        i++;
    }
    read.close();

    ofstream write;
    write.open(SALE_REPORT_FILE, ios::out);

    if (write.fail())
    {
        cout << "Error writing to sales report file." << endl;
        return;
    }

    write << "================================ SALES REPORT ====================================" << endl;
    write << setw(10) << "Sale ID"
          << setw(30) << "Title"
          << setw(10) << "Book ID"
          << setw(15) << "Quantity Sold"
          << setw(15) << "Total Price" << "\n";
    write << "----------------------------------------------------------------------------------" << endl;

    double grandTotal = 0;

    for (int j = 0; j < i; j++)
    {
        write << setw(10) << sales[j].id
              << setw(30) << sales[j].title
              << setw(10) << sales[j].bookId
              << setw(15) << sales[j].totalSold
              << fixed << setprecision(2)
              << setw(15) << sales[j].totalPrice << "\n";

        grandTotal += sales[j].totalPrice;
    }

    write << "----------------------------------------------------------------------------------" << endl;
    write << right << setw(70) << "Total Revenue: RM " << fixed << setprecision(2) << grandTotal << endl;
    write << "==================================================================================" << endl;

    write.close();

    sleep(2);

    cout << endl
         << endl
         << "Sales report generated successfully!" << endl
         << endl;
         
    cout << "Report can be view in " << SALE_REPORT_FILE << endl << endl;
}
