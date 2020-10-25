// Set new default font family and font color to mimic Bootstrap's default styling
Chart.defaults.global.defaultFontFamily = 'Nunito', '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#858796';

// Pie Chart 
var db_data7 = firebase.database().ref("Ultrasonic");
var ctx = document.getElementById("myPieChart");
var x = 0;
// var g =2;
db_data7.on('child_added',snap =>{
  g = snap.val()["distance"];

  if(g <= 5){  
   x = 100;
  }
  else if(g == 6){
    x = 90;
  }
  else if(g == 7){  
   x = 80;
  }
  else if(g == 8){
   x = 70;
  }
   else if(g == 9){
   x = 60;
   }
  else if(g == 10){
    x = 50;
    }
  else if(g == 11){
    x = 40;
    }
  else if(g == 12){
   x = 30;
   }
  else if(g == 13){
    x = 20;
    }      
  else{
   x = 0;
  }
  
  var y = 100-x;
   var myPieChart = new Chart(ctx, {
 
    type: 'doughnut',
    data: {
      labels: ["เหลือ", "ใช้ไปแล้ว"],
      datasets: [{
        data: [x,y],
        backgroundColor: ['#4e73df', '#1cc88a'],
        hoverBackgroundColor: ['#2e59d9', '#17a673'],
        hoverBorderColor: "rgba(234, 236, 244, 1)",
      }],
    },
    options: {
      maintainAspectRatio: false,
      tooltips: {
        backgroundColor: "rgb(255,255,255)",
        bodyFontColor: "#858796",
        borderColor: '#dddfeb',
        borderWidth: 1,
        xPadding: 15,
        yPadding: 15,
        displayColors: false,
        caretPadding: 10,
      },
      legend: {
        display: false
      },
      cutoutPercentage: 80,
    },
  });
   
});

