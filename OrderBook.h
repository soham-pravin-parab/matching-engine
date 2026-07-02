#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <algorithm>

struct order {
    int id;
    char side;
    double price;
    int quantity;
    order* next;
    order* prev;
};

struct pricelevel {
    double price;
    order* head = nullptr;
    order* tail = nullptr;
};

class OrderBook {
private:
    std::map<double, pricelevel, std::greater<double>> bidBook;
    std::map<double, pricelevel> askbook;

public:
    void processorder(int id, char side, double price, int quantity);
    void printBook();
};

#endif // ORDERBOOK_H

