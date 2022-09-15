import logo from './logo.svg';
import './App.css';
import calculatorAPI from './calculatorAPI';
import Calculator from './Calculator';
import ScheduleButton from './ScheduleButton';
import Timetable from './Timetable';

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

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <Timetable/>
      </header>
    </div>
  );
}
export default App;
