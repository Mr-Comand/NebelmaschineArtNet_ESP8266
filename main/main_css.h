
#ifndef main_css_H
#define main_css_H

#define main_css_code "body {\n\
    font-family: Roboto, sans-serif;\n\
    margin: 0;\n\
    padding: 0;\n\
    background-color: #121212;\n\
    color: #ffffff;\n\
    padding-top: 22px;\n\
}\n\
\n\
#main {\n\
    margin: 1%;\n\
}\n\
\n\
header {\n\
    background-color: #333;\n\
    color: white;\n\
    padding: 10px 0;\n\
    text-align: center;\n\
}\n\
\n\
input[type=button], input[type=submit], button {\n\
    background-color: #3e3e3e;\n\
    box-shadow: 0 0 #0003,0 0 #00000024,0 0 #0000001f;\n\
    border: 1px solid #5c5c5c;\n\
    padding-block: 1px;\n\
    padding-inline: 6px;\n\
    border-radius: 4px;\n\
    cursor: pointer;\n\
    color: white;\n\
    padding: 0.5em;\n\
    padding-left: 1em;\n\
    padding-right: 1em;\n\
}\n\
input[type=button]:hover, input[type=submit]:hover, button {\n\
    background-color: #464646;\n\
    transition-duration: .3s;\n\
}\n\
input[type=text], input[type=password], input[type=number] {\n\
    border: 1px solid #ffffff4d;\n\
}\n\
input[type=text]:hover, input[type=password]:hover, input[type=number]:hover {\n\
    border-color: transparent;\n\
    box-shadow: 0 0 0 2px white;\n\
    transition-duration: .3s;\n\
}\n\
input[type=radio] {\n\
    display: none;\n\
    &:checked {\n\
        + .box {\n\
          background-color: #272727;\n\
          box-shadow: 0 0 0 2px white; \n\
        }\n\
    }\n\
}\n\
.box {\n\
    width: 100px;\n\
    height: 25px;\n\
    background-color: #3e3e3e;\n\
    display: inline-block;\n\
    text-align: center;\n\
    cursor: pointer;\n\
    position: relative;\n\
    border-radius: 4px;\n\
    margin-right: 1em;\n\
    span {\n\
      padding: 0.5em;\n\
      font-size: smaller;\n\
      display: block;\n\
    }\n\
  }\n\
.box>span {\n\
    vertical-align: middle;\n\
}\n\
\n\
#control {\n\
    margin-top: 4em;\n\
}\n\
\n\
.input {\n\
    width: 95%;\n\
    padding: 10px;\n\
    margin: 10px 0;\n\
    border-radius: 5px;\n\
    border: 1px solid #ccc;\n\
    background-color: #0f0f0f;\n\
    color: #f0f0f0;\n\
\n\
}\n\
\n\
.save {\n\
    width: 15%;\n\
}\n\
\n\
.config {\n\
    margin-bottom: 4em;\n\
    margin-top: 4em;\n\
}\n\
\n\
#artnet>b {\n\
    display: block;\n\
    margin-bottom: 20px;\n\
}\n\
\n\
\n\
.button:hover :not(.sending,.failed){\n\
    background-color: #45a049;\n\
}\n\
@media (orientation: landscape) {\n\
.config, #artnetForm {\n\
    display: grid;\n\
    grid-template-columns: repeat(2, 1fr);\n\
    gap: 20px;\n\
    row-gap: 20px;\n\
}\n\
}\n\
\n\
\n\
\n\
\n\
#connectionStatus{\n\
    width: 100vw;\n\
    background-color: yellow;\n\
    height: 1.5em;\n\
    text-align: center;\n\
    font-size: smaller;\n\
    display: flex;\n\
    justify-content: space-around;\n\
    align-items: center;\n\
    padding: 2px;\n\
    \n\
        \n\
        position: fixed;\n\
        top: 0px;\n\
        \n\
}\n\
#connectionStatus.bad{\n\
    background-color: red;\n\
    color: rgb(109, 1, 1);\n\
}\n\
#connectionStatus.good{\n\
    background-color: green;\n\
    color: greenyellow;\n\
}\n\
\n\
.sending{\n\
    background-color: orange !important;\n\
}\n\
.failed{\n\
    background-color: red !important;\n\
}\n\
.success{\n\
    background-color: green !important;\n\
}\n\
\n\
.disabled{\n\
    input, button, .save, .box{\n\
        color: #2f2f2f;\n\
        cursor: not-allowed !important;\n\
    }\n\
    input[type=\"text\"]:hover, input[type=\"password\"]:hover, input[type=\"number\"]:hover {\n\
        border-color: transparent;\n\
        box-shadow: none;\n\
        border: 1px solid #5c5c5c;\n\
        transition-duration: .3s;\n\
        cursor: not-allowed !important;\n\
      }\n\
}"

#endif // main_css_H
