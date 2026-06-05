//
// Created by Rithish K R on 04/06/2026.
//

#include "order_book.h"

uint64_t OrderBook::add_order(const double price, const uint32_t quantity, const bool is_bid) {
    if (is_bid) {
        return add_bid(price, quantity);
    }
   return add_ask(price, quantity);
}

uint64_t OrderBook::add_bid(const double price, const uint32_t quantity) {
    bid_list.emplace_back(price, quantity);
    return bid_list.back().order_id;
}

uint64_t OrderBook::add_ask(const double price, const uint32_t quantity) {
    ask_list.emplace_back(price, quantity);
    return ask_list.back().order_id;
}

OrderBook::~OrderBook() {
    bid_list.clear();
    ask_list.clear();
}
