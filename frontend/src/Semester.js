import Timetable from "./Timetable"

const Semester = (props) =>{
    
    return (
        <div className='semester'>
            <label className='semester-label'>{props.semester}</label>
            <Timetable props={props.timetable}/>
        </div>
    )
}

export default Semester
