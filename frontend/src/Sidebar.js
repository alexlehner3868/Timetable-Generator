// -- React --
import React from 'react';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';

// -- Components --
import SearchBar from './Components/SearchBar';
import AddConstraintButton from './Components/NonEssentialComponents/AddConstraintButton.js';
import ActiveCourseList from './Components/ActiveCourseList';
import ConstraintExplinations from './Components/NonEssentialComponents/ConstraintExplinations';
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
          <ConstraintExplinations/>
        </TabPanel>

      </Tabs>
      </div>
    );
  }
}

// -- Exports --
export default Sidebar;
/*
   <div>
          {[...this.props.courses].map((course)=>(
            <p id='active-course-list'>{course}</p>
          ))}
         </div>
         */
