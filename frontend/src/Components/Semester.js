// -- Components --
import Timetable from "./Timetable"

// -- Module --
const Semester = (props) =>{
  return (
    <div className='semester'>
      <Timetable timetable={props.timetable} when={props.when} constraints={props.constraints} setConstraints={props.setConstraints}/>
    </div>
  )
}

// -- Exports --
export default Semester;
