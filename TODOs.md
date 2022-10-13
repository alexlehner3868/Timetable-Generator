Below is a list of coding tasks that still need to be completed 

1. General
    - What happens if no possible timetables are found [SAY NO TIMETABLE IS POSSIBLE WITH CURRENT SET OF CLASSES]
        - 1: hard time conflict and class overlaps -> report class x at time constraint y
        - 2: no timetables with that set of courses can be generated
    - Should we force semester by semester scheduling or do full year scheduling [SEMESTER BY SEMESTER]
    - Ask course data guy for data with course names [NATALIA WILL DO 10/10/22]
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
    - [DONE] Get timetable data to show up on timetables 
    - [DONE] Show different timetables for each semster 
    - Add labels (ie days and time) to timestables 
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
   

   PRIORITY LIST:
   1. [DONE] Connect Flask to React to create API calls
   2. Schedule Button -> press button and pre configured timetable appears on website
   3. Functionality for Front-End
        - add class button
        - remove class button
        - generate timetable button
        - constraint generation
    4. Adding more constraints & tune constraint cost
    5. Make scheduling semester to semester
    6. No timetable possible
    7. Add suppport for async classes
    8. Restrict number of classes per semester to 6
    9. Apply constraints to just one semester

