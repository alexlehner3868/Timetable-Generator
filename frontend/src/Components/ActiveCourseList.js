// -- Module --
const ActiveCourseList = ({courses, setCourses}) => {

    const removeCourse = course => {
      console.log(`removing course: ${course}`)
      setCourses(prev => new Set([...prev].filter(x => x !== course)))
    };
  
    return (
      <div class = "border-section">
         {[...courses].map((course)=>(
            <div class="active-course-list">
            <p id='active-course-list-text'>{course}</p>
            <button id='active-course-remove'onClick={event => removeCourse(course)} className="btn btn-primary mt-2">X</button>
            </div>
          ))}
        
      </div>
    )
  }
  
  // -- Exports --
  export default ActiveCourseList;
  