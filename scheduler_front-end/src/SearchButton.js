import React from "react";

const SearchButton = (props) =>{

    return (
    <input 
        type='button'
        value={props.caption}
        onClick = {props.onClick}/>
    );
}
        

export default SearchButton;
