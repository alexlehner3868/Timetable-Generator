// -- Module --
const Generate = ({courses, setTimetable}) => {
  const Request = async () => {
    // Extract the courses as strings
    const arr = Array.from(courses);
    console.log(`fetching: [${arr}]`);

    // Encode the courses to send to the API
    const encoded = encodeURIComponent(arr);

    // Perform an API fetch
    let response = await fetch(`http://127.0.0.1:5000/gen?courses=${encoded}`, {
      method: "GET",
      mode: "cors",
    })
    .then(response => response.json())
    // Log the response
    console.log("generated:", response);

    // Update the global state
    setTimetable(response);
  };

  return (
    <div>
      <button
        onClick={event => Request()}
        className="btn btn-primary mt-2"
      >Generate</button>
    </div>
  )
}

// -- Exports --
export default Generate;
