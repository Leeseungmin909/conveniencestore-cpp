#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>

using namespace std;

class Product {
private:
    string ItemName;    //상품 이름
    int ItemQuantity;   //상품 수량
    int ItemPrice;      //상품 가격
public:
    Product(const string& name, int quantity, int price);
    const string& getName();
    int getQuantity();
    int getPrice();
    void setQuantity(int q);
};

#endif // !PRODUCT_H