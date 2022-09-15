import React from "react";
import Period from "./Period";

const Timetable = () =>{
    const timetable = new Array(10);
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(5).fill(null);
    }

    return (
        <div> 
        {timetable.map((row)=>{
            return (
                <div>{
                    row.map(()=> <Period/>)
                }
                </div>
            )
        })}
        </div>
    )
}

export default Timetable;