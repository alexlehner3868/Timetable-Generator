

const AddConstraintButton = (props) => {
    const addConstraint = (constraint) => {
        console.log(`adding constraint: ${constraint}`)
        props.setConstraints(prev => new Set(prev.add(constraint)))
    }

       
    const removeConstraint = (constraint) => {
      console.log(`removing constraint: ${constraint}`)
      props.setConstraints(prev => new Set([...prev].filter(x => (x !== (constraint + "0")
                                                                && x!== (constraint + "1") 
                                                                && x!== (constraint + "2")
                                                                && x!== (constraint + "3")
                                                                ))))
    };
    
    const priority = 0;
    /*
        00 - prefer early classes
        01 - prefer afternoon classes
        02 - prefer evening classes
        03 - prefer minimum days on campus 
        04 - prefer async classes 
        05 - prefer syunc classes
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
      
      if (priority != "0") {
        console.log(priority);
        console.log("Prioritizing Early Classes");
        console.log("00" + priority);
        addConstraint("00" + priority);
      }
    } function handleSubmitAfternoon (event) {
        event.preventDefault()
        console.log(document.getElementById("afternoon_priorities").value);
        console.log("Prioritizing Afternoon Classes")
    } function handleSubmitEvening (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritizing Evening Classes")
    } function handleSubmitMinDay (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritizing Minimum Days on Campus")
    } function handleSubmitAsync (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritizing Asynchronous Courses")
    } function handleSubmitSync (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritizing Synchronous Courses")
    } function handleSubmitLunch (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritize Making Lunch Break")
    } function handleSubmitDinner (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritiing Making Dinner Break")
    } function handleSubmitNoClassBefore (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritize Classes After X")
    } function handleSubmitNoClassAfter (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Prioritize Classes After Y")
    } function handleSubmitMaxBack (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Setting longest possible break")
    } function handleSubmitMaxBreak (event) {
        event.preventDefault()
        //addConstraint()
        console.log("Setting longest possible break")
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
            <input type="number" id="before" min="10" max="20" onClick = {handleSubmitNoClassBefore} ></input><br></br>
            <label id="after">No Class After: </label>
            <input type="number" id="after" min="9" max="19" onClick = {handleSubmitNoClassAfter} ></input><br></br>
            <label id="max">Max Hours of Class Back to Back</label>
            <input type="number" id="max_class" min="0" max="12" onClick = {handleSubmitMaxBack} ></input><br></br>
            <label id="max">Max Hours of Break</label>
            <input type="number" id="max_break" min="0" max="12" onClick = {handleSubmitMaxBreak} ></input><br></br>

       </div>
  )}

export default AddConstraintButton;
