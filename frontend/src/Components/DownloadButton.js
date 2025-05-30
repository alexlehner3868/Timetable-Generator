import { jsPDF } from "jspdf";
// -- Module --
const DownloadButton = (props) => {
  const timetable = (props.timetables.length) ? props.timetables[props.ttbIndex] : [];
    
  function getTimetableCourseTxt (){
    // Extract sorted list of courses (for colouring)
    var course_dict = {};
    let courses = []; 
    for (const meet of timetable){
      var key = meet.course + ": " + meet.type
      course_dict[key] = meet.section;
    }

    let text = "";
    let idx = 1 ;
    text += ("Timetable Option " + 1+props.ttbIndex +":\n")
    text +=("_________________________________________\n")
    text +=("Here are the sections to enroll in:\n")
    for (const key in course_dict){
       
        text += ("     " + key + (course_dict[key]-1) + '\n');
    }
    
    return text;
  }

    function clickHandler(){
       // props.setTabIndex(1); The swtiching timetables doesnt currently work 
        downloadPDFWithjsPDF();
    }
  
    function downloadPDFWithjsPDF() {
      const doc = new jsPDF('l', 'pt', [624, 1000]); 
      doc.setFontSize(500);
      let course_txt = getTimetableCourseTxt();
      doc.html(document.querySelector('#timetable'), {
        callback: function (doc) {
          doc.addPage('l', 'pt', [624, 1000]);
          doc.text(course_txt, '20', '20');
          doc.save("TimetableOption"+ (props.ttbIndex+1) + ".pdf");
        },
        margin: [30, 30, 30, 30],
        width: 500,
      });     
    }


    return (
      <div className="download-button-div">
       <button id="button_image" onClick={clickHandler} value="download"><img className="download-button-img" src="https://i.ibb.co/ctMCKRD/532.png" alt="532" border="0"/></button>
      </div>
    )
  }

export default DownloadButton;