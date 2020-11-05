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


var data1 = document.getElementById("Countbutton1");

var db_data1 = firebase.database().ref("LM1");
db_data1.on('value',snap =>{
  
    data1.innerText = snap.val()["buttonPushCounter"];
    // console.log(data1.innerText);

});


    // console.log(data1.innerText);


var data2 = document.getElementById("Countbutton2");
var db_data2 = firebase.database().ref("LM2");


db_data2.on('value',snap =>{
    data2.innerText = snap.val()["buttonPushCounter2"];
    
    var data6 = document.getElementById("CountbuttonSum");
    data6_sum = data1.innerText+data2.innerText;
    

    var a = data1.innerText;
    var b = data2.innerText;

    a = parseInt(a);
    b = parseInt(b);

    var result = a + b;
    data6.innerText =  result;
});

var data3 = document.getElementById("buttonState");
var db_data3 = firebase.database().ref("LM1");

db_data3.on('value',snap =>{
    data3.innerText = snap.val()["buttonState"];
    console.log(data3.innerText);

    if ( data3.innerText == 1) {
        red();
        boxred();
        textstatus();
        } else {
        green();
        boxgreen();
        textstatus1();
        };
});

var data4 = document.getElementById("buttonState2");
var db_data4 = firebase.database().ref("LM2");

db_data4.on('value',snap =>{
    data4.innerText = snap.val()["buttonState2"];
   
    if ( data4.innerText == 1) {
        red1();
        boxred1();
        textstatus2();
        } else {
        green1();
        boxgreen1();  
        textstatus3();
        }; 
});

var data5 = document.getElementById("ultrasonic");
var db_data5 = firebase.database().ref("Ultrasonic");

db_data5.on('value',snap =>{
    data5.innerText = snap.val()["distance"];
    if ( data5.innerText <=18 ) {
        ultra1();
        } else {
        ultra2();
        }; 
});

var data6 = document.getElementById("air_quality");
var db_data6 = firebase.database().ref("MQ135");

db_data6.on('value',snap =>{
    data6.innerText = snap.val()["air_quality"];
    console.log(data6.innerText);
    if ( data6.innerText <=200 ) {
        quality_good();
      }
    if ( data6.innerText <=400 ) {
          quality_Satisfac();
      }
    if ( data6.innerText <=800 ) {
          quality_Moderate();
      }
    if ( data6.innerText <=1200 ) {
          quality_Poor();
      }
    if ( data6.innerText <=1800 ) {
          quality_Verypoor();
      }
    
      if ( data6.innerText >1800 ) {
        quality_Severe();
    }  
    
});



   
var textstatus = document.getElementById("textstatus");
var status2= document.getElementById("status2");

function red() {
    document.getElementById("circle").style.backgroundColor = "red";
  }
function boxred() {
    document.getElementById("box1").style.backgroundColor = "green";
  }

  
function green() {
    document.getElementById("circle").style.backgroundColor = "green";
  }
function boxgreen() {
    document.getElementById("box1").style.backgroundColor = "green";
  }

function red1() {
    document.getElementById("circle1").style.backgroundColor = "red";
  }
function boxred1() {
    document.getElementById("box2").style.backgroundColor = "red";
  }  
  
  
function green1() {
    document.getElementById("circle1").style.backgroundColor = "green";
  }
function boxgreen1() {
    document.getElementById("box2").style.backgroundColor = "green";
  }  
function ultra1() {
    document.getElementById("ultrasonic").innerHTML = "กระดาษชำระยังไม่หมด";
  }
  
function ultra2() {
    document.getElementById("ultrasonic").innerHTML = "กระดาษชำระหมด";
  }

function textstatus() {
    document.getElementById("textstatus").innerHTML = "ไม่ว่าง";
  } 

function textstatus1() {
    document.getElementById("textstatus").innerHTML = "ว่าง";
  } 

function textstatus2() {
   document.getElementById("status2").innerHTML = "ไม่ว่าง";
  } 
    
function textstatus3() {
    document.getElementById("status2").innerHTML = "ว่าง";
  }

function quality_good() {
    document.getElementById("air_quality").innerHTML = "ระดับดี";
  }

function quality_Satisfac() {
    document.getElementById("air_quality").innerHTML = "ระดับน่าพอใจ";
  }
  
function quality_Moderate() {
    document.getElementById("air_quality").innerHTML = "ระดับปานกลาง";
  } 

function quality_Poor() {
    document.getElementById("air_quality").innerHTML = "ระดับแย่";
  }

function quality_Verypoor() {
    document.getElementById("air_quality").innerHTML = "ระดับแย่มาก";
  }

function quality_Severe() {
    document.getElementById("air_quality").innerHTML = "ระดับรุนแรง";
  }

    var table = $('#table').DataTable();
    //  table.row.add( [ 1, 2, 3, 4, 5,6 ] ).draw();
    const dbRef = firebase.database().ref("LM1")
    dbRef.on("child_added", snap => {
    table.row.add( [ '<h6>SC2</h6>', '<h6>1</h6>', snap.val()["buttonState"], snap.val()["buttonPushCounter"], snap.val()["date"], snap.val()["time"] ]  ).draw();
    });
    const db2Ref = firebase.database().ref("LM2")
    db2Ref.on("child_added", snap => {
      table.row.add( [ '<h6>SC2</h6>', '<h6>2</h6>', snap.val()["buttonState2"],snap.val()["buttonPushCounter2"], snap.val()["date2"], snap.val()["time2"] ] ).draw();
      
    }); 
  // var table2 = $('#table2').DataTable();
  // const db3Ref = firebase.database().ref("MQ135")
  // db3Ref.on("child_added", snap => {
  // table.row.add( [ '<h6>SC2</h6>', '<h6></h6>', snap.val()["air_quality"],'<h6></h6>', snap.val()["date3"], snap.val()["time3"] ] ).draw();
  // });     
