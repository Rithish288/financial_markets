//
// Created by Rithish K R on 04/06/2026.
//

#include "order_book.h"

#include <iostream>

#include "trade_logger.h"

ID OrderBook::add_order(const double price, const uint32_t quantity, const bool is_bid) {
    Order order(price, quantity);
    return is_bid ? add_bid(order) : add_ask(order);
}

ID OrderBook::add_bid(Order& order) {
    bid_orders_count++;
    // Loop through the asking price levels to find matching ask
    for (auto it = ask_orders.begin(); it != ask_orders.end() && order.quantity > 0;) {
        auto&[price, vol, orders] = it->second;
        if (price > order.price) break;

        // Loop through orders at the price level
        for (auto oit = orders.begin(); oit != orders.end() && order.quantity > 0;) {
            const uint32_t matched_quantity = std::min(order.quantity, oit->quantity);
            order.quantity -= matched_quantity;
            oit->quantity -= matched_quantity;
            vol -= matched_quantity;
            TradeLogger::log(price, matched_quantity, "AAPL", true);
            matched_orders_count++;
            if (oit->quantity == 0) {
                // Unlink the order from lookup and erase it from the price level
                order_lookup.erase(oit->order_id);
                oit = orders.erase(oit);
            } else ++oit;
        }
        if (orders.empty()) {
            it = ask_orders.erase(it);
        } else ++it;
    }

    // If the order is not fully filled
    if (order.quantity > 0) {
        auto&[price, vol, orders] = bid_orders[order.price];
        price = order.price;
        vol += order.quantity;
        orders.push_back(order);
        // Link order lookup to the end of the list
        order_lookup[order.order_id] = std::prev(orders.end());
    }
    return order.order_id;
}

ID OrderBook::add_ask(Order& order) {
    ask_orders_count++;
    // Loop through the asking price levels to find matching ask
    for (auto it = bid_orders.begin(); it != bid_orders.end() && order.quantity > 0;) {
        auto&[price, vol, orders] = it->second;
        if (price < order.price) break;

        // Loop through orders at the price level
        for (auto oit = orders.begin(); oit != orders.end() && order.quantity > 0;) {
            const uint32_t matched_quantity = std::min(order.quantity, oit->quantity);
            order.quantity -= matched_quantity;
            oit->quantity -= matched_quantity;
            vol -= matched_quantity;
            TradeLogger::log(price, matched_quantity, "MSFT", false);
            matched_orders_count++;
            if (oit->quantity == 0) {
                // Unlink the order from lookup and erase it from the price level
                order_lookup.erase(oit->order_id);
                oit = orders.erase(oit);
            } else ++oit;
        }
        if (orders.empty()) {
            it = bid_orders.erase(it);
        } else ++it;
    }

    // If the order is not fully filled
    if (order.quantity > 0) {
        auto&[price, vol, orders] = ask_orders[order.price];
        price = order.price;
        vol += order.quantity;
        orders.push_back(order);
        // Link order lookup to the end of the list
        order_lookup[order.order_id] = std::prev(orders.end());
    }
    return order.order_id;
}

void OrderBook::print_stats() {
    std::cout << std::endl;
    std::cout << "Total bid orders: " << bid_orders_count << '\n';
    std::cout << "Total ask orders: " << ask_orders_count << '\n';
    std::cout << "Total orders in book: " << order_lookup.size() << '\n';
    std::cout << "Total orders matched: " << matched_orders_count << std::endl;
}

OrderBook::~OrderBook() = default;
