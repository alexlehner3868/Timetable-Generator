import logo from './logo.svg';
import './App.css';
import calculatorAPI from './calculatorAPI';
import Calculator from './Calculator';
import ScheduleButton from './ScheduleButton';
import Timetable from './Timetable';
import Sidebar from './Sidebar';
import MainWindow from './MainWindow';
/*
function App() {
  return (
    <div className="App">
      <header className="App-header">
       <Calculator calculatorAPI={new calculatorAPI('http://localhost:3000')}/>
      </header>
    </div>
  );
}
*/
// TODO: Get course data with class names
// TODO: Properly space timetable and sidebar so they're on left and right side
// TODO: When searching for a class, each result should be a button
// TODO: Clicking on Class button shows LEC/TUT/PRA Info 
// TODO: Clicking on Class button shows Add Course button
// TODO: Section to display classes already added to the plan
// TODO: Button to show only fall schedule
// TODO: Button to show only winter schedule
// TODO: Button to show both schedules
function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>Live Timetable Love</h1>
      </header>
      <div className='whole-webpage'>
        <MainWindow className="main-window"/>
        <Sidebar className="search-bar"/>
      </div>
    </div>
  );
}

export default App;
