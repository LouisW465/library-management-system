#include "menu.h"
#include "accounts.h"
#include "books.h"
#include "jsoncpp/json/json.h"

#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream accountFile("account.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(accountFile, root);

    string username;
    string password;
    string a;

    /* Clears console before program writes to it*/
    printf("\033c");    

    cout << "\n\t-LIBRARY MANAGEMENT SYSTEM LOGIN-" << "\n\n";       
    cout << " Are you a student or an admin: ";
    cin >> a;
    if (a == "Student" || a == "student") {
        printf("\033c");   
        cout << " Please enter your library account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
        string correctUsr, correctPswd;

        for (int i = 0; i < root["accounts"].size(); i++) {
            correctUsr = root["accounts"][i]["username"].asString();
            correctPswd = root["accounts"][i]["password"].asString();

            if (username == correctUsr && password == correctPswd) {
                menu m;
                m.mainMenu(username);
            }
        }   

    } else if (a == "Admin" || a == "admin") {
        printf("\033c");   
        cout << " Please enter your admin account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
        string correctUsr, correctPswd, isAdmin;

        for (int i = 0; i < root["accounts"].size(); i++) {
            correctUsr = root["accounts"][i]["username"].asString();
            correctPswd = root["accounts"][i]["password"].asString();
            isAdmin = root["accounts"][i]["isadmin"].asString();
            if (username == correctUsr && password == correctPswd && isAdmin == "true") {
                menu m;
                m.adminMenu(username);
            }
        }   

    } else {
        cout << "ERROR: Please enter either student or admin. Restartng ..." << endl;
        usleep(1000000);
        main();
    }
}