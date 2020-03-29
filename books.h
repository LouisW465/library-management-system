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
    void bookLoan(string usr);
    void bookReturn(string usr);
    void bookView();
};

void books::bookView() {
    //same JSON parser in main.cpp but for the JSON file that stores all books that can be rented
    ifstream bookFile("book.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(bookFile, root);

    printf("\033c");  
    //Loops through JSON data and prints the elements title and author for each book
    for (int i = 0; i < root["books"].size(); i++) {
        string title = root["books"][i]["title"].asString();
        string author = root["books"][i]["author"].asString();
        string quantity = root["books"][i]["quantity"].asString();
        cout << "TITLE: " << title << "\n" << "AUTHOR: " << author << "\n" << "QUANTITY: " << quantity << "\n\n";
    }
}

void books::bookLoan(string usr) {
    bookView();
}

void books::bookReturn(string usr) {
    bookView();
}

void books::bookAdd() {
    ifstream bookFile("book.json");
    Json::Value val;
    Json::Value newVal;
    Json::Value arr(Json::arrayValue);
    Json::Reader reader;
    reader.parse(bookFile, val);
    bookFile.close();
    string title, author;
    int quantity, bookNo;

    bookNo = val["books"].size();
    bookNo++;
    cout << bookNo;

    cout << "Please enter the book details." << "\n\n";
    cout << "\tTitle: ";
    cin >> title;
    cout << "\n\tAuthor: ";
    cin >> author;
    cout << "\n\tQuantity: ";
    cin >> quantity;

    newVal["title"] = title;
    newVal["author"] = author;
    newVal["bookNo"] = bookNo;
    newVal["quantity"] = quantity;

    val["books"].append(newVal);

    ofstream writeFile("book.json");
    Json::StyledWriter writer;
    writeFile << writer.write(val);
    writeFile.close();

    printf("\033c"); 
    cout << "\nThe book has successfuly been added to the system.\n\n"; 

}

void books::bookDelete() {
    
}