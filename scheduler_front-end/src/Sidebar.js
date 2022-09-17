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
        <div className="sidebar">
            
            <input type="text" placeholder="Search For Class" class="search-bar" onChange={event => setQuery(event.target.value)}/> 
            <div className="search-bar">
                <i class="fa fa-user fa-lg"></i>
            </div>
            
            <div className="search-results-box">
            {
                
            //{class_result.ACAD_ACT_CD}
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
                        
                        <button type="button" className="add-course-button" id="add-course-button">
                            

                            <div> 
                            <svg className="icon" xmlns="http://www.w3.org/2000/svg" width="24" height="24" 
                            viewBox="0 0 24 24"><path d="M12 0c-6.627 0-12 5.373-12 
                            12s5.373 12 12 12 12-5.373 12-12-5.373-12-12-12zm6 
                            13h-5v5h-2v-5h-5v-2h5v-5h2v5h5v2z"/></svg>
                            </div>
                            <span className="course-code"> {class_result.ACAD_ACT_CD} </span> <br></br>
                            <span className="course-name">  this is a course </span>
                            
                        </button>
                            
                        
                    </div>
            
            ))
            }
            
            </div>
            
        </div>
        
      

    )
} 


export default Sidebar;
//SVG PLUS SIGN ICON FROM: 
//https://iconmonstr.com/plus-2-svg/
