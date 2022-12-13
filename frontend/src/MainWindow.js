import Semester from './Semester';
import Timetable from './Timetable';


const MainWindow = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='main-window'>
            <div className='tr'>
                <div className='td'><Semester timetable={props.timetableData} semester="Fall"/></div>
                <div className='td'><Semester timetable={props.timetableData} semester="Winter"/></div>
            </div>
            <div className='tr' >
                <div className='td' id='resultMessage'>
                    <span>{props.resultMessage}</span>
                </div>
            </div>
           
        </div>
    
    )


}

export default MainWindow
