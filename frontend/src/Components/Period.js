// -- React --
import React from "react";

// -- Globals --
var colors = [
  "White",
  "navajowhite",
  "Lavender",
  "PaleTurquoise",
  "PaleVioletRed",
  "Pink",
  "Salmon",
  "LightSkyBlue",
  "Lavender",
  "HotPink",
  "LightBlue",
  "LightSeaGreen",
  "Salmon",
];

var blockedOffLevelColors = [
  "Gold",
  "DarkOrange",
  "Red",
]
// -- Module --
const Period = (props) => {
  // Extract course properties
  const code = props.code || null;
  let color = colors[props.color || 0];
  const section = (props.section) ? "01" + String(props.section).padStart(2, "0") : null;
  const type = props.type || null;
  const blockedOffLevel = props.blockedOffLevel || null;
  const multiPos = props.multiPos || null;
  if(blockedOffLevel !== null || blockedOffLevel > 0){
    color = blockedOffLevelColors[blockedOffLevel-1];
    
  }
  return (
    <div style = {{
      backgroundColor: color, 
      border: 2,
      borderWidth: 1,
      borderColor: colors[7],
      verticalAlign: 0,
    }} >
      <div className="class-id">{code}</div>
      <div className="class-section">{type} {section}</div>
    </div>
  )
}

// -- Exports --
export default Period;
