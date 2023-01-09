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

    // Extract the timetable to show
    const timetable = (this.props.timetables.length) ? this.props.timetables[this.props.ttbIndex] : [];

    return (
      <Tabs selectedIndex={this.state.tabIndex} onSelect={tabIndex => this.setState({ tabIndex })}>
        <TabList>
          <Tab>Fall</Tab>
          <Tab>Winter</Tab>
        </TabList>
        <TabPanel>
          <Semester timetable={timetable} when={fall}/>
        </TabPanel>
        <TabPanel>
          <Semester timetable={timetable} when={winter}/>
        </TabPanel>
      </Tabs>
    );
  }
}

// -- Exports --
export default MainWindow;
