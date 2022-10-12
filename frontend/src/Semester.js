import Timetable from "./Timetable"

const Semester = (props) =>{
    
    return (
        <div className='semester'>
            <label className='semester-label'>{props.semester}</label>
            <Timetable courses={props.timetable}/>
        </div>
    )
}

export default Semester
