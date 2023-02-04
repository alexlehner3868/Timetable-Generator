// -- React --
import React from 'react';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';

// -- Components --
import Semester from './Components/Semester';



// -- Module --
class MainWindow extends React.Component {
  constructor() {
    super();
    this.state = { tabIndex: 0, message: ""};
  }

 
  render() {

    const fall = {
      day: { begin: 0, end: 5},
      hour: { begin: 9, end: 21},
    };
    const winter = {
      day: { begin: 5, end: 10},
      hour: { begin: 9, end: 21},
    };
    /* Attempeed to preset which tab was open 
    let fall_count = 0;
    let winter_count = 0; 
    */
    // Extract the timetable to show
    const timetable = (this.props.timetables.length) ? this.props.timetables[this.props.ttbIndex] : [];
    /*Attempeed to preset which tab was open 
    for (const meet of timetable){
      if(meet.day < 6){
        fall_count++;
      }else if( meet.day < 10){
        winter_count++;
      }
    }
    // TODO -> change tab based on semester count
    */
    return (
      <div className='main-window'>
        
      <Tabs selectedIndex={this.state.tabIndex} onSelect={tabIndex => this.setState({ tabIndex })}>
        <TabList>
          <Tab><b>Fall</b></Tab>
          <Tab><b>Winter</b></Tab>
        </TabList>
        <TabPanel>
          <Semester timetable={timetable} when={fall}/>
        </TabPanel>
        <TabPanel>
          <Semester timetable={timetable} when={winter}/>
        </TabPanel>
      </Tabs>
      </div>
    );
  }
}

// -- Exports --
export default MainWindow;
