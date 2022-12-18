import Semester from './Semester';

const MainWindow = (props) =>{

    const both = new Array(2);
    let message = (props.resultMessage === ""  ? "UofT's Best Timetable Creater Tool!" : props.resultMessage)
    return (
        <div className='main-window'>
            <div className='tr'>
                <div className='td' id='semester_block'><Semester timetable={props.timetableData} semester="Fall"/></div>
                <div className='td' id='semester_block'><Semester timetable={props.timetableData} semester="Winter"/></div>
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
