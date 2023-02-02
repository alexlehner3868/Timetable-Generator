import React from 'react';
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';

// -- Module --
const ConstraintExplinations = () => {
    return (
        <Popup className="help-menu"
    trigger={<button id="button_image">
        <img className="constraint-help-image" src="https://i.postimg.cc/2bM57dn7/Screenshot-2023-02-01-at-4-22-01-PM.png" alt="532" border="0"/>
    </button>}
    modal
    nested
  >
    {close => (
      <div className="modal">
        <button className="close" onClick={close}>
          &times;
        </button>
        <div className="header">Constraints Priorities</div>
        <div className="content">
          {' '}
        Here are the prioritiy levels in increasing order: 
        <br/><br/>
        <li>Not Active (shown as blank) → I have no preference to this, ignore it</li>
        <li>Nice to Have</li>
        <li>Good to Have</li>
        <li>Must Have → This MUST be satisfied in my timetable</li>
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default ConstraintExplinations;
  