// https://tailwindcss.com/docs/guides/create-react-app 
//use this to make pretty dropdowns 
//https://reactjsexample.com/a-pretty-cool-country-selector-using-tailwindcss-and-framer-motion/ 
import { AwesomeButton } from 'react-awesome-button';
import 'react-awesome-button/dist/styles.css';
// -- Module --
const ActiveCourseList = ({courses, setCourses}) => {

    
    const removeCourse = course => {
      console.log(`removing course: ${course}`)
      setCourses(prev => new Set([...prev].filter(x => x !== course)))
    };

    const removeAllCourses = course => {
      setCourses(prev => new Set())
    };

    function handleSubmitPrepopulate (event) {
      event.preventDefault();
      //get the index of courses we want
      const timetable_value = document.getElementById("prepopulate").value;
      //console.log(timetable_value)
      switch (parseInt(timetable_value)) {
        case 0:
          //no preset defined
          break;
        case 1:
          //1st year ECE
          removeAllCourses();
          //add all first year ece courses
          setCourses(prev => new Set(prev.add("APS100H1")))
          setCourses(prev => new Set(prev.add("APS111H1")))
          setCourses(prev => new Set(prev.add("CIV100H1")))
          setCourses(prev => new Set(prev.add("APS110H1")))
          setCourses(prev => new Set(prev.add("MAT188H1")))
          setCourses(prev => new Set(prev.add("MAT186H1")))
          
          setCourses(prev => new Set(prev.add("APS105H1")))
          setCourses(prev => new Set(prev.add("APS112H1")))
          setCourses(prev => new Set(prev.add("MIE100H1")))
          setCourses(prev => new Set(prev.add("ECE110H1")))
          //setCourses(prev => new Set(prev.add("ECE191H1")))
          setCourses(prev => new Set(prev.add("MAT187H1"))) 

          break;
        case 2:
          // 1st year EngSci
          removeAllCourses();
          setCourses(prev => new Set(prev.add("PHY180H1")))
          setCourses(prev => new Set(prev.add("ESC101H1")))
          setCourses(prev => new Set(prev.add("CIV102H1")))
          setCourses(prev => new Set(prev.add("ESC103H1")))
          setCourses(prev => new Set(prev.add("ESC180H1")))
          setCourses(prev => new Set(prev.add("ESC194H1")))
          
          setCourses(prev => new Set(prev.add("ESC102H1")))
          setCourses(prev => new Set(prev.add("MSE160H1")))
          setCourses(prev => new Set(prev.add("ESC195H1")))
          setCourses(prev => new Set(prev.add("MAT185H1")))
          setCourses(prev => new Set(prev.add("ECE159H1")))
          setCourses(prev => new Set(prev.add("ESC190H1")))
          break;
        case 3:
          // 2nd year CIV
          removeAllCourses();
          setCourses(prev => new Set(prev.add("CIV220H1")))
          setCourses(prev => new Set(prev.add("CIV235H1")))
          setCourses(prev => new Set(prev.add("CIV280H1")))
          setCourses(prev => new Set(prev.add("CME210H1")))
          setCourses(prev => new Set(prev.add("CME261H1")))
          setCourses(prev => new Set(prev.add("CME270H1")))
          
          setCourses(prev => new Set(prev.add("CIV209H1")))
          setCourses(prev => new Set(prev.add("CIV214H1")))
          setCourses(prev => new Set(prev.add("CIV250H1")))
          setCourses(prev => new Set(prev.add("CME259H1")))
          setCourses(prev => new Set(prev.add("CME263H1")))
          setCourses(prev => new Set(prev.add("CME262H1")))
          break;
        case 4:
          //2nd year ECE
          removeAllCourses();
          setCourses(prev => new Set(prev.add("ECE201H1")))
          setCourses(prev => new Set(prev.add("ECE212H1")))
          setCourses(prev => new Set(prev.add("ECE241H1")))
          setCourses(prev => new Set(prev.add("ECE244H1")))
          setCourses(prev => new Set(prev.add("MAT290H1")))
          setCourses(prev => new Set(prev.add("MAT291H1")))
          
          setCourses(prev => new Set(prev.add("ECE216H1")))
          setCourses(prev => new Set(prev.add("ECE221H1")))
          setCourses(prev => new Set(prev.add("ECE231H1")))
          setCourses(prev => new Set(prev.add("ECE243H1")))
          setCourses(prev => new Set(prev.add("ECE297H1")))
          break;
        case 5:
          //2nd Year EngSci
          removeAllCourses();
          setCourses(prev => new Set(prev.add("AER210H1")))
          setCourses(prev => new Set(prev.add("CHE260H1")))
          setCourses(prev => new Set(prev.add("ECE253H1")))
          setCourses(prev => new Set(prev.add("ESC203H1")))
          setCourses(prev => new Set(prev.add("MAT292H1")))
          setCourses(prev => new Set(prev.add("PHY293H1")))
          
          setCourses(prev => new Set(prev.add("BME205H1")))
          setCourses(prev => new Set(prev.add("ECE259H1")))
          setCourses(prev => new Set(prev.add("ECE286H1")))
          setCourses(prev => new Set(prev.add("ESC204H1")))
          setCourses(prev => new Set(prev.add("PHY294H1")))
          break;
        case 6:
          //2nd Year Chem
          removeAllCourses();
          setCourses(prev => new Set(prev.add("CHE204H1")))
          setCourses(prev => new Set(prev.add("CHE208H1")))
          setCourses(prev => new Set(prev.add("CHE211H1")))
          setCourses(prev => new Set(prev.add("CHE220H1")))
          setCourses(prev => new Set(prev.add("CHE221H1")))
          setCourses(prev => new Set(prev.add("CHE223H1")))
          
          setCourses(prev => new Set(prev.add("CHE205H1")))
          setCourses(prev => new Set(prev.add("CHE210H1")))
          setCourses(prev => new Set(prev.add("CHE213H1")))
          setCourses(prev => new Set(prev.add("CHE222H1")))
          setCourses(prev => new Set(prev.add("CHE249H1")))
          break;
        case 7:
          //2nd Year Mineral
          removeAllCourses();
          setCourses(prev => new Set(prev.add("CME210H1")))
          setCourses(prev => new Set(prev.add("CME261H1")))
          setCourses(prev => new Set(prev.add("CME270H1")))
          setCourses(prev => new Set(prev.add("ESS262H1")))
          setCourses(prev => new Set(prev.add("MIN201H1")))
          setCourses(prev => new Set(prev.add("MSE202H1")))
          
          setCourses(prev => new Set(prev.add("CME259H1")))
          setCourses(prev => new Set(prev.add("CME262H1")))
          setCourses(prev => new Set(prev.add("CME263H1")))
          setCourses(prev => new Set(prev.add("ESS224H1")))
          setCourses(prev => new Set(prev.add("MIN250H1")))
          break;
        case 8:
          //2nd Year Material
          removeAllCourses();
          setCourses(prev => new Set(prev.add("MAT294H1")))
          setCourses(prev => new Set(prev.add("MSE202H1")))
          setCourses(prev => new Set(prev.add("MSE219H1")))
          setCourses(prev => new Set(prev.add("MSE244H1")))
          setCourses(prev => new Set(prev.add("MSE294H1")))
          setCourses(prev => new Set(prev.add("MSE296H1")))
          
          setCourses(prev => new Set(prev.add("MSE217H1")))
          setCourses(prev => new Set(prev.add("MSE218H1")))
          setCourses(prev => new Set(prev.add("MSE222H1")))
          setCourses(prev => new Set(prev.add("MSE238H1")))
          setCourses(prev => new Set(prev.add("MSE245H1")))
          setCourses(prev => new Set(prev.add("MSE295H1")))
          break;
        case 9:
          //2nd Year Mech
          removeAllCourses();
          setCourses(prev => new Set(prev.add("MIE230H1")))
          setCourses(prev => new Set(prev.add("MIE231H1")))
          setCourses(prev => new Set(prev.add("MIE243H1")))
          setCourses(prev => new Set(prev.add("MIE270H1")))
          
          setCourses(prev => new Set(prev.add("MAT234H1")))
          setCourses(prev => new Set(prev.add("MIE210H1")))
          setCourses(prev => new Set(prev.add("MIE221H1")))
          setCourses(prev => new Set(prev.add("MIE222H1")))
          break;
        default:
          break;

      }

    } 
    return (
      <div className = "active-courses" id="active-courses">
        
         <h4 id='course-list-header'> <u>Desired Classes:</u></h4>
         <div className="all-courses">
         {[...courses].map((course, index)=>(
            <div className="active-course-list" >
              
            <p id='active-course-list-text'>{course}</p>
            <button id='active-course-remove'onClick={event => removeCourse(course)} >X</button>
            </div>
            
          ))}</div>
        <AwesomeButton onPress={event => removeAllCourses()}>Clear All</AwesomeButton>
        <select list="prepopulate" class="dropdown" id="prepopulate" onChange = {handleSubmitPrepopulate}>
                <option value="0">Pick a Preset Schedule:</option>
                <option class="ece_1" value="1" >1st Year ECE/TrackOne</option>
                <option class="esci_1" value="2">1st Year EngSci</option>
                <option class="civ_2" value="3">2nd Year CIV</option>
                <option class="ece2" value="4">2nd Year ECE</option>
                <option class="esci_2" value ="5">2nd Year EngSci</option>
                <option class="chem2" value="6">2nd Year Chem</option>
                <option class="min2" value="7">2nd Year Mineral</option>
                <option class="mat2" value="8">2nd Year Materials</option>
                <option class="mech2" value="9">2nd Year Mech</option>
            </select> <br></br>
            
      </div>
    )
  }
  
  // -- Exports --
  export default ActiveCourseList;
  