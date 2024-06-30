
#ifndef main_js_H
#define main_js_H

#define main_js_code "var intervalActive = false;\n\
var channelMode = 0;\n\
function stopFog(button) {\n\
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
  xhr.send(formData);\n\
  var period = Math.ceil(document.getElementById(\"periodSlider\").value *1000);\n\
  var dutyCycle = Math.ceil(document.getElementById(\"dutyCycleSlider\").value*2.55);\n\
  var xhr2 = new XMLHttpRequest();\n\
  xhr2.open(\"POST\", url + \"/interval\", true);\n\
  var formData2 = new FormData();\n\
  formData2.append(\"period\", period);\n\
  formData2.append(\"dutyCycle\", dutyCycle);\n\
  formData2.append(\"active\", 0);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"success\");\n\
        intervalActive=(xhr.responseText==\"1\");\n\
        updateIntervalStatus(xhr.responseText==\"1\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      } else {\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"failed\");\n\
        setTimeout(() => { resetState(button); }, 3000);\n\
      }\n\
    }\n\
  };\n\
\n\
  xhr2.send(formData2);\n\
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
\n\
function activateInterval(button) {\n\
  if (channelMode!=3) return;\n\
  button.classList.remove(\"success\");\n\
  button.classList.remove(\"failed\");\n\
  button.classList.add(\"sending\");\n\
  var period = Math.ceil(document.getElementById(\"periodSlider\").value *1000);\n\
  var dutyCycle = Math.ceil(document.getElementById(\"dutyCycleSlider\").value*2.55);\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/interval\", true);\n\
\n\
  var formData = new FormData();\n\
  formData.append(\"period\", period);\n\
  formData.append(\"dutyCycle\", dutyCycle);\n\
  formData.append(\"active\", 1);\n\
\n\
  xhr.onreadystatechange = function () {\n\
    if (xhr.readyState === 4) {\n\
      if (xhr.status === 200) {\n\
        console.log(xhr.responseText);\n\
        button.classList.remove(\"sending\");\n\
        button.classList.add(\"success\");\n\
        intervalActive=(xhr.responseText==\"1\");\n\
        updateIntervalStatus(xhr.responseText==\"1\");\n\
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
function updatePeriodSlider(slider) {\n\
  const selectedPeriod = slider.value;\n\
\n\
  let result;\n\
  if (selectedPeriod < 60) {\n\
    result = `${selectedPeriod} seconds`;\n\
    slider.step = 0.1; // Step by 1 second\n\
  } else if (selectedPeriod < 3600) {\n\
    let minutes = (selectedPeriod / 60).toFixed(2);\n\
    result = `${minutes} minutes`;\n\
    slider.step = 6; // Step by 1 minute\n\
  } else if (selectedPeriod < 86400) {\n\
    let hours = (selectedPeriod / 3600).toFixed(2);\n\
    result = `${hours} hours`;\n\
    slider.step = 360; // Step by 1 hour\n\
  } else {\n\
    let days = (selectedPeriod / 86400).toFixed(2);\n\
    slider.step = 8640; // Step by 1 day\n\
    result = `${days} days`;\n\
  }\n\
\n\
  return result;\n\
}\n\
\n\
document.getElementById(\"periodSlider\").addEventListener(\"input\", function () {\n\
  disply_val = updatePeriodSlider(document.getElementById(\"periodSlider\"))\n\
  document.getElementById(\"selectedPeriod\").innerText = disply_val;\n\
  if (channelMode!=3) return;\n\
  var period = Math.ceil(document.getElementById(\"periodSlider\").value *1000);\n\
  var dutyCycle = Math.ceil(document.getElementById(\"dutyCycleSlider\").value*2.55);\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/interval\", true);\n\
  var formData = new FormData();\n\
  formData.append(\"period\", period);\n\
  formData.append(\"dutyCycle\", dutyCycle);\n\
  formData.append(\"active\", intervalActive*1);\n\
  xhr.send(formData);\n\
});\n\
\n\
\n\
document.getElementById(\"dutyCycleSlider\").addEventListener(\"input\", function () {\n\
  var selectedTime = document.getElementById(\"dutyCycleSlider\").value;\n\
  document.getElementById(\"selectedDutyCycle\").innerText = selectedTime;\n\
  if (channelMode!=3) return;\n\
  var period = Math.ceil(document.getElementById(\"periodSlider\").value *1000);\n\
  var dutyCycle = Math.ceil(document.getElementById(\"dutyCycleSlider\").value*2.55);\n\
  var xhr = new XMLHttpRequest();\n\
  xhr.open(\"POST\", url + \"/interval\", true);\n\
  var formData = new FormData();\n\
  formData.append(\"period\", period);\n\
  formData.append(\"dutyCycle\", dutyCycle);\n\
  formData.append(\"active\", intervalActive*1);\n\
  xhr.send(formData);\n\
});\n\
\n\
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
        channelMode=formData.get(\"channelMode\")\n\
        if (channelMode==3){\n\
          var intervalInputs =document.querySelectorAll(\"#interval button, #interval input\");\n\
          for (var i = 0; i < intervalInputs.length; i++) {\n\
            intervalInputs[i].disabled = false;\n\
            intervalInputs[i].classList.remove(\"disabled\");\n\
          }\n\
        }else{\n\
          var intervalInputs = document.querySelectorAll(\"#interval button, #interval input\");\n\
          for (var i = 0; i < intervalInputs.length; i++) {\n\
            intervalInputs[i].disabled = true;\n\
            intervalInputs[i].classList.add(\"disabled\");\n\
          }\n\
        }\n\
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
      document.getElementsByName(\"universe\")[0].value = data[1];\n\
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
      channelMode = data[4];\n\
      if (channelMode==3){\n\
        var intervalInputs = document.querySelectorAll(\"#interval button, #interval input\");\n\
        for (var i = 0; i < intervalInputs.length; i++) {\n\
          intervalInputs[i].disabled = false;\n\
          intervalInputs[i].classList.remove(\"disabled\");\n\
        }\n\
      }else{\n\
        var intervalInputs = document.querySelectorAll(\"#interval button, #interval input\");\n\
        for (var i = 0; i < intervalInputs.length; i++) {\n\
          intervalInputs[i].disabled = true;\n\
          intervalInputs[i].classList.add(\"disabled\");\n\
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
        document.getElementById(\"periodSlider\").value =  Math.ceil(data[3]/1000);\n\
        document.getElementById(\"dutyCycleSlider\").value =  Math.ceil(data[4]/2.55); \n\
        disply_val = updatePeriodSlider(document.getElementById(\"periodSlider\"))\n\
        document.getElementById(\"selectedPeriod\").innerText = disply_val;\n\
        document.getElementById(\"selectedDutyCycle\").innerText = Math.ceil(data[4]/2.55); \n\
        updateIntervalStatus(data[2]==\"1\")\n\
        if (channelMode==3){\n\
          var intervalInputs = document.querySelectorAll(\"#interval button, #interval input\");\n\
          for (var i = 0; i < intervalInputs.length; i++) {\n\
            intervalInputs[i].disabled = false;\n\
            intervalInputs[i].classList.remove(\"disabled\");\n\
          }\n\
        }else{\n\
          var intervalInputs = document.querySelectorAll(\"#interval button, #interval input\");\n\
          for (var i = 0; i < intervalInputs.length; i++) {\n\
            intervalInputs[i].disabled = true;\n\
            intervalInputs[i].classList.add(\"disabled\");\n\
          }\n\
        }\n\
\n\
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
const url = \"http://192.168.178.75\";\n\
document.addEventListener(\"keydown\", function (event) {\n\
  if (event.key === \"F5\") {\n\
    console.log(\"F5 key pressed\");\n\
    checkConnection();\n\
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
\n\
function updateIntervalStatus(status){\n\
  if (status){\n\
    document.getElementById(\"intervalStatus\").innerText = \"ON\"\n\
  }\n\
  else{\n\
    document.getElementById(\"intervalStatus\").innerText = \"OFF\"\n\
  }\n\
}"

#endif // main_js_H
