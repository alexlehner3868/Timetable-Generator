// -- Module --
const BackButton = ({nTimetables, ttbIndex, setTtbIndex}) => {
  const Back = async () => {
    setTtbIndex((nTimetables + ttbIndex - 1) % nTimetables)
  };

  return (
    <div>
      <button
        onClick={event => Back()}
        className="btn btn-primary mt-2"
      >BACK</button>
    </div>
  )
}

// -- Exports --
export default BackButton;
