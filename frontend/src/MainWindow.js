import Semester from './Semester';
import Timetable from './Timetable';


const MainWindow = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='main-window'>
            <Semester props={props} semester="Fall"/>
            <Semester props={props} semester="Winter"/>
        </div>
    
    
    )


}

export default MainWindow
