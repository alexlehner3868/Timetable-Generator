import { useState } from 'react';
import AddConstraintServiceAPI from './AddConstraintService';

const AddConstraintButton = (props) => {
    const [constraint, setConstraintName] = useState('')
    const addConstraint = () =>{
      AddConstraintServiceAPI.AddConstraint({constraint})
      .then((response) => props.removedClass(response))
      .catch(error => console.log('error',error))
    }

    function handleSubmit (event) { 
      event.preventDefault()
      setConstraintName("Prioritize Early Classes")
      document.getElementById("early").checked = true;
      addConstraint()
      console.log("Prioritizing Early Classes")
    }
    
  return (
       <div>
             <form>
                <input type="checkbox" id="early" name="fav_language" value="early" onClick = {handleSubmit}></input>
                <label for="early">Prefer Morning Classes</label>
                <input type="checkbox" id="afternoon" name="fav_language" value="afternoon" onClick = {handleSubmit}></input>
                <label for="afternoon">Prefer Afternoon Classes</label>
                <input type="checkbox" id="evening" name="fav_language" value="evening" onClick = {handleSubmit}></input>
                <label for="evening">Prefer Evening Classes</label>
            </form>
       </div>
  )}

export default AddConstraintButton;
