Below is a list of coding tasks that still need to be completed

1. General
    - What happens if no possible timetables are found [SAY NO TIMETABLE IS POSSIBLE WITH CURRENT SET OF CLASSES]
        - 1: hard time conflict and class overlaps -> report class x at time constraint y (preprocess fn)
        - 2: no timetables with that set of courses can be generated
        - 3: semester specified, but course not offered
    - Should we force semester by semester scheduling or do full year scheduling [SEMESTER BY SEMESTER]
    - [DONE] Ask course data guy for data with course names [NATALIA WILL DO 10/10/22]
    - Allow classes to be locked into a section

2. Scheduler
    - Add support for async classes
    - Full year classes
    - Force a class to be in a certain semester
    - Restrict number of classes to a certain semester 6
    - Allow classes to be locked into a section
    - Are the unique strings getting rid of unique timetables?

3. Constraints
    - Add constraint support for
        - Communiting (no giant large breaks between classes) [yes/no, priority] [DONE] ->renamed to no_breaks_larger_than_X_
        - Prefering morning/afternoon/evening classes -> [Morning, Afternoon, Evening] + priority [DONE]
        - Prefer no classes during lunch times [yes/no, priority] [DONE]
        - Prefer no classes during dinner times [yes/no, priority] [DONE]
        - Minimize days at school [yes/no, priority] [DONE]
        - No more than X hours back to back [X, priority] [DONE]
        - No more than X hours per day [X, priority] [DONE]
        - Prefer async/non async classes [DONE]
    - Tune timetable cost function to create more variability in timetables (ie numbers in constraint factor) [DONE]
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
        - Prefer async/non async classes
        - No more than X hours per day [X, prioirty]
    - [DONE] Get timetable data to show up on timetables
    - [DONE] Show different timetables for each semster
    - Add labels (ie days and time) to timestables
    - Add classes
    - Remove classes
    - Create schedule button
    - Add a way to cycle through created timetables [ZAK]
    - Add a way to set the number of timetables to see [ie config: max_num_of_timetables_to_show]
    - Add a way to save timetable [Timetable + its courses, times and sections]
    - Allow classes to be locked into a section
    - Make it look pretty and aestetic
    - Add a help pop up and constraint explainer
    - Add async classes to front end


5. Back End
    - Connect Flask to React to create API calls
    - Connect all react components to algo backends
        - Search bar
        - Timetable
        - Constraint inputs
    - Reformat timetable output to be in the form the front end needs


   PRIORITY LIST: (due 20th)
   
    1. [DONE] Add suppport for async classes [ALEX] 
    1.5 [DONE] Add support for full year classes (kinda done)
    2. Are the unique strings getting rid of unique timetables? (bug?) if you change the numb of time  tables to show from 5->bigger num, the number of timetables doesnt grow [NAT]
    3. Apply constraints to just one semester
    4. Use new database (replace all previous) [NAT]
    5. [DONE] Add extra non-essential contraints that we brainstromed [ALEX]
    6. A front end way to cycle through timetables [ZAK]
    7. Connect python to algo so buttons calls scheduler/constraint methods [ZAK] (main.cc switch case needs to call cosntraint methods, course methods and scheduler)
    8. Get things to save [ZAK]


