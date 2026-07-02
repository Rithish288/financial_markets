//
// Created by Rithish K R on 29/06/2026.
//

#include "trade_simulator.h"
#include <random>
#include <chrono>
#include <thread>

void TradeSimulator::generateTrades(const int &n) {
    for (size_t i = 0; i < n; ++i) {
        int delay = static_cast<int>(arrival_dist(engine));
        // std::cout << "Trade created with delay: " << delay << "ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        lob.add_order(price_dist(engine), volume_dist(engine), side_dist(engine));
    }
}
