#include "EquityDivide.h"
#include "SelectRandomStocks.h"
#include <iostream>

int main() {
	EquityDivide divider = EquityDivide("EPS/EPS.csv");
	Group divided_stocks = divider.divide_group();
	//cout << divided_stocks[0][1].first << endl;
	StockShuffler shuffler = StockShuffler(divided_stocks);
	
	for (int i = 0; i < 3; i++) {
		Group empty_stocks(3);
		shuffler.ShuffleStocks();
		shuffler.Get30StocksPerGroup(empty_stocks);
		cout << empty_stocks[0][1].first << endl;
		cout << empty_stocks[0].size() << endl;
	}
	
	system("pause");
	return 0;
}