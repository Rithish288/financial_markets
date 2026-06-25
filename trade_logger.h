//
// Created by Rithish K R on 25/06/2026.
//

#ifndef FINANCIAL_MARKETS_TRADE_LOGGER_H
#define FINANCIAL_MARKETS_TRADE_LOGGER_H

#include <fstream>
#include <chrono>
#include <string>

class TradeLogger {
public:
    static void init(const std::string& filename);

    static void log(const double price, const uint32_t quantity, const std::string& asset, const bool is_bid);
private:
    static std::ofstream file;

    static std::string timestamp();
};

#endif //FINANCIAL_MARKETS_TRADE_LOGGER_H