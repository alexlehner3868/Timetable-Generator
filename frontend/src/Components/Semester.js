// -- Components --
import Timetable from "./Timetable"

// -- Module --
const Semester = ({timetable, when}) =>{
  return (
    <div className='semester'>
      <Timetable timetable={timetable} when={when}/>
    </div>
  )
}

// -- Exports --
export default Semester;
