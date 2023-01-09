// -- Module --
const BackButton = ({timetables, setTimetables}) => {
    const Request = async () => {
      // Update the global state
      
      const len_timetables = timetables.length;
      if (len_timetables > 1) {
        console.log("Attempting to get previous timetable.");
        const last_of_arr = timetables[len_timetables - 1];
        timetables.unshift(last_of_arr);
        setTimetables(timetables.slice(0,-1));
      }
    };

    return (
      <div>
        <button
          onClick={event => Request()}
          className="btn btn-primary mt-2"
        >BACK</button>
      </div>
    )
  }
  
  // -- Exports --
  export default BackButton;
  