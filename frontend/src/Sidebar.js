// -- React --
import React from 'react';
import { Tab, Tabs, TabList, TabPanel } from 'react-tabs';

// -- Components --
import SearchBar from './Components/SearchBar';

// -- Module --
class Sidebar extends React.Component {
  constructor() {
    super();
    this.state = { tabIndex: 0, message: ""};
  }

  render() {
    ;

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
          
        </TabPanel>
        <TabPanel>
          
        </TabPanel>
      </Tabs>
    );
  }
}

// -- Exports --
export default Sidebar;
