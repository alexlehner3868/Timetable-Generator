// -- Module --
const EditCourse = ({course, setCourses, showResults}) => {
  const addCourse = course => {
    console.log(`adding course: ${course}`)
    setCourses(prev => new Set(prev.add(course)))
  };

  function clearInput() {
    document.getElementById("search-course-form").reset();
  };

  const AddCourseButtonClick = course => {
    addCourse(course);
    showResults("");
    clearInput();
  };

  
 
  const removeCourse = course => {
    console.log(`removing course: ${course}`)
    setCourses(prev => new Set([...prev].filter(x => x !== course)))
  };

  return (
    <div>
      <button
        onClick={event => AddCourseButtonClick(course)}
        className="btn btn-primary mt-2"
      >Add</button>
    </div>
  )
}

// -- Exports --
export default EditCourse;
