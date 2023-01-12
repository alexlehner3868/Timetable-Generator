

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

    function handleSubmitEarly (event) {
      event.preventDefault()
      // remove all "early" constraints existing previously
      removeConstraint("00");
      const priority = document.getElementById("morning_priorities").value
      
      if (priority !== "0") {
        console.log(priority);
        console.log("Prioritizing Early Classes");
        console.log("00" + priority + "00");
        addConstraint("00" + priority + "00");
      }
    } function handleSubmitAfternoon (event) {
        event.preventDefault()
        removeConstraint("01");
        const priority = document.getElementById("afternoon_priorities").value
      
        if (priority !== "0") {
        console.log(priority);
        console.log("Prioritizing Afternoon Classes");
        console.log("01" + priority + "00");
        addConstraint("01" + priority + "00");
        }
    } function handleSubmitEvening (event) {
        event.preventDefault()
        removeConstraint("02");
        const priority = document.getElementById("evening_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Evening Classes");
            console.log("02" + priority + "00");
            addConstraint("02" + priority + "00");
        }
    } function handleSubmitMinDay (event) {
        event.preventDefault()
        removeConstraint("03");
        const priority = document.getElementById("minimize_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Minimum Days on Campus")
            console.log("03" + priority + "00");
            addConstraint("03" + priority + "00");
        }
    } function handleSubmitAsync (event) {
        event.preventDefault()
        removeConstraint("04");
        const priority = document.getElementById("async_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Asynchronous Courses")
            console.log("04" + priority + "00");
            addConstraint("04" + priority + "00");
        }
    } function handleSubmitSync (event) {
        event.preventDefault()
        removeConstraint("05");
        const priority = document.getElementById("sync_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Synchronous Courses")
            console.log("05" + priority + "00");
            addConstraint("05" + priority + "00");
        }
    } function handleSubmitLunch (event) {
        event.preventDefault()
        removeConstraint("06");
        const priority = document.getElementById("lunch_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Making Lunch Break")
            console.log("06" + priority + "00");
            addConstraint("06" + priority + "00");
        }
    } function handleSubmitDinner (event) {
        event.preventDefault()
        removeConstraint("07");
        const priority = document.getElementById("dinner_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Making Dinner Break")
            console.log("07" + priority + "00");
            addConstraint("07" + priority + "00");
        }
    } function handleSubmitNoClassBefore (event) {
        event.preventDefault()
        removeConstraint("08");
        const priority = document.getElementById("before_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Courses Before X")
            console.log("08" + priority + "00");
            addConstraint("08" + priority + "00");
        }
        console.log("Prioritizing Classes After X")
    } function handleSubmitNoClassAfter (event) {
        event.preventDefault()
        removeConstraint("09");
        const priority = document.getElementById("after_priorities").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Classes Before Y");
            console.log("09" + priority + "00");
            addConstraint("09" + priority + "00");
        }
    } function handleSubmitMaxBack (event) {
        event.preventDefault()
        removeConstraint("10");
        const priority = document.getElementById("max_class_priorities").value
        const hours = document.getElementById("max_class_value").value
        console.log(hours);
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Shortest Possible B2B Hours of Class");
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
        event.preventDefault()
        removeConstraint("11");
        const priority = document.getElementById("max_break_priorities").value
        const hours = document.getElementById("max_break_value").value
      
        if (priority !== "0") {
            console.log(priority);
            console.log("Prioritizing Shortest Break")
            console.log("11" + priority + hours);
            const int_hours = parseInt(hours);
            if (int_hours < 10 && int_hours > 0) { //single digit hour value
                addConstraint("11" + priority + "0" + hours);
            } else if (int_hours > 9 && int_hours < 13 ) {
                addConstraint("11" + priority + hours);
            } else {
                // error so don't do anything
            }
        }
    } 
    
    
    
  return (
       <div>
            <label>Prefer Morning Classes</label>
            <select list="Priority" id="morning_priorities" onClick = {handleSubmitEarly}>
                <option value="0" ></option>
                <option value="1" >Good To Have</option>
                <option value="2" >Great To Have</option>
                <option value="3" >Must Have</option>
            </select> <br></br>
            <label>Prefer Afternoon Classes</label>
            <select list="Priority" id="afternoon_priorities" onClick = {handleSubmitAfternoon}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Evening Classes</label>
            <select list="Priority" id="evening_priorities" onClick = {handleSubmitEvening}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Minimize Days with Classes</label>
            <select list="Priority" id="minimize_priorities" onClick = {handleSubmitMinDay}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Async Classes</label>
            <select list="Priority" id="async_priorities" onClick = {handleSubmitAsync}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Sync Classes</label>
            <select list="Priority" id="sync_priorities" onClick = {handleSubmitSync}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Lunch Break</label>
            <select list="Priority" id="lunch_priorities" onClick = {handleSubmitLunch}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Dinner Break</label>
            <select list="Priority" id="dinner_priorities" onClick = {handleSubmitDinner}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
                
            <label id="before">No Class Before: </label>
            <input type="number" id="before_value" min="10" max="20" onClick = {handleSubmitNoClassBefore} ></input> 
            <select list="Priority" id="before_priorities" onClick = {handleSubmitNoClassBefore}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label id="after">No Class After: </label>
            <input type="number" id="after_value" min="9" max="19" onClick = {handleSubmitNoClassAfter} ></input>
            <select list="Priority" id="after_priorities" onClick = {handleSubmitNoClassAfter}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label id="max">Max Hours of Class Back to Back</label>
            <input type="number" id="max_class_value" min="0" max="12" onClick = {handleSubmitMaxBack} ></input>
            <select list="Priority" id="max_class_priorities" onClick = {handleSubmitMaxBack}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label id="max">Max Hours of Break</label>
            <input type="number" id="max_break_value" min="0" max="12" onClick = {handleSubmitMaxBreak} ></input>
            <select list="Priority" id="max_break_priorities" onClick = {handleSubmitMaxBreak}>
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>

       </div>
  )}

export default AddConstraintButton;
