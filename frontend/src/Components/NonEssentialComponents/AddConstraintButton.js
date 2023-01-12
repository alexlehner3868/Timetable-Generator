

const AddConstraintButton = (props) => {
    const addConstraint = (constraint) => {
        console.log(`adding constraint: ${constraint}`)
        props.setConstraints(prev => new Set(prev.add(constraint)))
    }

       
    const removeConstraint = (constraint) => {
      console.log(`removing constraint: ${constraint}`)
      props.setConstraints(prev => new Set([...prev].filter(x => x !== constraint)))
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
      console.log(document.getElementById("morning_priorities").value);
      console.log("Prioritizing Early Classes")
    } function handleSubmitAfternoon (event) {
        event.preventDefault()
        document.getElementById("afternoon_priorities").value = priority;
        addConstraint()
        console.log("Prioritizing Afternoon Classes")
    } function handleSubmitEvening (event) {
        event.preventDefault()
        addConstraint()
        console.log("Prioritizing Evening Classes")
    } function handleSubmitMinDay (event) {
        event.preventDefault()
        addConstraint()
        console.log("Prioritizing Minimum Days on Campus")
    } function handleSubmitBackBefore (event) {
        event.preventDefault()
        addConstraint()
        console.log("Prioritize Classes After X")
    } function handleSubmitBackAfter (event) {
    } function handleSubmitBack (event) {
    } function handleSubmitBreak (event) {
        event.preventDefault()
        addConstraint()
        console.log("Blocking Off Time")
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
            <select list="Priority" id="afternoon_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Evening Classes</label>
            <select list="Priority" id="evening_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Minimize Days with Classes</label>
            <select list="Priority" id="minimize_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Async Classes</label>
            <select list="Priority" id="async_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Sync Classes</label>
            <select list="Priority" id="sync_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Lunch Break</label>
            <select list="Priority" id="lunch_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
            <label>Prefer Dinner Break</label>
            <select list="Priority" id="dinner_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
            </select> <br></br>
                
            <label id="before">No Class Before: </label>
            <input type="number" id="before" min="10" max="20" onClick = {handleSubmitBackBefore} ></input><br></br>
            <label id="after">No Class After: </label>
            <input type="number" id="after" min="9" max="19" onClick = {handleSubmitBackAfter} ></input><br></br>
            <label id="max">Max Hours of Class Back to Back</label>
            <input type="number" id="max_class" min="0" max="12" onClick = {handleSubmitBack} ></input><br></br>
            <label id="max">Max Hours of Break</label>
            <input type="number" id="max_break" min="0" max="12" onClick = {handleSubmitBreak} ></input><br></br>

       </div>
  )}

export default AddConstraintButton;
