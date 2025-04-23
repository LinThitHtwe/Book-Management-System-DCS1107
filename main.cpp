#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <cstring>

using namespace std;

#define BOOK_FILE "books.txt"
#define USER_FILE "users.txt"
#define TRANSACTION_FILE "transactions.txt"
#define SALE_REPORT_FILE "sales_report.txt"
#define SUPPLIER_NOTI_FILE "supplier_noti.txt"
#define MAX_ARRAY_SIZE 100
#define RED_COLOR "\033[31m"
#define YELLOW_COLOR "\033[33m"
#define GREEN_COLOR "\033[32m"
#define WHITE_COLOR "\033[0m"
#define SUPPLIER_ROLE "supplier"
#define USER_ROLE "user"
#define ADMIN_ROLE "admin"
#define DEFAULT_PASSWORD "pass"

struct Book
{
    char title[100], author[100], status[50];
    int id, stockQuantity, quantitySold, supplierId;
    double price;
};

struct User
{
    int id;
    char password[100], email[100], role[50];
};

struct Transaction
{
    int id, userId, bookId, quantity;
    char email[100], bookTitle[100];
    double bookPrice;
};

struct SupplierNotification
{
    int id, supplierId, bookId, stockLeft;
    char bookTitle[100];
};

bool Login(char email[50], char password[50], User &currentUser);
bool SignUp(char email[50], char password[50], User &currentUser);
void ForgetPassword();
void ResetPassword(User currentUser);
int GetLatestUserID();
int ReadUsersData(User users[], int i);

void DisplayWelcomeBanner();
void DisplayLogin();
void DisplayLoginSuccessfulBanner();
void DisplaySignUp();
void DisplaySignUpSuccessfulBanner();
void DisplayForgetPassword();
void DisplayResetPassword();
void DisplayOptionMenuUserBookList();
void DisplayOptionsMenu();
void DisplayBackToMenuBanner();
void DisplayProgramQuitBanner();
void DisplayAdminMenu();
void DisplayUserMenu();
void DisplaySupplierMenu();
void DisplayAddAdmin();
void DisplayAddSupplier();
void DisplayLogoutSuccessfulBanner();
void DisplayBackToMenuBannerSalesReport();
void DisplayBackToMenuInventoryStatus();
void DisplayLoading();

void AddBook();
void UpdateBookByID();
void DisplayBooksAdmin();
void DisplayBooksUser();
int GetLatestBookID();
int ReadBooksData(Book books[], int i);
void BubbleSortBooks(Book books[], int size);

bool BuyBook(User currentUser);
void DisplayTransactions();
void DisplaySalesReport();
void GenerateSalesReport();
int GetLatestTransactionID();
int ReadTransactionData(Transaction transactions[], int i);

void DisplayInventoryStatus();
bool IsSupplierIdExists(User users[], int userCount, int supplierId);
int GetSupplierList(User suppliers[], int i);
void DisplaySupplierList();
void DisplayNotifications();

void AddAdmin();
void AddSupplier();

int GetSupplierNotificationsById(SupplierNotification notis[], int supplierId);
void DisplaySupplierNotifications(int supplierId);
void NotifySuppliersForLowStock();
int GetLatestSupplierNotiId();

main()
{
    int choice;
    bool isLogin = false, isSignUp = false, shouldQuitProgram = false;
    char email[50], password[50], confirmPassword[50];
    struct User currentUser;

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
                cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
            }
            else if (choice == 0)
            {
                system("cls");
                DisplayLogin();
                cout << endl
                     << endl;
                cin.ignore();
                do
                {
                    cout << "Enter your email : ";

                    cin.getline(email, 50);

                    cout << "Enter your password : ";
                    cin.getline(password, 50);

                    isLogin = Login(email, password, currentUser);
                    if (!isLogin)
                    {
                        cout << RED_COLOR << "Invalid Email or Password. Try Again" << WHITE_COLOR << endl;
                    }
                    else
                    {
                        system("cls");
                        DisplayLoading();
                    }
                } while (!isLogin);
            }
            else if (choice == 1)
            {
                system("cls");
                DisplaySignUp();
                cout << endl
                     << endl;

                bool isPassSame = false;
                cin.ignore();
                do
                {
                    cout << "Enter your email : ";
                    cin.getline(email, 50);

                    if (email[0] == '\0')
                    {
                        cout << RED_COLOR << "Email cannot be empty." << WHITE_COLOR << endl;
                    }
                } while (email[0] == '\0');
                do
                {
                    do
                    {

                        cout << "Enter your password : ";
                        cin.getline(password, 50);
                        if (password[0] == '\0')
                        {
                            cout << RED_COLOR << "Password cannot be empty." << WHITE_COLOR << endl;
                        }
                    } while (password[0] == '\0');

                    cout << "Enter your confirm password :";
                    cin.getline(confirmPassword, 50);

                    if (strcmp(password, confirmPassword) == 0)
                    {
                        isPassSame = true;
                        isSignUp = SignUp(email, password, currentUser);
                    }
                    else
                    {
                        cout << RED_COLOR << "Confirm password should be the same as password." << WHITE_COLOR << endl;
                    }

                    if (isSignUp)
                    {
                        system("cls");
                        DisplayLoading();
                    }
                } while (!isSignUp || !isPassSame);
            }

            else if (choice == 2)
            {
                system("cls");
                DisplayForgetPassword();
                ForgetPassword();
                DisplayBackToMenuBanner();
                do
                {
                    cin >> choice;

                    if (choice != 0)
                    {
                        cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                    }
                } while (choice != 0);
                system("cls");
            }
            else if (choice == 3)
            {
                shouldQuitProgram = true;
                system("cls");
                DisplayLoading();
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
            sleep(1);
        }

        if (isSignUp)
        {
            system("cls");
            DisplaySignUpSuccessfulBanner();
            sleep(1);
        }

        while (isLogin || isSignUp)
        {
            if (strcmp(currentUser.role, ADMIN_ROLE) == 0)
            {

                DisplayAdminMenu();
                do
                {
                    cout << "Please enter your choice (0-11) : ";
                    cin >> choice;

                    if (choice < 0 || choice > 11)
                    {
                        cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                    }
                } while (choice < 0 || choice > 11);

                system("cls");

                // Display Book
                if (choice == 0)
                {
                    DisplayBooksAdmin();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
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
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
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
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
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
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
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
                                    cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                                }
                            } while (choice != 0);
                        }

                    } while (choice != 0 && choice != 1);
                    system("cls");
                }
                // InventoryStatus
                else if (choice == 4)
                {
                    system("cls");
                    DisplayInventoryStatus();
                    DisplayBackToMenuInventoryStatus();
                    do
                    {
                        cin >> choice;

                        if (choice != 0 && choice != 1)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                        if (choice == 1)
                        {
                            NotifySuppliersForLowStock();
                            DisplayBackToMenuBanner();
                            do
                            {
                                cin >> choice;

                                if (choice != 0)
                                {
                                    cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                                }
                            } while (choice != 0);
                            system("cls");
                        }
                    } while (choice != 1 && choice != 0);
                    system("cls");
                }
                // Display Notifications
                else if (choice == 5)
                {
                    system("cls");
                    DisplayNotifications();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Supplier List
                else if (choice == 6)
                {
                    system("cls");
                    DisplaySupplierList();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Display Transactions
                else if (choice == 7)
                {
                    system("cls");
                    DisplayTransactions();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Add Admin
                else if (choice == 8)
                {
                    system("cls");
                    DisplayAddAdmin();
                    AddAdmin();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Reset Password
                else if (choice == 9)
                {
                    system("cls");
                    DisplayResetPassword();
                    ResetPassword(currentUser);
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Add Supplier
                else if (choice == 10)
                {
                    system("cls");
                    DisplayAddSupplier();
                    AddSupplier();
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Log out
                else if (choice == 11)
                {
                    isLogin = false;
                    DisplayLoading();
                    DisplayLogoutSuccessfulBanner();
                    sleep(1);
                    break;
                }
            }
            // If the user role is user
            else if (strcmp(currentUser.role, USER_ROLE) == 0)
            {
                DisplayUserMenu();

                do
                {
                    cout << "Please enter your choice (0, 1, or 2): ";
                    cin >> choice;

                    if (choice != 0 && choice != 1 && choice != 2)
                    {
                        cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                    }
                } while (choice != 0 && choice != 1 && choice != 2);

                // Buy Book (Display Book List)
                if (choice == 0)
                {
                    bool isBookBought = false;
                    system("cls");
                    DisplayBooksUser();
                    DisplayOptionMenuUserBookList();

                    do
                    {
                        cout << "Please enter your choice (0 or 1): ";
                        cin >> choice;

                        if (choice != 0 && choice != 1)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0 && choice != 1);
                    cout << endl
                         << endl;

                    // Buy Book
                    if (choice == 1)
                    {
                        do
                        {
                            isBookBought = BuyBook(currentUser);
                        } while (!isBookBought);
                        cout << endl
                             << endl;
                        DisplayBackToMenuBanner();
                        do
                        {
                            cin >> choice;

                            if (choice != 0)
                            {
                                cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                            }
                        } while (choice != 0);
                    }
                    system("cls");
                }
                // Reset Password
                else if (choice == 1)
                {
                    system("cls");
                    DisplayResetPassword();
                    ResetPassword(currentUser);
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Logout
                else if (choice == 2)
                {
                    isLogin = false;
                    DisplayLoading();
                    DisplayLogoutSuccessfulBanner();
                    sleep(1);
                    break;
                }
            }
            // If the user is a supplier
            else if (strcmp(currentUser.role, SUPPLIER_ROLE) == 0)
            {
                DisplaySupplierMenu();
                do
                {
                    cout << "Please enter your choice (0, 1, or 2): ";
                    cin >> choice;

                    if (choice != 0 && choice != 1 && choice != 2)
                    {
                        cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                    }
                } while (choice != 0 && choice != 1 && choice != 2);

                // Display Supplier Notifications
                if (choice == 0)
                {
                    system("cls");
                    DisplaySupplierNotifications(currentUser.id);
                    cout << endl
                         << endl;
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Reset Password
                else if (choice == 1)
                {
                    system("cls");
                    DisplayResetPassword();
                    ResetPassword(currentUser);
                    DisplayBackToMenuBanner();
                    do
                    {
                        cin >> choice;

                        if (choice != 0)
                        {
                            cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
                        }
                    } while (choice != 0);
                    system("cls");
                }
                // Logout
                else if (choice == 2)
                {
                    isLogin = false;
                    DisplayLoading();
                    DisplayLogoutSuccessfulBanner();
                    sleep(1);
                    break;
                }
            }
        }
    }
}

void DisplayLogin()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                          L O G I N !                             ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplaySignUp()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                         S I G N   U P                            ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayForgetPassword()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                  F O R G E T   P A S S W O R D                   ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayResetPassword()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                  R E S E T   P A S S W O R D                     ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
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

void DisplayAddAdmin()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                        A D D   A D M I N                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayAddSupplier()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                      A D D   S U P P L I E R                     ||" << endl;
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
    cout << "||                   " << GREEN_COLOR << "L O G I N   S U C C E S S F U L" << WHITE_COLOR << "                ||" << endl;
    cout << "||                          W E L C O M E !                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplaySignUpSuccessfulBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                   " << GREEN_COLOR << "S I G N U P  S U C C E S S F U L" << WHITE_COLOR "               ||" << endl;
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
    cout << "||                   " << GREEN_COLOR << "L O G O U T   S U C C E S S F U L" << WHITE_COLOR << "              ||" << endl;
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
    cout << "||               " << GREEN_COLOR << "P R O G R A M   S U C C E S S F U L L Y" << WHITE_COLOR << "            ||" << endl;
    cout << "||                           " << GREEN_COLOR << "Q U I T !" << WHITE_COLOR << "                              ||" << endl;
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
    cout << "||  [5] Notifications                                               ||" << endl;
    cout << "||  [6] Suppliers List                                              ||" << endl;
    cout << "||  [7] Transactions Detail                                         ||" << endl;
    cout << "||  [8] Add Admin                                                   ||" << endl;
    cout << "||  [9] Reset Password                                              ||" << endl;
    cout << "||  [10] Add Suppliers                                              ||" << endl;
    cout << "||  [11] Logout Program                                             ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayUserMenu()
{
    cout << "=========================== USER MENU ================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Buy Book                                                    ||" << endl;
    cout << "||  [1] Reset Password                                              ||" << endl;
    cout << "||  [2] Logout                                                      ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplaySupplierMenu()
{
    cout << "=========================== SUPPLIER MENU ============================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Notifications                                               ||" << endl;
    cout << "||  [1] Reset Password                                              ||" << endl;
    cout << "||  [2] Logout                                                      ||" << endl;
    cout << "||                                                                  ||" << endl;
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
    cout << "=======================================================================" << endl;
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

void DisplayOptionMenuUserBookList()
{
    cout << "\n";
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                Press 1 to buy book                                ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
    cout << "Enter your choice: ";
}

void DisplayBackToMenuInventoryStatus()
{
    cout << "\n";
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                Press 1 to sent noti to supplier                   ||" << endl;
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

bool Login(char email[50], char password[50], User &currentUser)
{
    struct User users[100];
    int i = 0;

    i = ReadUsersData(users, i);

    for (int j = 0; j < i; j++)
    {

        if (strcmp(users[j].email, email) == 0 && strcmp(users[j].password, password) == 0)
        {
            currentUser.id = users[j].id;
            strcpy(currentUser.email, users[j].email);
            strcpy(currentUser.password, users[j].password);
            strcpy(currentUser.role, users[j].role);
            return true;
        }
    }
    return false;
}

bool SignUp(char email[100], char password[100], User &currentUser)
{

    User users[MAX_ARRAY_SIZE];
    int userCount = ReadUsersData(users, 0);
    ifstream read;
    read.open(USER_FILE);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].email, email) == 0)
        {
            cout << RED_COLOR << "Account with this email already exists. Try again." << WHITE_COLOR << endl;
            return false;
        }
    }

    int newId = GetLatestUserID() + 1;

    currentUser.id = newId;
    strcpy(currentUser.email, email);
    strcpy(currentUser.password, password);
    strcpy(currentUser.role, USER_ROLE);

    ofstream write(USER_FILE, ios::app);

    bool isFileEmpty = read.peek() == EOF;
    read.close();

    if (!isFileEmpty)
    {
        write << "\n";
    }

    write << currentUser.id << "\n"
          << currentUser.email << "\n"
          << currentUser.password << "\n"
          << currentUser.role;

    write.close();

    return true;
}

void ForgetPassword()
{
    char email[100], newPassword[100], confirmPassword[100];
    int count = 0;
    bool found = false, isPassSame = false;

    User users[MAX_ARRAY_SIZE];
    count = ReadUsersData(users, 0);

    do
    {
        cout << "Enter your email to reset password: ";
        cin.ignore();
        cin.getline(email, 100);

        for (int i = 0; i < count; i++)
        {
            if (strcmp(users[i].email, email) == 0)
            {
                found = true;

                do
                {
                    cout << "Enter your new password: ";
                    cin.getline(newPassword, 100);

                    cout << "Confirm your new password: ";
                    cin.getline(confirmPassword, 100);

                    if (strcmp(newPassword, confirmPassword) == 0)
                    {
                        strcpy(users[i].password, newPassword);
                        isPassSame = true;
                    }
                    else
                    {
                        cout << RED_COLOR << "Passwords do not match. Please try again." << WHITE_COLOR << endl;
                    }
                } while (!isPassSame);

                break;
            }
        }

        if (!found)
        {
            cout << RED_COLOR << "No account found with that email. Please try again." << WHITE_COLOR
                 << endl;
        }

    } while (!found);

    ofstream write;
    write.open(USER_FILE, ios::out);

    for (int i = 0; i < count; i++)
    {
        if (i != 0)
        {
            write << "\n";
        }

        write << users[i].id << "\n"
              << users[i].email << "\n"
              << users[i].password << "\n"
              << users[i].role;
    }

    write.close();
    cout << "Loading..." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Password reset successfully!" << WHITE_COLOR << endl;
}

void ResetPassword(User currentUser)
{
    char newPassword[100], confirmPassword[100];
    bool isPassSame = false;

    User users[MAX_ARRAY_SIZE];
    int count = ReadUsersData(users, 0);

    cin.ignore();

    do
    {
        do
        {
            cout << "Enter your new password: ";

            cin.getline(newPassword, 100);

            if (newPassword[0] == '\0')
            {
                cout << RED_COLOR << "Password cannot be empty" << WHITE_COLOR << endl;
            }

        } while (newPassword[0] == '\0');

        cout << "Confirm your new password: ";
        cin.getline(confirmPassword, 100);

        if (strcmp(newPassword, confirmPassword) == 0)
        {
            isPassSame = true;
        }
        else
        {
            cout << RED_COLOR << "Passwords do not match. Please try again." << WHITE_COLOR
                 << endl;
        }

    } while (!isPassSame);

    for (int i = 0; i < count; i++)
    {
        if (users[i].id == currentUser.id)
        {
            strcpy(users[i].password, newPassword);
            break;
        }
    }

    ofstream write;
    write.open(USER_FILE, ios::out);

    for (int i = 0; i < count; i++)
    {
        if (i != 0)
        {
            write << "\n";
        }

        write << users[i].id << "\n"
              << users[i].email << "\n"
              << users[i].password << "\n"
              << users[i].role;
    }

    write.close();

    cout << "Loading..." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Password has been reset successfully!" << WHITE_COLOR << endl;
}

void AddAdmin()
{
    char email[100];
    bool exists = false;
    int count = 0;

    User users[MAX_ARRAY_SIZE];
    count = ReadUsersData(users, 0);

    cin.ignore();
    do
    {
        exists = false;
        do
        {

            cout << "Enter new admin email: ";
            cin.getline(email, 100);
            if (email[0] == '\0')
            {
                cout << RED_COLOR << "Email cannot be empty." << WHITE_COLOR << endl;
            }

        } while (email[0] == '\0');

        for (int i = 0; i < count; i++)
        {
            if (strcmp(users[i].email, email) == 0)
            {
                exists = true;
                break;
            }
        }

        if (exists)
        {
            cout << RED_COLOR << "An account with this email already exists!" << WHITE_COLOR << endl;
        }
    } while (exists);

    int newId = GetLatestUserID() + 1;
    User newUser;
    newUser.id = newId;
    strcpy(newUser.email, email);
    strcpy(newUser.password, DEFAULT_PASSWORD);
    strcpy(newUser.role, ADMIN_ROLE);

    ofstream write;
    write.open(USER_FILE, ios::app);

    write << "\n"
          << newUser.id << "\n"
          << newUser.email << "\n"
          << newUser.password << "\n"
          << newUser.role;

    write.close();

    cout << "Loading..." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Admin account created successfully with default password - " << DEFAULT_PASSWORD << WHITE_COLOR << endl;
}

void AddSupplier()
{
    char email[100];
    bool exists = false;
    int count = 0;

    User users[MAX_ARRAY_SIZE];
    count = ReadUsersData(users, 0);

    cin.ignore();
    do
    {
        exists = false;
        do
        {

            cout << "Enter new supplier email: ";
            cin.getline(email, 100);
            if (email[0] == '\0')
            {
                cout << RED_COLOR << "Email cannot be empty." << WHITE_COLOR << endl;
            }

        } while (email[0] == '\0');

        for (int i = 0; i < count; i++)
        {
            if (strcmp(users[i].email, email) == 0)
            {
                exists = true;
                break;
            }
        }

        if (exists)
        {
            cout << RED_COLOR << "An account with this email already exists!" << WHITE_COLOR << endl;
        }
    } while (exists);

    int newId = GetLatestUserID() + 1;
    User newUser;
    newUser.id = newId;
    strcpy(newUser.email, email);
    strcpy(newUser.password, DEFAULT_PASSWORD);
    strcpy(newUser.role, SUPPLIER_ROLE);

    ofstream write;
    write.open(USER_FILE, ios::app);

    write << "\n"
          << newUser.id << "\n"
          << newUser.email << "\n"
          << newUser.password << "\n"
          << newUser.role;

    write.close();

    cout << "Loading..." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Supplier account created successfully with default password - " << DEFAULT_PASSWORD << WHITE_COLOR << endl;
}

void DisplayBooksAdmin()
{
    struct Book books[MAX_ARRAY_SIZE];
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

void DisplayBooksUser()
{
    struct Book books[MAX_ARRAY_SIZE];
    int i = 0;
    DisplayLoading();

    i = ReadBooksData(books, i);

    cout << "======================================== BOOK LIST =========================================" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout
        << setw(6) << "ID"
        << setw(25) << "Title"
        << setw(20) << "Author"
        << setw(12) << "Stock Left"
        << setw(15) << "Price(RM)" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < i; j++)
    {
        cout
            << setw(6) << books[j].id
            << setw(25) << books[j].title
            << setw(20) << books[j].author
            << setw(12) << books[j].stockQuantity - books[j].quantitySold
            << setw(15) << fixed << setprecision(2) << books[j].price << endl;
    }

    cout << "--------------------------------------------------------------------------------------------" << endl
         << endl;

    BubbleSortBooks(books, i);

    cout << "================================= TOP 3 BEST-SELLING BOOKS =================================" << endl;
    cout
        << setw(6) << "Id"
        << setw(25) << "Title"
        << setw(25) << "Author"
        << setw(18) << "Price"
        << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < 3; j++)
    {
        cout
            << setw(6) << books[j].id
            << setw(25) << books[j].title
            << setw(25) << books[j].author
            << fixed << setprecision(2)
            << setw(18) << books[j].price << endl;
    }

    cout << "============================================================================================" << endl
         << endl
         << endl;
}

void AddBook()
{
    ofstream write;
    struct Book book;

    struct User users[MAX_ARRAY_SIZE];
    ifstream read;
    read.open(BOOK_FILE);
    int i = 0;
    i = ReadUsersData(users, i);

    cout << "============================= ADD BOOK ===============================" << endl;

    book.id = GetLatestBookID() + 1;

    do
    {
        cout << "Enter book title: ";
        cin.ignore();
        cin.getline(book.title, 100);
        if (book.title[0] == '\0')
        {
            cout << RED_COLOR << "Title cannot be empty." << WHITE_COLOR << endl;
        }
    } while (book.title[0] == '\0');

    do
    {
        cout << "Enter book author: ";
        cin.getline(book.author, 100);
        if (book.author[0] == '\0')
        {
            cout << RED_COLOR << "Author name cannot be empty." << WHITE_COLOR << endl;
        }
    } while (book.author[0] == '\0');

    do
    {
        cout << "Enter book quantity to sell : ";
        cin >> book.stockQuantity;
        if (book.stockQuantity < 1)
        {
            cout << RED_COLOR << "Invalid input. Please enter a non-negative integer for quantity." << WHITE_COLOR << endl;
        }
    } while (book.stockQuantity < 1);

    do
    {
        cout << "Enter book price: ";
        cin >> book.price;
        if (book.price < 1)
        {
            cout << RED_COLOR << "Invalid input. Please enter a non-negative number for price." << WHITE_COLOR << endl;
        }
    } while (book.price < 1);

    do
    {
        cout << "Enter supplier Id: ";
        cin >> book.supplierId;

        if (!IsSupplierIdExists(users, i, book.supplierId))
        {
            cout << RED_COLOR << "Supplier ID does not exist. Please try again." << WHITE_COLOR << endl;
        }

    } while (!IsSupplierIdExists(users, i, book.supplierId));
    book.quantitySold = 0;

    write.open(BOOK_FILE, ios::app);

    bool isFileEmpty = read.peek() == EOF;
    read.close();
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

    cout << "Adding Book...." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Book added successfully!" << WHITE_COLOR << endl;
}

void UpdateBookByID()
{
    struct Book books[MAX_ARRAY_SIZE];
    struct User users[MAX_ARRAY_SIZE];
    int count = 0, targetId, j = 0;
    bool found = false;

    cout << "============================= UPDATE BOOK ===============================" << endl;

    count = ReadBooksData(books, count);
    j = ReadUsersData(users, j);

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
                    cout << RED_COLOR << "Title cannot be empty." << WHITE_COLOR << endl;
                }
            } while (books[i].title[0] == '\0');

            do
            {
                cout << "Enter book author to update: ";
                cin.getline(books[i].author, 100);
                if (books[i].author[0] == '\0')
                {
                    cout << RED_COLOR << "Author name cannot be empty." << WHITE_COLOR << endl;
                }
            } while (books[i].author[0] == '\0');

            do
            {
                cout << "Enter book initial stock quantity to update: ";
                cin >> books[i].stockQuantity;
                if (books[i].stockQuantity < 1)
                {
                    cout << RED_COLOR << "Invalid input. Please enter a non-negative integer for quantity." << WHITE_COLOR << endl;
                }
            } while (books[i].stockQuantity < 1);

            do
            {
                cout << "Enter book price to update: ";
                cin >> books[i].price;
                if (books[i].price < 1)
                {
                    cout << RED_COLOR << "Invalid input. Please enter a non-negative number for price." << WHITE_COLOR << endl;
                }
            } while (books[i].price < 1);

            do
            {
                cout << "Enter supplier Id: ";
                cin >> books[i].supplierId;

                if (!IsSupplierIdExists(users, j, books[i].supplierId))
                {
                    cout << RED_COLOR << "Supplier ID does not exist. Please try again." << WHITE_COLOR << endl;
                }

            } while (!IsSupplierIdExists(users, j, books[i].supplierId));

            break;
        }
    }

    if (!found)
    {
        cout << RED_COLOR << "Book with ID " << targetId << " not found." << WHITE_COLOR << endl;
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
              << books[i].price << "\n"
              << books[i].supplierId;
    }
    write.close();

    cout << "Updating Book..." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Book updated successfully!" << WHITE_COLOR << endl;
}

bool BuyBook(User currentUser)
{
    struct Book books[MAX_ARRAY_SIZE];
    struct User users[MAX_ARRAY_SIZE];
    int count = 0, targetId, quantity;
    bool found = false;
    ifstream read;
    read.open(TRANSACTION_FILE);

    cout << "============================= BUY BOOK ===============================" << endl;

    count = ReadBooksData(books, count);

    cout << "Enter the Book ID to buy: ";
    cin >> targetId;

    for (int i = 0; i < count; i++)
    {
        if (books[i].id == targetId)
        {
            int stockLeft = books[i].stockQuantity - books[i].quantitySold;
            found = true;
            cout << "\n=========================== CURRENT BOOK INFO ===========================" << endl;
            cout << left;
            cout << setw(24) << "ID" << ": " << setw(20) << books[i].id << endl;
            cout << setw(24) << "Title" << ": " << setw(20) << books[i].title << endl;
            cout << setw(24) << "Author" << ": " << setw(20) << books[i].author << endl;
            cout << setw(24) << "Stock Left" << ": " << setw(20) << stockLeft << endl;
            cout << setw(24) << "Price" << ": " << setw(20) << fixed << setprecision(2) << books[i].price << endl;
            cout << "==========================================================================" << endl
                 << endl;

            do
            {
                cout << "Enter book quantity to buy : ";
                cin >> quantity;

                if (quantity < 1 || quantity > stockLeft)
                {
                    cout << RED_COLOR << "Invalid Quantity. Try again." << WHITE_COLOR << endl;
                }
            } while (quantity < 1 || quantity > stockLeft);

            ofstream writeTrans;
            writeTrans.open(TRANSACTION_FILE, ios::app);

            bool isFileEmpty = read.peek() == EOF;
            read.close();

            if (!isFileEmpty)
            {
                writeTrans << "\n";
            }

            int transactionId = GetLatestTransactionID();

            if (transactionId < 0)
            {
                cout << RED_COLOR << "Something went wrong!!" << WHITE_COLOR << endl;
                return false;
            }

            transactionId += 1;

            books[i].quantitySold = books[i].quantitySold + quantity;

            writeTrans << transactionId << "\n"
                       << currentUser.id << "\n"
                       << books[i].id << "\n"
                       << quantity << "\n"
                       << currentUser.email << "\n"
                       << books[i].title << "\n"
                       << books[i].price;

            writeTrans.close();

            ofstream writeBook;
            writeBook.open(BOOK_FILE, ios::out);

            for (int i = 0; i < count; i++)
            {
                if (i != 0)
                {
                    writeBook << "\n";
                }

                writeBook << books[i].id << "\n"
                          << books[i].title << "\n"
                          << books[i].author << "\n"
                          << books[i].stockQuantity << "\n"
                          << books[i].quantitySold << "\n"
                          << books[i].price << "\n"
                          << books[i].supplierId;
            }
            writeBook.close();

            cout << "Loading..." << endl;
            sleep(1);
            cout << GREEN_COLOR << "Book bought successfully!" << WHITE_COLOR << endl;

            break;
        }
    }

    if (!found)
    {
        cout << RED_COLOR << "Book with ID " << targetId << " not found. Tray again." << WHITE_COLOR << endl;
        return false;
    }

    return found;
}

int GetLatestSupplierNotiId()
{
    ifstream read;
    read.open(SUPPLIER_NOTI_FILE);
    SupplierNotification supNoti;
    int latestId = 0;

    if (read.peek() == EOF)
    {
        return 1;
    }

    if (read.fail())
    {
        cout << RED_COLOR << "Error opening " << SUPPLIER_NOTI_FILE << " file." << WHITE_COLOR << endl;
        return -1;
    }

    while (!read.eof())
    {
        read >> supNoti.supplierId;
        read >> supNoti.bookId;
        read >> supNoti.stockLeft;
        read.ignore();
        read.getline(supNoti.bookTitle, 100);
        latestId = supNoti.id + 1;
    }
    read.close();

    return latestId;
}

int GetLatestBookID()
{
    ifstream read(BOOK_FILE);
    struct Book book;
    int latestId = 0;

    if (read.fail())
    {
        cout << RED_COLOR << "Error opening " << BOOK_FILE << " file." << WHITE_COLOR << endl;
        return -1;
    }

    if (read.peek() == EOF)
    {
        return 1;
    }

    while (!read.eof())
    {
        read.ignore();
        read.getline(book.title, 100);
        read.getline(book.author, 100);
        read >> book.stockQuantity;
        read >> book.quantitySold;
        read >> book.price;
        read >> book.supplierId;
        read.ignore();
        latestId = book.id;
    }

    read.close();
    return latestId;
}

int GetLatestUserID()
{
    ifstream read(USER_FILE);
    struct User user;
    int latestId = 0;

    if (read.fail())
    {
        cout << RED_COLOR << "Error opening " << USER_FILE << " file." << WHITE_COLOR << endl;
        return -1;
    }

    if (read.peek() == EOF)
    {
        return 1;
    }

    while (!read.eof())
    {
        read >> user.id;
        read.ignore();
        read.getline(user.email, 100);
        read.getline(user.password, 100);
        read.getline(user.role, 50);
        latestId = user.id;
    }

    read.close();
    return latestId;
}

int GetLatestTransactionID()
{
    ifstream read(TRANSACTION_FILE);
    Transaction transaction;
    int latestId = 0;

    if (read.fail())
    {
        cout << RED_COLOR << "Error opening " << TRANSACTION_FILE << "." << WHITE_COLOR << endl;
        return -1;
    }

    if (read.peek() == EOF)
    {
        return 1;
    }

    while (!read.eof())
    {
        read >> transaction.id;
        read >> transaction.userId;
        read >> transaction.bookId;
        read >> transaction.quantity;
        read.ignore();
        read.getline(transaction.email, 100);
        read.getline(transaction.bookTitle, 100);
        read >> transaction.bookPrice;
        read.ignore();
        latestId = transaction.id;
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
        cout << RED_COLOR << "Error opening " << BOOK_FILE << " file." << WHITE_COLOR << endl;
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
        read >> books[i].supplierId;
        read.ignore();
        i++;
    }

    read.close();

    return i;
}

int ReadUsersData(User users[], int i)
{
    ifstream read;
    read.open(USER_FILE);

    if (read.fail())
    {
        cout << RED_COLOR << "Error opening " << USER_FILE << "." << WHITE_COLOR << endl;
        return 0;
    }

    while (!read.eof())
    {
        read >> users[i].id;
        read.ignore();
        read.getline(users[i].email, 100);
        read.getline(users[i].password, 100);
        read.getline(users[i].role, 50);
        i++;
    }

    read.close();
    return i;
}

int ReadTransactionData(Transaction transactions[], int i)
{
    ifstream read;

    read.open(TRANSACTION_FILE);

    if (read.fail())
    {
        cout << RED_COLOR "Error opening " << TRANSACTION_FILE << "." << WHITE_COLOR << endl;
        return 0;
    }

    while (!read.eof())
    {
        read >> transactions[i].id;
        read.ignore();

        read >> transactions[i].userId;
        read.ignore();

        read >> transactions[i].bookId;
        read.ignore();

        read >> transactions[i].quantity;
        read.ignore();

        read.getline(transactions[i].email, 100);
        read.getline(transactions[i].bookTitle, 100);

        read >> transactions[i].bookPrice;
        read.ignore();

        i++;
    }

    read.close();
    return i;
}

bool IsSupplierIdExists(User users[], int userCount, int supplierId)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == supplierId && strcmp(users[i].role, SUPPLIER_ROLE) == 0)
        {
            return true;
        }
    }
    return false;
}

int GetSupplierList(User suppliers[], int i)
{
    User allUsers[MAX_ARRAY_SIZE];
    int totalUsers = ReadUsersData(allUsers, 0);
    int supplierCount = 0;

    for (int j = 0; j < totalUsers; j++)
    {
        if (strcmp(allUsers[j].role, SUPPLIER_ROLE) == 0)
        {
            suppliers[supplierCount] = allUsers[j];
            supplierCount++;
        }
    }

    return supplierCount;
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
    Book books[MAX_ARRAY_SIZE];
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
    Book books[MAX_ARRAY_SIZE];
    int i = 0;

    cout << endl
         << endl;
    cout << "==================================================================" << endl;
    cout << "||      G E N E R A T I N G      R E P O R T     F I L E        ||" << endl;
    cout << "==================================================================" << endl;

    i = ReadBooksData(books, i);

    ofstream write;
    write.open(SALE_REPORT_FILE, ios::out);

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
         << GREEN_COLOR << "Sales report generated successfully!" << WHITE_COLOR << endl
         << endl;

    cout << "Report can be viewed in: " << SALE_REPORT_FILE << endl
         << endl;
}

void DisplayInventoryStatus()
{
    Book books[MAX_ARRAY_SIZE];
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

void DisplayNotifications()
{
    Book books[MAX_ARRAY_SIZE];
    int i = 0;

    DisplayLoading();

    i = ReadBooksData(books, i);

    cout << "======================= STOCK NOTIFICATIONS =======================" << endl;

    for (int j = 0; j < i; j++)
    {
        int leftQty = books[j].stockQuantity - books[j].quantitySold;

        if (leftQty <= 0)
        {
            strcpy(books[j].status, "Out of Stock");
            cout << "--------------------------------------------------------------" << endl;
            cout << RED_COLOR << books[j].title << " is out of stock, need to reorder." << WHITE_COLOR << endl;
        }
        else if (leftQty <= 5)
        {
            strcpy(books[j].status, "Low Stock");
            cout << "--------------------------------------------------------------" << endl;
            cout << YELLOW_COLOR << books[j].title << " is low stock, only left " << leftQty << "." << WHITE_COLOR << endl;
        }
    }

    cout << "--------------------------------------------------------------" << endl
         << endl;
}

void DisplaySupplierList()
{
    struct User suppliers[MAX_ARRAY_SIZE];
    int count = GetSupplierList(suppliers, 0);

    DisplayLoading();

    cout << "================ SUPPLIER LIST =================" << endl;
    cout << "------------------------------------------------" << endl;
    cout
        << setw(6) << "ID"
        << setw(30) << "Email" << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout
            << setw(6) << suppliers[i].id
            << setw(30) << suppliers[i].email
            << endl;
    }

    cout << "------------------------------------------------" << endl
         << endl;
}

void DisplayTransactions()
{
    Transaction transactions[MAX_ARRAY_SIZE];
    int count = ReadTransactionData(transactions, 0);

    DisplayLoading();

    cout << "========================================== TRANSACTION LIST ========================================" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout
        << setw(6) << "ID"
        << setw(10) << "UserID"
        << setw(30) << "Email"
        << setw(10) << "BookID"
        << setw(10) << "Qty"
        << setw(15) << "Price"
        << setw(15) << "Total" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        double total = transactions[i].quantity * transactions[i].bookPrice;

        cout
            << setw(6) << transactions[i].id
            << setw(10) << transactions[i].userId
            << setw(30) << transactions[i].email
            << setw(10) << transactions[i].bookId
            << setw(10) << transactions[i].quantity
            << setw(15) << fixed << setprecision(2) << transactions[i].bookPrice
            << setw(15) << fixed << setprecision(2) << total << endl;
    }

    cout << "----------------------------------------------------------------------------------------------------" << endl
         << endl
         << endl;
}

int GetSupplierNotificationsById(SupplierNotification notis[], int supplierId)
{
    ifstream read(SUPPLIER_NOTI_FILE);
    int count = 0;

    if (read.fail())
    {
        cout << "Error opening " << SUPPLIER_NOTI_FILE << endl;
        return 0;
    }

    while (!read.eof())
    {
        SupplierNotification temp;
        read >> temp.id;
        read.ignore();
        read >> temp.supplierId;
        read.ignore();
        read >> temp.bookId;
        read.ignore();
        read >> temp.stockLeft;
        read.ignore();
        read.getline(temp.bookTitle, 100);

        if (read.fail())
            break;

        if (temp.supplierId == supplierId)
        {
            notis[count++] = temp;
        }
    }

    read.close();
    return count;
}

void DisplaySupplierNotifications(int supplierId)
{
    SupplierNotification notis[MAX_ARRAY_SIZE];
    int count = GetSupplierNotificationsById(notis, supplierId);

    if (count == 0)
    {
        cout << "No notifications found for supplier ID: " << supplierId << endl;
        return;
    }

    DisplayLoading();

    cout << "=============== SUPPLIER NOTIFICATIONS ===============" << endl;
    cout << "------------------------------------------------------" << endl;
    cout
        << setw(6) << "ID"
        << setw(12) << "Book ID"
        << setw(20) << "Book Title"
        << setw(15) << "Stock Left"
        << endl;
    cout << "------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout
            << setw(6) << notis[i].id
            << setw(12) << notis[i].bookId
            << setw(20) << notis[i].bookTitle
            << setw(15) << notis[i].stockLeft
            << endl;
    }

    cout << "------------------------------------------------------" << endl
         << endl;

    cout << YELLOW_COLOR << "Admin has requested to re-stock these book which are low or out of stock." << WHITE_COLOR << endl;
}

void NotifySuppliersForLowStock()
{
    Book books[MAX_ARRAY_SIZE];

    SupplierNotification notifications[MAX_ARRAY_SIZE];
    int bookCount = 0, notiId = 0;

    bookCount = ReadBooksData(books, bookCount);

    notiId = GetLatestSupplierNotiId();

    ifstream read;
    read.open(SUPPLIER_NOTI_FILE);

    ofstream write;
    write.open(SUPPLIER_NOTI_FILE, ios::app);

    for (int i = 0; i < bookCount; i++)
    {
        int leftQty = books[i].stockQuantity - books[i].quantitySold;

        if (leftQty <= 5)
        {

            for (int j = 0; j < bookCount; j++)
            {

                SupplierNotification noti;
                noti.id = notiId++;
                noti.supplierId = books[i].supplierId;
                noti.bookId = books[i].id;
                noti.stockLeft = leftQty;
                strcpy(noti.bookTitle, books[i].title);

                bool isFileEmpty = read.peek() == EOF;

                if (!isFileEmpty)
                {
                    write << "\n";
                }

                write << noti.id << "\n"
                      << noti.supplierId << "\n"
                      << noti.bookId << "\n"
                      << noti.stockLeft << "\n"
                      << noti.bookTitle;

                break;
            }
        }
    }

    write.close();
    cout << "Sending noti to suppliers...." << endl;
    sleep(1);
    cout << GREEN_COLOR << "Low stock/out of stock notifications sent to suppliers." << WHITE_COLOR << endl;
}
