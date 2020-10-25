// manage database


function saveOnClick(){
    var age=document.getElementById('age')
    var name=document.getElementById('name')
  
    
    insertData(age.value,name.value);
    
}
function insertData(age,name){
    var db=firebase.database().ref("User");
    db.push({
        age:age,
        name:name
    });
console.log("Insert Success");
}

window.onload = function(){
  showData();


}
function showData(){
    const db = firebase.database().ref("User").orderByChild("name");
    db.once('value').then(function(dataSnapshot){
    dataSnapshot.forEach(function(childSnapshot){
        var childKey = childSnapshot.key;
        var childData = childSnapshot.val();
        // console.log(childKey);
        // console.log(childData);
  
});
});
}


var data1 = document.getElementById("name");

var db_data1 = firebase.database().ref("LM1");
db_data1.on('child_added',snap =>{
    data1.innerText = snap.val()["buttonPushCounter"];
    console.log(data1.innerText);

    // var p = document.createElement("p"); 
    // var newContent = document.createTextNode(data1.innerText);
    // p.appendChild(newContent); 
    // document.getElementById("text_box").appendChild(p);

});


    // console.log(data1.innerText);

   
var data2 = document.getElementById("age");
var db_data2 = firebase.database().ref("LM2");

db_data2.on('child_added',snap =>{
    data2.innerText = snap.val()["buttonPushCounter2"];
    console.log(data2.innerText);

    // var p = document.createElement("p"); 
    // var newContent = document.createTextNode(data2.innerText);
    // p.appendChild(newContent); 
    // document.getElementById("text_box").appendChild(p);
});

// var p = document.createElement('p');
// p.name = 'generated_input';
// document.getElementbyId('inputs_contained').appendChild(p);

