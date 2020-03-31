#pragma once
#include "jsoncpp/json/json.h"

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

class books {
private:
    string bookNo;

protected:
    void bookAdd();
    void bookDelete();
    void bookEdit();

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
    bookFile.close();
    printf("\033c");  
    //Loops through JSON data and prints the elements title and author for each book
    for (int i = 0; i < root["books"].size(); i++) {
        string title = root["books"][i]["title"].asString();
        string author = root["books"][i]["author"].asString();
        int quantity = root["books"][i]["quantity"].asInt();
        if (quantity == 0) {
            cout << "TITLE: " << title << "\n" << "AUTHOR: " << author << "\n" << "QUANTITY: " << "OUT OF STOCK" << "\n\n";
        } else {
            cout << "TITLE: " << title << "\n" << "AUTHOR: " << author << "\n" << "QUANTITY: " << quantity << "\n\n";
        }
    }
}

void books::bookLoan(string usr) {
    bookView();
    int bookNo, quantity;
    string title;

    ifstream bookFile("book.json");
    Json::Reader reader;
    Json::Value root;
    reader.parse(bookFile, root);
    bookFile.close();

    cout << "\n\nPlease select the book you would like to loan(bookNo): ";
    cin >> bookNo;
    
    for (int i = 0; i < root["books"].size(); i++) {
        if (bookNo == root["books"][i]["bookNo"].asInt()) {
            title = root["books"][i]["title"].asString();
            quantity = root["books"][i]["quantity"].asInt();
            if (quantity == 0) {
                printf("\033c");  
                cout << "ERROR: this book is out of stock, please select one that is in stock, thank you. \n";
                usleep(1000000);
                bookLoan(usr);
            } 
            break;
        }
    }
    string a;
    cout << "\nThe book you have chosen is: " << title << " Would you like to loan this book? (Y or N) "; 
    cin >> a;

    if (a == "Y" || a == "y") {
        
    } else if (a == "N" || a == "n")
    {
        bookLoan(usr);
    }
    
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
    ifstream bookFile("book.json");
    Json::Value val;
    Json::Value newVal;
    Json::Reader reader;
    reader.parse(bookFile, val);
    bookFile.close();

    string line;
    int skip, del;

    printf("\033c"); 
    cout << "\nPlease enter the bookNo of the book you would like to delete: \n";
    cin >> del;
    
    for (int i = 0; i < val["books"].size(); ++i) {
        int a = val["books"][i]["bookNo"].asInt();
        if (del == a) {
            skip = i;
            break;
        }
    }
    for (int j = 0; j < val["books"].size(); ++j) {
        if (j != skip) {
            newVal["books"][j] = val["books"][j];
        } 
    }
    
    ofstream writeFile("book.json");
    Json::StyledWriter writer;
    writeFile << writer.write(newVal);
    writeFile.close();
    
    string n = "null";
    ifstream readFile("book.json");
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
    ofstream temp2("book.json");

    while (getline(temp, line))
    {
       temp2 << line << endl;
    }
    
    temp.close();
    temp2.close();
    remove("temp.json");    
}

void books::bookEdit() {

}