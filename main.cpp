#include "menu.h"
#include "accounts.h"
#include "books.h"

#include <unistd.h>

int main() {

    string username;
    string password;
    string a;

    /* Clears console before program writes to it*/
    printf("\033c");    

    cout << "\n\t-LIBRARY MANAGEMENT SYSTEM-" << "\n\n";       
    cout << " Are you a Student or an Admin: ";
    cin >> a;
    if (a == "Student") {
        printf("\033c");   
        cout << " Please enter your library account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
    } else if (a == "Admin") {
        printf("\033c");   
        cout << " Please enter your admin account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
    } else {
        cout << "ERROR: Please enter correct input. Restartng ..." << endl;
        usleep(1000000);
        main();
    }
}