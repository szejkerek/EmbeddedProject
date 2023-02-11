const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Temperature site</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link href='http://fonts.googleapis.com/css?family=Roboto' rel='stylesheet' type='text/css'>
  <style>
  html {
    font-family: 'Roboto', sans-serif;
    display: inline-block;
    text-align: center;
}

p {  
    font-size: 1.2rem;
}

body {  
    margin: 0;
}

.topnav {
    overflow: hidden;
    background-color: #1a3c22;
    color: rgb(255, 255, 255);
    font-size: 1.7rem;
}

.content { 
    padding: 30px;
}

.card { 
    background-color: white;
    box-shadow: 2px 2px 25px 1px rgba(81, 81, 81, 0.5);
    border-radius: 25px;
    border: 2px solid #c7c7c7;
    padding: 20px;
    width: 200px;
    height: 150px;
}

.cards { 
    max-width: 700px;
    margin: 0 auto;
    display: grid;
    grid-gap: 3rem;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
}

.reading { 
    font-size: 2.5rem;
}

.packet { 
    font-size: 0.8rem;
    color: #bebebe; 
}

.card.temperature { 
    color: #0c4f23;
}

.headerText{
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100%;
}
  </style>
</head>
<body>
  <script src="script.js"></script>
  
  <div class="topnav">
    <h3 class="headerText">
        <img src="https://cdn.discordapp.com/attachments/726825755345944646/1073321734918381568/aei_logo-1.png" alt="AEI" style="width: 111px; height: 111px; margin-right: 20px;">
        Temperature measurements at home
    </h3>
  </div>

  <div class="content">
    <div class="cards">

      <div class="card temperature">
        <h4>Sensor 1</h4><p><span class="reading"><span id="t1">...</span> &deg;C</span></p><p class="packet">Reading ID: <span id="rt1"></span></p>
      </div>

      <div class="card temperature">
        <h4>Sensor 2</h4><p><span class="reading"><span id="t2">...</span> &deg;C</span></p><p class="packet">Reading ID: <span id="rt2"></span></p>
      </div>

      <div class="card temperature">
        <h4>Sensor x</h4><p><span class="reading"><span id="t3"></span>---</span></p><p class="packet">Preview additional board<span id="rt3"></span></p>
      </div>

    </div>
  </div>

<script>
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('new_readings', function(e) {
  console.log("new_readings", e.data);
  var obj = JSON.parse(e.data);
  document.getElementById("t"+obj.id).innerHTML = obj.temperature.toFixed(2);
  document.getElementById("rt"+obj.id).innerHTML = obj.readingId;
  
 }, false);
}
</script>

</body>
</html>
)rawliteral";