#include <string>
#include <iostream>

using namespace std;

class menu {
private:
    string username;
    string password;
    
public:
    void mainMenu();
    void adminMenu();
};

void menu::mainMenu() {
    cout << "---------------------------" << endl;
    cout << " LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "---------------------------" << endl;
}

void menu::adminMenu() {

}