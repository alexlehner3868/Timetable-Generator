import Semester from './Semester';
import Timetable from './Timetable';


const MainWindow = (props) =>{

    const both = new Array(2);
    console.log("IN main window")
    console.log(props.timetableData)
    return (
        <div className='main-window'>
            <Semester timetable={props.timetableData} semester="Fall"/>
            <Semester timetable={props.timetableData} semester="Winter"/>
        </div>
    
    
    )


}

export default MainWindow
