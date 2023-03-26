import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';

const AddConstraintButton = (props) => {
    const addConstraint = (constraint) => {
        console.log(`adding constraint: ${constraint}`)
        props.setConstraints(prev => new Set(prev.add(constraint)))
    }

       
    const removeConstraint = (constraint) => {
      console.log(`removing constraint: ${constraint}`)
      props.setConstraints(prev => new Set([...prev].filter(x => (x.slice(0,3) !== (constraint + "0")
                                                                && x.slice(0,3)!== (constraint + "1") 
                                                                && x.slice(0,3)!== (constraint + "2")
                                                                && x.slice(0,3)!== (constraint + "3")
                                                                ))))
    };

    const removeAllConstraints = (constraint) => {
        props.setConstraints(prev => new Set())
        document.getElementById("morning_priorities").value = 0;
        document.getElementById("afternoon_priorities").value = 0;
        document.getElementById("evening_priorities").value = 0;
        document.getElementById("minimize_priorities").value = 0;
        document.getElementById("async_priorities").value = 0;
        document.getElementById("sync_priorities").value = 0;
        document.getElementById("lunch_priorities").value = 0;
        document.getElementById("dinner_priorities").value = 0;
        document.getElementById("before_priorities").value = 0;
        document.getElementById("before_value").value = "";
        document.getElementById("after_priorities").value = 0;
        document.getElementById("after_value").value = "";
        document.getElementById("max_class_priorities").value = 0;
        document.getElementById("max_class_value").value = "";
        document.getElementById("max_break_priorities").value = 0;
        document.getElementById("max_break_value").value = "";
    };
    /* First two digits indicate constraint type, third indicates priority, fourth and fifth digit include time info (for constraints 7-11):
        00 - prefer early classes
        01 - prefer afternoon classes
        02 - prefer evening classes
        03 - prefer minimum days on campus 
        04 - prefer async classes 
        05 - prefer sync classes
        06 - prefer break at lunch
        07 - prefer break at dinner
        08 - no class before a certain time
        09 - no class after a certain time
        10 - max hours of class back to back
        11 - no breaks longer than a certain time
    */
    function handleDeleteAll (event) {
        event.preventDefault()
        removeAllConstraints();
        console.log("deleting all constraints");
        console.log()
    }
    function handleSubmitEarly (event) {
      event.preventDefault()
      // remove all "early" constraints existing previously
      removeConstraint("00");
      console.log("HERE")
      const priority = document.getElementById("morning_priorities").value;
      
      if (priority !== "0") {
        //console.log(priority);
        //console.log("Prioritizing Early Classes");
        //console.log("00" + priority + "00");
        console.log("ADDING mornign const", priority)
        addConstraint("00" + priority + "00");
      }
    } function handleSubmitAfternoon (event) {
        event.preventDefault();
        removeConstraint("01");
        const priority = document.getElementById("afternoon_priorities").value;
      
        if (priority !== "0") {
        //console.log(priority);
        //console.log("Prioritizing Afternoon Classes");
        //console.log("01" + priority + "00");
        addConstraint("01" + priority + "00");
        }
    } function handleSubmitEvening (event) {
        event.preventDefault();
        removeConstraint("02");
        const priority = document.getElementById("evening_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Evening Classes");
            //console.log("02" + priority + "00");
            addConstraint("02" + priority + "00");
        }
    } function handleSubmitMinDay (event) {
        event.preventDefault();
        removeConstraint("03");
        const priority = document.getElementById("minimize_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Minimum Days on Campus")
            //console.log("03" + priority + "00");
            addConstraint("03" + priority + "00");
        }
    } function handleSubmitAsync (event) {
        event.preventDefault();
        removeConstraint("04");
        const priority = document.getElementById("async_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Asynchronous Courses")
            //console.log("04" + priority + "00");
            addConstraint("04" + priority + "00");
        }
    } function handleSubmitSync (event) {
        event.preventDefault();
        removeConstraint("05");
        const priority = document.getElementById("sync_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Synchronous Courses")
            //console.log("05" + priority + "00");
            addConstraint("05" + priority + "00");
        }
    } function handleSubmitLunch (event) {
        event.preventDefault();
        removeConstraint("06");
        const priority = document.getElementById("lunch_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Making Lunch Break")
            //console.log("06" + priority + "00");
            addConstraint("06" + priority + "00");
        }
    } function handleSubmitDinner (event) {
        event.preventDefault();
        removeConstraint("07");
        const priority = document.getElementById("dinner_priorities").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Making Dinner Break")
            //console.log("07" + priority + "00");
            addConstraint("07" + priority + "00");
        }
    } function handleSubmitNoClassBefore (event) {
        event.preventDefault();
        removeConstraint("08");
        const priority = document.getElementById("before_priorities").value;
        const hours = document.getElementById("before_value").value;
        var string_hours;
        //if hours between 10 and 20 (inclusive) 
        if (hours >= 10 && hours <= 20) {
            string_hours = hours.toString();
        } else {
            string_hours = "00";
        }

        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Courses Before X")
            //console.log("08" + priority + "00");
            addConstraint("08" + priority + string_hours);
        }
        console.log("Prioritizing Classes After X")
    } function handleSubmitNoClassAfter (event) {
        event.preventDefault();
        removeConstraint("09");
        const priority = document.getElementById("after_priorities").value;
        const hours = document.getElementById("after_value").value;
        var string_hours;
        //if hours between 10 and 20 (inclusive) 
        if (hours > 9 && hours <= 19) {
            string_hours = hours.toString();
        } else if (hours == 9) {
            string_hours = "09"
        } else {
            string_hours = "00";
        }
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Classes Before Y");
            //console.log("09" + priority + "00");
            addConstraint("09" + priority + string_hours);
        }
    } function handleSubmitMaxBack (event) {
        event.preventDefault();
        removeConstraint("10");
        const priority = document.getElementById("max_class_priorities").value;
        const hours = document.getElementById("max_class_value").value;
        //console.log(hours);
        if (priority !== "0") {
            //onsole.log(priority);
            //console.log("Prioritizing Shortest Possible B2B Hours of Class");
            const int_hours = parseInt(hours);
            if (int_hours < 10 && int_hours > 0) { //single digit hour value
                addConstraint("10" + priority + "0" + hours);
            } else if (int_hours > 9 && int_hours < 13 ) {
                addConstraint("10" + priority + hours);
            } else {
                // error so don't do anything
            }
        }
    } function handleSubmitMaxBreak (event) {
        event.preventDefault();
        removeConstraint("11");
        const priority = document.getElementById("max_break_priorities").value;
        const hours = document.getElementById("max_break_value").value;
      
        if (priority !== "0") {
            //console.log(priority);
            //console.log("Prioritizing Shortest Break")
            //console.log("11" + priority + hours);
            const int_hours = parseInt(hours);
            if (int_hours < 10 && int_hours > 0) { //single digit hour value
                addConstraint("11" + priority + "0" + hours);
            } else if (int_hours > 9 && int_hours < 13 ) {
                addConstraint("11" + priority + hours);
            } else {
                // error so don't do anything
            }
        }
    } function handleSubmitTimeBlock (event) {
        event.preventDefault();
        
    } 
    
    var morning;
    var afternoon;
    var evening;
    var minimize;
    var async;
    var sync;
    var lunch;
    var dinner;
    var before;
    var before_value;
    var after;
    var after_value;
    var max_class;
    var max_class_value;
    var max_break;
    var max_break_value;

    function repopulate_constraints(constraint) {
        //for each element, find constraint number and get the document id to match
        //console.log(constraint)
        //first extract first two characters (those are the constraint type)
        const type = parseInt(constraint.slice(0,2))
        //second char is constraint priority
        const priority = parseInt(constraint.slice(2,3))
        //3rd and 4th char are hours (useless unless for last for constraints)
        
        var hours_refresh = 0;
        if (constraint.slice(3,5)) {
            hours_refresh = parseInt(constraint.slice(3,5))
        } else {
            hours_refresh = 0;
        }
        //console.log("type is ", type, ", priority is ", priority, ", hours is ", hours_refresh)
        
        //don't assign priority unless 1-3 (set)
        if (priority == 1 || priority == 2 || priority == 3) {
                
            switch (type) {
                case 0:
                    morning = priority;
                    break;
                case 1:
                    afternoon = priority;
                    break;
                case 2:
                    evening = priority;
                    break;
                case 3:
                    minimize = priority;
                    break;
                case 4:
                    async = priority;
                    break;
                case 5:
                    sync = priority;
                    break;
                case 6:
                    lunch = priority;
                    break;
                case 7:
                    dinner = priority;
                    break;
                case 8:
                    before = priority;
                    if (hours_refresh < 10 || hours_refresh > 20) {
                        //invalid
                        hours_refresh = 0;
                    } else {
                        //valid
                        before_value = hours_refresh;
                    }
                    break;
                case 9:
                    after = priority;
                    if (hours_refresh < 9 || hours_refresh > 19) {
                        //invalid
                        hours_refresh = 0;
                    } else {
                        //valid
                        after_value = hours_refresh;
                    }
                    break;
                case 10:
                    max_class = priority;
                    if (hours_refresh < 1 || hours_refresh > 12) {
                        hours_refresh = 0;
                    } else {
                        max_class_value = hours_refresh;
                    }
                    break;
                case 11:
                    max_break = priority;
                    //not valid
                    if (hours_refresh < 1 || hours_refresh > 12) {
                        hours_refresh = 0;
                    } else {
                        //valid
                        max_break_value = hours_refresh;
                    }
                    break;
                default:
                    break;
                
            }
        }
    }
    props.constraints.forEach(function(constraint) {
        repopulate_constraints(constraint);
    });

    

  return (
       <div>
            <label>Prefer No Morning Classes</label>
            <select list="Priority" defaultValue={morning} class="dropdown" id="morning_priorities" onChange = {handleSubmitEarly}>
                <option value="0" ></option>
                <option class="good_to_have" value="1" >Good To Have</option>
                <option class="great_to_have" value="2" >Great To Have</option>
                <option class="must_have" value="3" >Must Have</option>
            </select> <br></br>
            <label>Prefer No Afternoon Classes</label>
            <select list="Priority" defaultValue={afternoon} class="dropdown" id="afternoon_priorities" onChange = {handleSubmitAfternoon}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
                </select> <br></br>
            <label>Prefer No Evening Classes</label>
            <select list="Priority" defaultValue={evening} class="dropdown" id="evening_priorities" onChange = {handleSubmitEvening}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label>Minimize Days with Classes</label>
            <select list="Priority" defaultValue={minimize} class="dropdown" id="minimize_priorities" onChange = {handleSubmitMinDay}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Async Classes</label>
            <select list="Priority" defaultValue={async} class="dropdown" id="async_priorities" onChange = {handleSubmitAsync}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Sync Classes</label>
            <select list="Priority" defaultValue={sync} class="dropdown" id="sync_priorities" onChange = {handleSubmitSync}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Lunch Break</label>
            <select list="Priority" defaultValue={lunch} class="dropdown" id="lunch_priorities" onChange = {handleSubmitLunch}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Dinner Break</label>
            <select list="Priority" defaultValue={dinner} class="dropdown" id="dinner_priorities" onChange = {handleSubmitDinner}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
                
            <label id="before">No Class Before: </label>
            <input type="number" defaultValue={before_value} id="before_value" min="10" max="20" onClick = {handleSubmitNoClassBefore} ></input> 
            <select list="Priority" defaultValue={before} class="dropdown" id="before_priorities" onChange = {handleSubmitNoClassBefore}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label id="after">No Class After: </label>
            <input type="number" defaultValue={after_value} id="after_value" min="9" max="19" onClick = {handleSubmitNoClassAfter} ></input>
            <select list="Priority" defaultValue={after} class="dropdown" id="after_priorities" onChange = {handleSubmitNoClassAfter}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label id="max">Max Hours of Class Back to Back</label>
            <input type="number" defaultValue={max_class_value} id="max_class_value" min="1" max="12" onChange = {handleSubmitMaxBack} ></input>
            <select list="Priority" defaultValue={max_class} class="dropdown" id="max_class_priorities" onChange = {handleSubmitMaxBack}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
            <label id="max">Max Hours of Break</label>
            <input type="number" defaultValue={max_break_value} id="max_break_value" min="1" max="12" onChange = {handleSubmitMaxBreak} ></input>
            <select list="Priority" defaultValue={max_break} class="dropdown" id="max_break_priorities" onChange = {handleSubmitMaxBreak}>
                <option value="0"></option>
                <option class="good_to_have" value="1">Good To Have</option>
                <option class="great_to_have" value="2">Great To Have</option>
                <option class="must_have" value="3">Must Have</option>
            </select> <br></br>
           
       </div>
  )}


export default AddConstraintButton;
