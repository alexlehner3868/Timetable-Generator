import React from "react";
import SearchButton from "./SearchButton";
import Data from "./data/courses.json";

import {useState} from "react";

const Sidebar = (props) =>{
    // for search bar
    const [query, setQuery] = useState("")

    // make sidebar for seaching classes, adding and removing
    
    // two main sections of sidebar: 
    // the buttons on top, and the bottom 'display' section
    const sidebar = new Array(2);
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
  // place sidebar and {class_button} in here below
  return (
        <div class_name="search-bar"> 
            <input placeholder="Search For Class" onChange={event => setQuery(event.target.value)} />
            {
                
               
               Data.filter( class_result => {
                if (query === "") {
                    //nothing in the search bar, don't show anything
                    //return class_result;
                } else if (class_result.ACAD_ACT_CD.toLowerCase().includes(query.toLowerCase())) {
                    //returns array with all matches
                    return class_result;
                } // TODO: add searching by class name here once we add class-Name to the database
             }).map((class_result, index) => (
                    <div className="search-results" key={index}>
                        <p>Course code:{class_result.ACAD_ACT_CD}</p>
                    </div>
        
               ))
            }
           </div>
        
      

    )
} 


export default Sidebar;
