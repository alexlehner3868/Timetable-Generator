// -- React --
import React from 'react';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';

// -- Components --
import SearchBar from './Components/SearchBar';
import AddConstraintButton from './Components/NonEssentialComponents/AddConstraintButton.js';
import AddConstraintServiceAPI from './Components/NonEssentialServices/AddConstraintService.js';

// -- Module --
class Sidebar extends React.Component {
  constructor() {
    super();
    this.state = { tabIndex: 0, message: ""};
  }

  render() {
    ;
    
    
  
 //likely temporary while we introduce constraints connections
  
    return (
      <Tabs selectedIndex={this.state.tabIndex} onSelect={tabIndex => this.setState({ tabIndex })}>
        <TabList>
          <Tab>Search</Tab>
          <Tab>Constraints</Tab>
          <Tab>Classes</Tab>
        </TabList>
        <TabPanel>
          <SearchBar courses={this.props.courses} setCourses={this.props.setCourses}/>
        </TabPanel>
        <TabPanel>
          <AddConstraintButton action="{{ url_for('add-constraint') }}" method="post" addedConstraint={this.props.addedConstraint} />
        </TabPanel>
        <TabPanel>
          
        </TabPanel>
      </Tabs>
    );
  }
}

// -- Exports --
export default Sidebar;
