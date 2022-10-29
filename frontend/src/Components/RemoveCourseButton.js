import { useState } from 'react';
import RemoveCourseServiceAPI from './RemoveCourseService'

const RemoveCourseButton = (props) => {
    const [class_name, setClassName] = useState('')
    const removeClass = () =>{
      RemoveCourseServiceAPI.RemoveClass({class_name})
      .then((response) => props.removedClass(response))
      .catch(error => console.log('error',error))
    }

    const handleSubmit=(event)=>{ 
      event.preventDefault()
      setClassName(props.course_code)
      removeClass()
      console.log(props.course_code)
    }
    
  return (
       <div>
             <button onClick = {handleSubmit} className="btn btn-primary mt-2" > Remove Course from Schedule </button>
       </div>
  )}

export default RemoveCourseButton;
