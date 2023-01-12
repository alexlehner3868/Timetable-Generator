

const AddConstraintButton = (props) => {
    const addConstraint = (constraint) => {
        console.log(`adding constraint: ${constraint}`)
        props.setConstraints(prev => new Set(prev.add(constraint)))
    }

       
    const removeConstraint = (constraint) => {
      console.log(`removing constraint: ${constraint}`)
      props.setConstraints(prev => new Set([...prev].filter(x => x !== constraint)))
    };

    function handleSubmitEarly (event) {
      event.preventDefault()
      //these only work if they're all the same
      addConstraint("")
      console.log("Prioritizing Early Classes")
    } function handleSubmitAfternoon (event) {
        event.preventDefault()
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
    } function handleSubmitBlock (event) {
        event.preventDefault()
        addConstraint()
        console.log("Blocking Off Time")
    }
    //use fieldset disabled key for constraints later
  return (
       <div>
            <label>Prefer Morning Classes</label>
            <select list="Priority" id="morning_priorities">
                <option value="0"></option>
                <option value="1">Good To Have</option>
                <option value="2">Great To Have</option>
                <option value="3">Must Have</option>
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
                
                <label for="before">No Class Before: </label>
                <input type="number" id="before" min="10" max="20" onClick = {handleSubmitBackBefore} ></input><br></br>
                <label for="after">No Class After: </label>
                <input type="number" id="after" min="9" max="19" onClick = {handleSubmitBackAfter} ></input><br></br>
                <label for="max">Max Hours of Class Back to Back</label>
                <input type="number" id="max_class" min="0" max="12" onClick = {handleSubmitBack} ></input><br></br>
                <label for="max">Max Hours of Break</label>
                <input type="number" id="max_break" min="0" max="12" onClick = {handleSubmitBack} ></input><br></br>

                <fieldset class="fieldset-form">
                        <legend> Block Off Time </legend>
                        <form>
                            <label for="block">Block off: </label>
                            <select list="time" id="times">
                                <option value="none">Select:</option>
                                <option value="1">1</option>
                                <option value="2">2</option>
                                <option value="3">3</option>
                                <option value="4">4</option>
                                <option value="5">5</option>
                                <option value="6">6</option>
                                <option value="7">7</option>
                                <option value="8">8</option>
                                <option value="9">9</option>
                                <option value="10">10</option>
                                <option value="11">11</option>
                                <option value="12">12</option>
                            </select>
                            <label for="block"> Hours on: </label>
                            <select list="day" id="days">
                                <option value="none">Select:</option>
                                <option value="Monday">Monday</option>
                                <option value="Tuesday">Tuesday</option>
                                <option value="Wednesday">Wednesday</option>
                                <option value="Thursday">Thursday</option>
                                <option value="Friday">Friday</option>
                            </select>
                            <label for="block"> at: </label>
                            <select list="time_" id="times_">
                                <option value="none">Select:</option>
                                <option value="9">9</option>
                                <option value="10">10</option>
                                <option value="11">11</option>
                                <option value="12">12</option>
                                <option value="13">1</option>
                                <option value="14">2</option>
                                <option value="15">3</option>
                                <option value="16">4</option>
                                <option value="17">5</option>
                                <option value="18">6</option>
                                <option value="19">7</option>
                                <option value="20">8</option>
                            </select>
                            <input type="submit" onClick = {handleSubmitBlock} ></input>
                        </form>
                </fieldset>

       </div>
  )}

export default AddConstraintButton;
