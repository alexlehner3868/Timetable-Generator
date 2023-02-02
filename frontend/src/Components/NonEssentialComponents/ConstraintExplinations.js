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
        <ul>1. Not Active (shown as blank)</ul>
        <ul>2. Nice to Have</ul>
        <ul>3. Good to Have</ul>
        <ul>4. Must Have </ul>

        <br/>
        <b>Notes:</b>
        <br/>
        <li>Must Have constraints <u>MUST</u> be satisfied by every timetable created</li>
        <li>Times are displayed in a 24 hour clock (ie military time)</li>
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default ConstraintExplinations;
  