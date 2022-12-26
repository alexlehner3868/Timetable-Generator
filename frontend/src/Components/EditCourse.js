// -- Module --
const EditCourse = ({course, setCourses}) => {
  const addCourse = course => {
    console.log(`adding course: ${course}`)
    setCourses(prev => new Set(prev.add(course)))
  };

  const removeCourse = course => {
    console.log(`removing course: ${course}`)
    setCourses(prev => new Set([...prev].filter(x => x !== course)))
  };

  return (
    <div>
      <button
        onClick={event => addCourse(course)}
        className="btn btn-primary mt-2"
      >Add</button>
      <button
        onClick={event => removeCourse(course)}
        className="btn btn-primary mt-2"
      >Remove</button>
    </div>
  )
}

// -- Exports --
export default EditCourse;
