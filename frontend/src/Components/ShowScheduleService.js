  // Insert a Class
     function ShowSchedule(){
        var out = fetch(`http://localhost:5000/basic-schedule`,{
            'method':'POST',
             headers : {
            'Content-Type':'text/plain'
      }
    })
        return out;
    }

