#include "constraints.hh"
#include "print_functions.hh"

#include <iostream>
#include <string>
#include <sstream>

#include "course_data.hh"

using namespace std;

void ConstraintHandler::add_time_constraint(int start_time,
                                            int duration,
                                            int day,
                                            char semester,
                                            int priority) {
    for (int i = 0; i < duration; i++) {
        if (semester == 'W') {
            day += 5;
        }
        time_constraints_.insert({make_pair(day, start_time + i), priority});
    }
}

void ConstraintHandler::set_back_to_back_constraint(int max_back_to_back, int priority) {
    back_to_back_constraint_ = make_pair(max_back_to_back, priority);
}

void ConstraintHandler::set_no_classes_after_X_constraint(int X, int priority) {
    no_classes_after_X_ = make_pair(X, priority);
}

void ConstraintHandler::set_no_classes_before_X_constraint(int X, int priority) {
    no_classes_before_X_ = make_pair(X, priority);
}

void ConstraintHandler::set_minimize_days_at_school_constraint(int priority) {
    minimize_days_at_school_ = priority;
}

void ConstraintHandler::set_prefer_morning_classes_constraint(int priority) {
    prefer_morning_classes_ = priority;
}

void ConstraintHandler::set_prefer_afternoon_classes_constraint(int priority) {
    prefer_afternoon_classes_ = priority;
}

void ConstraintHandler::set_prefer_evening_classes_constraint(int priority) {
    prefer_evening_classes_ = priority;
}
void ConstraintHandler::set_prefer_async_classes_constraint(int priority){
  prefer_async_classes_ = priority;
}
void ConstraintHandler::set_prefer_sync_classes_constraint(int priority){
  prefer_sync_classes_ = priority;
}

void ConstraintHandler::set_no_more_than_X_hours_per_day_constraint(int X, int priority){
  no_more_than_X_hours_per_day_ = make_pair(X, priority);
}

void ConstraintHandler::set_no_breaks_larger_than_X_constraint(int X, int priority){
  no_breaks_larger_than_X_ = make_pair(X, priority);
}

void ConstraintHandler::set_prefer_lunch_break_constraint(int priority){
  prefer_lunch_break_ = priority;
}
void ConstraintHandler::set_prefer_dinner_break_constraint(int priority){
  prefer_dinner_break_ = priority;
}

bool ConstraintHandler::preprocess_high_priority_classes_out(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& original_offerings, string& result){
  // Maybe? Add before_X and after_X times if it is a high priority (ie add all times above X for all days )
  // TimeConstraint(int start, int day, int priority, char semester)
  bool section_removed = false;
  bool valid_sections_after_removal = true;

  vector<Section> new_lec_sections;
  vector<Section> new_tut_sections;
  vector<Section> new_pra_sections;

  unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> new_offerings;
  // copy original_offerings so we can loop through it and delete at the same time
  //unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>::iterator offerings_iterator = original_offerings.begin();
  for(auto offering: original_offerings){
    bool lec_exists = offering.lecture_sections_.size() > 0;
    bool tut_exists = offering.tutorial_sections_.size() > 0;
    bool pra_exists = offering.practical_sections_.size() > 0;
    vector<Section>::iterator lect_section = offering.lecture_sections_.begin();
    vector<Section>::iterator tut_section = offering.tutorial_sections_.begin();
    vector<Section>::iterator pra_section = offering.practical_sections_.begin();
    while(lect_section != offering.lecture_sections_.end()){
      //cout << lect_section.section_id_ << " and course id is " << offering.course_id_ << endl;
      //cout << lect_section.day_[0] << " and time " << lect_section.start_time_[0] << endl;
      for(int i = 0; i < (*lect_section).num_classes_in_section() && !section_removed; i++){
        for(int j = 0; j < (*lect_section).duration_[i] && !section_removed; j++){
          auto it = time_constraints_.find({(*lect_section).day_[i], (*lect_section).start_time_[i]+j});
          if(it != time_constraints_.end() && it->second == MUST_HAVE && !section_removed){
            // found a class that occurs at the same time as a constraint that is priority 4, MUST_HAVE
            // take it out of original_offerings
            //                                                        offering.lecture_sections_.begin() +section_num
            //cout << "Erased lecture " << offering.course_id_ << " in section " << (*lect_section).section_id_ << endl;
            //cout << offering.lecture_sections_[offering.lecture_sections_.begin()+section_num].section_id_ << endl;

            lect_section = offering.lecture_sections_.erase(lect_section);
            number_of_classes_preprossed_out++;
            //lect_section = offering.lecture_sections_.erase(offering.lecture_sections_.begin()+(*lect_section).section_id_-1);
            section_removed = true;
          }


        }
      }
      if (!section_removed) {
        ++lect_section;
      }
      section_removed = false;
    }
    while(tut_section != offering.tutorial_sections_.end()){
      //cout << lect_section.section_id_ << " and course id is " << offering.course_id_ << endl;
      for(int i = 0; i < (*tut_section).num_classes_in_section() && !section_removed; i++){
        for(int j = 0; j < (*tut_section).duration_[i] && !section_removed; j++){
          auto it = time_constraints_.find({(*tut_section).day_[i], (*tut_section).start_time_[i]+j});
          if(it != time_constraints_.end() && it->second == MUST_HAVE && !section_removed){
            // found a class that occurs at the same time as a constraint that is priority 4, MUST_HAVE
            // take it out of original_offerings
            //                                                        offering.lecture_sections_.begin() +section_num
            //cout << "Erased tutorial " << offering.course_id_ << " in section " << (*tut_section).section_id_ << endl;
            tut_section = offering.tutorial_sections_.erase(tut_section);
            number_of_classes_preprossed_out++;
            section_removed = true;
          }


        }
      }
      if (!section_removed) {
        ++tut_section;
      }
      section_removed = false;
    }
    while(pra_section != offering.practical_sections_.end()){
      //cout << lect_section.section_id_ << " and course id is " << offering.course_id_ << endl;
      //cout << lect_section.day_[0] << " and time " << lect_section.start_time_[0] << endl;
      for(int i = 0; i < (*pra_section).num_classes_in_section() && !section_removed; i++){
        for(int j = 0; j < (*pra_section).duration_[i] && !section_removed; j++){
          auto it = time_constraints_.find({(*pra_section).day_[i], (*pra_section).start_time_[i]+j});
          if(it != time_constraints_.end() && it->second == MUST_HAVE && !section_removed){
            // found a class that occurs at the same time as a constraint that is priority 4, MUST_HAVE
            // take it out of original_offerings
            //                                                        offering.lecture_sections_.begin() +section_num
            //cout << "Erased practical " << offering.course_id_ << " in section " << (*pra_section).section_id_ << endl;
            pra_section = offering.practical_sections_.erase(pra_section);
            number_of_classes_preprossed_out++;
            section_removed = true;
          }


        }
      }
      if (!section_removed) {
        ++pra_section;
      }
      section_removed = false;
    }

    //copy offering to a new variable so we don't lose the deleted items
    new_lec_sections = offering.lecture_sections_;
    new_tut_sections = offering.tutorial_sections_;
    new_pra_sections = offering.practical_sections_;
    if (lec_exists && new_lec_sections.size() == 0) {
      result += offering.name_ + ": could not schedule; all lectures conflict with hard constraints. ";
      valid_sections_after_removal = false;
    }
    if (tut_exists && new_tut_sections.size() == 0) {
      result += offering.name_ + ": could not schedule; all tutorials conflict with hard constraints ";
      valid_sections_after_removal = false;
    }
    if (pra_exists && new_pra_sections.size() == 0) {
      result +=offering.name_ + ": could not schedule; all practicals conflict with hard constraints ";
      valid_sections_after_removal = false;
    }
    std::string new_course_name = offering.name_;
    std::string new_course_id = offering.course_id_;
    CourseOfferings preprocessed_class(new_course_name,new_course_id,new_lec_sections, new_tut_sections, new_pra_sections);
    preprocessed_class.semester_ = offering.semester_;
    new_offerings.insert(preprocessed_class);
  }

  //copy new offerings over
  original_offerings = new_offerings;
  return valid_sections_after_removal;
}

bool ConstraintHandler::prune_semesters(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &offerings) {
  bool succeeded = true;

  // Ignore offerings that are in the wrong semester
  for (auto offering : offerings)
    succeeded &= offering.prune_semester();

  return succeeded;
}

int ConstraintHandler::cost_of_class(Date d) {
    int cost = 0;
    // Penalize class for being in a blocked off region (increase cost)
    if (time_constraints_.find(d) != time_constraints_.end()) {
        cost += (time_constraints_[d]);
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_morning_classes_ != NO_PRIORITY && d.second < 11) {
        cost -= prefer_morning_classes_;
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_evening_classes_ != NO_PRIORITY && d.second > 4) {
        cost -= prefer_evening_classes_;
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_afternoon_classes_ != NO_PRIORITY && d.second > 12 && d.second < 4) {
        cost -= prefer_afternoon_classes_;
    }
    // Penalize class for being after time (increase cost)
    if (no_classes_after_X_.second > NO_PRIORITY && d.second >= no_classes_after_X_.first) {
        cost += (no_classes_after_X_.second );
    }
    // Penalize class for being before time (increase cost)
    if (no_classes_before_X_.second > NO_PRIORITY && d.second < no_classes_before_X_.first) {
        cost += (no_classes_before_X_.second);
    }
    return cost;
}

int ConstraintHandler::sync_vs_async_cost(bool is_class_sync){
  int cost;
  if(is_class_sync){
    cost =  prefer_async_classes_ - prefer_sync_classes_;
  }else{
    cost =  prefer_sync_classes_ - prefer_async_classes_;
  }
  return cost;
}

int ConstraintHandler::cost_of_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable){
  int multiplier = 10;
  // The cost associated with the timetable
  int cost = 0;

  vector<vector<bool>> schedule;

  // Set up vector to store timetable
  for(int i = 0; i < 10; i++){
    // Add 24 hours to each day
    schedule.push_back(vector<bool>(24, false));
  }

  // Mark where each class occurs
  for(auto period : timetable){
    Date d = period.first;
    schedule[d.first-1][d.second] = true;
  }

  // A count for the number of days that have classes
  int days_at_school = 0;

  // Loop through all days
  for(int day = 0; day < 10; day++){
    // Used to "back_to_back_constraint_" constraint
    int back_to_back = 0;
    // Used for "minimize_days_at_school_" constraint
    bool class_on_this_day = false;
    // Used for "no_more_than_X_hours_per_day_" constraint
    int hours_per_day = 0;
    // Used for "no_breaks_larger_than_X_" constraint
    int prev_class_hour = 0;
    // Used for prefer_lunch_break_
    bool break_for_lunch = false;
    // Used for prefer_dinner_break_
    bool break_for_dinner = false;
    // Loop through all hours per day
    for(int hour = 0; hour < 24; hour ++){
        // Check if a class is at this time and update constraint trackers
        if(schedule[day][hour]){
          back_to_back++;
          class_on_this_day = true;
          hours_per_day++;
          
          // If no_breaks_larger_than_X_ is active, check gap between classes
          if(prev_class_hour != 0){
            int break_between_classes = hour - prev_class_hour;
            if(no_breaks_larger_than_X_.second && break_between_classes > no_breaks_larger_than_X_.first){
              cost += no_breaks_larger_than_X_.second * (break_between_classes - no_breaks_larger_than_X_.first);
            } 
          }
          prev_class_hour = hour;
        }else{
          // If back_to_back is an active constraint, check if more than X hours are back to back
          if(back_to_back_constraint_.second && back_to_back > back_to_back_constraint_.first){
            cost+= (back_to_back_constraint_.second * (back_to_back - back_to_back_constraint_.first)*multiplier/2);
          }
          // Reset back to back cost
          back_to_back = 0;

          if(hour < 14 && hour >= 11){
            break_for_lunch = true;
          }else if(hour > 17 && hour < 20){
            break_for_dinner = true;
          }
        }
    }
    // If back_to_back is an active constraint, check if more than X hours are back to back (Need to check for last interval)
    if(back_to_back_constraint_.second && back_to_back > back_to_back_constraint_.first){
      cost+= (back_to_back_constraint_.second * (back_to_back - back_to_back_constraint_.first) * multiplier);
    }
    // If at least one class was on this day, increment the counter
    if(class_on_this_day){
      days_at_school++;
    }
    // If no_more_than_X_hours_per_day_ is active and we have more than X hours that day 
    if(no_more_than_X_hours_per_day_.second && hours_per_day > no_more_than_X_hours_per_day_.first){
      cost += no_more_than_X_hours_per_day_.second * (hours_per_day - no_more_than_X_hours_per_day_.first);
    }
    // If prefer_lunch_break_ is active and no lunch break 
    if(prefer_lunch_break_ && !break_for_lunch){
      cost += prefer_lunch_break_;
    }
     // If prefer_dinner_break_ is active and no lunch break 
    if(prefer_dinner_break_ && !break_for_dinner){
      cost += prefer_dinner_break_;
    }
  }

  // Check for number of days at school
  // If a days off preference is selected, the cost is increased perportional to priority and number of days at school
  cost += (minimize_days_at_school_ !=NO_PRIORITY ? minimize_days_at_school_ *  days_at_school * multiplier: 0);



  return cost;
}

ConstraintHandler::ConstraintHandler() {
    time_constraints_.clear();

    back_to_back_constraint_ = make_pair(24, NO_PRIORITY);
    no_classes_after_X_ = make_pair(24, NO_PRIORITY);
    no_classes_before_X_ = make_pair(0, NO_PRIORITY); 
    no_breaks_larger_than_X_ = make_pair(24, NO_PRIORITY);
    no_more_than_X_hours_per_day_ = make_pair(24, NO_PRIORITY);

    minimize_days_at_school_ = NO_PRIORITY;
    prefer_morning_classes_ = NO_PRIORITY;
    prefer_afternoon_classes_ = NO_PRIORITY;
    prefer_evening_classes_ = NO_PRIORITY;
    prefer_async_classes_ = NO_PRIORITY;
    prefer_sync_classes_ = NO_PRIORITY;

    prefer_lunch_break_ = NO_PRIORITY;
    prefer_dinner_break_ = NO_PRIORITY;

}


stringstream ConstraintHandler::output_constraints_stats(){
  stringstream ss;
  ss<<"List of Active Constraints: "<<endl;
  if(time_constraints_.size() >0){
    ss<<"   Blocked-Off Time Constraints: "<<endl;
    for(auto timeC : time_constraints_){
      ss<<"      "<<toDay(timeC.first.first) <<" " << toTime(timeC.first.second)<<": "<<toPriority(timeC.second)<<endl;
    }
  }
  ss<<endl;
  if(back_to_back_constraint_.second != NO_PRIORITY){
    ss<<"   No More Than " << back_to_back_constraint_.first<< " Hours Back-To-Back: "<< toPriority(back_to_back_constraint_.second)<<endl;
  }
  if(no_classes_after_X_.second != NO_PRIORITY){
    ss<<"   No Class After" << toTime(no_classes_after_X_.first)<< ": "<< toPriority(no_classes_after_X_.second)<<endl;
  }
  if(no_classes_before_X_.second != NO_PRIORITY){
    ss<<"   No Class Before" << toTime(no_classes_before_X_.first)<< ": "<< toPriority(no_classes_before_X_.second)<<endl;
  }
  if(minimize_days_at_school_ != NO_PRIORITY){
    ss<<"   Minimize Days At School: "<< toPriority(minimize_days_at_school_)<<endl;
  }
  if(prefer_morning_classes_ != NO_PRIORITY){
    ss<<"   Prefer Morning Classes: "<< toPriority(prefer_morning_classes_)<<endl;
  }
  if(prefer_afternoon_classes_ != NO_PRIORITY){
    ss<<"   Prefer Afternoon Classes: "<< toPriority(prefer_afternoon_classes_)<<endl;
  }
  if(prefer_evening_classes_ != NO_PRIORITY){
    ss<<"   Prefer Evening Classes: "<< toPriority(prefer_evening_classes_)<<endl;
  }
  if(prefer_async_classes_ != NO_PRIORITY){
     ss<<"   Prefer Async Classes: "<< toPriority(prefer_async_classes_)<<endl;
  }
  if(prefer_sync_classes_ != NO_PRIORITY){
     ss<<"   Prefer Sync Classes: "<< toPriority(prefer_sync_classes_)<<endl;
  }
  if(no_more_than_X_hours_per_day_.second != NO_PRIORITY){
    ss<<"   No More Than" << no_more_than_X_hours_per_day_.first<< "Hours Per Day: "<< toPriority(no_more_than_X_hours_per_day_.second)<<endl;
  }
  if(no_breaks_larger_than_X_.second != NO_PRIORITY){
    ss<<"   Breaks No Longer Than " << no_breaks_larger_than_X_.first<< " Hours: "<< toPriority(no_breaks_larger_than_X_.second)<<endl;
  }
  if(prefer_lunch_break_ != NO_PRIORITY){
      ss<<"   Prefer Lunch Break: "<< toPriority(prefer_lunch_break_)<<endl;
  }
  if(prefer_dinner_break_ != NO_PRIORITY){
      ss<<"   Prefer Dinner Break: "<< toPriority(prefer_dinner_break_)<<endl;
  }
  ss<<"Number of Sections Preprocessed Out: "<<number_of_classes_preprossed_out<<endl;
  return ss;
}
