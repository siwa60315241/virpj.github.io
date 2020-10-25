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
  client.subscribe("@msg/temp3");
}

function doFail(e){
    console.log(e);
  }

function onMessageArrived(message) {
    
  // document.getElementById("show3").innerHTML = message.payloadString;
  var msg = message.payloadString
  var split_msg = msg.split(","); //String data 
    // document.getElementById("ultrasonic").innerHTML = msg;
    document.getElementById("show3").innerHTML = message.payloadString;
    document.getElementById("ultrasonic").innerHTML = split_msg[0];
    
console.log("ultrasonic");
if (split_msg[0] <= 24) {
  ultra1();
  } else {
  ultra2();
  };

}
function ultra1() {
  document.getElementById("ultrasonic").innerHTML = "กระดาษชำระยังไม่หมด";
}

function ultra2() {
  document.getElementById("ultrasonic").innerHTML = "กระดาษชำระหมด";
}

