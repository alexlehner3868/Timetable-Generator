import Semester from './Semester';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';
import { resetIdCounter } from 'react-tabs';
import React from 'react';


class MainWindow extends React.Component {
    constructor() {
        super();
        this.state = { tabIndex: 0, message: ""};
      }
    
      //message =  setState(message = (this.props.resultMessage === ""  ? "UofT's Best Timetable Creater Tool!" : this.props.resultMessage))

      render() {
        return (
          <Tabs selectedIndex={this.state.tabIndex} onSelect={tabIndex => this.setState({ tabIndex })}>
            <TabList>
              <Tab>Fall</Tab>
              <Tab>Winter</Tab>
            </TabList>
            <TabPanel><Semester timetable={this.props.timetableData} /></TabPanel>
            <TabPanel><Semester timetable={this.props.timetableData} /></TabPanel>
          </Tabs>
        );
      }
}   

export default MainWindow
