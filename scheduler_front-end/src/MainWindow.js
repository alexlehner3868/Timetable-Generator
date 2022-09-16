import Timetable from './Timetable';

const MainWindow = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='main-window'>
            <Timetable/>
            <Timetable/>
        </div>
    
    
    )


}

export default MainWindow
