#include "trade_logger.h"

std::ofstream TradeLogger::file;

void TradeLogger::init(const std::string& filename) {
    if (file.is_open()) {
        file.close();
    }
    file.open(filename, std::ios::out);
    if (file.tellp() == 0)
        file << "timestamp,asset,side,price,quantity\n";
}

void TradeLogger::log(const double price, const uint32_t quantity, const std::string& asset, const bool is_bid) {
    if (!file.is_open()) return;
    file << timestamp() << "," << asset << "," << (is_bid ? "BUY" : "SELL")
         << "," << price << "," << quantity << "\n";
    file.flush();
}

std::string TradeLogger::timestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto t = std::chrono::system_clock::to_time_t(now);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return buf;
}
