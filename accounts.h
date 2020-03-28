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
    Json::Value appendEntry;   
    Json::Value arr(Json::arrayValue);

    ofstream accountFile("account.json");
    //Json::Reader reader;
    //Json::Value root;
    //reader.parse(accountFile, root);

    appendEntry["username"] = "newUser";
    appendEntry["password"] = "newPassword";
    appendEntry["bookNo"] = arr;
    appendEntry["isadmin"] = "false";

    accountFile << appendEntry;
}

void accounts::accountDelete() {
    
}

void accounts::accountEdit() {
    
}