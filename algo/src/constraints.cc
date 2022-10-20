#include "constraints.hh"

#include <iostream>
#include <string>

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

void ConstraintHandler::set_minimize_days_at_school_constraint(bool ans, int priority) {
    minimize_days_at_school_ = make_pair(ans, priority);
}

void ConstraintHandler::set_prefer_morning_classes_constraint(bool ans, int priority) {
    prefer_morning_classes_ = make_pair(ans, priority);
}

void ConstraintHandler::set_prefer_afternoon_classes_constraint(bool ans, int priority) {
    prefer_afternoon_classes_ = make_pair(ans, priority);
}

void ConstraintHandler::set_prefer_evening_classes_constraint(bool ans, int priority) {
    prefer_evening_classes_ = make_pair(ans, priority);
}

bool ConstraintHandler::preprocess_high_priority_classes_out(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& original_offerings){
  // Maybe? Add before_X and after_X times if it is a high priority (ie add all times above X for all days )
  // TimeConstraint(int start, int day, int priority, char semester)
  bool section_removed = false;
  bool remove_section = false;
  
  vector<Section> new_lec_sections;
  vector<Section> new_tut_sections;
  vector<Section> new_pra_sections;
  
  unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> new_offerings;
  // copy original_offerings so we can loop through it and delete at the same time
  //unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>::iterator offerings_iterator = original_offerings.begin();
  for(auto offering: original_offerings){
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
            cout << "Erased lecture " << offering.course_id_ << " in section " << (*lect_section).section_id_ << endl;
            //cout << offering.lecture_sections_[offering.lecture_sections_.begin()+section_num].section_id_ << endl;
            
            lect_section = offering.lecture_sections_.erase(lect_section);
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
            cout << "Erased tutorial " << offering.course_id_ << " in section " << (*tut_section).section_id_ << endl;
            tut_section = offering.tutorial_sections_.erase(tut_section);
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
            cout << "Erased practical " << offering.course_id_ << " in section " << (*pra_section).section_id_ << endl;
            pra_section = offering.practical_sections_.erase(pra_section);
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
  std::string new_course_name = offering.name_;
  std::string new_course_id = offering.course_id_;
  CourseOfferings preprocessed_class(new_course_name,new_course_id,new_lec_sections, new_tut_sections, new_pra_sections);
  new_offerings.insert(preprocessed_class);
  }

  //copy new offerings over
  original_offerings = new_offerings;
  return remove_section;
}

int ConstraintHandler::cost_of_class(Date d) {
    int cost = 0;
    // Penalize class for being in a blocked off region (increase cost)
    if (time_constraints_.find(d) != time_constraints_.end()) {
        cost += (time_constraints_[d]);
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_morning_classes_.first && d.second < 11) {
        cost -= prefer_morning_classes_.second;
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_evening_classes_.first && d.second > 4) {
        cost -= prefer_evening_classes_.second;
    }
    // Reward clas for being in a prefered time (decrease cost)
    if (prefer_afternoon_classes_.first && d.second > 12 && d.second < 4) {
        cost -= prefer_afternoon_classes_.second;
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

ConstraintHandler::ConstraintHandler() {
    time_constraints_.clear();
    back_to_back_constraint_ = make_pair(24, NO_PRIORITY);
    no_classes_after_X_ = make_pair(24, NO_PRIORITY);
    no_classes_before_X_ = make_pair(0, NO_PRIORITY);
}