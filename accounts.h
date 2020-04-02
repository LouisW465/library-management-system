#pragma once
#include "jsoncpp/json/json.h"

#include <string>
#include <fstream>

using namespace std;

class accounts {
private:
    string accountName;
    string accountPassword;

protected:
    void accountAdd();
    void accountDelete();
    void accountEdit();
};

void accounts::accountAdd() {
    ifstream accountFile("account.json");
    Json::Value val;
    Json::Value newVal;
    Json::Value arr(Json::arrayValue);
    Json::Reader reader;
    reader.parse(accountFile, val);
    accountFile.close();
    string newUser, newPass, isAdmin;

    cout << "Please enter the account details." << "\n\n";
    cout << "\tUsername: ";
    cin >> newUser;
    cout << "\n\tPassword: ";
    cin >> newPass;
    cout << "\n\tIs this an admin account(true or false): ";
    cin >> isAdmin;

    newVal["username"] = newUser;
    newVal["password"] = newPass;
    newVal["bookNo"] = arr;
    newVal["isadmin"] = isAdmin;

    val["accounts"].append(newVal);

    ofstream writeFile("account.json");
    Json::StyledWriter writer;
    writeFile << writer.write(val);
    writeFile.close();

    printf("\033c"); 
    cout << "\nThe account has successfuly been added to the system.\n\n";
}

void accounts::accountDelete() {
    ifstream accountFile("account.json");
    Json::Value val;
    Json::Value newVal;
    Json::Reader reader;
    reader.parse(accountFile, val);
    accountFile.close();

    string del, line;
    int skip = 4;

    printf("\033c"); 
    cout << "\nPlease enter the username of the account you would like to delete: \n";
    cin >> del;
    
    for (int i = 0; i < val["accounts"].size(); ++i) {
        string a = val["accounts"][i]["username"].asString();
        if (del == a) {
            skip = i;
            break;
        }
    }
    for (int j = 0; j < val["accounts"].size(); ++j) {
        if (j != skip) {
            newVal["accounts"][j] = val["accounts"][j];
        } 
    }
    
    ofstream writeFile("account.json");
    Json::StyledWriter writer;
    writeFile << writer.write(newVal);
    writeFile.close();
    
    string n = "null";
    ifstream readFile("account.json");
    ofstream delNull("temp.json");
    while (getline(readFile, line)) {
        if (line.find(n) != string::npos) {
            continue;
        }
        delNull << line << endl;
    }

    readFile.close();
    delNull.close();
    
    ifstream temp("temp.json");
    ofstream temp2("account.json");

    while (getline(temp, line))
    {
       temp2 << line << endl;
    }
    
    temp.close();
    temp2.close();
    remove("temp.json");

    cout << "\n\nThe account has been deleted successfully.\n";
}

void accounts::accountEdit() {
    ifstream accountFile("account.json");
    Json::Value val, usr, pass;
    Json::Reader reader;
    reader.parse(accountFile, val);
    accountFile.close();
    string edit;
    printf("\033c"); 
    cout << "\nPlease enter the username of the account you would like to delete: \n";
    cin >> edit;

    for (int i = 0; i < val["accounts"].size(); ++i) {
        if (edit == val["accounts"][i]["username"].asString()){
            int a;
            cout << "would you like to edit the username(1) or the password(2) for this account: ";
            cin >> a;
            if (a == 1) {
                string newUsr;
                cout << "Please enter the new username for this account: ";
                cin >> newUsr;
                usr = newUsr;
                val["accounts"][i]["username"] = usr;
                break;
            } else if (a == 2) {
                string newPass;
                cout << "Please enter the new password for this account: ";
                cin >> newPass;
                pass = newPass;
                val["accounts"][i]["password"] = pass;
                break;
            } else {
                printf("\033c");  
                cout << "ERROR: Incorrect input, please try again\n";
                usleep(1000000);
                printf("\033c"); 
                i = 0;
                continue;
            }
        }
    }
    ofstream writeEdit("account.json");
    Json::StyledWriter writer;
    writeEdit << writer.write(val);
    writeEdit.close();

    cout << "\n\nDetails have been updated successfully.\n";
}