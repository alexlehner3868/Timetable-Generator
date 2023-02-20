import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';
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
    <div className="add-button">
      <AwesomeButton
        onPress={event => AddCourseButtonClick(course)}
        
      >Add</AwesomeButton>
    </div>
  )
}

// -- Exports --
export default EditCourse;
