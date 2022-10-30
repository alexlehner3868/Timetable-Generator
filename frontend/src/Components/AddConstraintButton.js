import { useState } from 'react';
import AddConstraintServiceAPI from './AddConstraintService';

const AddConstraintButton = (props) => {
    const [constraint, setConstraintName] = useState('')
    const addConstraint = () =>{
      AddConstraintServiceAPI.AddConstraint({constraint})
      .then((response) => props.addedConstraint(response))
      .catch(error => console.log('error',error))
    }

    function handleSubmitEarly (event) { 
      event.preventDefault()
      setConstraintName("Prioritize Early Classes")
      //these only work if they're all the same
      document.getElementById("early").checked = true;
      addConstraint()
      console.log("Prioritizing Early Classes")
    } function handleSubmitAfternoon (event) { 
        event.preventDefault()
        setConstraintName("Prioritize Afternoon Classes")
        document.getElementById("afternoon").checked = true;
        addConstraint()
        console.log("Prioritizing Afternoon Classes")
    } function handleSubmitEvening (event) { 
        event.preventDefault()
        setConstraintName("Prioritize Evening Classes")
        document.getElementById("evening").checked = true;
        addConstraint()
        console.log("Prioritizing Evening Classes")
    } function handleSubmitMinDay (event) { 
        event.preventDefault()
        setConstraintName("Prioritize Minimum Days")
        document.getElementById("min_day").checked = true;
        addConstraint()
        console.log("Prioritizing Minimum Days on Campus")
    } function handleSubmitBackBefore (event) { 
        event.preventDefault()
        setConstraintName("Prioritize Back to Back Classes")
        addConstraint()
        console.log("Prioritizing Back to Back Classes")
    } function handleSubmitBackAfter (event) { 
        event.preventDefault()
        setConstraintName("Prioritize Back to Back Classes")
        addConstraint()
        console.log("Prioritizing Back to Back Classes")
    }
    
  return (
       <div>
             <form>
                <input type="checkbox" id="early" name="fav_language" value="early" onClick = {handleSubmitEarly}></input>
                <label for="early">Prefer Morning Classes</label><br></br>
                <input type="checkbox" id="afternoon" name="fav_language" value="afternoon" onClick = {handleSubmitAfternoon}></input>
                <label for="afternoon">Prefer Afternoon Classes</label><br></br>
                <input type="checkbox" id="evening" name="fav_language" value="evening" onClick = {handleSubmitEvening}></input>
                <label for="evening">Prefer Evening Classes</label><br></br>
                <input type="checkbox" id="min_day" name="fav_language" value="min_day" onClick = {handleSubmitMinDay}></input>
                <label for="min_day">Prefer Minimum Days on Campus</label><br></br>
                <label for="back2back">No Class Before: </label>
                <input type="number" min="10" max="20" onClick = {handleSubmitBackBefore} ></input><br></br> 
                <label for="back2back">No Class After: </label>
                <input type="number" min="9" max="19" onClick = {handleSubmitBackAfter} ></input><br></br> 

            </form>
       </div>
  )}

export default AddConstraintButton;
