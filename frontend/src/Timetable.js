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
    const num_days  = 5;
    const num_hours = 11;
    const timetable = new Array(num_hours); 
    let count = 0;
    for(let i = 0; i < timetable.length; i++){
        timetable[i] = new Array(num_days).fill(null); 
        
    }
    
    if(props.courses !== undefined){
        for(let i = 0; i < num_hours; i++){
            for(let j = 0; j < num_days; j++){
                    timetable[i][j] = (props.courses[count] !== undefined ? props.courses[count] : {
                        classID: "",
                        classSection: "",
                        classColorIdx: "",
                        classType: "",
                        className: "",
                    });
                    if(count %2 === 0){
                        timetable[i][j] = {
                            classID: "ALX3838",
                            classSection: "03",
                            classColorIdx: (i*j)%15,
                            classType: "LEC", 
                            className: "Intro to Alex-ology"
                        }
                    }
                    count++;
                
            }
        }
    }else{
        for(let i = 0; i < num_hours; i++){
            for(let j = 0; j < num_days; j++){
                timetable[i][j] = {
                    classID: "",
                    classSection: "",
                    classColorIdx: "",
                    classType: "",
                    className: "",
                };
                count++;
            }
        }
    }
  /*
    timetable.map((row)=>{
        row.map((col)=>{
            console.log(col)
        })
    });
*/
    let time = 9;
    return (
        <div className="timetable"> 
        <div className="tr">
            <div className="td" id='legend-times'> </div>
            <div className="td">Monday</div>
            <div className="td">Tuesday</div>
            <div className="td">Wednesday</div>
            <div className="td">Thursday</div>
            <div className="td">Friday</div>
        </div>
        {timetable.map((row)=>{
            return (
                <div className ='tr' id="table_day">
                    <div className="td" id="legend-times"> {time <= 12 ? time++ +'AM': time++-12 + 'PM'}</div>
                {    
                    
                    row.map((col)=> (
                            <div className='td' id="table_hour">
                            <Period ClassID={col.classID} classSection={col.classSection} classColorIdx={col.classColorIdx} classType={col.classType} className={col.className}/>
                            </div>
                    ))
                  
                }
             
              </div> 
            )
        })} 
        </div>
    )

}

export default Timetable;
