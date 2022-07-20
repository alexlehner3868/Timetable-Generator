#include <string>
#include <iostream>

using namespace std;


class Section {
	private:
		string section_id_;
		int duration_;
		int start_time_;
		char semester_; 
		bool async_; 
	public:
		Section(string section_id, int duration, int start_time, char semester, bool async = false) {
			string section_id_ = section_id;
			duration_ = duration;
			start_time_ = start_time;
			semester_ = semester; 
			async_ = async;
		}

};