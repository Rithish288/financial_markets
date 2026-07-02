#include "order_book.h"
#include "trade_logger.h"
#include "trade_simulator.h"

int main() {
    TradeLogger::init("trades.csv");
    OrderBook book;
    TradeSimulator trade_sim(book, 0);
    trade_sim.generateTrades(100);
    book.print_stats();
    return 0;
}
