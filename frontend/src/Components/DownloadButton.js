
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

            text.push("Timetable Option " + props.ttbIndex +":\n")
            text.push("_________________________________________\n")
            text.push("Here are the sections to enroll in:\n")
            for( const course  of courses){
                text.push("     " + course.code + " " + course.type + " section: " + course.section + '\n');
            }
            let unique_courses = [...new Set(text)]
            console.log(unique_courses)
            // file object
            const file = new Blob(unique_courses, {type: 'text/plain'});
            // anchor link
            const element = document.createElement("a");
            element.href = URL.createObjectURL(file);
            element.download = "timetable_option_"+ props.ttbIndex + ".txt";
            // simulate link click
            document.body.appendChild(element);
            // Required for this to work in FireFox
            element.click();
    }

    function downloadPDFWithjsPDF() {
        var doc = new window.jspdf.jsPDF('p', 'pt', 'a4');
      
        doc.html(document.querySelector('#styledTable'), {
          callback: function (doc) {
            doc.save('MLB World Series Winners.pdf');
          },
          margin: [60, 60, 60, 60],
          x: 32,
          y: 32,
        });
      }

    return (
      <div className="download-button-div">
       <button id="button_image" onClick={downloadTxtFile} value="download"><img className="download-button-img" src="https://i.ibb.co/ctMCKRD/532.png" alt="532" border="0"/></button>
      </div>
    )
  }

export default DownloadButton;