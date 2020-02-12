#include <ESP8266WiFi.h>
#define RELAY 0 // relay connected to  GPIO0

WiFiServer server(80);
IPAddress  apIP(10, 10, 10, 1);   // Private network address: local & gateway
int value = LOW;

void setup(){

  Serial.begin(115200);
  Serial.println();

  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, LOW);
  Serial.println("Diagnostic: RELAY ON");

  Serial.print("Use this URL to connect: ");
  Serial.print(WiFi.softAPIP());
  Serial.println("/");

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)); // subnet FF FF FF 00

  Serial.print("Setting AP... ");
  boolean result = WiFi.softAP("Forme_52DD4BS", "forme52dd4bs");
  if(result == true){
    Serial.println("Ready");
  }
  else{
    Serial.println("Failed!");
  }
  server.begin();
}

void loop(){
  unsigned char number_client;
  struct station_info *stat_info;
  
  struct ipv4_addr *IPaddress;
  IPAddress address;
  int i=1;
  
  if(WiFi.softAPgetStationNum()!=0){

    WiFiClient client = server.available();

    if (!client) 
    {
      return;
    }
  
    // Wait until the client sends some data
    Serial.println("Serial: Client connected.");
    while(!client.available())
    {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
  
    // Match the request
    if (request.indexOf("/RELAY=ON") != -1)  
    {
      digitalWrite(RELAY,LOW);
      value = LOW;
      Serial.println("Diagnostic: RELAY ON");
    }
    if (request.indexOf("/RELAY=OFF") != -1)  
    {
      digitalWrite(RELAY,HIGH);
      value = HIGH;
      Serial.println("Diagnostic: RELAY OFF");
    }
    
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // this is a must
    client.println("<!DOCTYPE HTML>");
    client.println("<html style=\"margin:0;padding:0;height:100%;\">");
    client.println("");
    client.println("<head style=\"margin: 0;");
    client.println("  padding: 0;\">");
    client.println("    <title style=\"margin: 0;");
    client.println("  padding: 0;\">Forme Web Diagnostics</title>");
    client.println("    <link rel=\"stylesheet\" type=\"text/css\" href=\"style/style.css\" title=\"style\" style=\"margin: 0;");
    client.println("  padding: 0;\">");
    client.println("</head>");
    client.println("");
    client.println("<body style=\"margin:0;padding:0;font:normal .80em 'trebuchet ms', arial, sans-serif;background: #000000; url(background.png) repeat;color:#000;\">");
    client.println("    <div id=\"main\" style=\"margin:0;padding:0;margin-left:auto;margin-right:auto;\">");
    client.println("        <div id=\"header\" style=\"margin:0;padding:0;background:transparent;height:202px;\">");
    client.println("            <div id=\"logo\" style=\"margin:0;padding:0;margin-left:auto;margin-right:auto;width:898px;position:relative;height:148px;border-bottom:2px solid #FFF;\">");
    client.println("                <div id=\"logo_text\" style=\"margin:0;padding:0;position:absolute;top:20px;left:0;\">");
    client.println("                    <h1 style=\"margin:0;padding:22px 0 0 0;font:normal 300% 'century gothic', arial, sans-serif;color:#FFF;border-bottom:0;text-transform:none;letter-spacing:-1px;text-decoration:none;\">Forme Charger Companion - Prototype MK1</h1>");
    client.println("                    <h2 style=\"margin:0;padding:4px 0 0 0;font:normal 300% 'century gothic', arial, sans-serif;color:#FFF;border-bottom:0;text-transform:none;font-size:100%;\">Onboard Diagnostics</h2>");
    client.println("                </div>");
    client.println("            </div>");
    client.println("            <div id=\"menubar\" style=\"margin:0;padding:0;margin-left:auto;margin-right:auto;width:898px;height:52px;background:#000;\">");
    client.println("                <ul id=\"menu\" style=\"margin:0;padding:0;float:left;\">");
    client.println("                    <li class=\"selected\" style=\"margin:0;padding:0;list-style-type:circle;float:left;list-style:none;\"><a href=\"/status\" style=\"margin:10px 0 0 10px;padding:9px 26px 6px 26px;outline:none;text-decoration:none;color:#FFF;letter-spacing:0.1em;font:normal 100% arial, sans-serif;display:block;float:left;height:17px;text-align:center;text-transform:uppercase;background:transparent url(transparent_light.png) repeat;\">System Status</a></li>");
    client.println("                    <li style=\"margin:0;padding:0;list-style-type:circle;float:left;list-style:none;\"><a href=\"/devices\" style=\"margin:10px 0 0 10px;padding:9px 26px 6px 26px;outline:none;text-decoration:none;color:#FFF;letter-spacing:0.1em;font:normal 100% arial, sans-serif;display:block;float:left;height:17px;text-align:center;text-transform:uppercase;background:transparent;\">Connected Devices</a></li>");
    client.println("                    <li style=\"margin:0;padding:0;list-style-type:circle;float:left;list-style:none;\"><a href=\"/control\" style=\"margin:10px 0 0 10px;padding:9px 26px 6px 26px;outline:none;text-decoration:none;color:#FFF;letter-spacing:0.1em;font:normal 100% arial, sans-serif;display:block;float:left;height:17px;text-align:center;text-transform:uppercase;background:transparent;\">Manual Control</a></li>");
    client.println("                    <li style=\"margin:0;padding:0;list-style-type:circle;float:left;list-style:none;\"><a href=\"/reset\" style=\"margin:10px 0 0 10px;padding:9px 26px 6px 26px;outline:none;text-decoration:none;color:#FFF;letter-spacing:0.1em;font:normal 100% arial, sans-serif;display:block;float:left;height:17px;text-align:center;text-transform:uppercase;background:transparent;\">Reset</a></li>");
    client.println("                    <li style=\"margin:0;padding:0;list-style-type:circle;float:left;list-style:none;\"><a href=\"about\" style=\"margin:10px 0 0 10px;padding:9px 26px 6px 26px;outline:none;text-decoration:none;color:#FFF;letter-spacing:0.1em;font:normal 100% arial, sans-serif;display:block;float:left;height:17px;text-align:center;text-transform:uppercase;background:transparent;\">About</a></li>");
    client.println("                </ul>");
    client.println("            </div>");
    client.println("        </div>");

    if(request.indexOf("/RELAY=ON") != -1 || request.indexOf("/RELAY=OFF") != -1 || request.indexOf("/status") != -1){
      client.println("        <div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("            <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">General status:</h3>");
      client.println("                <table style=\"width:100%;margin:10px 0 30px 0;padding:0;\">");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">System Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">OK</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Controller Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Normal</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Relay Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.print("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">");
      
      if(value == LOW)
        client.print("ON");
      else
        client.print("OFF");
      
      client.println("</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Charging Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">");
      
      if(value == LOW)
        client.print("Plugged in, charging");
      else
        client.print("Not charging");

      client.println("</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("<tr style=\"margin: 0; padding: 0;\">");
      client.println("<td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("<h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Output Voltage: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">5V</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Diagnostic IP: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">10.10.10.1 DHCP</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                </table>");
      client.println("            </div>");
      client.println("        </div>");
    }

    else if(request.indexOf("/control") != -1){
      client.println("<div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("        <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">System override:</h3>");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">This menu allows you to manually control the relay without the companion application installed on your phone.</h4>");
      client.println("            <button onclick=\"window.location.href = '/RELAY=ON';\" style=\"height:50px;width:100px");
      client.println("\">Turn on Relay</button><br><br>");
      client.println("<button onclick=\"window.location.href = '/RELAY=OFF';\" style=\"height:50px;width:100px");
      client.println("\">Turn off Relay</button>");
      client.println("        </div>");
      client.println("");
      client.println("    </div>");
    }

    else if(request.indexOf("/RESETForme") != -1){
      client.println("<div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("        <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Now restarting, wait for upto 30 seconds...</h4>");
      Serial.println("Now restarting, wait for upto 30 seconds...");
      client.println("        </div>");
      client.println("");
      client.println("    </div>");
      client.println("    </div>");
      client.println("</body>");
      client.println("");
      client.println("</html>");
      ESP.reset();
    }


    else if(request.indexOf("/reset") != -1){
      client.println("<div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("        <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">Reset Forme:</h3>");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">This action will restart your Forme. Restart will take upto 10 seconds. Continue?</h4>");
      client.println("            <button onclick=\"window.location.href = '/RESETForme';\" style=\"height:50px;width:100px");
      client.println("\">Restart Forme</button><br><br>");
      client.println("        </div>");
      client.println("");
      client.println("    </div>");
    }
    else if(request.indexOf("/devices") != -1){
      number_client= wifi_softap_get_station_num();
      stat_info = wifi_softap_get_station_info();


      client.println("        <div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("            <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">Connected clients:</h3>");
      client.println("                <table style=\"width:100%;margin:10px 0 30px 0;padding:0;\">");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\"><b>IP Address</b></h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\"><b>MAC Address</b></h4>");
      client.println("                        </td>");
      client.println("                    </tr>");

      while (stat_info != NULL) {
    
        IPaddress = &stat_info->ip;
        address = IPaddress->addr;

        client.println("                    <tr style=\"margin: 0;");
        client.println("  padding: 0;\">");
        client.println("                        <th style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
        client.print("                            <h3 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">"); client.print(address); client.println("</h3>");
        client.println("                        </th>");
        client.println("                        <th style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
        client.println("                            <h3 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">");
        client.print(stat_info->bssid[0],HEX);client.print(":");
        client.print(stat_info->bssid[1],HEX);client.print(":");
        client.print(stat_info->bssid[2],HEX);client.print(":");
        client.print(stat_info->bssid[3],HEX);client.print(":");
        client.print(stat_info->bssid[4],HEX);client.print(":");
        client.print(stat_info->bssid[5],HEX);
        client.println("</h3>");
        client.println("                        </th>");
        client.println("                    </tr>");
        
        stat_info = STAILQ_NEXT(stat_info, next);
        i++;
      }
      client.println("                </table>");
      client.println("            </div>");
      client.println("        </div>");
      
    }
    else if(request.indexOf("/about") != -1){
      client.println("<div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("        <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\">");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">About: Forme Charger Companion</h3>");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Prototype MK1</h4>");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Development unit - not for resale</h4>");
      client.println("            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Property of Forme Inc.</h4>");
      client.println("            <br style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("            <p style=\"margin:0;padding:0 0 20px 0;line-height:1.7em;\"><b style=\"margin: 0;");
      client.print("  padding: 0;\">Your Forme's MAC: </b>");client.print(WiFi.macAddress()); client.println("<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Serial number:</b> 52DD4BS</p>");
      client.println("");
      client.println("            <p style=\"margin:0;padding:0 0 20px 0;line-height:1.7em;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Model:</b> ProtoMK1<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Firmware version:</b> 1.0.34<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Diagnostics version:</b> 1.0.5 Stable<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Build info:</b> rah@vmwareesxi-lvmsystem:crosshatch202002121730<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Firmware build date:</b> 12-02-2020 1740 hours GMT+0530<br style=\"margin: 0;");
      client.println("  padding: 0;\"><b style=\"margin: 0;");
      client.println("  padding: 0;\">Firmware install date:</b> 12-02-2020 1749 hours GMT+0530</p>");
      client.println("        </div>");
      client.println("");
      client.println("    </div>");
    }
    else{
      client.println("        <div id=\"site_content\" style=\"margin:0 auto 0 auto;padding:0 24px 20px 20px;margin-left:auto;margin-right:auto;width:854px;overflow:hidden;background:#FFF;\">");
      client.println("            <div id=\"content\" style=\"margin:0;padding:0;text-align:left;float:left;width:595px;\"><br>");
      client.println("            <h3 style=\"margin:0 0 15px 0;padding:15px 0 5px 0;font:normal 175% 'century gothic', arial, sans-serif;color:#000;\">General status:</h3>");
      client.println("                <table style=\"width:100%;margin:10px 0 30px 0;padding:0;\">");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">System Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">OK</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Controller Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Normal</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Relay Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.print("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">");
      
      if(value == LOW)
        client.print("ON");
      else
        client.print("OFF");
      
      client.println("</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Charging Status: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">");
      
      if(value == LOW)
        client.print("Plugged in, charging");
      else
        client.print("Not charging");

      client.println("</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("<tr style=\"margin: 0; padding: 0;\">");
      client.println("<td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("<h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Output Voltage: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">5V</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                    <tr style=\"margin: 0;");
      client.println("  padding: 0;\">");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">Diagnostic IP: </h4>");
      client.println("                        </td>");
      client.println("                        <td style=\"margin:0;padding:7px 4px;background:#F0EFE2;color:#47433F;text-align:left;border-top:1px solid #FFF;\">");
      client.println("                            <h4 style=\"margin:0;padding:0 0 5px 0;font:normal 120% arial, sans-serif;color:#000;\">10.10.10.1 DHCP</h4>");
      client.println("                        </td>");
      client.println("                    </tr>");
      client.println("                </table>");
      client.println("            </div>");
      client.println("        </div>");
    }

   
    client.println("        <div id=\"footer\" style=\"margin:0;padding:24px 0 5px 0;margin-left:auto;margin-right:auto;width:898px;font:normal 100% 'lucida sans unicode', arial, sans-serif;height:33px;text-align:center;background:transparent;color:#FFF;text-transform:uppercase;letter-spacing:0.1em;\">");
    client.println("            Copyright &copy;2020 Forme Inc.<br>Diagnostics version 1.0.5 Stable");
    client.println("        </div>");
    client.println("    </div>");
    client.println("</body>");
    client.println("");
    client.println("</html>");
  
    delay(1);
    Serial.println("Serial: Client disconnected.");
    Serial.println("");
  }
}