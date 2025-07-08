# Book Store Console Application (1st sem final project)

Book Management System Console Application, a final group project for DCS1107 at INTI. Developed in collaboration with [liewjunkit91](https://github.com/liewjunkit91) and [me](https://github.com/LinThitHtwe).

## Project Screenshots

### Admin

#### Admin Menu

This will appear after admin have login. It show Login successful message and main menu. Admin can choose from 0-11.

![Admin Menu](/docs/admin/Admin_Menu.png)

#### Admin Book Lists Page

The book list will be shown after admin have choose 0 in main menu. The book lists will be shown in table format with fields starting from
Id, Title, Author, Initial Quantity, Sold Quantity, InStock Quantity and Price. These data are read and shown from book.txt file.

![Admin Book List](/docs/admin/Admin_BookLists.png)

#### Admin Add Book (After successfully added book)

If admin choose 1 in main menu, it will redirect to Add Book UI. It will ask admin to fill out each field for book starting from title, author,
quantity (to sell), price and supplierId. System will validate each field so admin cannot enter black field or for numbers, it cannot be less than
or equal to 0. The system will also validate supplier Id by checking if supplier id exists in user.txt file first, admin cannot add id that doesn’t
exist as a supplier in user.txt file. If every field has been validated, the system will save the book. The book id will be auto added by system
by getting the latest id of the book lists (for example, if the latest id of the book is 9, the system will save the new book with id of 10), to
avoid duplication. It gets the latest id of the book by reading all the books data from book.txt file.

![Admin Add Book](/docs/admin/Admin_Add_Book.png)

#### Admin Update Book (After successfully updating book)

If admin choose 2 in menu, it will redirect to update book page. The system will first ask to enter the book id for update. If book id is not
found, it will show cannot find book with that id. If found, it first shows the current info of the book before updating. After that it asked to
update for each field of the book. Each field is validated the same way as Add Book, starting from title to supplier Id. If everything is
validated, it will update the book. The system will first update the array of the book, and the updated array will overwrite the book.txt file.
(for example, if we have 7 book, and update the 5th book, it updated the array first , and overwrite file with the updated array )

![Admin Update Book](/docs/admin/Admin_Update_Book.png)

#### Admin Sale Report

If admin choose 3 in menu, it will redirect to Sale Report Page. It read the data from book.txt file and display the ID, Title, Sold Quantity and
Total of each book. Total is calculated by multiplying quantity sold and price. It also shows the total revenue, by adding all the total of each
book. Underneath, it shows Top 3 best-selling books, by sorting books by quantity sold. For sorting, the bubble sort algorithm is used. Admin
can either choose 0 and go back to menu or choose 1 to generate the report in text file

![Admin Sale Report](/docs/admin/Admin_Sale_Report.png)

#### Admin Generate Sale Report

If admin choose 1 to generate sale report in sale report page, it will direct to the UI shown underneath. The system will call the function that
write exactly as how the Sale Report Page shown into sales_report.txt file.

![Admin Generate Sale Report](/docs/admin/Admin_Generate_Sale_Report.png)

#### Generated Sale Report text file

Underneath is how the text file will look like after admin generated the Sale Report.

![Admin Generated Sale Report](/docs/admin/Admin_Generated_Sale_Report.png)

#### Admin Inventory Status

Admin can see the inventory status after choosing 4 in menu. This will display the data for each book by reading from the text file. It shows
Title, Initial quantity, quantity sold, quantity left and status. Quantity left is calculated by differencing initial quantity to quantity sold. If
quantity left is 0, the status will show out of stock, if quantity left is less than or equal to 5, it will show low stock. Any other will be show as
available. Admin can either go back to menu, or choose 1 to notify the supplier about the low/out of stock book.

![Admin Inventory Status](/docs/admin/Admin_Inventory_Status.png)

#### Notify Suppliers (After successfully sending noti to suppliers)

If admin choose 1 to notify the supplier about the low/out of stock books, the system will save bookId, supplierId, quantity left, book title will
be saved inside the supplier_noti.txt file. Each id for notification will be added automatically by the system, the same way as adding book,
by getting the latest id from the text file and increasing one.

![Admin Notify Suppliers](/docs/admin/Admin_Notify_Supplier.png)

#### Admin Stock Notifications

Admin can see the notification by choosing 5 in main menu. The system will read the book.txt file and filter out the books that are low or out
of stock. If quantity left is less than or equal to 5, it will show BookTitle is low stock, only left QuantityLeft. If quantity left is 0, it will
display BookTitle is out of stock, need to reorder. Quantity left is calculated by InitialQuantity – SoldQuantity.

![Admin Stock Notification](/docs/admin/Admin_Stock_Noti.png)

#### Admin Supplier List

IF admin choose 6, it will display supplier list. The system will read the user.txt file and filter out the user whose role are equal to supplier. It
will display user id and email of the supplier.

![Admin Suppliers List](/docs/admin/Admin_Supplier_List.png)

#### Admin Transaction List

If admin choose 7 at menu, it will show Transaction Lists. The system will read the data from transactions.txt file and display it back.
It will show the Id (transaction id), user id and email, how much quantity that user bought, price for the book and the total. Total is calculated
by multiplying quantity with price. In this page , admin can see what user bought what book and how many it bought for one transaction.

![Admin Transaction List](/docs/admin/Admin_Transaction_List.png)

#### Admin Add Admin (After successfully added)

If admin choose 8 in the menu, add admin page will be redirected. It will ask admin to add new admin email. The System will validate by not
allowing empty value for email. It will also validate to check if entered email already exists in the system by reading into users.txt file. The
system will not allow users to enter duplicate email. If everything is validated, the system will add user with the entered email, admin as a
role, and default password. The user id will be automatically added by the system, the same way book id is added, by getting the latest user id
and increasing one.

![Admin Add Admin](/docs/admin/Admin_Add_Admin.png)

#### Admin Add Supplier (After Successfully added)

If admin choose 9 in the menu, add supplier page will be redirected. It will ask admin to add new supplier email. The System will validate by
not allowing empty value for email. It will also validate to check if entered email already exists in the system by reading into users.txt file.
The system will not allow users to enter duplicate email. If everything is validated, the system will add user with the entered email, supplier
as a role, and default password. The user id will be automatically added by the system, the same way book id is added, by getting the latest
user id and increasing one.

![Admin Add Supplier](/docs/admin/Admin_Add_Supplier.png)

### User

#### User Menu (After successul login)

This page will display after user successfully login to the system. User can choose 0-2 from the menu.

![User Menu](/docs/user/User_Menu.png)

#### User Buy Book (Book Lists Display)

If user choose 0 in menu, the system will redirect to book page. The system will show all the books as a table list, starting from id, title,
author, stock left and price. These data are read from book.txt file. The system will also display top 3 best-selling books, by bubble sorting
the books. The same function as how top 3 selling books in shown in the Admin UI, Sale Report. User can either go back to menu or press 1
to buy a book.

![User Book List](/docs/user/User_Book_List.png)

#### User Buy Book (After successfully buying a book)

If user press 1 to buy a book in buy book function, the system will first ask user to enter the book id they want to buy. The system will check
if entered id exists in book list or not. If does not exist, it will ask user to retype again. If exist, it will first show the current info of the book,
starting with id, title, author, stock left and price. Then, the system will ask user to enter the quantity to buy. The system will validate so user
cannot enter less than 1 , more than the stock left. The system also only allows to buy maximum of 10 books per transaction. If all is
validated, the system will save the transaction with current login user’s id, book id, quantity, current login user’s email, book title and book
price. The transaction Id will be auto added by the system, by getting the latestId of the transaction by reading from transactions.txt file. The
system will also update the quantity sold field from book.txt file to math with newly sold data.

![User Buy Book](/docs/user/User_Buy_Book.png)

### Supplier

#### Supplier Menu (After successufl login)

This page will be shown after supplier successfully login to the system. Supplier can choose option 0-2.

![Supplier Menu](/docs/supplier/Supplier_Menu.png)

#### Supplier Notifications

If Supplier choose option 0 in menu, it will redirect to supplier notifications page. This page will read data from suppliers_noti.txt file and
filter the data related to current login supplier. The system will only get the data whose supplier id field is the same as current login supplier
id. Then It show in table format, Id(noti id), book id, book title and stock left. It also shows a text saying, “Admin has requested to re-stock
these books which are low or out of stock.” to let supplier know that books need to be restock.

![Supplier Menu](/docs/supplier/Supplier_Noti.png)

### Common UIs

#### Reset Password

The system user can reset their account password. The system will ask to fill out both new password and confirm password. The system will
validate to check if entered new password and confirm password are the same. It will also check to make sure that password cannot be blank.
If everything is validated, the system will update the user.txt file with the new password.

![Reset Password](/docs/common/Reset_Password.png)

#### Option Menu (After successfully Logout)

This page will show after system user has decided to logout. They can choose 0-3

![Option Menu](/docs/common/Option_Menu.png)

#### Program Quit

This page will be shown after system user decided to quite the program.

![Program Quit](/docs/common/Program_Quit.png)

#### Login Page

The system will ask email and password to enter and check with the data form user.txt file. If both email and password are same as data from
the file. It will set the isLogin value to true and redirect to respective menu pages depending on role (admin, user, supplier). It will also set
current login user structure value with data from file.

![Login Page](/docs/common/Login.png)

#### Sign Up Page

The system will ask user to enter email, password and confirm password. It will validate so email and password cannot be empty. It will also
validate so user cannot put existing email by reading and checking with the data from users,txt file. If everything is passed, it will set the role
to user, save it to the file and redirect to user menu. It will also set current login user value with the sign-up user data.

![Signup Page](/docs/common/Signup.png)

#### Forget Password(Successfully Reseted)

The system will ask for user to enter the email first. It will then find that email address inside the users.txt file. If not found, the system will
display cannot find email and ask to re-enter again. If found, the system will ask to enter password and confirm password. The system will
validate so password cannot be an empty value. If everything validated, the system will update the password in users.txt file. If password
reset successfully, user can go back to menu to try login with new password.

![Forget Password Page](/docs/common/Forget_Password.png)
