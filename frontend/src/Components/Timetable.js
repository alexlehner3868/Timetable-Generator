// -- React --
import React from "react";

// -- Components --
import Period from "./Period";
import AddConstraintButton from "./NonEssentialComponents/AddConstraintButton.js";

const blockedOffTimes = [...Array(24)].map(_ => Array(10).fill(0));
// -- Module --
const Timetable = (props) => {
  // TODO:
  // - Currently only printing for one semester. (Need to do both semesters.)
  // - Decide how to view the 2 semesters
  // - Need to add padding underneath the timetable 
  
  // Create an 2D grid of all possible time slots
  const ndays = 10;
  const nhours = 24;
  const grid = [...Array(nhours)].map(_ => Array(ndays).fill({}));
  const semester = (props.when.day.begin == 0 ? 'F' : 'S');
  

  // Extract sorted list of courses (for colouring)
  let courses = [];
  for (const meet of props.timetable)
    if (!courses.includes(meet.course))
      courses.push(meet.course)
  courses.sort()

  // Determine timetable colours
  let idx = 1;
  let colors = {};
  for (const course of courses)
    if (colors[course] === undefined)
      colors[course] = idx++;

  // Process the timetable
  let async_courses = new Set()
  if (props.timetable) {
    for (const meet of props.timetable) {
     
      if(meet.time == -1){
        if(meet.semester == semester){
          console.log(meet);
          async_courses.add(meet)
        }
       
        continue;
      }
      grid[meet.time][meet.day - 1] = meet;
    }
  }


  let async_course_list = ""
  if(async_courses.size > 0){
    async_course_list = "Asynchronous Courses: "
    for(const meet of async_courses){
      async_course_list += meet.course + " (" + meet.type + "0"+ meet.section + ") "
    }
  }
  console.log(async_course_list)
  // Compute x is in [begin, end)
  const inRange = (x, begin, end) => {
    return (begin <= x) && (x < end);
  };

  // Convert from time index to hour string
  const int2hour = hour => {
    return (hour <= 12) ? hour + "AM": (hour - 12) + "PM"
  };


  const blockOffHour = (day, hour) => {
    /*
    blockedOffTimes[hour][day]++;
    if(blockedOffTimes[hour][day]>3){
      blockedOffTimes[hour][day] = blockedOffTimes[hour][day] - 4;
    }
    grid[hour][day].block++;
    if(grid[hour][day].block === 4){
      grid[hour][day].block = 0;
    }
    */
    // TODO add a block component to meet so that it can be changed 
    console.log(hour, day)

    //have the hour and day to block off time
    //simply add the block off time constraint

    //new functions for adding/removing time blocks 
    const addConstraint = (constraint) => {
      console.log(`adding constraint: ${constraint}`)
      props.setConstraints(prev => new Set(prev.add(constraint)))
    }
    const removeConstraintTime = (constraint) => {
      console.log(`removing constraint: ${constraint}`)
      props.setConstraints(prev => new Set([...prev].filter(x => (x.slice(0,5) !== (constraint.slice(0,5))))))
    };

    //since the constraint type is 12, days is always one char and time is two chars, use "hours" for time 
    //when blocked off and "priority" for the day
    //constraint type is 
    
    if (hour == 9) {
      var constraint = "12" + day + "0" + hour;
      if ( !props.constraints.has(constraint)) {
        addConstraint(constraint);
        blockedOffTimes[hour][day] = 3;
        grid[hour][day].block = 3;
      } else {
        removeConstraintTime(constraint);
        blockedOffTimes[hour][day] = 0;
        grid[hour][day].block = 0;
      }
    } else if (hour > 9 && hour < 21) {
      var constraint = "12" + day + hour;
      console.log(props.constraints);
      if ( !props.constraints.has(constraint)) {
        console.log("adding")
        addConstraint(constraint);
        blockedOffTimes[hour][day] = 3;
        grid[hour][day].block = 2;/*
        grid[hour][day] = {
          course: "BLOCKED OFF TIME",
          day: {day},
          section: 3,
          semester:"F",
          time: {hour},
          type: "PRA"
        }
        console.log(grid[hour][day])*/
      } else {
        console.log("removing", constraint)
        removeConstraintTime(constraint);
        blockedOffTimes[hour][day] = 0;
        grid[hour][day].block = 0;
        console.log(props.constraints)
      }
    }
    //then recall generate
  }

  for (var i = 0; i < 24; i++) {
    for (var j = 0; j < 10; j++) {
      //check if class exists, two hours of class in a row,
      //class info matches
      if (grid[i][j] && grid[i][j+1] && grid[i][j].course == grid[i][j].course && grid[i][j].type == grid[i][j].type && grid[i][j].section == grid[i][j].section) {
        //console.log("hiiii");
        grid[i][j].multiPos = 1;
        grid[i][j+1].multiPos = 2;
      }
    }
  }
  
  // Render the timetable
  return (
  <div>
      <div className="timetable" id="timetable">
        <div className="tr">
          <div className="td" id='legend-times'> </div>
          <div className="td"><b>Monday</b></div>
          <div className="td"><b>Tuesday</b></div>
          <div className="td"><b>Wednesday</b></div>
          <div className="td"><b>Thursday</b></div>
          <div className="td"><b>Friday</b></div>
        </div>
        {grid.map((row, hour) => (
          <div className="tr" id="table_day" key={hour}>
            <div className="td" id="legend-times"><b>{int2hour(hour)}</b></div>
            {row.map((meet, day) => (
              <div className='td' id="table_hour" key={day} onClick={() => blockOffHour(day, hour)}>
                <Period 
                  code={meet.course}
                  color={colors[meet.course]}
                  name={meet.name}
                  section={meet.section-1}
                  type={meet.type}
                  blockedOffLevel={blockedOffTimes[hour][day]}
                  multiPos={meet.multiPos}
                />
              </div>
            )).filter((_, day) => inRange(day, props.when.day.begin, props.when.day.end))}
          </div>
        )).filter((_, hour) => inRange(hour, props.when.hour.begin, props.when.hour.end))}
      </div>
      <p1>{async_course_list}</p1>
    </div>
  )
}

// -- Exports --
export default Timetable;
