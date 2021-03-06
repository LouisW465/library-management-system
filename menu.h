#pragma once
#include "books.h"
#include "accounts.h"

#include <string>
#include <iostream>

using namespace std;

class menu {
public:
    void mainMenu(string usr);
};

class admMenu : books, accounts {
public:
    void adminMenu(string usr);
};

void menu::mainMenu(string usr) {
    //Main menu for students that will allow them to call the public functions from books for loaning/returning/searching
    int a;
    printf("\033c");  
    cout << "\n\t---------------------------" << endl;
    cout << "\t LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "\t---------------------------\n\n" << endl;
    cout << " Welcome: " << usr << "\n\n";
    cout << "Would you like to:\n\t1.Loan a book.\n\t2.Return a book.\n\t3.Search for a book.\n\n";
    cin >> a;
    books b;
    switch (a) {
        case 1:
            b.bookLoan(usr);
            break;
        case 2:
            b.bookReturn(usr);
            break;
        case 3:
            b.bookView();
            break;
        default:
            printf("Error");
    }   
}

void admMenu::adminMenu(string usr) {
    //Admin panel for admin accounts, allowing them to perform all admin operations such as manipulating accounts and books
    int a;
    printf("\033c");  
    cout << "\n\t--------------------" << endl;
    cout << "\t LIBRARY ADMIN PANEL" << endl;
    cout << "\t--------------------\n\n" << endl;
    cout << " Welcome: " << usr << "\n\n";
    cout << "Would you like to:\n\t1.Add an account.\n\t2.Delete an account.\n\t3.Edit an accounts details.\n\t";
    cout << "4.Add a book.\n\t5.Delete a book.\n\n";
    cin >> a;
    
    switch (a) {
        case 1:
            accountAdd();
            break;
        case 2:
            accountDelete();
            break;
        case 3:
            accountEdit();
            break;
        case 4:
            bookAdd();
            break;
        case 5:
            bookDelete();
            break;
        default:
            printf("Error");
    }
}