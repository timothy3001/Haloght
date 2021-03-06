#include <Arduino.h>

const char pageWiFiSetupServerRoot[] PROGMEM = R"=====(
<!DOCTYPE html>
<head>
  <link
    rel="stylesheet"
    href="/bootstrap.min.css"
  />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta charset="utf-8" />
</head>

<body>
  <div class="container">
    <div class="page-header mt-4">
      <h1>WiFi setup</h1>
      <hr />
    </div>
    <div class="row">
      <div class="col-sm-6">
        <form class="form-horizontal" action="/config" method="post">
          <div class="form-group">
            <label class="control-label col-sm-3" for="ssid">SSID</label>
            <div class="col-sm-9">
              <input
                type="text"
                class="form-control"
                id="ssid"
                name="ssid"
                placeholder="Enter SSID..."
              />
            </div>
          </div>
          <div class="form-group">
            <label class="control-label col-sm-3" for="password"
              >Password</label
            >
            <div class="col-sm-9">
              <input
                type="password"
                class="form-control"
                id="password"
                name="password"
                placeholder="Enter password..."
              />
            </div>
          </div>
          <div class="form-group">
            <div class="col-sm-offset-3 col-sm-9">
              <button type="submit" class="btn btn-default">Submit</button>
            </div>
          </div>
        </form>
      </div>
    </div>
  </div>
</body>


)=====";
