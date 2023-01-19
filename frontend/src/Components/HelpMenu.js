import React from 'react';
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';

// -- Module --
const HelpMenu = () => {

    return (
        <Popup className="help-menu"
    trigger={<button className="button">Help</button>}
    modal
    nested
  >
    {close => (
      <div className="modal">
        <button className="close" onClick={close}>
          &times;
        </button>
        <div className="header"> Live Timetable Love Help </div>
        <div className="content">
          {' '}
          Lorem ipsum dolor sit amet consectetur adipisicing elit. Atque, a nostrum.
          Dolorem, repellat quidem ut, minima sint vel eveniet quibusdam voluptates
          delectus doloremque, explicabo tempore dicta adipisci fugit amet dignissimos?
          <br />
          Lorem ipsum dolor sit amet, consectetur adipisicing elit. Consequatur sit
          commodi beatae optio voluptatum sed eius cumque, delectus saepe repudiandae
          explicabo nemo nam libero ad, doloribus, voluptas rem alias. Vitae?
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default HelpMenu;
  