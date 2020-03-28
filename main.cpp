#include "menu.h"
#include "accounts.h"
#include "books.h"
#include "jsoncpp/json/json.h"

#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    //JSON parser setup, stores all data from account JSON file in root
    ifstream accountFile("account.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(accountFile, root);

    string username;
    string password;
    string a;

    //Clears console before program writes to it
    printf("\033c");    

    cout << "\n\t-LIBRARY MANAGEMENT SYSTEM LOGIN-" << "\n\n";       
    cout << " Are you a student or an admin: "; //Prompts the user to choose whether they are a student or an admin
    cin >> a;
    if (a == "Student" || a == "student") {
        //User input from here is used to check whether the entered username+password combo is inside the JSON file
        printf("\033c");   
        cout << " Please enter your library account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
        string correctUsr, correctPswd;
        //Loops through each element in "accounts", each iterations stores each username and password and then checks it against user input
        //If correct, mainMenu function will be called from menu class
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
        //User input from here is used to check whether the entered username+password combo is inside the JSON file
        cout << " Please enter your admin account username and password." << "\n\n";
        cout << " Username: ";
        cin >> username;
        cout << " Password: ";
        cin >> password;
        string correctUsr, correctPswd, isAdmin;
        //Loops through the same as above but also stored the "isadmin" element of each account 
        //to ensure that the account to login to the admin panel is actually an admin account
        for (int i = 0; i < root["accounts"].size(); i++) {
            correctUsr = root["accounts"][i]["username"].asString();
            correctPswd = root["accounts"][i]["password"].asString();
            isAdmin = root["accounts"][i]["isadmin"].asString();
            if (username == correctUsr && password == correctPswd && isAdmin == "true") {
                admMenu m;
                m.adminMenu(username);
            }
        }   

    } else {    
        cout << "ERROR: Please enter either student or admin. Restartng ..." << endl;
        usleep(1000000);
        main();
    }
}