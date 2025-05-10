#pragma once
#ifndef POSMACHINE_H
#define POSMACHINE_H
#include "ConvenienceStore.h"
#include <iostream>
#include <string>

class PosMachine : public ConvenienceStore {
public:
    void MakePayment(const string& ItemName);
    void run();
    void ShowSalesHistory();
    void addProduct();
    void deleteProduct();
    void updateProduct();
    void managerRun(string pass);
    void refund();
};

#endif // !POSMACHINE_H