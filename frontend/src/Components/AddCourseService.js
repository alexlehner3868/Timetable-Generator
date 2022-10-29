export default class APIService{
    // Insert a Class
    static InsertClass(body){
        return fetch(`http://localhost:5000/send-request`,{
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
