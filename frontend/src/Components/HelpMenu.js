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
        <div className="header">Instructions</div>
        <div className="content">
          {' '}
          Welcome to Live Timetable Love aka UofT's best timetable generator tool.
          <br/>
          <br/>We take in the courses that you want to take and any timing constraints you have 
          <br/>and can generator a set of possible timetables that meets your unique needs! 
          <br/><br/>
          <u>How it works:</u>
          <br/>
           Step 1: Use the search bar on the right panel to search for and add all the courses you want.
          <br/>
          Step 2: On the right panel, use the constraint tab to insert your preferences and constraints.
          <ul>
            <li>Must Have: Highest priority aka must be satisfied in each constraint</li>
            <li>Good to Have: Medium priority </li>
            <li>Nice to Have: Lowest priority</li>
            <li>No Priority: No preference aka dont take it into account</li>
          </ul>
          Step 3: Once all your classes and constraints are inserted, click the "generate" button
          <br />
          Step 4: The timetables will be shown on the two center tabs, use the arrows on the left panel to
          <br/>cycle through the options. They are ranked based on how well they satisfy your constraints 
          <br/> with 1 being the best  
          <br />
          Step 5: [Something here about dwnloading or saving blah] 
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default HelpMenu;
  