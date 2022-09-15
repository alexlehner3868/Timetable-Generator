import logo from './logo.svg';
import './App.css';
import calculatorAPI from './calculatorAPI';
import Calculator from './Calculator';


function App() {
  return (
    <div className="App">
      <header className="App-header">
       <Calculator calculatorAPI={new calculatorAPI('http://localhost:3000')}/>
      </header>
    </div>
  );
}

export default App;
