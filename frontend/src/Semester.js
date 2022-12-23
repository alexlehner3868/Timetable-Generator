import Timetable from "./Timetable"

const Semester = (props) =>{

    return (
        <div className='semester'>
            <Timetable courses={props.timetable}/>
        </div>
    )
}

export default Semester
