import Semester from './Semester';
import Timetable from './Timetable';


const MainWindow = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='main-window'>
            <Semester timetable={props} semester="Fall"/>
            <Semester timetable={props} semester="Winter"/>
        </div>
    
    
    )


}

export default MainWindow
