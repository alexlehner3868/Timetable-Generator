export default class RemoveCourseServiceAPI{
    // Insert a Class
    static RemoveClass(body){
        return fetch(`http://localhost:5000/remove-class`,{
            'method':'POST',
             headers : {
            'Content-Type':'text/plain'
      },
      body:JSON.stringify(body)
    })
    .then(response => response.json())
    .catch(error => console.log(error))
    }

}
