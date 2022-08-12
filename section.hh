#include <string>
#include <iostream>

using namespace std;


class Section {
	private:

	public:
		Section(string section_id, int duration, int start_time, char semester, int day, bool async = false) {
			string section_id_ = section_id;
			duration_ = duration;
			start_time_ = start_time;
			day_ = day;
			semester_ = semester; 
			async_ = async;
		}
		string section_id_;
		int duration_;
		int start_time_;
		int day_; // Monday = 0 .... Fri = 5
		char semester_; 
		bool async_; 

};