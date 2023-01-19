import React from 'react';
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';

// -- Module --
const HelpMenu = () => {
    return (
        <Popup className="help-menu"
    trigger={<button id="button_image">
        <img className="help-image" src="https://i.ibb.co/D4PDG3V/Screenshot-2023-01-18-at-10-36-50-PM.png" alt="532" border="0"/>
    </button>}
    modal
    nested
  >
    {close => (
      <div className="modal">
        <button className="close" onClick={close}>
          &times;
        </button>
        <div className="header"> How It Works  </div>
        <div className="content">
          {' '}
          1. Use the panel on left to insert 
          <br/>
          2. 

          <br />
          3. 
          <br />
          4. 
          <br />
          5. 
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default HelpMenu;
  