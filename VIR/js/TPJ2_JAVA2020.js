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
  // client.subscribe("@shadow/TPJ/button1");
   client.subscribe("@msg/temp_2");
}
console.log("temp2");
function doFail(e){
    console.log(e);
  }

function onMessageArrived(message) {

  console.log("gfhfghfghfghfgh");
  document.getElementById("show2").innerHTML = message.payloadString;
  var msg = message.payloadString
  var split_msg = msg.split(","); //String data 
    console.log(msg);  // for debug
  document.getElementById("button2").innerHTML = split_msg[0];
  document.getElementById("Countbutton2").innerHTML = split_msg[1];
if (split_msg[0] == 1) {
  red1();
  } else {
  green1();
  };

}

function red1() {
  document.getElementById("circle1").style.backgroundColor = "red";
}

function green1() {
  document.getElementById("circle1").style.backgroundColor = "green";
}