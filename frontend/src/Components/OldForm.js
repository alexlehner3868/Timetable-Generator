import { useState } from 'react';
import APIService from '../Components/APIService'

const Form = (props) => {
    const [class_name, setClassName] = useState('')

    const insertClass = () =>{
      APIService.InsertClass({class_name})
      .then((response) => props.insertedClass(response))
      .catch(error => console.log('error',error))
    }

    const handleSubmit=(event)=>{ 
      event.preventDefault()
      insertClass()
      setClassName('')
    }

  return (
       <div>
           <form onSubmit = {handleSubmit} >

              

              <label htmlFor="class_name" className="form-label">Class</label>
              <textarea 
              className="form-control" 
              placeholder ="Enter class name" 
              rows='6'
              value={class_name}
              onChange={(e)=>setClassName(e.target.value)}
              required
              >
              </textarea>

              <button 
              className="btn btn-primary mt-2"
              >
              Publish Class</button>
              
            </form>
       </div>
  )}

export default Form;
