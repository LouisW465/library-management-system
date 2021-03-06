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
    int bookNo = 0, quantity = 0;
    string title = "";

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
        ifstream accountFile("account.json");
        Json::Value val;
        
        Json::Value arr(Json::arrayValue);
        Json::Reader reader;
        reader.parse(accountFile, val);
        accountFile.close();

        for (int i = 0; val["accounts"].size(); i++) {
            if (usr == val["accounts"][i]["username"].asString()) {
                arr = val["accounts"][i]["bookNo"];
                arr.append(bookNo);
                val["accounts"][i]["bookNo"] = arr;
                quantity -= 1;
                ofstream writeFile("account.json");
                Json::StyledWriter writer;
                writeFile << writer.write(val);
                writeFile.close();

                cout << "\n The book has been loaned successfully.\n\n";
                break;
            }
        }
        
        ifstream readUpdate("book.json");
        reader.parse(readUpdate, val);
        readUpdate.close();
        int newQuantity = val["books"][bookNo - 1]["quantity"].asInt() - 1;   //NEED TO MODIFY THIS AND PUT IT BACK INTO THE FILE
        Json::Value quant = newQuantity;

        val["books"][bookNo - 1]["quantity"] = quant;

        ofstream writeUpdate("book.json");
        Json::StyledWriter writer;
        writeUpdate << writer.write(val);
        writeUpdate.close();    

    } else if (a == "N" || a == "n")
    {
        bookLoan(usr);
    }
    
    cout << "\n\nThe book has been loaned successfully.\n";
}

void books::bookReturn(string usr) {
    ifstream accountFile("account.json");
    Json::Value val;
    Json::Value newBookNo(Json::arrayValue);
    Json::Reader reader;
    reader.parse(accountFile, val);
    int returnNo, i;

    for (i = 0; i < val["accounts"].size(); i++) {
        if (usr == val["accounts"][i]["username"].asString()) {
            
            cout << val["accounts"][i]["bookNo"] << "\n\n";
            cout << "\nPlease select the book you would like to return: " << endl;
            cin >> returnNo;
            if (returnNo != val["accounts"][i]["bookNo"][0].asInt()) {
                printf("ERROR book has not been loaned");
                printf("\033c"); 
                bookReturn(usr);
            }
            for (int j = 0; j < val["accounts"][i]["bookNo"].size(); j++) {
                if (returnNo == val["accounts"][i]["bookNo"][j].asInt()) {
                    continue;
                }
                newBookNo.append(val["accounts"][i]["bookNo"][j]);
            }
            val["accounts"][i]["bookNo"] = newBookNo;
        }
    }

    ofstream writeUpdate("account.json");
    Json::StyledWriter writer;
    writeUpdate << writer.write(val);
    writeUpdate.close();

    ifstream readReturn("book.json");
    reader.parse(readReturn, val);
    readReturn.close();
    int newQuantity = val["books"][returnNo - 1]["quantity"].asInt() + 1;   //NEED TO MODIFY THIS AND PUT IT BACK INTO THE FILE
    Json::Value quant = newQuantity;

    val["books"][returnNo - 1]["quantity"] = quant;

    ofstream writeReturn("book.json");
    writeReturn << writer.write(val);
    writeReturn.close();    

    printf("\033c"); 
    cout << "\n\nThe book has been returned successfully.\n";
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

    cout << "\n\nThe book has been deleted successfully.\n";
}