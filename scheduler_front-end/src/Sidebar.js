import React from "react";

const Sidebar = (props) =>{
  

    // make sidebar for seaching classes, adding and removing
    
    // two main sections of sidebar: 
    // the buttons on top, and the bottom 'display' section
    const sidebar = new Array(2);
    // buttons
    sidebar[0] = new Array(2).fill(null);
    // display
    sidebar[1] = new Array(1).fill(null);  
  
  return (
        <div> 
        {sidebar.map((row)=>{
            return (
                <div>{
                
                    row.map(()=> <Period  ClassID={props.classID} classSection={props.classSection} classNum={props.classNum}/>)
                    
                }
                </div>
            )
        })}
        </div>

    )
} 


export default Sidebar;
