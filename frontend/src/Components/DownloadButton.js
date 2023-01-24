import { jsPDF } from "jspdf";

// -- Module --
const DownloadButton = (props) => {
  const timetable = (props.timetables.length) ? props.timetables[props.ttbIndex] : [];
    const downloadTxtFile = () => {
           // text content
            
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
      const doc = new jsPDF('l', 'pt');
      doc.setFontSize(500);
      
      doc.html(document.querySelector('#timetable'), {
        callback: function (doc) {
          
          doc.save("TimetableOption"+ (props.ttbIndex+1) + ".pdf");
        },
        margin: [30, 30, 30, 30],
        width: 552,
      });
      }


    return (
      <div className="download-button-div">
       <button id="button_image" onClick={downloadPDFWithjsPDF} value="download"><img className="download-button-img" src="https://i.ibb.co/ctMCKRD/532.png" alt="532" border="0"/></button>
      </div>
    )
  }

export default DownloadButton;