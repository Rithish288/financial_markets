//
// Created by Rithish K R on 29/06/2026.
//

#ifndef FINANCIAL_MARKETS_TRADE_SIMULATOR_H
#define FINANCIAL_MARKETS_TRADE_SIMULATOR_H

#include <random>

#include "order_book.h"

class TradeSimulator {
public:
    void generateTrades(const int& n);
    TradeSimulator(OrderBook& lob, const unsigned int& seed):
        engine(seed), arrival_dist(.1), volume_dist(0.1), price_dist(10.0, 0.25),
        side_dist(0.5), lob(lob){
    }
private:
    OrderBook& lob;

    std::mt19937 engine;

    // Distributions for different order features
    std::exponential_distribution<double> arrival_dist; // Timing (Lambda = 0.1, ~10ms average arrival)
    std::geometric_distribution<uint32_t> volume_dist;     // Size (multiple small orders and few institutional orders)
    std::normal_distribution<double> price_dist;         // Price (Centered around mid-price)
    std::bernoulli_distribution side_dist;               // Buy vs Sell (50/50 chance)
};


#endif //FINANCIAL_MARKETS_TRADE_SIMULATOR_H