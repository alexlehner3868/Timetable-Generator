// -- Module --
const BackButtonT = ({nTimetables, ttbIndex, setTtbIndex}) => {
    const Back = async () => {
      
    };
  
    return (
      <div className="back-button">
        <button
          onClick={event => Back()}
          id="button_image">
              <img id="up-btn" className="up_down-button-img" src="https://i.postimg.cc/mtCtrMKz/up.png" alt="532" border="0"/>
        </button>
      </div>
    )
  }
  
  // -- Exports --
  export default BackButtonT;
  