import React from "react";
import SearchButton from "./SearchButton";

const Sidebar = (props) =>{
  

    // make sidebar for seaching classes, adding and removing
    
    // two main sections of sidebar: 
    // the buttons on top, and the bottom 'display' section
    const sidebar = new Array(1);
    const buttons = [
        {text: "Search", handler: () => props.searchForClass("0")},
        {text: "Add Class", handler: () => props.addClass("1")}    
    ]
    const class_button = buttons.map((value, index) => {
        return <SearchButton 
        caption={value.text}
        onClick={value.handler} />
    });
    // buttons
    //sidebar[0] = new Array(2).fill(null);
    // display
    //sidebar[1] = new Array(1).fill(null);  
  
  return (
        <div> 
        {class_button}
        </div>

    )
} 


export default Sidebar;
