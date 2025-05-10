#include "ConvenienceStore.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

ConvenienceStore::ConvenienceStore() {
    loadInventory();
}

void ConvenienceStore::loadInventory() {
    ifstream fin(filename);
    ifstream hin(hilename);
    if (!fin) {
        cerr << "파일 열기 실패" << endl;
        return;
    }
    if (!hin) {
        cerr << "파일 열기 실패" << endl;
        return;
    }

    inventory.clear();
    vecsalesHistory.clear();

    string name;
    int quantity, price;
    while (fin >> name >> quantity >> price) {
        inventory.push_back(Product(name, quantity, price));
    }
    fin.close();

    while (hin >> name >> quantity >> price) {
        stringstream ss;
        ss << name << " " << quantity << " " << price;
        string line = ss.str();
        vecsalesHistory.push_back(line);
    }
    //cout << "vecsalesHistory.size() = " << vecsalesHistory.size() << endl;

}

void ConvenienceStore::saveInventory() {
    ofstream fout(filename);
    if (!fout) {
        cerr << "파일 쓰기 실패" << endl;
        return;
    }
    for (Product& item : inventory) {
        fout << item.getName() << " "
            << item.getQuantity() << " "
            << item.getPrice() << endl;
    }
    fout.close();
}

bool ConvenienceStore::sellProduct(const string& ItemName) {
    for (Product& item : inventory) {
        if (item.getName() == ItemName) {
            if (item.getQuantity() > 0) {
                cout << "구매하실 갯수:";
                int i;
                cin >> i;
                cin.ignore();
                setCount(i);

                if (i <= 0) {
                    cout << "0 이하의 값은 들어올 수 없습니다." << endl;
                    return false;
                }

                if (i > item.getQuantity()) {
                    cout << ItemName << " 재고가 부족합니다" << endl;
                    return false;
                }

                item.setQuantity(item.getQuantity() - getCount());
                saveInventory();
                cout << ItemName << " 판매 완료 , 남은 수량: " << item.getQuantity() << endl;
                setTotalPay(item.getPrice()*getCount());
                loadInventory();
                return true;

            }
            else {
                cout << ItemName << " 재고가 없습니다" << endl;
                return false;
            }
        }
    }
    cout << ItemName << "(은/는) 존재하지 않는 상품입니다." << endl;
    return false;
}

void ConvenienceStore::displayInventory() {
    cout << "=== 현재 재고 ===" << endl;
    for (Product& item : inventory) {
        cout << "상품명: " << item.getName()
            << "/수량: " << item.getQuantity()
            << "/가격: " << item.getPrice() << "원" << endl;
    }
}

bool ConvenienceStore::login(string pass) {
    if (getCorrectPass() == pass) {
        return true;
    }
    else {
        cout << "로그인 fail" << endl;
        return false;
    }
}

string ConvenienceStore::getCorrectPass() {
    return correctPass;
}

void ConvenienceStore::refundFunction(const int& Index) {
    string refundData = vecsalesHistory[Index];
    vecsalesHistory.erase(vecsalesHistory.begin() + Index);
    
    ofstream fout(hilename);
    for (const auto& line : vecsalesHistory) {
        fout << line << endl;
    }
    fout.close();
    //cout << "@test refundData:" << refundData << endl; // 지워야함
    cin.get();

    vector<string> tokens;
    char delemiter = ' ';
    string buf;
    istringstream iss(refundData);
    while (getline(iss, buf, delemiter)) {
        tokens.push_back(buf);
    }
    //cout << tokens[0] << endl; // item 이름
    //cout << tokens[1] << endl; // tokens[1] 의 값이 수량의 갯수이다.    

    int newQuantity = 0;

    for (Product& item : inventory) {
        if (item.getName() == tokens[0]) {
            int newQuantity = item.getQuantity() + stoi(tokens[1]);
            item.setQuantity(newQuantity);  
            break;
        }
    }

    saveInventory();

    cout << tokens[0] << " " << tokens[1] << "개 환불 완료" << endl;
    cin.get();
    loadInventory();
}


int ConvenienceStore::getCount() {
    return count;
}
void ConvenienceStore::setCount(int i) {
    this->count = i;
}
int ConvenienceStore::getTotalPay() {
    return totalPay;
}
void ConvenienceStore::setTotalPay(int i) {
    this->totalPay = i;
}

void ConvenienceStore::addProductFunction(const string& ItemName){    
    for (Product& item : inventory) {
        if (item.getName() == ItemName) {
            cout << "이미 존재하는 상품입니다." << endl;
            return;
        }
    }
    int quantity , price;
    cout << "수량을 입력해주세요:";
    cin >> quantity;
    cout << "가격을 입력해주세요:";
    cin >> price;
    inventory.push_back(Product(ItemName, quantity, price));
    saveInventory();
    cout << "상품이 추가되었습니다." << endl;
    
}

void ConvenienceStore::deleteProductFunction(const string& ItemName) {
    auto it = inventory.begin();
    while (it != inventory.end()) {
        if (it->getName() == ItemName) {
            it = inventory.erase(it);
            saveInventory();
            cout << "상품이 삭제되었습니다." << endl;
            return;
        }
        else {
            it++;
        }
    }
    cout << "상품을 찾을 수 없습니다." << endl;
}

void ConvenienceStore::updateProductFunction(const string& ItemName){
    for (Product& item : inventory) {
        if (item.getName() == ItemName) {
            int newQuantity;
            cout << "변경할 새 수량을 입력하세요: ";
            cin >> newQuantity;
            item.setQuantity(newQuantity);
            saveInventory(); 
            cout << "수량이 변경되었습니다." << endl;
            return;
        }
    }
    cout << "상품을 찾을 수 없습니다." << endl;
}