
import Sidebar from './Sidebar';
import MainWindow from './MainWindow';

const Both = (props) =>{

    const both = new Array(2);
    
    return (
        <div className='whole-webpage'>
            <MainWindow/>
            <Sidebar/>
        </div>
    
    
    )


}

export default Both
