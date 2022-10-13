import React from "react";

var colorArray = ['#e0e0e0', '#ffb0b0', '#b8ffc2', '#b8fdff', '#9eb5ff', 
		  '#d2b0ff', '#ffd17d', '#fffd9c'];

const Period = (props) => {
    const classData = new Array(2);
    
    classData[0] = (props.ClassID === "" ? null : props.ClassID);
    classData[1] = (props.classSection === "" ? null : props.classSection);
    classData[2] = props.classNum === "" ? colorArray[0] : colorArray[props.classNum];
    console.log("In period: " + classData[0]+ " "+ props.classSection + " " + classData[2]);
    return (
        <div className="empty-period" style ={{
            backgroundColor: classData[2],
        }}>
            <p className="class-name">{classData[0]}</p>
            <p className="class-id"> {classData[1]}</p>

        </div>
    )
}

export default Period;