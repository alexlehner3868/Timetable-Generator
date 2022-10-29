import { useState } from 'react';
import APIService from './AddCourseService'

const Form = (props) => {
    const [class_name, setClassName] = useState('')
    const insertClass = () =>{
      APIService.InsertClass({class_name})
      .then((response) => props.insertedClass(response))
      .catch(error => console.log('error',error))
    }

    const handleSubmit=(event)=>{ 
      event.preventDefault()
      setClassName(props.course_code)
      insertClass()
      console.log(props.course_code)
    }
    
  return (
       <div>
             <button onClick = {handleSubmit} className="btn btn-primary mt-2"> Add Course to Plan </button>
       </div>
  )}

export default Form;
