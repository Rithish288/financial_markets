//
// Created by Rithish K R on 04/06/2026.
//

#ifndef FINANCIAL_MARKETS_ORDER_BOOK_H
#define FINANCIAL_MARKETS_ORDER_BOOK_H

#include <chrono>
#include <list>

struct Order {
    double price;
    uint32_t quantity;
    uint64_t timestamp;
    uint64_t order_id;
    inline static uint64_t order_id_counter = 0;
    Order(const double price, const uint32_t quantity) :
    price(price),
    quantity(quantity),
    order_id(order_id_counter++) {
        const auto now = std::chrono::high_resolution_clock::now();
        timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    };
};

class OrderBook {
public:
    std::vector<Order> bid_list;
    std::vector<Order> ask_list;

    /**
     * Creates and adds a new order to the order queue
     * @param price the price (per share) of the bid/ask
     * @param quantity the number of shares to buy
     * @param is_bid 1=bid and 0=ask
     * @return the id of the order
     */
    uint64_t add_order(double price, uint32_t quantity, bool is_bid);
    void remove_order(uint64_t order_id);
    void match_orders();

    ~OrderBook();

private:
    uint64_t add_bid(double price, uint32_t quantity);
    uint64_t add_ask(double price, uint32_t quantity);
};

#endif //FINANCIAL_MARKETS_ORDER_BOOK_H