Below is a list of coding tasks that still need to be completed 

1. General
    - What happens is no possible timetables are found 
    - Should we force semester by semester scheduling or do full year scheduling 
    - Ask course data guy for data with course names 
    - Allow classes to be locked into a section

2. Scheduler 
    - Add support for async classes 
    - Full year classes 
    - Force a class to be in a certain semester 
    - Restrict number of classes to a certain semester 6
    - Allow classes to be locked into a section 

3. Constraints 
    - Add constraint support for 
        - Communiting (ie no super late classes, no giant large breaks between classes) [yes/no, priority]
        - Prefering morning/afternoon/evening classes -> drop down menu [Morning, Afternoon, Evening] + priority
        - Prefer no classes during meal times [yes/no, priority]
        - Minimize days at school [yes/no, priority]
        - No more than X hours back to back [X, priority]
        - No more than X hours per day [X, prioirty]
    - Tune timetable cost function to create more variability in timetables 
    - Apply constraints to only one semester 
    
4. Front End 
    - Add ways to input constraints (Add/Remove)
        - Blocked-off times [click on times on timetable + priorty]  -> change timetable to buttons to allow click? 
        - Communiting (ie no super late classes, no giant large breaks between classes) [yes/no, priority]
        - Prefering morning/afternoon/evening classes -> drop down menu [Morning, Afternoon, Evening] + priority
        - No classes after X o clock [X, priority]
        - No classes before X [X, prioirty]
        - Prefer no classes during meal times [yes/no, priority]
        - Minimize days at school [yes/no, priority]
        - No more than X hours back to back [X, priority]
        - No more than X hours per day [X, prioirty]
    - Get timetable data to show up on timetables 
    - Add classes 
    - Remove classes 
    - Create schedule button 
    - Add a way to cycle through created timetables 
    - Add a way to set the number of timetables to see [ie config: max_num_of_timetables_to_show]
    - Add a way to save timetable [Timetable + its courses, times and sections]
    - Allow classes to be locked into a section
    - Make it look pretty and aestetic
    

5. Back End 
    - Connect Flask to React to create API calls 
    - Connect all react components to algo backends 
        - Search bar
        - Timetable 
        - Constraint inputs 
   