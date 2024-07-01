var intervalActive = false;
var channelMode = 0;
function stopFog(button) {
  button.classList.remove("success");
  button.classList.remove("failed");
  button.classList.add("sending");

  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/fire", true);

  var formData = new FormData();
  formData.append("time", "0");

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");
        button.classList.add("success");
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };
  xhr.send(formData);
  var period = Math.ceil(document.getElementById("periodSlider").value *1000);
  var dutyCycle = Math.ceil(document.getElementById("dutyCycleSlider").value*2.55);
  var xhr2 = new XMLHttpRequest();
  xhr2.open("POST", url + "/interval", true);
  var formData2 = new FormData();
  formData2.append("period", period);
  formData2.append("dutyCycle", dutyCycle);
  formData2.append("active", 0);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");
        button.classList.add("success");
        intervalActive=(xhr.responseText=="1");
        updateIntervalStatus(xhr.responseText=="1");
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };

  xhr2.send(formData2);
}
function sendTimer(button) {
  button.classList.remove("success");
  button.classList.remove("failed");
  button.classList.add("sending");
  var selectedTime = document.getElementById("selectedTime").innerText;

  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/fire", true);

  var formData = new FormData();
  formData.append("time", selectedTime * 1000);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");
        button.classList.add("success");
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };

  xhr.send(formData);
}

document.getElementById("timeSlider").addEventListener("input", function () {
  var selectedTime = document.getElementById("timeSlider").value;
  document.getElementById("selectedTime").innerText = selectedTime;
});


function activateInterval(button) {
  if (channelMode!=3) return;
  button.classList.remove("success");
  button.classList.remove("failed");
  button.classList.add("sending");
  var period = Math.ceil(document.getElementById("periodSlider").value *1000);
  var dutyCycle = Math.ceil(document.getElementById("dutyCycleSlider").value*2.55);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/interval", true);

  var formData = new FormData();
  formData.append("period", period);
  formData.append("dutyCycle", dutyCycle);
  formData.append("active", 1);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");
        button.classList.add("success");
        intervalActive=(xhr.responseText=="1");
        updateIntervalStatus(xhr.responseText=="1");
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };

  xhr.send(formData);
}
function updatePeriodSlider(slider) {
  const selectedPeriod = slider.value;

  let result;
  if (selectedPeriod < 60) {
    result = `${selectedPeriod} seconds`;
    slider.step = 0.1; // Step by 1 second
  } else if (selectedPeriod < 3600) {
    let minutes = (selectedPeriod / 60).toFixed(2);
    result = `${minutes} minutes`;
    slider.step = 6; // Step by 1 minute
  } else if (selectedPeriod < 86400) {
    let hours = (selectedPeriod / 3600).toFixed(2);
    result = `${hours} hours`;
    slider.step = 360; // Step by 1 hour
  } else {
    let days = (selectedPeriod / 86400).toFixed(2);
    slider.step = 8640; // Step by 1 day
    result = `${days} days`;
  }

  return result;
}

document.getElementById("periodSlider").addEventListener("input", function () {
  disply_val = updatePeriodSlider(document.getElementById("periodSlider"))
  document.getElementById("selectedPeriod").innerText = disply_val;
  if (channelMode!=3) return;
  var period = Math.ceil(document.getElementById("periodSlider").value *1000);
  var dutyCycle = Math.ceil(document.getElementById("dutyCycleSlider").value*2.55);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/interval", true);
  var formData = new FormData();
  formData.append("period", period);
  formData.append("dutyCycle", dutyCycle);
  formData.append("active", intervalActive*1);
  xhr.send(formData);
});


document.getElementById("dutyCycleSlider").addEventListener("input", function () {
  var selectedTime = document.getElementById("dutyCycleSlider").value;
  document.getElementById("selectedDutyCycle").innerText = selectedTime;
  if (channelMode!=3) return;
  var period = Math.ceil(document.getElementById("periodSlider").value *1000);
  var dutyCycle = Math.ceil(document.getElementById("dutyCycleSlider").value*2.55);
  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/interval", true);
  var formData = new FormData();
  formData.append("period", period);
  formData.append("dutyCycle", dutyCycle);
  formData.append("active", intervalActive*1);
  xhr.send(formData);
});


function saveArtnet(button) {
  button.classList.remove("success");
  button.classList.remove("failed");
  button.classList.add("sending");
  var form = document.getElementById("artnetForm");
  var formData = new FormData(form);

  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + "/putArtnet", true);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");
        button.classList.add("success");
        channelMode=formData.get("channelMode")
        if (channelMode==3){
          var intervalInputs =document.querySelectorAll("#interval button, #interval input");
          for (var i = 0; i < intervalInputs.length; i++) {
            intervalInputs[i].disabled = false;
            intervalInputs[i].classList.remove("disabled");
          }
        }else{
          var intervalInputs = document.querySelectorAll("#interval button, #interval input");
          for (var i = 0; i < intervalInputs.length; i++) {
            intervalInputs[i].disabled = true;
            intervalInputs[i].classList.add("disabled");
          }
        }
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };

  xhr.send(formData);
}
function saveConfig(formId, actionUrl) {
  var form = document.getElementById(formId);
  button = form.getElementsByClassName("save")[0];
  button.classList.remove("success");
  button.classList.remove("failed");
  button.classList.add("sending");
  var formData = new FormData(form);

  var xhr = new XMLHttpRequest();
  xhr.open("POST", url + actionUrl, true);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        console.log(xhr.responseText);
        button.classList.remove("sending");

        button.classList.add("success");
        setTimeout(() => { resetState(button); }, 3000);
      } else {
        button.classList.remove("sending");
        button.classList.add("failed");
        setTimeout(() => { resetState(button); }, 3000);
      }
    }
  };

  xhr.send(formData);
}
function loadSSIDsandArtnet() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", url + "/getData", true);

  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var ssids = JSON.parse(xhr.responseText);

      document.getElementsByName("ssid").forEach(function (input, index) {
        input.value = ssids[index];
      });
    }
  };

  xhr.send();
  var xhr2 = new XMLHttpRequest();
  xhr2.open("GET", url + "/getArtnet", true);

  xhr2.onreadystatechange = function () {
    if (xhr2.readyState === 4 && xhr2.status === 200) {
      var data = JSON.parse(xhr2.responseText);

      document.getElementsByName("address")[0].value = data[0];
      document.getElementsByName("universe")[0].value = data[1];
      document.getElementsByName("shortname")[0].value = data[2];
      document.getElementsByName("longname")[0].value = data[3];
      document.title = "ESP-Nebel "+data[3];
      var radioButtons = document.getElementsByName("channelMode");
      for (var i = 0; i < radioButtons.length; i++) {
        if (radioButtons[i].value === data[4]) {
          radioButtons[i].checked = true;
          break;
        }
      }
      channelMode = data[4];
      if (channelMode==3){
        var intervalInputs = document.querySelectorAll("#interval button, #interval input");
        for (var i = 0; i < intervalInputs.length; i++) {
          intervalInputs[i].disabled = false;
          intervalInputs[i].classList.remove("disabled");
        }
      }else{
        var intervalInputs = document.querySelectorAll("#interval button, #interval input");
        for (var i = 0; i < intervalInputs.length; i++) {
          intervalInputs[i].disabled = true;
          intervalInputs[i].classList.add("disabled");
        }
      }
    }
  };
  xhr2.send();
}
function checkConnection() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", url + "/ping", true);
  xhr.timeout = 3000;
  xhr.onreadystatechange = function () {
    if (xhr.readyState === 4) {
      if (xhr.status === 200) {
        document.getElementById("connectionStatus").innerHTML =
          "Connected to API: OK";
        document.getElementById("connectionStatus").classList.remove("bad");
        document.getElementById("connectionStatus").classList.add("good");
        var data = JSON.parse(xhr.responseText);

        if (data[0] === "1") {
          var element = document.getElementById("artnet");
          element.classList.add("disabled");
          var artnetInputs = element.getElementsByTagName("input");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = true;
          }
          var artnetInputs = element.getElementsByTagName("button");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = true;
          }
        } else {
          var element = document.getElementById("artnet");
          element.classList.remove("disabled");
          var artnetInputs = element.getElementsByTagName("input");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = false;
          }
          var artnetInputs = element.getElementsByTagName("button");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = false;
          }
        }
        if (data[1] === "1") {
          var element = document.getElementById("control");
          element.classList.add("disabled");
          var artnetInputs = element.getElementsByTagName("input");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = true;
          }
          var artnetInputs = element.getElementsByTagName("button");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = true;
          }
        } else {
          var element = document.getElementById("control");
          element.classList.remove("disabled");
          var artnetInputs = element.getElementsByTagName("input");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = false;
          }
          var artnetInputs = element.getElementsByTagName("button");
          for (var i = 0; i < artnetInputs.length; i++) {
            artnetInputs[i].disabled = false;
          }
        }
        document.getElementById("periodSlider").value =  Math.ceil(data[3]/1000);
        document.getElementById("dutyCycleSlider").value =  Math.ceil(data[4]/2.55); 
        disply_val = updatePeriodSlider(document.getElementById("periodSlider"))
        document.getElementById("selectedPeriod").innerText = disply_val;
        document.getElementById("selectedDutyCycle").innerText = Math.ceil(data[4]/2.55); 
        updateIntervalStatus(data[2]=="1")
        if (channelMode==3){
          var intervalInputs = document.querySelectorAll("#interval button, #interval input");
          for (var i = 0; i < intervalInputs.length; i++) {
            intervalInputs[i].disabled = false;
            intervalInputs[i].classList.remove("disabled");
          }
        }else{
          var intervalInputs = document.querySelectorAll("#interval button, #interval input");
          for (var i = 0; i < intervalInputs.length; i++) {
            intervalInputs[i].disabled = true;
            intervalInputs[i].classList.add("disabled");
          }
        }

      } else {
        // Connection failed
        document.getElementById("connectionStatus").innerHTML =
          "Unable to connect to API";
        document.getElementById("connectionStatus").classList.remove("good");
        document.getElementById("connectionStatus").classList.add("bad");
        
      }
    }
  };

  xhr.send();
}
window.onload = function () {
  checkConnection();
  loadSSIDsandArtnet();
};
setInterval(function () {
  checkConnection();
}, 10000);
const url = "";
document.addEventListener("keydown", function (event) {
  if (event.key === "F5") {
    console.log("F5 key pressed");
    checkConnection();
    loadSSIDsandArtnet();
    event.preventDefault();
  }
});
function resetState(element){
  element.classList.remove("success");
  element.classList.remove("failed");
  element.classList.remove("sending");
}


function updateIntervalStatus(status){
  if (status){
    document.getElementById("intervalStatus").innerText = "ON"
  }
  else{
    document.getElementById("intervalStatus").innerText = "OFF"
  }
}