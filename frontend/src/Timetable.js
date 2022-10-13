import React from "react";
import Period from "./Period";

//TODO:
// Currently only printing for one semester. Need to do both semesters. 
// Decide how to view the 2 semesters
const Timetable = (props) =>{
     
    /*
    const timetable = new Array(11); 
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(6).fill(null); 
    }
*/
//Testing timetable
    const timetable = new Array(2); 
    let count = 0;
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(2).fill(null); 
        
    }

    for(let i = 0; i < 2; i++){
        for(let j = 0; j < 2; j++){
            timetable[i][j] = (props.courses[count] !== undefined ? props.courses[count] : {
                classID: "",
                classSection: "",
                classNum: ""
            });
            console.log("tdata at" + count);
            console.log(timetable[i][j]);
            count++;
        }
    }
    console.log("props in timetable")
    console.log(props.courses);

  
    return (
        <div className="timetable"> 
        {timetable.map((row)=>{
            return (
                <div>
                {    
                    row.map((col)=> <Period  ClassID={col.classID} classSection={col.classSection} classNum={col.classNum}/>)
                }
                </div>
                
            )

        })}
        </div>

    )
    
}

export default Timetable;
