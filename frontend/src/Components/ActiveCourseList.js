// -- Module --
const ActiveCourseList = ({courses, setCourses}) => {

    const removeCourse = course => {
      console.log(`removing course: ${course}`)
      setCourses(prev => new Set([...prev].filter(x => x !== course)))
    };

    const removeAllCourses = course => {
      setCourses(prev => new Set())
    };

    function handleSubmitPrepopulate (event) {
      event.preventDefault();
      //get the index of courses we want
      const timetable_value = document.getElementById("prepopulate").value;
      console.log(timetable_value)
      switch (parseInt(timetable_value)) {
        case 0:
          
          break;
        case 1:
          //1st year ECE
          removeAllCourses();
          //add all first year ece courses
          setCourses(prev => new Set(prev.add("APS100H1")))
          setCourses(prev => new Set(prev.add("APS111H1")))
          setCourses(prev => new Set(prev.add("CIV100H1")))
          setCourses(prev => new Set(prev.add("APS110H1")))
          setCourses(prev => new Set(prev.add("MAT188H1")))
          setCourses(prev => new Set(prev.add("MAT186H1")))
          
          setCourses(prev => new Set(prev.add("APS105H1")))
          setCourses(prev => new Set(prev.add("APS112H1")))
          setCourses(prev => new Set(prev.add("MIE100H1")))
          setCourses(prev => new Set(prev.add("ECE110H1")))
          setCourses(prev => new Set(prev.add("ECE191H1")))
          setCourses(prev => new Set(prev.add("MAT187H1"))) 

          break;
        case 2:
          break;
        default:
          break;

      }

    } 
    return (
      <div className = "active-courses" id="active-courses">
        
         <h4 id='course-list-header'> <u>Desired Classes:</u></h4>
         {[...courses].map((course)=>(
            <div className="active-course-list" >
              
            <p id='active-course-list-text'>{course}</p>
            <button id='active-course-remove'onClick={event => removeCourse(course)} >X</button>
            </div>
            
          ))}
        <button onClick={event => removeAllCourses()}>Clear All</button>
        <select list="prepopulate" class="dropdown" id="prepopulate" onChange = {handleSubmitPrepopulate}>
                <option value="0"></option>
                <option class="ece_1" value="1" >1st Year ECE</option>
                <option class="ece_2" value="2">2nd Year ECE</option>
                <option class="civ_2" value="3">2nd Year CIV</option>
                <option class="esci_1" value="4">1st Year EngSci</option>
            </select> <br></br>
      </div>
    )
  }
  
  // -- Exports --
  export default ActiveCourseList;
  