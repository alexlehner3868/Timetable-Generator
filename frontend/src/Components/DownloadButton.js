
// -- Module --
const DownloadButton = (props) => {
    
    const downloadTxtFile = () => {
           // text content
            const timetable = (props.timetables.length) ? props.timetables[props.ttbIndex] : [];
            // Extract sorted list of courses (for colouring)
            let courses = []; 
            for (const meet of timetable){
                if (!courses.includes(
                    {
                        "code":meet.course,
                        "type":meet.type,
                        "section" :meet.section

                    })){
                        courses.push({"code":meet.course,"type":meet.type, "section" :meet.section})
                }
            }
            let text = [];
            console.log(courses)
            text.push("Timetable Option " + props.ttbIndex +":\n")
            for( const course  of courses){
                text.push(course.code + " " + course.type + " section: " + course.section + '\n');
            }
            // file object
            const file = new Blob(text, {type: 'text/plain'});
            // anchor link
            const element = document.createElement("a");
            element.href = URL.createObjectURL(file);
            element.download = "timetable_option_"+ props.ttbIndex + ".txt";
            // simulate link click
            document.body.appendChild(element);
            // Required for this to work in FireFox
            element.click();
    }


    return (
      <div>
       
       <button id="downloadBtn" onClick={downloadTxtFile} value="download">Download</button>
      </div>
    )
  }

export default DownloadButton;