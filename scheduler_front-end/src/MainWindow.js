import Semester from './data/Semester';
import Timetable from './Timetable';

const MainWindow = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='main-window'>
            <Semester semester="Fall"/>
            <Semester semester="Winter"/>
        </div>
    
    
    )


}

export default MainWindow
