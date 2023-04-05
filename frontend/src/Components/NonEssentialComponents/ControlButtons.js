import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';
import Generate from '../Generate';

const ControlButtons = ({courses, constraints, setTimetables, setTtbIndex, num_timetables, setCourses, setConstraints, setNumTimetables, setMessage}) => {

    const Request = async () => {
        setMessage("Please wait for a timeable to generate...");
        // Extract the courses, constraints as strings
        const course_array = Array.from(courses);
        const constraint_array = Array.from(constraints);
        const num_timetables_array = num_timetables;
        console.log(`fetching: [${course_array}], with: [${constraint_array}], with ${num_timetables_array}`);
    
        // Encode the courses to send to the API
        const courses_encoded = encodeURIComponent(course_array);
        const constraints_encoded = encodeURIComponent(constraint_array);
        const num_timetables_encoded = encodeURIComponent(num_timetables_array);
        // Perform an API fetch
        let response = await fetch(`http://127.0.0.1:5000/gen?courses=${courses_encoded}&constraints=${constraints_encoded}&numtimetables=${num_timetables_encoded}`, {
          method: "GET",
          mode: "cors",
        })
        .then(response =>  response.json())
        // Log the response
        setMessage("Timetable generation completed.");
        //console.log("about to print");
        console.log("response is", response)
        if (response.length != 0) {
          //console.log("generated:", response.slice(0,-1));
          //console.log("message:", response.slice(-1)[0][0].Message);
          setMessage(response.slice(-1)[0][0].Message);
          setTimetables(response.slice(0,-1));
        } else {
          setMessage("Empty timetable. Please add courses and/or constraints.")
          setTimetables([])
        }
        // Update the global state
        // Put the user back on first timetable
        setTtbIndex(0);
      };

    const removeAll = (constraint) => {
        if (document.getElementById("morning_priorities")) {
          document.getElementById("morning_priorities").value = 0;
        } if (document.getElementById("afternoon_priorities")) {
          document.getElementById("afternoon_priorities").value = 0;
        } if (document.getElementById("evening_priorities")) {
          document.getElementById("evening_priorities").value = 0;
        } if (document.getElementById("minimize_priorities")) {
          document.getElementById("minimize_priorities").value = 0;
        } if (document.getElementById("async_priorities")) {
          document.getElementById("async_priorities").value = 0;
        } if (document.getElementById("sync_priorities")) {
          document.getElementById("sync_priorities").value = 0;
        } if (document.getElementById("lunch_priorities")) {
          document.getElementById("lunch_priorities").value = 0;
        } if (document.getElementById("dinner_priorities")) {
          document.getElementById("dinner_priorities").value = 0;
        } if (document.getElementById("before_priorities")) {
          document.getElementById("before_priorities").value = 0;
        } if (document.getElementById("before_value")) {
          document.getElementById("before_value").value = "";
        } if (document.getElementById("after_priorities")) {
          document.getElementById("after_priorities").value = 0;
        } if (document.getElementById("after_value")) {
          document.getElementById("after_value").value = "";
        } if (document.getElementById("max_class_priorities")) {
          document.getElementById("max_class_priorities").value = 0;
        } if (document.getElementById("max_class_value")) {
          document.getElementById("max_class_value").value = "";
        } if (document.getElementById("max_break_priorities")) {
          document.getElementById("max_break_priorities").value = 0;
        } if (document.getElementById("max_break_value")) {
          document.getElementById("max_break_value").value = "";
        }
        setConstraints(prev => new Set())
        setCourses(prev => new Set())
        setNumTimetables(20);
        setMessage("Please add courses and constraints to generate timetables.");
      };

      const removeAllCourses = course => {
        setCourses(prev => new Set())
        setMessage("Please add a course to generate timetables.");
      };

      const removeAllConstraints = (constraint) => {
        if (document.getElementById("morning_priorities")) {
          document.getElementById("morning_priorities").value = 0;
        } if (document.getElementById("afternoon_priorities")) {
          document.getElementById("afternoon_priorities").value = 0;
        } if (document.getElementById("evening_priorities")) {
          document.getElementById("evening_priorities").value = 0;
        } if (document.getElementById("minimize_priorities")) {
          document.getElementById("minimize_priorities").value = 0;
        } if (document.getElementById("async_priorities")) {
          document.getElementById("async_priorities").value = 0;
        } if (document.getElementById("sync_priorities")) {
          document.getElementById("sync_priorities").value = 0;
        } if (document.getElementById("lunch_priorities")) {
          document.getElementById("lunch_priorities").value = 0;
        } if (document.getElementById("dinner_priorities")) {
          document.getElementById("dinner_priorities").value = 0;
        } if (document.getElementById("before_priorities")) {
          document.getElementById("before_priorities").value = 0;
        } if (document.getElementById("before_value")) {
          document.getElementById("before_value").value = "";
        } if (document.getElementById("after_priorities")) {
          document.getElementById("after_priorities").value = 0;
        } if (document.getElementById("after_value")) {
          document.getElementById("after_value").value = "";
        } if (document.getElementById("max_class_priorities")) {
          document.getElementById("max_class_priorities").value = 0;
        } if (document.getElementById("max_class_value")) {
          document.getElementById("max_class_value").value = "";
        } if (document.getElementById("max_break_priorities")) {
          document.getElementById("max_break_priorities").value = 0;
        } if (document.getElementById("max_break_value")) {
          document.getElementById("max_break_value").value = "";
        }
        setConstraints(prev => new Set())
        setNumTimetables(20);
        setMessage("Please generate timetables again.");
    };

      function handleDeleteAll (event) {
        event.preventDefault()
        removeAllConstraints();
        console.log("deleting all constraints");
        console.log()
    }


    
  return (
    <div className="control-buttons">
         <AwesomeButton className="generate-button" type="primary" onPress={event => Request()} >Generate Timetables</AwesomeButton>
        <AwesomeButton className="clear-class" onPress={event => removeAllCourses()}>Clear Courses</AwesomeButton>
        <AwesomeButton className="clear-constraints" onPress = {handleDeleteAll}>Clear Constraints</AwesomeButton>
        <AwesomeButton  className="clear-all" onPress={event => removeAll()}>Clear Courses & Constraints</AwesomeButton>
    </div>
  )}


export default ControlButtons;
