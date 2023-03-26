// -- React --
import React from 'react';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';

// -- Components --
import SearchBar from './Components/SearchBar';
import AddConstraintButton from './Components/NonEssentialComponents/AddConstraintButton.js';
import ActiveCourseList from './Components/ActiveCourseList';
import ConstraintExplinations from './Components/NonEssentialComponents/ConstraintExplinations';
import ControlButtons from './Components/NonEssentialComponents/ControlButtons';
// -- Module --
class Sidebar extends React.Component {
  constructor() {
    super();
    this.state = { tabIndex: 0, message: "", t: 0};
  }
  render() {
    // NOTE: likely temporary while we introduce constraints connections

    return (
      <div className='sidebar'>
      <Tabs selectedIndex={this.state.tabIndex} onSelect={tabIndex => this.setState({ tabIndex })}>
        <TabList>
          <Tab>Classes</Tab>
          <Tab>Constraints</Tab>
        </TabList>
        <TabPanel >
          <SearchBar courses={this.props.courses} setCourses={this.props.setCourses}/>
          <ActiveCourseList courses={this.props.courses} setCourses={this.props.setCourses}/>
        </TabPanel>
        <TabPanel>
          <AddConstraintButton constraints={this.props.constraints} setConstraints={this.props.setConstraints}/>
          <p>Tip 1: Input all times using a 24-hour clock (ie military time)</p>
          <p>Tip 2: To block off time, click on the timetable </p>
          <ConstraintExplinations/>
        </TabPanel>

      </Tabs>
      <ControlButtons courses={this.props.courses} constraints={this.props.constraints} setTimetables={this.props.setTimetables} setTtbIndex={this.props.setTtbIndex} num_timetables={this.props.num_timetables} setCourses={this.props.setCourses} setConstraints={this.props.setConstraints} setNumTimetables={this.props.setNumTimetables}/>
      </div>
    );
  }
}

// -- Exports --
export default Sidebar;

