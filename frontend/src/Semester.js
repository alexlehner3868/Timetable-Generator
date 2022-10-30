import Timetable from "./Timetable"

const Semester = (props) =>{
    console.log("in semester");
    return (
        <div className='semester'>
            <label className='semester-label'>{props.semester}</label>
            <Timetable courses={props.timetable}/>
        </div>
    )
}

export default Semester
