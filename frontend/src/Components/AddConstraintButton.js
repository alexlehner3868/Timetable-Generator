import { useState } from 'react';
import AddConstraintServiceAPI from './AddConstraintService';

const AddConstraintButton = (props) => {
    const [constraint, setConstraintName] = useState('')
    const addConstraint = () =>{
      AddConstraintServiceAPI.AddConstraint({constraint})
      .then((response) => props.removedClass(response))
      .catch(error => console.log('error',error))
    }

    const handleSubmit=(event)=>{ 
      event.preventDefault()
      setConstraintName("Prioritize Early Classes")
      addConstraint()
      console.log("Prioritizing Early Classes")
    }
    
  return (
       <div>
             <button onClick = {handleSubmit} className="btn btn-primary mt-2" > Prioritize Early Classes </button>
       </div>
  )}

export default AddConstraintButton;
