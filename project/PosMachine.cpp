#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "PosMachine.h"
using namespace std;



/**
* @ 메인 메뉴
*/
void PosMachine::run() {
    int choice;
    while (1) {
        system("cls");
        cout << "==========================================================" << endl;
        cout << "1. 상품목록 보기(판매)" << endl;
        cout << "2. 판매내역 보기(환불)" << endl;
        cout << "3. 메니저 메뉴" << endl;
        cout << "0. 종료" << endl;
        cout << "메뉴를 선택하세요: ";
        cin >> choice;

        switch (choice) {
        case 1: {
             system("cls");
             string Item;
             displayInventory();   // 상품 목록 출력
             cout << "==============================" << endl;
             cout << "구매할 상품명을 입력하세요: ";
             cin >> Item;
             MakePayment(Item); // 결제 함수 호출
             system("pause");
             break;
        }
        case 2:
            system("cls");
            ShowSalesHistory();   // 판매 내역 출력
            cout << "환불을 원하시면 '1' 번을 입력해주세요 :";
            cin >> choice;
            if (choice == 1) {
                refund();
            }
            break;

        case 3:                 // 관리자 모드 진입후 제품 추가 삭제 변경을 가능하게함
        {
            system("cls");
            string pass;
            cout << "비밀번호를 입력하세요 :";
            cin >> pass;
            managerRun(pass);
            break;
        }
        case 0:
            cout << "프로그램을 종료합니다." << endl;
            return;
        default:
            cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
            system("pause");
        }
    }
}

/**
* @ 결제가 완료되면 결제 내역을 salesHistory.txt (구매한 오브젝트의 이름을)파일에 넣는다.
*/
void PosMachine::MakePayment(const string& ItemName) {
    if (sellProduct(ItemName)) {

        string entry = ItemName + " " + to_string(getCount()) + " " + to_string(getTotalPay());
        //cout <<"@test 값" << ItemName + " " + to_string(getCount()) + " " + to_string(getTotalPay());
        vecsalesHistory.push_back(entry);


        ofstream hout(hilename, ios::app); // 판매 내역 기록
        hout << ItemName << " " << to_string(getCount()) << " " << to_string(getTotalPay()) << endl;
        hout.close();
    }

}

/**
* @ saleHistory.txt를 불러들여 판매내역(판매된 오브젝트 이름)을 출력한다.
*/
void PosMachine::ShowSalesHistory() {
    system("cls");
    ifstream fin(hilename);
    if (!fin) {
        cout << "판매 내역이 없습니다." << endl;
        return;
    }

    int count = 1;
    //cout << "판매내역 길이" << lines.size() << endl;
    cout << "=== 판매 내역 ===" << endl;
    for (int i = vecsalesHistory.size() - 1; i >= 0; i--, count++) {
        cout << '[' << count << ']' << vecsalesHistory[i] << endl;
    }
}

void PosMachine::refund() { 
    int choice;
    cout << "=================================" << endl;
    cout << "환불할 인덱스 번호를 입력하세요 ('1' 부터 시작): ";
    cin >> choice;

    int Index = vecsalesHistory.size() - choice;

    if (choice < 1 || choice > vecsalesHistory.size()) {
        cout << "잘못된 인덱스 번호 입니다 다시 입력해주세요." << endl;
        cin.get();
        return;
    }
    //cout << "@test refundFunction 호출됨, index=" << Index << endl;
    //cout << "@test 환불 처리: " << vecsalesHistory[Index] << endl;
    refundFunction(Index);
}



/**
* @ 메니저 메뉴
*/
void PosMachine::managerRun(string pass) {
    int choise;

    if (login(pass)) {
        while (1) {
            system("cls");
            displayInventory();
            cout << "========메니저 메뉴==========" << endl;
            cout << "1. 제품 추가" << endl;
            cout << "2. 제품 삭제" << endl;
            cout << "3. 제품수량 변경" << endl;
            cout << "4. 메인 메뉴로 가기" << endl;
            cout << "==============================" << endl;
            cin >> choise;

            switch (choise) {
            case 1: {
                addProduct();
                system("pause");
                break;
            }
            case 2:
                deleteProduct();
                system("pause");
                break;
            case 3:
                updateProduct();
                system("pause");
                break;
            case 4:
                run();
                system("pause");
            default:
                cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
                system("pause");
            }
        }
    }
}

/**
* @ 제품 추가
*/
void PosMachine::addProduct() {
    cout << "추가하실 제품의 이름을 입력해주세요(띄어쓰기 금지):";
    string itemName;
    cin >> itemName;
    addProductFunction(itemName);
}

/**
* @ 제품 변경 (이름은 변경 불가 , 이름을 변경하고 싶으면 제품 삭제후 추가)
*/
void PosMachine::deleteProduct() {
    cout << "삭제하실 제품의 이름을 입력해주세요(띄어쓰기 금지):";
    string itemName;
    cin >> itemName;
    deleteProductFunction(itemName);
}

/**
* @ 제품 삭제
*/
void PosMachine::updateProduct() {
    cout << "변경하실 제품의 이름을 입력해주세요(띄어쓰기 금지):";
    string itemName;
    cin >> itemName;
    updateProductFunction(itemName);
}