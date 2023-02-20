// -- Module --
const NextButtonT = ({nTimetables, ttbIndex, setTtbIndex}) => {
  const Next = async () => {
    
  };

  return (
    <div className="next-button">
      <button
        onClick={event => Next()}
        id="button_image">
          <img id="down-btn" className="up_down-button-img" src="https://i.postimg.cc/K1h37QtD/down.png" alt="532" border="0"/>
        </button>
    </div>
  )
}

// -- Exports --
export default NextButtonT;