client = new Paho.MQTT.Client("mqtt.netpie.io", 443, "bd326a6b-0d0f-43ca-9488-3a901d321140");
client.onMessageArrived = onMessageArrived;

var options = {
  useSSL: true,
  userName : "6CJGfXz4iVvUJYZQUf3Z6qHbaSU2q6MK",
  password : "_Czm84p~-I8#SrVtHX7E8CO$(uiR8~iV",  
  onSuccess: onConnect,
  onFailure:doFail,
}

client.connect(options);

function onConnect() {
  client.subscribe("@msg/temp");
  client.subscribe("@msg/temp3");

}

function doFail(e){
    console.log(e);
  }
  var temp = ""; var hum = ""; 
  function onMessageArrived(message) { 
   // console.log(message.payloadString);
    if(message.destinationName == "@msg/temp"){ 
      temp = message.payloadString; 
      console.log(temp);
    } 
      if(message.destinationName == "@msg/temp3"){
         hum = message.payloadString; 
      console.log(hum);
      

        } 
    

  var split_msg_temp = temp.split(","); //String data 
  var split_msg_hum = hum.split(","); //String data 

  

  document.getElementById("show").innerHTML = temp;

  document.getElementById("show3").innerHTML = hum;
    document.getElementById("ultrasonic").innerHTML = split_msg_hum[0];

  document.getElementById("button1").innerHTML = split_msg_temp[0];
  document.getElementById("Countbutton1").innerHTML = split_msg_temp[1];
  // document.getElementById("button2").innerHTML = split_msg_hum[0];
  // document.getElementById("Countbutton2").innerHTML = split_msg_hum[1];
if (split_msg_temp[0] == 1) {
  red();
  } else {
  green();
  };

  if (split_msg[2] == 1) {
    red1();
    } else {
    green1();
    };
  }

function red() {
  document.getElementById("circle").style.backgroundColor = "red";
}

function green() {
  document.getElementById("circle").style.backgroundColor = "green";
}

function red1() {
  document.getElementById("circle1").style.backgroundColor = "red";
}

function green1() {
  document.getElementById("circle1").style.backgroundColor = "green";
}

