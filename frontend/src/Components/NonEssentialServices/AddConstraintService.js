export default class AddConstraintServiceAPI{
    // Insert a Class
    static AddConstraint(body){
        return fetch(`http://localhost:5000/add-constraint`,{
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