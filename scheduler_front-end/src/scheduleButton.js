import React from 'react'

function ScheduleButton(props){
    return (
        <input 
            type='button' 
            value= {props.caption}
            className = {props.caption == "=" ? "calculator-equal-button" : null}
            onClick = {props.onClick}/>
    );
}

export default ScheduleButton;