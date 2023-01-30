// -- Module --
const ActiveCourseList = ({courses, setCourses}) => {

    const removeCourse = course => {
      console.log(`removing course: ${course}`)
      setCourses(prev => new Set([...prev].filter(x => x !== course)))
    };

  
    return (
      <div className = "active-courses" id="active-courses">
         <h4 id='course-list-header'> <u>Desired Classes:</u></h4>
         {[...courses].map((course)=>(
            <div className="active-course-list">
              
            <p id='active-course-list-text'>{course}</p>
            <button id='active-course-remove'onClick={event => removeCourse(course)} >X</button>
            </div>
          ))}
        
      </div>
    )
  }
  
  // -- Exports --
  export default ActiveCourseList;
  