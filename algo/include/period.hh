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
	
		bool operator==(const Period & other){
			return (other.day_ == day_) && (other.time_hour_ == time_hour_);
		}
};

template <>
struct std::hash<Period> {
	std::size_t operator()(const Period& p) const{
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(p.day_)
               ^ (hash<int>()(p.time_hour_) << 1)) >> 1);
    }
  };

#endif