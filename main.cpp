#include <iostream>
#include "order_book.h"
#include "trade_logger.h"

int main() {
    TradeLogger::init("trades.csv");
    OrderBook book;
    // Add some resting asks
    book.add_order(100.0, 10, false); // ask: 10 units @ £100
    book.add_order(101.0, 5,  false); // ask: 5 units  @ £101

    // Add some resting bids
    book.add_order(99.0, 8, true);    // bid: 8 units  @ £99
    book.add_order(98.0, 12, true);   // bid: 12 units @ £98

    // This bid should match against the £100 ask
    book.add_order(100.0, 6, true);   // bid: 6 units  @ £100

    // This ask should match against the £99 bid
    book.add_order(99.0, 3, false);   // ask: 3 units  @ £99

    return 0;
}
