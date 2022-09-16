import React from "react";

const SearchButton = (props) =>{

    return (
    <input 
        type='button'
        value={props.caption}
        className = {props.caption == "Search" ? "search-button" : null}
        onClick = {props.onClick}/>
    );
}
        

export default SearchButton;
