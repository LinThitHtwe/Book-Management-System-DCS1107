#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <cstring>

using namespace std;

#define BOOK_FILE "books.txt"
#define SALE_FILE "sales.txt"
#define SALE_REPORT_FILE "sales_report.txt"
#define MAX_BOOKS 100
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"
#define GREEN_COLOR "\033[32m"
#define WHITE_COLOR "\033[0m"

struct Book
{
    char title[100], author[100], status[50];
    int id, stockQuantity, quantitySold;
    double price;
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
int ReadBooksData(Book books[], int i);
void DisplayInventoryStatus();
void BubbleSortBooks(Book books[], int size);

main()
{
    int choice;
    bool isLogin = false, shouldQuitProgram = false;
    DisplayWelcomeBanner();
    sleep(2);
    system("cls");
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
                cout << "Please enter your choice (0, 1, 2, 3, 4 or 5): ";
                cin >> choice;

                if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);
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
            else if (choice == 4)
            {
                system("cls");
                DisplayInventoryStatus();
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
            // Log out
            else if (choice == 5)
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
    cout << "||  [4] Inventory Status                                            ||" << endl;
    cout << "||  [5] Logout Program                                              ||" << endl;
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
    cout << "=======================================================================" << endl;
    cout << "Enter your choice: ";
}

void DisplayLoading()
{
    cout << endl
         << endl;
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
    DisplayLoading();

    i = ReadBooksData(books, i);

    cout << "============================================= BOOK LIST ==============================================" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout
        << setw(6) << "ID"
        << setw(25) << "Title"
        << setw(20) << "Author"
        << setw(12) << "InitialQty"
        << setw(12) << "SoldQty"
        << setw(12) << "InStockQty"
        << setw(10) << "Price" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        cout
            << setw(6) << books[j].id
            << setw(25) << books[j].title
            << setw(20) << books[j].author
            << setw(12) << books[j].stockQuantity
            << setw(12) << books[j].quantitySold
            << setw(12) << books[j].stockQuantity - books[j].quantitySold
            << fixed << setprecision(2)
            << setw(10) << books[j].price << endl;
    }

    cout << "------------------------------------------------------------------------------------------------------" << endl
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
        cout << "Enter book quantity to sell : ";
        cin >> book.stockQuantity;
        if (book.stockQuantity < 1)
        {
            cout << "Invalid input. Please enter a non-negative integer for quantity." << endl;
        }
    } while (book.stockQuantity < 1);

    do
    {
        cout << "Enter book price: ";
        cin >> book.price;
        if (book.price < 1)
        {
            cout << "Invalid input. Please enter a non-negative number for price." << endl;
        }
    } while (book.price < 1);

    book.quantitySold = 0;

    write.open(BOOK_FILE, ios::app);

    bool isFileEmpty = read.peek() == EOF;

    if (!isFileEmpty)
    {
        write << "\n";
    }

    write << book.id << "\n"
          << book.title << "\n"
          << book.author << "\n"
          << book.stockQuantity << "\n"
          << book.quantitySold << "\n"
          << book.price;

    write.close();

    cout << "Book added successfully!" << endl;
}

void UpdateBookByID()
{
    Book books[MAX_BOOKS];
    int count = 0, targetId;
    bool found = false;

    cout << "============================= UPDATE BOOK ===============================" << endl;

    count = ReadBooksData(books, count);

    cout << "Enter the Book ID to update: ";
    cin >> targetId;

    for (int i = 0; i < count; i++)
    {
        if (books[i].id == targetId)
        {
            found = true;
            cout << "\n=========================== CURRENT BOOK INFO ===========================" << endl;
            cout << left;
            cout << setw(24) << "ID" << ": " << setw(20) << books[i].id << endl;
            cout << setw(24) << "Title" << ": " << setw(20) << books[i].title << endl;
            cout << setw(24) << "Author" << ": " << setw(20) << books[i].author << endl;
            cout << setw(24) << "Initial Stock Quantity" << ": " << setw(20) << books[i].stockQuantity << endl;
            cout << setw(24) << "Sold Quantity" << ": " << setw(20) << books[i].quantitySold << endl;
            cout << setw(24) << "Stock Left" << ": " << setw(20) << (books[i].stockQuantity - books[i].quantitySold) << endl;
            cout << setw(24) << "Price" << ": " << setw(20) << fixed << setprecision(2) << books[i].price << endl;
            cout << "==========================================================================" << endl
                 << endl;

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
                cout << "Enter book initial stock quantity to update: ";
                cin >> books[i].stockQuantity;
                if (books[i].stockQuantity < 1)
                {
                    cout << "Invalid input. Please enter a non-negative integer for quantity." << endl;
                }
            } while (books[i].stockQuantity < 1);

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
        {
            write << "\n";
        }

        write << books[i].id << "\n"
              << books[i].title << "\n"
              << books[i].author << "\n"
              << books[i].stockQuantity << "\n"
              << books[i].quantitySold << "\n"
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
        read >> book.stockQuantity;
        read >> book.quantitySold;
        read >> book.price;
        read.ignore();

        latestId = book.id;
    }

    read.close();
    return latestId;
}

int ReadBooksData(Book books[], int i)
{
    ifstream read;

    read.open(BOOK_FILE);

    if (read.fail())
    {
        cout << "Error opening books file." << endl;
        return 0;
    }

    while (!read.eof())
    {
        read >> books[i].id;
        read.ignore();
        read.getline(books[i].title, 100);
        read.getline(books[i].author, 100);
        read >> books[i].stockQuantity;
        read >> books[i].quantitySold;
        read >> books[i].price;
        read.ignore();
        i++;
    }

    read.close();

    return i;
}

void BubbleSortBooks(Book books[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (books[j].quantitySold < books[j + 1].quantitySold)
            {
                Book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
}

void DisplaySalesReport()
{
    Book books[MAX_BOOKS];
    int i = 0;
    double grandTotal = 0;

    DisplayLoading();

    i = ReadBooksData(books, i);

    cout << "================================= SALES REPORT ==================================" << endl;
    cout
        << setw(6) << "ID"
        << setw(25) << "Title"
        << setw(12) << "Sold Qty"
        << setw(15) << "Total (RM)" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        double total = books[j].quantitySold * books[j].price;

        cout
            << setw(6) << books[j].id
            << setw(25) << books[j].title
            << setw(12) << books[j].quantitySold
            << fixed << setprecision(2)
            << setw(15) << total << endl;

        grandTotal += total;
    }

    cout << "---------------------------------------------------------------------------------" << endl
         << endl;
    cout << right << setw(58) << "Total Revenue: RM " << fixed << setprecision(2) << grandTotal << endl;
    cout << "=================================================================================" << endl
         << endl
         << endl
         << endl;

    BubbleSortBooks(books, i);

    cout << "============================ TOP 3 BEST-SELLING BOOKS ===========================" << endl;
    cout
        << setw(6) << "Rank"
        << setw(25) << "Title"
        << setw(12) << "Sold Qty"
        << setw(15) << "Total (RM)" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < 3; j++)
    {
        double total = books[j].quantitySold * books[j].price;

        cout
            << setw(6) << (j + 1)
            << setw(25) << books[j].title
            << setw(12) << books[j].quantitySold
            << fixed << setprecision(2)
            << setw(15) << total << endl;
    }

    cout << "=================================================================================" << endl
         << endl
         << endl;
}

void GenerateSalesReport()
{
    Book books[MAX_BOOKS];
    int i = 0;

    cout << endl
         << endl;
    cout << "==================================================================" << endl;
    cout << "||      G E N E R A T I N G      R E P O R T     F I L E        ||" << endl;
    cout << "==================================================================" << endl;

    i = ReadBooksData(books, i);

    ofstream write(SALE_REPORT_FILE, ios::out);

    if (write.fail())
    {
        cout << "Error writing to sales report file." << endl;
        return;
    }

    write << "================================ SALES REPORT ====================================" << endl;
    write << setw(10) << "Book ID"
          << setw(30) << "Title"
          << setw(15) << "Sold Qty"
          << setw(15) << "Unit Price"
          << setw(15) << "Total Price" << "\n";
    write << "----------------------------------------------------------------------------------" << endl;

    double grandTotal = 0;

    for (int j = 0; j < i; j++)
    {
        double totalPrice = books[j].quantitySold * books[j].price;

        write << setw(10) << books[j].id
              << setw(30) << books[j].title
              << setw(15) << books[j].quantitySold
              << fixed << setprecision(2)
              << setw(15) << books[j].price
              << setw(15) << totalPrice << "\n";

        grandTotal += totalPrice;
    }

    write << "----------------------------------------------------------------------------------" << endl;
    write << right << setw(70) << "Total Revenue: RM " << fixed << setprecision(2) << grandTotal << endl;
    write << "==================================================================================" << endl
          << endl
          << endl;

    BubbleSortBooks(books, i);

    write << "============================ TOP 3 BEST-SELLING BOOKS ===========================" << endl;
    write
        << setw(6) << "Rank"
        << setw(25) << "Title"
        << setw(12) << "Sold Qty"
        << setw(15) << "Total (RM)" << endl;
    write << "---------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < 3; j++)
    {
        double total = books[j].quantitySold * books[j].price;

        write
            << setw(6) << (j + 1)
            << setw(25) << books[j].title
            << setw(12) << books[j].quantitySold
            << fixed << setprecision(2)
            << setw(15) << total << endl;
    }

    write << "=================================================================================" << endl
          << endl
          << endl;

    write.close();

    sleep(2);

    cout << endl
         << endl
         << "Sales report generated successfully!" << endl
         << endl;

    cout << "Report can be viewed in: " << SALE_REPORT_FILE << endl
         << endl;
}

void DisplayInventoryStatus()
{
    Book books[MAX_BOOKS];
    int i = 0;

    DisplayLoading();

    i = ReadBooksData(books, i);

    cout << "=================================== INVENTORY STATUS ===================================" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << left
         << setw(30) << "Book Title"
         << setw(15) << "Initial Qty"
         << setw(15) << "Qty Sold"
         << setw(15) << "Qty Left"
         << setw(20) << "Status" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        int leftQty = books[j].stockQuantity - books[j].quantitySold;

        char colorCode[10];

        if (leftQty <= 0)
        {
            strcpy(books[j].status, "Out of Stock");
            strcpy(colorCode, RED_COLOR);
        }
        else if (leftQty <= 5)
        {
            strcpy(books[j].status, "Low Stock");
            strcpy(colorCode, YELLOW_COLOR);
        }
        else
        {
            strcpy(books[j].status, "Available");
            strcpy(colorCode, GREEN_COLOR);
        }

        cout
            << setw(30) << books[j].title
            << setw(15) << books[j].stockQuantity
            << setw(15) << books[j].quantitySold
            << setw(15) << leftQty << colorCode
            << setw(20) << books[j].status << WHITE_COLOR << endl;
    }

    cout << "-----------------------------------------------------------------------------------------" << endl
         << endl;
}
