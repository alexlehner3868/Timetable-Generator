import React from "react";

const SearchButton = (props) =>{

    return (
    <input 
        type='button'
        value="Search"
        onClick = {props.onClick}/>
    );
}
        

export default SearchButton;
