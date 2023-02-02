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
       Contstaint Priority Levels (in increasing order):
        <br/>
        <ul>
            <li>Must Have: Highest priority, <u>MUST</u> be satisfied in each constraint</li>
            <li>Good to Have: Medium priority </li>
            <li>Nice to Have: Lowest priority</li>
            <li>No Priority: No preference, dont take it into account</li>
          </ul>
        <br/>
        <b>Notes:</b>
        <br/>
        <li>Times are displayed in a 24 hour clock (ie military time)</li>
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default ConstraintExplinations;
  