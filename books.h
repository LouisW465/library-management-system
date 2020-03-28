#pragma once
#include "jsoncpp/json/json.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class books {
private:
    string bookNo;

protected:
    void bookAdd();
    void bookDelete();

public:
    void bookLoan();
    void bookReturn();
    void bookView();
};

void books::bookView() {
    //same JSON parser in main.cpp but for the JSON file that stores all books that can be rented
    ifstream bookFile("book.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(bookFile, root);

    //Loops through JSON data and prints the elements title and author for each book
    for (int i = 0; i < root["books"].size(); i++) {
        string title = root["books"][i]["title"].asString();
        string author = root["books"][i]["author"].asString();
        cout << "TITLE: " << title << "\n" << "AUTHOR: " << author << "\n\n";
    }
}