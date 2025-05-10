#pragma once
#pragma once
#ifndef CONVENIENCESTORE_H
#define CONVENIENCESTORE_H
#include "Product.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ConvenienceStore {
private:
    void loadInventory();
    void saveInventory();
    string correctPass = "20203188";
    int count = 0;  
    int totalPay = 0;
protected:
    string filename = "inventory.txt";
    string hilename = "salesHistory.txt";
    vector<Product> inventory;
    vector<string> vecsalesHistory;
public:
    ConvenienceStore();
    int getCount();
    void setCount(int i);
    int getTotalPay();
    void setTotalPay(int i);
    string getCorrectPass();
    bool sellProduct(const string& ItemName);
    void displayInventory();
    bool login(string pass);
    void refundFunction(const int& Index);
    void addProductFunction(const string& ItemName);
    void deleteProductFunction(const string& ItemName);
    void updateProductFunction(const string& ItemName);
};

#endif // !CONVENIENCESTORE_H