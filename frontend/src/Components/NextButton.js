// -- Module --
const NextButton = ({timetables, setTimetables}) => {
    const Request = async () => {
      // Update the global state
      if (timetables.length != 0) {
        console.log(timetables);
        console.log("Attempting to get next timetable.");
        const timetable_left = timetables.shift();
        setTimetables([]);
        setTimetables([...timetables, timetable_left]);
        console.log(timetables);
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
  