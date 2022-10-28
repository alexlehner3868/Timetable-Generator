export default class APIService{
    // Insert a Class
    static InsertClass(){
        return fetch(`http://localhost:5000/basic-schedule`,{
            'method':'GET',
             headers : {
            'Content-Type':'text/plain'
      },
    })
    .then(response => response.json())
    .catch(error => console.log(error))
    }

}
