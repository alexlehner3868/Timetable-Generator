import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';

// NOTE: THIS ITEM IS NO LONGER USED. IT HAS BEEN MERGED INTO CONTROL BUTTONS
// -- Module --
/*
const Generate = ({courses, constraints, setTimetables, setTtbIndex, num_timetables}) => {
  const Request = async () => {
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
    .then(response => response.json())
    // Log the response
    
    console.log("about to print");
    console.log("generated:", response.slice(0,-1));
    console.log("message:", response.slice(-1));
    // Update the global state
    setTimetables(response.slice(0,-1));
    //setMessage(response.slice(-1))
    // Put the user back on first timetable
    setTtbIndex(0);
  };

  return (
    <div >
      <AwesomeButton className="generate-button"
      type="primary"
        onPress={event => Request()}
      >Generate</AwesomeButton>
    </div>
  )
}

// -- Exports --
export default Generate;
*/