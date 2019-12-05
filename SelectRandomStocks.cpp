#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "EquityDivide.h"

// right now, this is a placeholder: these numbers will be the size of each of the groups in Group
int size_miss;
int size_meet;
int size_beat;


// a vector of random integers that will serve as indices
vector<int> numbers_miss;
vector<int> numbers_meet;
vector<int> numbers_beat;

for (int i = 0; i < size_miss; i++) {
	numbers_miss.push_back(i);
}
for (int i = 0; i < size_meet; i++) {
	numbers_meet.push_back(i);
}
for (int i = 0; i < size_beat; i++) {
	numbers_meet.push_back(i);
}

shuffle(numbers_miss.begin(), numbers_miss.end(), default_random_engine);
shuffle(numbers_meet.begin(), numbers_meet.end(), default_random_engine);
shuffle(numbers_beat.begin(), numbers_beat.end(), default_random_engine)