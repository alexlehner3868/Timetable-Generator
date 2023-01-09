// -- Module --
const NextButton = ({nTimetables, ttbIndex, setTtbIndex}) => {
  const Next = async () => {
    setTtbIndex((ttbIndex + 1) % nTimetables)
  };

  return (
    <div>
      <button
        onClick={event => Next()}
        className="btn btn-primary mt-2"
      >NEXT</button>
    </div>
  )
}

// -- Exports --
export default NextButton;
