import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';
// -- Module --
const Generate = ({courses, constraints, setTimetables, setTtbIndex}) => {
  const Request = async () => {
    // Extract the courses, constraints as strings
    const course_array = Array.from(courses);
    const constraint_array = Array.from(constraints);
    console.log(`fetching: [${course_array}], with: [${constraint_array}]`);

    // Encode the courses to send to the API
    const courses_encoded = encodeURIComponent(course_array);
    const constraints_encoded = encodeURIComponent(constraint_array);
    // Perform an API fetch
    let response = await fetch(`http://127.0.0.1:5000/gen?courses=${courses_encoded}&constraints=${constraints_encoded}`, {
      method: "GET",
      mode: "cors",
    })
    .then(response => response.json())
    // Log the response
    console.log("generated:", response);
    // Update the global state
    setTimetables(response);
    // Put the user back on first timetable
    setTtbIndex(0);
  };

  return (
    <div className="generate-button">
      <AwesomeButton
      type="primary"
        onPress={event => Request()}
      >Generate</AwesomeButton>
    </div>
  )
}

// -- Exports --
export default Generate;
