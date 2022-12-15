import Semester from './Semester';
import Timetable from './Timetable';


const MainWindow = (props) =>{

    const both = new Array(2);
    console.log("Result message:", props.resultMessage)
    let message = (props.resultMessage === ""  ? "UofT's Best Timetable Creater Tool!" : props.resultMessage)
    return (
        <div className='main-window'>
            <div className='tr'>
                <div className='td'><Semester timetable={props.timetableData} semester="Fall"/></div>
                <div className='td'><Semester timetable={props.timetableData} semester="Winter"/></div>
            </div>
            <div className='tr' >
                <div className='td' id='resultMessage'>
                    <span>{message}</span>
                </div>
            </div>
           
        </div>
    
    )


}

export default MainWindow
