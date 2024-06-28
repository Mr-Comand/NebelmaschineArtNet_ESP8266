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
      document.getElementsByName("univers")[0].value = data[1];
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
    loadSSIDsandArtnet();
    event.preventDefault();
  }
});
function resetState(element){
  element.classList.remove("success");
  element.classList.remove("failed");
  element.classList.remove("sending");
}


