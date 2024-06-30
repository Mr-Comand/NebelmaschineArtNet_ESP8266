
#ifndef index_html_H
#define index_html_H

#define index_html_code "<!DOCTYPE html>\n\
<html>\n\
\n\
<head>\n\
    <link rel=\"stylesheet\" href=\"main.css\">\n\
</head>\n\
\n\
<body>\n\
    <div>\n\
        <div id=\"connectionStatus\" class=\"bad\">\n\
            Connecting to API...\n\
        </div>\n\
        <div id=\"main\">\n\
            <div id=\"head\">\n\
                <h1>TechnikFLG Fog machine</h1>\n\
                <h3>Fog machine configuration Page</h3>\n\
            </div>\n\
            <div id=\"content\">\n\
                <input class=\"button reload\" type=\"button\" value=\"Reload\" onclick=\"loadSSIDsandArtnet()\">\n\
                <div class=\"config\">\n\
                    <b>WiFi Settings</b>\n\
                    <span></span>\n\
                    <div class=\"wlan\" id=\"Wlan1\">\n\
                        <span>WLAN 1</span>\n\
                        <form id=\"wlanForm1\">\n\
                            <input type=\"text\" class=\"input\" name=\"ssid\" maxlength=\"32\" placeholder=\"Wlan SSID\">\n\
                            <input type=\"password\" class=\"input\" name=\"pwd\" maxlength=\"63\" placeholder=\"Password\">\n\
                            <input class=\"button save\" type=\"button\" value=\"Save\"\n\
                                onclick=\"saveConfig('wlanForm1', '/wlan1')\">\n\
                        </form>\n\
                    </div>\n\
                    <div class=\"wlan\" id=\"Wlan2\">\n\
                        <span>WLAN 2</span>\n\
                        <form id=\"wlanForm2\">\n\
                            <input type=\"text\" class=\"input\" name=\"ssid\" maxlength=\"32\" placeholder=\"Wlan SSID\">\n\
                            <input type=\"password\" class=\"input\" name=\"pwd\" maxlength=\"63\" placeholder=\"Password\">\n\
                            <input class=\"button save\" type=\"button\" value=\"Save\"\n\
                                onclick=\"saveConfig('wlanForm2', '/wlan2')\">\n\
                        </form>\n\
                    </div>\n\
                    <div class=\"wlan\" id=\"Wlan3\">\n\
                        <span>WLAN 3</span>\n\
                        <form id=\"wlanForm3\">\n\
                            <input type=\"text\" class=\"input\" name=\"ssid\" maxlength=\"32\" placeholder=\"Wlan SSID\">\n\
                            <input type=\"password\" class=\"input\" name=\"pwd\" maxlength=\"63\" placeholder=\"Password\">\n\
                            <input class=\"button save\" type=\"button\" value=\"Save\"\n\
                                onclick=\"saveConfig('wlanForm3', '/wlan3')\">\n\
                        </form>\n\
                    </div>\n\
                    <div class=\"wlan\" id=\"ap\">\n\
                        <span>Access Point</span>\n\
                        <form id=\"apForm\">\n\
                            <input type=\"text\" class=\"input\" name=\"ssid\" maxlength=\"32\" placeholder=\"AP SSID\">\n\
                            <input type=\"password\" class=\"input\" name=\"pwd\" maxlength=\"63\" placeholder=\"Password\">\n\
                            <input class=\"button save\" type=\"button\" value=\"Save\" onclick=\"saveConfig('apForm', '/ap')\">\n\
                        </form>\n\
                    </div>\n\
                </div>\n\
                <div class=\"artnetconfig\">\n\
                    <div id=\"artnet\">\n\
                        <b>Artnet settings</b>\n\
                        <form id=\"artnetForm\">\n\
                            <span>\n\
                                <label for=\"univers\">Universe:</label>\n\
                                <input type=\"number\" class=\"input\" name=\"univers\" id=\"univers\" max=\"254\" min=\"0\"\n\
                                    placeholder=\"Universe\">\n\
                            </span>\n\
                            <span>\n\
                                <label for=\"address\">Address:</label>\n\
                                <input type=\"number\" class=\"input\" name=\"address\" id=\"address\" max=\"511\" min=\"0\"\n\
                                    placeholder=\"Address\">\n\
                            </span>\n\
                            <span>\n\
                                <label for=\"shortname\">Shortname:</label>\n\
                                <input type=\"text\" class=\"input\" name=\"shortname\" id=\"shortname\" maxlength=\"18\"\n\
                                    placeholder=\"Shortname\">\n\
                            </span>\n\
                            <span>\n\
                                <label for=\"longname\">Longname:</label>\n\
                                <input type=\"text\" class=\"input\" name=\"longname\" id=\"longname\" maxlength=\"64\"\n\
                                    placeholder=\"Longname\">\n\
                            </span>\n\
                            <span>\n\
                                <label>\n\
                                    <input type=\"radio\" id=\"1ch\" name=\"channelMode\" value=\"1\" checked>\n\
                                    <div class=\"box\">\n\
                                        <span>1 Channel</span>\n\
                                    </div>\n\
                                </label>\n\
                                <label>\n\
                                    <input type=\"radio\" id=\"1ch\" name=\"channelMode\" value=\"2\">\n\
                                    <div class=\"box\">\n\
                                        <span>2 Channel</span>\n\
                                    </div>\n\
                                </label>\n\
                                <label>\n\
                                    <input type=\"radio\" id=\"1ch\" name=\"channelMode\" value=\"3\">\n\
                                    <div class=\"box\">\n\
                                        <span>3 Channel</span>\n\
                                    </div>\n\
                                </label>\n\
                            </span>\n\
\n\
                            <input class=\"button save\" type=\"button\" value=\"Save\" onclick=\"saveArtnet(this)\">\n\
                        </form>\n\
\n\
                    </div>\n\
                </div>\n\
                <div id=\"control\">\n\
                    <div id=\"timer\">\n\
                        <h3>Direkte Kontrolle</h3>\n\
                        <input type=\"range\" min=\"0.1\" max=\"5\" value=\"1\" step=\"0.1\" class=\"slider\" id=\"timeSlider\">\n\
                        <p>Nebeldauer: <span id=\"selectedTime\">1</span> Sekunden</p>\n\
                        <button class=\"button\" onclick=\"sendTimer(this)\">Nebeln</button>\n\
                        <button class=\"button\" onclick=\"stopFog(this)\">Stopp</button>\n\
                    </div>\n\
                    <div id=\"interval\">\n\
                        <h3>Intervall Kontrolle. Status: <span id=\"intervalStatus\">OFF</span></h3> \n\
                        <input type=\"range\" min=\"0.1\" max=\"1800\" value=\"1\" step=\"1\" class=\"slider\" id=\"periodSlider\">\n\
                        <p>Periodendauer: <span id=\"selectedPeriod\">1</span></p>\n\
                        <input type=\"range\" min=\"0.1\" max=\"100\" value=\"1\" step=\"0.1\" class=\"slider\" id=\"dutyCycleSlider\">\n\
                        <p>Nebel Anteil: <span id=\"selectedDutyCycle\">1</span> %</p>\n\
                        <button class=\"button\" onclick=\"activateInterval(this)\">Aktivie Intervall</button>\n\
                        <button class=\"button\" onclick=\"stopFog(this)\">Stopp Intervall</button>\n\
                    </div>\n\
                </div>\n\
            </div>\n\
        </div>\n\
    </div>\n\
    <script type=\"text/javascript\" src=\"main.js\"></script>\n\
</body>\n\
\n\
</html>"

#endif // index_html_H
