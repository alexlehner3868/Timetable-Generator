import React from "react";


const Period = (props) => {
    // Props should give us classID (ECE421), SectionID (Lec01) and it should give us a classCountIdx (1),which will let us
    //change the color of the period based on a color array
    // TODO:
    // Work out how to pass input
    const classData = new Array(2);
    classData[0] = (props.ClassID === "" ? null : props.ClassID);
    classData[1] = (props.SecionID === "" ? null : props.SecionID);
    return (
        <div className="empty-period" >
            <text className="class-name">Class Name</text>
            <text className="class-id"> ClassId</text>
        </div>
    )
}

export default Period;