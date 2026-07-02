//
// Created by Rithish K R on 29/06/2026.
//

#ifndef FINANCIAL_MARKETS_ORDER_H
#define FINANCIAL_MARKETS_ORDER_H

using ID = uint64_t;

struct Order {
    double price;
    uint32_t quantity;
    uint64_t timestamp;

    ID order_id;
    inline static ID order_id_counter = 0;
    Order(const double price, const uint32_t quantity) :
    price(price),
    quantity(quantity),
    order_id(order_id_counter++) {
        const auto now = std::chrono::high_resolution_clock::now();
        timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    };
};

#endif //FINANCIAL_MARKETS_ORDER_H