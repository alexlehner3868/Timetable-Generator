#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;


class Period {
	private:

	public:
		Period(int day, int time_hour) {
			day_ = day;
			time_hour_ = time_hour;
		}

		int day_;
		int time_hour_;

};

#endif