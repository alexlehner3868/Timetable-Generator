import React from "react";

var colorArray = ['#e0e0e0', '#ffb0b0', '#b8ffc2', '#b8fdff', '#9eb5ff', 
		  '#d2b0ff', '#ffd17d', '#fffd9c'];

const Period = (props) => {
    const classData = new Array(3);
    
    classData[0] = (props.ClassID === "" ? null : props.ClassID);
    classData[1] = (props.classSection === "" ? null : props.classSection);
    classData[2] = props.classColorIdx === "" ? colorArray[0] : colorArray[props.classColorIdx];
    classData[3] = (props.classType === "" ? null : props.classType);
    return (
        <div className="empty-period" style ={{
            backgroundColor: classData[2],
        }}>
            <p className="class-name">{classData[0]}</p>
            <p className="class-id"> {classData[1]}</p>
            <p className = "class-id">{classData[3]}</p>

        </div>
    )
}

export default Period;