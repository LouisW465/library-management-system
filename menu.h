#include "books.h"

#include <string>
#include <iostream>

using namespace std;

class menu {
public:
    void mainMenu(string usr);
};

class admMenu {
public:
    void adminMenu(string usr);
};

void menu::mainMenu(string usr) {
    books b;
    string a;
    printf("\033c");  
    cout << "\n\t---------------------------" << endl;
    cout << "\t LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "\t---------------------------\n\n" << endl;
    cout << " Welcome: " << usr << "\n\n";
    cout << "Would you like to:\n\t1.Loan a book.\n\t2.Return a book.\n\t3.Search for a book.\n\n";
    cin >> a;

}

void admMenu::adminMenu(string usr) {
    string a;
    printf("\033c");  
    cout << "\n\t--------------------" << endl;
    cout << "\t LIBRARY ADMIN PANEL" << endl;
    cout << "\t--------------------\n\n" << endl;
    cout << " Welcome: " << usr << "\n\n";
    cout << "Would you like to:\n\t1.Add an account.\n\t2.Delete an account.\n\t3.Edit an accounts details.\n\t";
    cout << "4.Add a book.\n\t5.Delete a book.\n\n";
    cin >> a;
    
}