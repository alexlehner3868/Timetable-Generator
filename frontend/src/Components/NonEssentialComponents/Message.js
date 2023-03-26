// -- React --
import React from "react";

// -- Module --
const Message = ({message}) => {
   const msg = (message == null || message == "" ? "Add courses and constraints to generate timetables" : message)

    return (
        <div className="resultMessage" id="resultMessage">
        <p>{msg}</p>
        </div>
    )
}

// -- Exports --
export default Message;
