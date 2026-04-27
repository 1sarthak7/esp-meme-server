#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

// AP (your fake WiFi)
const char* ap_ssid = "Room104_FreeWiFi 😏";
const char* ap_password = "";

// Your real WiFi (for internet)
const char* sta_ssid = "Room no.104 network";
const char* sta_password = "45544554";

ESP8266WebServer server(80);
DNSServer dns;

void handlePortal() {

  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Free WiFi</title>

<style>
* { margin: 0; padding: 0; box-sizing: border-box; }

body {
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
  background: #f0f2f5;
  min-height: 100vh;
  display: flex;
  align-items: center;
  justify-content: center;
}

.card {
  background: #fff;
  border-radius: 16px;
  box-shadow: 0 4px 24px rgba(0,0,0,0.09);
  padding: 48px 36px;
  width: 90%;
  max-width: 340px;
  text-align: center;
}

.wifi-icon { margin-bottom: 20px; }
.wifi-icon svg { width: 64px; height: 64px; }

h1 {
  font-size: 1.4rem;
  font-weight: 700;
  color: #111;
  margin-bottom: 6px;
}

.sub {
  font-size: 0.875rem;
  color: #888;
  margin-bottom: 32px;
}

button {
  width: 100%;
  padding: 14px;
  background: #0070f3;
  color: #fff;
  border: none;
  border-radius: 10px;
  font-size: 1rem;
  font-weight: 600;
  cursor: pointer;
  transition: background 0.15s, transform 0.1s;
}

button:hover { background: #005ecc; }
button:active { transform: scale(0.98); }

#prank {
  display: none;
  position: fixed;
  inset: 0;
  background: #000;
  z-index: 9999;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  text-align: center;
  padding: 20px;
}

#prank.show { display: flex; }

#prank img {
  max-width: min(88vw, 420px);
  max-height: 62vh;
  border-radius: 14px;
  object-fit: contain;
}

#prank-text {
  color: #fff;
  font-size: clamp(1.3rem, 5vw, 2rem);
  font-weight: 800;
  margin-top: 28px;
}
</style>

</head>
<body>

<div class="card">
  <div class="wifi-icon">
    <svg viewBox="0 0 64 64" fill="none">
      <circle cx="32" cy="32" r="32" fill="#EBF4FF"/>
      <path d="M32 42a4 4 0 1 1 0 8 4 4 0 0 1 0-8z" fill="#0070f3"/>
      <path d="M21 33a16 16 0 0 1 22 0" stroke="#0070f3" stroke-width="3" stroke-linecap="round"/>
      <path d="M13 25a27 27 0 0 1 38 0" stroke="#0070f3" stroke-width="3" stroke-linecap="round" opacity="0.35"/>
    </svg>
  </div>

  <h1>Free WiFi Available</h1>
  <p class="sub">Tap below to get instant access</p>
  <button onclick="triggerPrank()">🔓 Get WiFi</button>
</div>

<div id="prank">
  <img src="https://cdn.jsdelivr.net/gh/1sarthak7/esp-meme-server/monkey.jpg" />
  <p id="prank-text">😂 No WiFi for you!<br>Stop stealing! 🙅</p>
</div>

<audio id="sfx" preload="auto">
  <source src="https://cdn.jsdelivr.net/gh/1sarthak7/esp-meme-server/meme.mp3" type="audio/mpeg">
</audio>

<script>
function triggerPrank() {
  document.getElementById('prank').classList.add('show');

  let audio = document.getElementById('sfx');
  audio.play().catch(e => console.log(e));
}
</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

  // Start fake WiFi
  WiFi.softAP(ap_ssid, ap_password);

  // Connect to real WiFi
  WiFi.begin(sta_ssid, sta_password);

  Serial.print("Connecting to internet");

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
  } else {
    Serial.println("\nFailed to connect!");
  }

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  dns.start(53, "*", WiFi.softAPIP());

  server.on("/", handlePortal);
  server.onNotFound(handlePortal);

  server.begin();
}

void loop() {
  dns.processNextRequest();
  server.handleClient();
}
