// -- Module --
const NextButton = ({timetables, setTimetables}) => {
    const Request = async () => {
      // Update the global state
      if (timetables.length > 1) {
        console.log("Attempting to get next timetable.");
        const timetable_left = timetables.shift();
        setTimetables([...timetables, timetable_left]);
      }
    };
  
    return (
      <div>
        <button
          onClick={event => Request()}
          className="btn btn-primary mt-2"
        >NEXT</button>
      </div>
    )
  }
  
  // -- Exports --
  export default NextButton;
  