
    
    var firebaseConfig = {
        apiKey: "AIzaSyBPfOiPzd_qg0f_8KvYH2WCOaBNNJgJ14g",
        authDomain: "virpj-5c808.firebaseapp.com",
        databaseURL: "https://virpj-5c808.firebaseio.com",
        projectId: "virpj-5c808",
        storageBucket: "virpj-5c808.appspot.com",
        messagingSenderId: "954404746522",
        appId: "1:954404746522:web:b8ee79b967110fb16e68a3",
        measurementId: "G-MK43078CWB"
      };
      // Initialize Firebase
      firebase.initializeApp(firebaseConfig);
      firebase.database();
  
      database.ref("LM1/").once('child_added', function(snapshot){
        if(snapshot.exists()){
            var content = '';
            snapshot.forEach(function(data){
                var val = data.val();
                console.log("row",data.val());
                console.log("title",data.getKey());
              
                content +='<tr>';
                content += '<td>' + data.getKey() + '</td>';
                content += '<td>' + val.title + '</td>';
                content += '<td>' + val.content + '</td>';
                content += '<td><a href="'+val.thumbnail+'" target="_blank"> Click for Preview</a></td>';
                content += '<td><a href="edit.html?id='+data.getKey()+'" class="mdl-button mdl-js-button mdl-button--raised mdl-button--accent">Edit</a></td>';
                content += '</tr>';
                
            });
            var theDiv = document.getElementById("ex-table");
            theDiv.innerHTML += content; 
            //$('#ex-table').append(content);
        }
  });