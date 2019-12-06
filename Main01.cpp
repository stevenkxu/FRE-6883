#include "EquityDivide.h"
#include "SelectRandomStocks.h"
#include <iostream>

int main() {
	EquityDivide divider = EquityDivide("EPS/EPS.csv");
	Group divided_stocks = divider.divide_group();
	//cout << divided_stocks[0][1].first << endl;
	StockShuffler shuffler = StockShuffler(divided_stocks);
	
	for (int i = 0; i < 3; i++) {
		//This code will randomly output 30 stocks!
		Group empty_stocks(3);
		shuffler.ShuffleStocks();
		shuffler.Get30StocksPerGroup(empty_stocks);

		// This is how you can get the ticker of the 30 stocks! Right now, the functionality is to cout them, but this can be used as a string input for the next part of the program
		for (int j = 0; j < 30; j++) {
			cout << empty_stocks[0][j].first << " ";
		}


		cout << endl;
		cout << empty_stocks[0].size() << endl;
	}
	
	system("pause");
	return 0;
}