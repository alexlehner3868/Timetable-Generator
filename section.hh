#include <string>
#include <iostream>

using namespace std;


class Section {
	private:

	public:
		Section(string section_id, vector<int> duration, vector<int> start_time, vector<int> semester, vector<int> day, vector<int> async = false) {
			int section_id_ = section_id;
			duration_ = duration;
			start_time_ = start_time;
			day_ = day;
			semester_ = semester; 
			async_ = async;
		}
		int section_id_;
		vector<int> duration_;
		vector<int> start_time_;
		vector<int> day_; // Monday = 0 .... Fri = 5
		vector<int> semester_; 
		vector<int> async_; 

};