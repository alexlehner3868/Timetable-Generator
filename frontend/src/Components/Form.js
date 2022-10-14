import { useState } from 'react';
import APIService from '../Components/APIService'

const Form = (props) => {
    const [body, setBody] = useState('')

    const insertArticle = () =>{
      APIService.InsertArticle({body})
      .then((response) => props.insertedArticle(response))
      .catch(error => console.log('error',error))
    }

    const handleSubmit=(event)=>{ 
      event.preventDefault()
      insertArticle()
      setBody('')
    }

  return (
       <div>
           <form onSubmit = {handleSubmit} >

              

              <label htmlFor="body" className="form-label">Body</label>
              <textarea 
              className="form-control" 
              placeholder ="Enter body" 
              rows='6'
              value={body}
              onChange={(e)=>setBody(e.target.value)}
              required
              >
              </textarea>

              <button 
              className="btn btn-primary mt-2"
              >
              Publish article</button>
              
            </form>
       </div>
  )}

export default Form;
