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
    void accountView();
    void accountAdd();
    void accountDelete();
    void accountEdit();
};

void accounts::accountView() {

}

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
    
}

void accounts::accountEdit() {
    
}