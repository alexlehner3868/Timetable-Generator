import React from 'react';
import Popup from 'reactjs-popup';
import 'reactjs-popup/dist/index.css';

// -- Module --
const HelpMenu = () => {
    return (
        <Popup className="help-menu"
    trigger={<button id="button_image">
        <img className="help-image" src="https://i.postimg.cc/w74ggBjy/Untitled.png" alt="532" border="0"/>
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
          <b><u>How it works:</u></b>
          <br/>
           <b>Step 1: </b>Use the search bar on the right panel to search for and add all the courses you want.
          <br/>
          <b>Step 2: </b> On the right panel, use the constraint tab to insert your preferences and constraints.
          <ul>
            <li>Must Have: Highest priority aka must be satisfied in each constraint</li>
            <li>Good to Have: Medium priority </li>
            <li>Nice to Have: Lowest priority</li>
            <li>No Priority: No preference aka dont take it into account</li>
          </ul>
          <ul>
            <li>Tip 1: Enter time in using a 24-hour clock</li>
            <li>Tip 2: Click on the timetable to block off a certain hour </li>
          </ul>
          <b>Step 3: </b> Once all your classes and constraints are inserted, click the "Generate Timetable" button
          <br />
          <b>Step 4: </b> The timetables will be shown on the two center tabs, use the arrows on the left panel to
          <br/>cycle through the options. They are ranked based on how well they satisfy your constraints 
          <br/> with 1 being the best  

          <br/>
          <hr/>
          <u><b>Special Mentions:</b></u><br/>
          This project is dedicated to Professor Hans Kunov with special thanks to Professor Micah Stickel for his continued support and guidance throughout this project! 
        </div>
      </div>
    )}
  </Popup>
    )
  }
  
// -- Exports --
export default HelpMenu;
  