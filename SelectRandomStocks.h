#pragma once
#ifndef SelectRandomStocks_h
#define SelectRandomStocks_h
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "EquityDivide.h"
using namespace std;

class StockShuffler {
private:
	//this data structure is a vector<vector<pair<Ticker, Earnings-Date>>>
	Group stock_groups;
public:
	//should be initialized with a Group as given earlier
	StockShuffler(Group stock_groups_) {stock_groups = stock_groups_};
	// only shuffles the stocks! does not return them!
	void ShuffleStocks();
	// must pass an empty vector/group that can be filled by use of this get function
	// Emphasis on EMPTY group
	void Get30StocksPerGroup(Group &vec);
};






#endif // !SelectRandomStocks_h
