// -- React --
import React from "react";

// -- Module --
const Message = ({message}) => {
   const msg = (message == null || message == "" ? "Timetable generation status will show here..." : message)

    return (
        <div className="resultMessage" id="resultMessage">
        <p>{msg}</p>
        </div>
    )
}

// -- Exports --
export default Message;
