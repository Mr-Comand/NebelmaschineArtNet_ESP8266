
#ifndef main_js_H
#define main_js_H

#define main_js_code "function stopFog(button) {\n\
  button.classList.remove(\"success\");\n\
  button.classList.remove(\"failed\");\n\
  button.classList.add(\"sending\");\n\
\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/fire\", true);\n\
\n\
  var formData = new FormData();\n\
  formData.append(\"time\", \"0\");\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"success\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      } else {\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"failed\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      }\n\
    }\n\
  };\n\
\n\
  xhr.send(formData);\n\
}\n\
function sendTimer(button) {\n\
  button.classList.remove(\"success\");\n\
  button.classList.remove(\"failed\");\n\
  button.classList.add(\"sending\");\n\
  var selectedTime = document.getElementById(\"selectedTime\").innerText;\n\
\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/fire\", true);\n\
\n\
  var formData = new FormData();\n\
  formData.append(\"time\", selectedTime * 1000);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"success\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      } else {\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"failed\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      }\n\
    }\n\
  };\n\
\n\
  xhr.send(formData);\n\
}\n\
\n\
document.getElementById(\"timeSlider\").addEventListener(\"input\", function () {\n\
  var selectedTime = document.getElementById(\"timeSlider\").value;\n\
  document.getElementById(\"selectedTime\").innerText = selectedTime;\n\
});\n\
\n\
function saveArtnet(button) {\n\
  button.classList.remove(\"success\");\n\
  button.classList.remove(\"failed\");\n\
  button.classList.add(\"sending\");\n\
  var form = document.getElementById(\"artnetForm\");\n\
  var formData = new FormData(form);\n\
\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/putArtnet\", true);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"success\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      } else {\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"failed\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      }\n\
    }\n\
  };\n\
\n\
  xhr.send(formData);\n\
}\n\
function saveConfig(formId, actionUrl) {\n\
  var form = document.getElementById(formId);\n\
  button = form.getElementsByClassName(\"save\")[0];\n\
  button.classList.remove(\"success\");\n\
  button.classList.remove(\"failed\");\n\
  button.classList.add(\"sending\");\n\
  var formData = new FormData(form);\n\
\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + actionUrl, true);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
\n\
        button.classList.add(\"success\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      } else {\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"failed\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      }\n\
    }\n\
  };\n\
\n\
  xhr.send(formData);\n\
}\n\
function loadSSIDsandArtnet() {\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"GET\", url + \"/getData\", true);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4 && xhr.status === 200) {\n\
      var ssids = JSON.parse(xhr.responseText);\n\
\n\
      document.getElementsByName(\"ssid\").forEach(function (input, index) {\n\
        input.value = ssids[index];\n\
      });\n\
    }\n\
  };\n\
\n\
  xhr.send();\n\
  var xhr2 = new XMLHttpRequest();\n\
  xhr2.open(\"GET\", url + \"/getArtnet\", true);\n\
\n\
  xhr2.onreadystatechange = function () {\n\
    if (xhr2.readyState === 4 && xhr2.status === 200) {\n\
      var data = JSON.parse(xhr2.responseText);\n\
\n\
      document.getElementsByName(\"address\")[0].value = data[0];\n\
      document.getElementsByName(\"univers\")[0].value = data[1];\n\
      document.getElementsByName(\"shortname\")[0].value = data[2];\n\
      document.getElementsByName(\"longname\")[0].value = data[3];\n\
      document.title = \"ESP-Nebel \"+data[3];\n\
      var radioButtons = document.getElementsByName(\"channelMode\");\n\
      for (var i = 0; i < radioButtons.length; i++) {\n\
        if (radioButtons[i].value === data[4]) {\n\
          radioButtons[i].checked = true;\n\
          break;\n\
        }\n\
      }\n\
    }\n\
  };\n\
  xhr2.send();\n\
}\n\
function checkConnection() {\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"GET\", url + \"/ping\", true);\n\
  xhr.timeout = 3000;\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        document.getElementById(\"connectionStatus\").innerHTML =\n\
          \"Connected to API: OK\";\n\
        document.getElementById(\"connectionStatus\").classList.remove(\"bad\");\n\
        document.getElementById(\"connectionStatus\").classList.add(\"good\");\n\
        var data = JSON.parse(xhr.responseText);\n\
\n\
        if (data[0] === \"1\") {\n\
          var element = document.getElementById(\"artnet\");\n\
          element.classList.add(\"disabled\");\n\
          var artnetInputs = element.getElementsByTagName(\"input\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = true;\n\
          }\n\
          var artnetInputs = element.getElementsByTagName(\"button\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = true;\n\
          }\n\
        } else {\n\
          var element = document.getElementById(\"artnet\");\n\
          element.classList.remove(\"disabled\");\n\
          var artnetInputs = element.getElementsByTagName(\"input\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = false;\n\
          }\n\
          var artnetInputs = element.getElementsByTagName(\"button\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = false;\n\
          }\n\
        }\n\
        if (data[1] === \"1\") {\n\
          var element = document.getElementById(\"control\");\n\
          element.classList.add(\"disabled\");\n\
          var artnetInputs = element.getElementsByTagName(\"input\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = true;\n\
          }\n\
          var artnetInputs = element.getElementsByTagName(\"button\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = true;\n\
          }\n\
        } else {\n\
          var element = document.getElementById(\"control\");\n\
          element.classList.remove(\"disabled\");\n\
          var artnetInputs = element.getElementsByTagName(\"input\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = false;\n\
          }\n\
          var artnetInputs = element.getElementsByTagName(\"button\");\n\
          for (var i = 0; i < artnetInputs.length; i++) {\n\
            artnetInputs[i].disabled = false;\n\
          }\n\
        }\n\
      } else {\n\
        // Connection failed\n\
        document.getElementById(\"connectionStatus\").innerHTML =\n\
          \"Unable to connect to API\";\n\
        document.getElementById(\"connectionStatus\").classList.remove(\"good\");\n\
        document.getElementById(\"connectionStatus\").classList.add(\"bad\");\n\
        \n\
      }\n\
    }\n\
  };\n\
\n\
  xhr.send();\n\
}\n\
window.onload = function () {\n\
  checkConnection();\n\
  loadSSIDsandArtnet();\n\
};\n\
setInterval(function () {\n\
  checkConnection();\n\
}, 10000);\n\
const url = \"\";\n\
document.addEventListener(\"keydown\", function (event) {\n\
  if (event.key === \"F5\") {\n\
    console.log(\"F5 key pressed\");\n\
    loadSSIDsandArtnet();\n\
    event.preventDefault();\n\
  }\n\
});\n\
function resetState(element){\n\
  element.classList.remove(\"success\");\n\
  element.classList.remove(\"failed\");\n\
  element.classList.remove(\"sending\");\n\
}\n\
\n\
"

#endif // main_js_H
