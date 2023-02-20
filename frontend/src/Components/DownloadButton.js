import { jsPDF } from "jspdf";

// -- Module --
const DownloadButton = (props) => {
  const timetable = (props.timetables.length) ? props.timetables[props.ttbIndex] : [];
    
  function getTimetableCourseTxt (){
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
    let text = "";

    text += ("Timetable Option " + props.ttbIndex +":\n")
    text +=("_________________________________________\n")
    text +=("Here are the sections to enroll in:\n")
    for( const course  of courses){
        text += ("     " + course.code + " " + course.type + " section: " + (course.section-1) + '\n');
    }
    
    return text;
  }
  
    function downloadPDFWithjsPDF() {
      const doc = new jsPDF('l', 'pt');
      doc.setFontSize(500);
      let course_txt = getTimetableCourseTxt();
      doc.html(document.querySelector('#timetable'), {
        callback: function (doc) {
          doc.addPage('l', 'pt');
          doc.text(course_txt, '20', '20');
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