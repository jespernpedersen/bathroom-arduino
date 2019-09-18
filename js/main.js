(function() {

    // Set the configuration for your app
    // TODO: Replace with your project's config object
    var config = {
        apiKey: "AIzaSyCu8x2gWsXJfjBqU6qyacMknfgqppdAUkc",
        authDomain: "bathroom-28f4f.firebaseapp.com",
        databaseURL: "https://bathroom-28f4f.firebaseio.com",
        projectId: "bathroom-28f4f",
        storageBucket: "bathroom-28f4f.appspot.com",
        messagingSenderId: "690661487151",
        appId: "1:690661487151:web:866fcc9d85cfde08188cda"
    };

    firebase.initializeApp(config);
    database = firebase.database();

    var ref = database.ref('DHT11/Humidity');
    ref.on('value', gotData, errData);


    function gotData(data) {
        console.log(data);
    }

    function errData(err) {
        console.log("ERROR");
        console.log(err);
    }
}());