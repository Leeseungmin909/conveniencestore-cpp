#include "Product.h"
using namespace std;

Product::Product(const string& name, int quantity, int price) {
	ItemName = name;
	ItemQuantity = quantity;
	ItemPrice = price;
}

const string& Product::getName() {
	return ItemName;
}

int Product::getQuantity() {
	return ItemQuantity;
}

int Product::getPrice() {
	return ItemPrice;
}

void Product::setQuantity(int quantity) {
	ItemQuantity = quantity;
}