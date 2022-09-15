import React from "react";


const Period = (props) => {
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