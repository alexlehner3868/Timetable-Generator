import React from 'react'

function ScheduleButton(props){
    return (
        <input 
            type='button' 
            value= {props.caption}/>
    );
}

export default ScheduleButton;