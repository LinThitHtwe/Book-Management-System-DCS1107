#include <iostream>
using namespace std;

void displayWelcomeBanner();
void displayOptionsMenu();

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
