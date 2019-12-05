#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "EquityDivide.h"
#include "SelectRandomStocks.h"


void StockShuffler::ShuffleStocks() {
	shuffle(stock_groups[0].begin(), stock_groups[0].end(), default_random_engine);
	shuffle(stock_groups[1].begin(), stock_groups[1].end(), default_random_engine);
	shuffle(stock_groups[2].begin(), stock_groups[2].end(), default_random_engine);
}

void StockShuffler::Get30StocksPerGroup(Group &chosen_stocks) {
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j < 30; j++) {
			chosen_stocks[i][j] = stock_groups[i][j];
		}
	}
}
// will probably put all of this into a class wrapper
// right now, this is a placeholder: these numbers will be the size of each of the groups in Group
//int size_miss;
//int size_meet;
//int size_beat;
//
//
//// a vector of random integers that will serve as indices (proof of concept)
//vector<int> numbers_miss;
//vector<int> numbers_meet;
//vector<int> numbers_beat;
//
//for (int i = 0; i < size_miss; i++) {
//	numbers_miss.push_back(i);
//}
//for (int i = 0; i < size_meet; i++) {
//	numbers_meet.push_back(i);
//}
//for (int i = 0; i < size_beat; i++) {
//	numbers_meet.push_back(i);
//}
//
//shuffle(numbers_miss.begin(), numbers_miss.end(), default_random_engine);
//shuffle(numbers_meet.begin(), numbers_meet.end(), default_random_engine);
//shuffle(numbers_beat.begin(), numbers_beat.end(), default_random_engine);

//alternate idea: generate a group and just shuffle the vectors.
//EquityDivide equitydivider= EquityDivide("/EPS/EPS.csv");
//Group stock_groups;
//stock_groups = equitydivider.divide_group();

