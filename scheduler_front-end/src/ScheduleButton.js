import React from 'react'

function ScheduleButton(props){
    return (
        <input 
            type='button' 
            value= 'Schedule'
            className = {props.caption == "=" ? "calculator-equal-button" : null}
            onClick = {props.onClick}/>
    );
}

export default ScheduleButton;