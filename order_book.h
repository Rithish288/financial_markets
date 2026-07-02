//
// Created by Rithish K R on 04/06/2026.
//

#ifndef FINANCIAL_MARKETS_ORDER_BOOK_H
#define FINANCIAL_MARKETS_ORDER_BOOK_H

#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include "order.h"

struct CompareBid {
    bool operator()(const Order& lhs, const Order& rhs) const {
        if (lhs.price != rhs.price)
            return lhs.price > rhs.price;
        return lhs.timestamp < rhs.timestamp;
    }
};
struct CompareAsk {
    bool operator()(const Order& lhs, const Order& rhs) const {
        if (lhs.price != rhs.price)
            return lhs.price < rhs.price;
        return lhs.timestamp < rhs.timestamp;
    }
};
struct PriceLevel {
    double price;
    uint32_t vol;
    std::list<Order> orders;
};
class OrderBook {
public:
    /**
     * Creates and adds a new order to the order queue
     * @param price the price (per share) of the bid/ask
     * @param quantity the number of shares to buy
     * @param is_bid 1=bid and 0=ask
     * @return the id of the order
     */
    ID add_order(double price, uint32_t quantity, bool is_bid);
    void print_stats();

    ~OrderBook();

private:
    ID add_bid(Order& order);
    ID add_ask(Order& order);
    std::map<double, PriceLevel, std::greater<>> bid_orders;
    std::map<double, PriceLevel, std::less<>> ask_orders;
    std::unordered_map<ID, std::list<Order>::iterator> order_lookup;

    uint64_t bid_orders_count = 0;
    uint64_t ask_orders_count = 0;
    uint64_t matched_orders_count = 0;
};

#endif //FINANCIAL_MARKETS_ORDER_BOOK_H