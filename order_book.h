//
// Created by Rithish K R on 04/06/2026.
//

#ifndef FINANCIAL_MARKETS_ORDER_BOOK_H
#define FINANCIAL_MARKETS_ORDER_BOOK_H
#include <chrono>


class order_book {
};

class order {
    double price;
    int quantity;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};

#endif //FINANCIAL_MARKETS_ORDER_BOOK_H