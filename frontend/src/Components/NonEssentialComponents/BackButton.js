// -- Module --
const BackButton = ({nTimetables, ttbIndex, setTtbIndex}) => {
  const Back = async () => {
    setTtbIndex((nTimetables + ttbIndex - 1) % nTimetables)
  };

  return (
    <div className="back-button">
      <button
        onClick={event => Back()}
        id="button_image">
            <img id="up-btn" className="up_down-button-img" src="https://i.ibb.co/jTycPTf/Up-Arrow.png" alt="532" border="0"/>
      </button>
    </div>
  )
}

// -- Exports --
export default BackButton;
