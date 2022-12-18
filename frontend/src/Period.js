import React from "react";

var colorArray = ['#e0e0e0', '#ffb0b0', '#b8ffc2', '#b8fdff', '#9eb5ff', 
		  '#d2b0ff', '#ffd17d', '#fffd9c', '#F4BFBF', '#FFD9C0', '#FAF0D7', '#8CC0DE', '#68A7AD', '#99C4C8', '#E5CB9F'];

const Period = (props) => {
    const classData = new Array(4);

    classData[0] = (props.ClassID === "" ? null : props.ClassID);
    classData[1] = (props.classSection === "" ? null : props.classSection);
    classData[2] = props.classColorIdx === "" ? colorArray[0] : colorArray[props.classColorIdx];
    classData[3] = (props.classType === "" ? null : props.classType);
    classData[4] = props.className === "" ? null : props.className;
    //console.log(classData[0]) 

    return (
        <div style ={{
            backgroundColor: classData[2],
        }}>
             <p className = "class-id">{classData[0]}</p>
            <p className="class-name">{classData[4]} </p>
            <p className = "class-section">{classData[3]} {classData[1]}</p>
           
        </div>
    )
}

export default Period;