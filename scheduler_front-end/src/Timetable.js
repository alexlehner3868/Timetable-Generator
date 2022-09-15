import React from "react";
import Period from "./Period";

const Timetable = () =>{
    //make sidebar for seaching classes, adding and removing
    //const sidebar = new Array(2);
    //sidebar[0] = new Array(3).fill(null);
    //sidebar[1] = new Array(1).fill(null);

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