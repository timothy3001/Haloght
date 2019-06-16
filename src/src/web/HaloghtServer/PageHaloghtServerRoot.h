#include <Arduino.h>

const char pageHaloghtServerRoot[] PROGMEM = R"=====(
<!DOCTYPE html>
<head>
  <link
    rel="stylesheet"
    href="/bootstrap.min.css"
  />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta charset="utf-8" />
  <script>
    var sendSolidColorButton;
    var solidColorInput;
    var sendFireButton;
    var onOffSwitch;
    var brightnessRangeSlider;

    window.onload = function() {
      sendSolidColorButton = document.getElementById("sendSolidColorButton");
      sendFireButton = document.getElementById("sendFireButton");
      sendWaterButton = document.getElementById("sendWaterButton");
      solidColorInput = document.getElementById("solidColorInput");
      onOffSwitch = document.getElementById("onOffSwitch");
      brightnessRangeSlider = document.getElementById("brightnessRangeSlider");

      updateState();

      sendSolidColorButton.addEventListener("click", () => {
        sendPost("/setSolidColor", "color=" + solidColorInput.value);
      });

      sendFireButton.addEventListener("click", () => {
        sendPost("/sendFire", "");
      });

      sendWaterButton.addEventListener("click", () => {
        sendPost("/sendWater", "");
      });

      onOffSwitch.addEventListener("change", () => {
        sendPost("/onOffState", "on=" + onOffSwitch.checked);
      });

      brightnessRangeSlider.addEventListener("change", () => {
        sendPost(
          "/setBrightness",
          "brightness=" + brightnessRangeSlider.value / 100
        );
      });
    };

    function sendPost(url, data) {
      var req = new XMLHttpRequest();
      req.open("POST", url, true);
      req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      req.send(data);
    }

    function updateState() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          data = JSON.parse(xhttp.responseText);
          brightness = Math.round(data.brightness * 100);

          onOffSwitch.checked = data.turnedOn;
          brightnessRangeSlider.value = brightness;
        }
      };
      xhttp.open("GET", "/state", true);
      xhttp.send();
    }
  </script>
  <style>
    .imgHeaderSolidColor {
      background-image: url("data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+CjxzdmcgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCBtZWV0IiB2aWV3Qm94PSIwIDAgNjQwIDMyMCIgd2lkdGg9IjY0MCIgaGVpZ2h0PSIzMjAiPjxkZWZzPjxwYXRoIGQ9Ik0xMjUuMDEgMzIwTDI0MC4wMSAwTDE5NS4wMSAwTDgwLjAxIDMyMEwxMjUuMDEgMzIwWiIgaWQ9ImcxRm9OQURMaHciPjwvcGF0aD48bGluZWFyR3JhZGllbnQgaWQ9ImdyYWRpZW50YmFOdndBcmJYIiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgeDE9IjE2MC4wMSIgeTE9IjAiIHgyPSIxNjAiIHkyPSIzMjAiPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjOTBmZjAwO3N0b3Atb3BhY2l0eTogMSIgb2Zmc2V0PSIwJSI+PC9zdG9wPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjMDEwMDAwO3N0b3Atb3BhY2l0eTogMCIgb2Zmc2V0PSIxMDAlIj48L3N0b3A+PC9saW5lYXJHcmFkaWVudD48cGF0aCBkPSJNMjA1IDMyMEwzMjAgMEwyNzUgMEwxNjAgMzIwTDIwNSAzMjBaIiBpZD0iYjZLTWZ4OWRCQiI+PC9wYXRoPjxsaW5lYXJHcmFkaWVudCBpZD0iZ3JhZGllbnRhNFU0RWo1Q2JrIiBncmFkaWVudFVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgeDE9IjI0MCIgeTE9IjAiIHgyPSIyNDAiIHkyPSIzMjAiPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjMDBmZmM2O3N0b3Atb3BhY2l0eTogMSIgb2Zmc2V0PSIwJSI+PC9zdG9wPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjMDEwMDAwO3N0b3Atb3BhY2l0eTogMCIgb2Zmc2V0PSIxMDAlIj48L3N0b3A+PC9saW5lYXJHcmFkaWVudD48cGF0aCBkPSJNMjg1LjAxIDMyMEw0MDAgMEwzNTUgMEwyNDAuMDEgMzIwTDI4NS4wMSAzMjBaIiBpZD0iYjF0clIyZmdzRiI+PC9wYXRoPjxsaW5lYXJHcmFkaWVudCBpZD0iZ3JhZGllbnRhWTZZNkEwaE0iIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iMzIwLjAxIiB5MT0iMCIgeDI9IjMyMC4wMSIgeTI9IjMyMCI+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMDQ1ZmY7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMTAwMDA7c3RvcC1vcGFjaXR5OiAwIiBvZmZzZXQ9IjEwMCUiPjwvc3RvcD48L2xpbmVhckdyYWRpZW50PjxwYXRoIGQ9Ik0zNjUgMzIwTDQ4MCAwTDQzNSAwTDMyMCAzMjBMMzY1IDMyMFoiIGlkPSJkMzJKbVgxdTVhIj48L3BhdGg+PGxpbmVhckdyYWRpZW50IGlkPSJncmFkaWVudGI1NFdpcGlydHciIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iNDAwIiB5MT0iMCIgeDI9IjQwMCIgeTI9IjMyMCI+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMGZmZDg7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMTAwMDA7c3RvcC1vcGFjaXR5OiAwIiBvZmZzZXQ9IjEwMCUiPjwvc3RvcD48L2xpbmVhckdyYWRpZW50PjxwYXRoIGQ9Ik00NDUuMDEgMzIwTDU2MCAwTDUxNSAwTDQwMCAzMjBMNDQ1LjAxIDMyMFoiIGlkPSJiMm14Q2VoMjV3Ij48L3BhdGg+PGxpbmVhckdyYWRpZW50IGlkPSJncmFkaWVudGk1d3I2NEdVSVMiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iNDgwIiB5MT0iMCIgeDI9IjQ4MCIgeTI9IjMyMCI+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICNhYmZmMDA7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMTAwMDA7c3RvcC1vcGFjaXR5OiAwIiBvZmZzZXQ9IjEwMCUiPjwvc3RvcD48L2xpbmVhckdyYWRpZW50PjxwYXRoIGQ9Ik01MjUgMzIwTDY0MCAwTDU5NSAwTDQ4MCAzMjBMNTI1IDMyMFoiIGlkPSJqMXQ3NXVIVkh5Ij48L3BhdGg+PGxpbmVhckdyYWRpZW50IGlkPSJncmFkaWVudGYxa2V5UE5rV2YiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iNTYwIiB5MT0iMCIgeDI9IjU2MCIgeTI9IjMyMCI+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICNmZmU3MDA7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMTAwMDA7c3RvcC1vcGFjaXR5OiAwIiBvZmZzZXQ9IjEwMCUiPjwvc3RvcD48L2xpbmVhckdyYWRpZW50PjxwYXRoIGQ9Ik02MDUgMzIwTDcyMCAwTDY3NSAwTDU2MCAzMjBMNjA1IDMyMFoiIGlkPSJhNm43R2FTdVVYIj48L3BhdGg+PGxpbmVhckdyYWRpZW50IGlkPSJncmFkaWVudGMyRm95V1B4amQiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iNjQwIiB5MT0iMCIgeDI9IjY0MCIgeTI9IjMyMCI+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICNmZmZmZmY7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICNmZjAwMDA7c3RvcC1vcGFjaXR5OiAxIiBvZmZzZXQ9IjAlIj48L3N0b3A+PHN0b3Agc3R5bGU9InN0b3AtY29sb3I6ICMwMTAwMDA7c3RvcC1vcGFjaXR5OiAwIiBvZmZzZXQ9IjEwMCUiPjwvc3RvcD48L2xpbmVhckdyYWRpZW50PjxwYXRoIGQ9Ik0tMzQuOTkgMzIwTDgwLjAxIDBMMzUuMDEgMEwtNzkuOTkgMzIwTC0zNC45OSAzMjBaIiBpZD0iajFscWlVUkVaRyI+PC9wYXRoPjxsaW5lYXJHcmFkaWVudCBpZD0iZ3JhZGllbnRhclZuTWpkMkYiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iMC4wMSIgeTE9IjAiIHgyPSIwLjAxIiB5Mj0iMzIwIj48c3RvcCBzdHlsZT0ic3RvcC1jb2xvcjogI2ZmMDAwMDtzdG9wLW9wYWNpdHk6IDEiIG9mZnNldD0iMCUiPjwvc3RvcD48c3RvcCBzdHlsZT0ic3RvcC1jb2xvcjogIzAxMDAwMDtzdG9wLW9wYWNpdHk6IDAiIG9mZnNldD0iMTAwJSI+PC9zdG9wPjwvbGluZWFyR3JhZGllbnQ+PHBhdGggZD0iTTQ1LjAxIDMyMEwxNjAuMDEgMEwxMTUuMDEgMEwwLjAxIDMyMEw0NS4wMSAzMjBaIiBpZD0iYzROYlZ1UTdpIj48L3BhdGg+PGxpbmVhckdyYWRpZW50IGlkPSJncmFkaWVudGE0UzRGZ2NtWjgiIGdyYWRpZW50VW5pdHM9InVzZXJTcGFjZU9uVXNlIiB4MT0iODAuMDEiIHkxPSIwIiB4Mj0iODAuMDEiIHkyPSIzMjAiPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjZmZkZTAwO3N0b3Atb3BhY2l0eTogMSIgb2Zmc2V0PSIwJSI+PC9zdG9wPjxzdG9wIHN0eWxlPSJzdG9wLWNvbG9yOiAjMDAwMDAwO3N0b3Atb3BhY2l0eTogMCIgb2Zmc2V0PSIxMDAlIj48L3N0b3A+PC9saW5lYXJHcmFkaWVudD48L2RlZnM+PGc+PGc+PGc+PHVzZSB4bGluazpocmVmPSIjZzFGb05BRExodyIgb3BhY2l0eT0iMSIgZmlsbD0idXJsKCNncmFkaWVudGJhTnZ3QXJiWCkiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2cxRm9OQURMaHciIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2I2S01meDlkQkIiIG9wYWNpdHk9IjEiIGZpbGw9InVybCgjZ3JhZGllbnRhNFU0RWo1Q2JrKSI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjYjZLTWZ4OWRCQiIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjYjF0clIyZmdzRiIgb3BhY2l0eT0iMSIgZmlsbD0idXJsKCNncmFkaWVudGFZNlk2QTBoTSkiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2IxdHJSMmZnc0YiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2QzMkptWDF1NWEiIG9wYWNpdHk9IjEiIGZpbGw9InVybCgjZ3JhZGllbnRiNTRXaXBpcnR3KSI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjZDMySm1YMXU1YSIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjYjJteENlaDI1dyIgb3BhY2l0eT0iMSIgZmlsbD0idXJsKCNncmFkaWVudGk1d3I2NEdVSVMpIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNiMm14Q2VoMjV3IiBvcGFjaXR5PSIxIiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iIzAwMDAwMCIgc3Ryb2tlLXdpZHRoPSIxIiBzdHJva2Utb3BhY2l0eT0iMCI+PC91c2U+PC9nPjwvZz48Zz48dXNlIHhsaW5rOmhyZWY9IiNqMXQ3NXVIVkh5IiBvcGFjaXR5PSIxIiBmaWxsPSJ1cmwoI2dyYWRpZW50ZjFrZXlQTmtXZikiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2oxdDc1dUhWSHkiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2E2bjdHYVN1VVgiIG9wYWNpdHk9IjEiIGZpbGw9InVybCgjZ3JhZGllbnRjMkZveVdQeGpkKSI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjYTZuN0dhU3VVWCIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjajFscWlVUkVaRyIgb3BhY2l0eT0iMSIgZmlsbD0idXJsKCNncmFkaWVudGFyVm5NamQyRikiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2oxbHFpVVJFWkciIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2M0TmJWdVE3aSIgb3BhY2l0eT0iMSIgZmlsbD0idXJsKCNncmFkaWVudGE0UzRGZ2NtWjgpIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNjNE5iVnVRN2kiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjwvZz48L2c+PC9zdmc+");
      height: 80px;
      background-size: contain;
      background-origin: content-box;
    }

    .imgHeaderFire {
      background-image: url("data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+CjxzdmcgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCBtZWV0IiB2aWV3Qm94PSIwIDAgNjQwIDMyMCIgd2lkdGg9IjY0MCIgaGVpZ2h0PSIzMjAiPjxkZWZzPjxwYXRoIGQ9Ik0zODcuMDIgMzIwQzQwMy4yIDI3NS41NCAzOTUuNjIgMjQzLjk4IDM2NC4yOSAyMjUuMzJDMzMyLjk2IDIwNi42NSAzMDkuNzMgMTU2LjQgMjk0LjU5IDc0LjU3QzIzMy41NCAxNzMuMjkgMjE5LjY5IDI1NS4xIDI1My4wMiAzMjAiIGlkPSJiYlFHQW5oSHoiPjwvcGF0aD48cGF0aCBkPSJNMTEyLjEyIDMyMEM2OS42OCAyNzUuMDUgNjQuMTIgMjQzLjI0IDk1LjQ1IDIyNC41N0MxNDIuNDUgMTk2LjU3IDgxLjk4IDIwLjEyIDgwLjk4IDE1LjQ4QzI1MS45OCA4OC44NCAyOTYuMTIgMjIyLjY0IDI0Ni4xMiAzMjAiIGlkPSJjMjFETXRub0xZIj48L3BhdGg+PHBhdGggZD0iTTE2NS4xMiAzMjBDMTM5LjQ1IDI4MS44OSAxMzQuNzkgMjU5LjcyIDE1MS4xMiAyNTMuNDhDMTkwLjYyIDIwMy4xMiAxNTMuMTIgMTMxLjI3IDE1Ni4xMiAxMzAuNjNDMjE4Ljc5IDE3OC44NyAyMzguNDUgMjQxLjk5IDIxNS4xMiAzMjAiIGlkPSJoMnhYNTMwQ0U5Ij48L3BhdGg+PHBhdGggZD0iTTE1OS42MSAzMjBDMTkwLjk0IDI3NS4wNSAxOTAuOTQgMjQzLjI0IDE1OS42MSAyMjQuNTdDMTEyLjYxIDE5Ni41NyAxNjMuOTkgOTIuODUgMTY0Ljk5IDg4LjIxQy02LjAxIDE2MS41NiAtMjYuNDggMjIyLjY0IDIzLjUyIDMyMCIgaWQ9ImUxNXN2WVpJbVMiPjwvcGF0aD48cGF0aCBkPSJNMzM0LjAyIDMyMEMzNTAuMzUgMjg3Ljk1IDM1MC4zNSAyNjguODEgMzM0LjAyIDI2Mi41N0MyOTQuNTIgMjEyLjIxIDI5Ni45IDE5NS44MSAyODguNDcgMTg1LjkyQzI2Mi42NiAyMjYuODEgMjYxLjE3IDI3MS41IDI4NC4wMiAzMjAiIGlkPSJibG5xY21WQ0QiPjwvcGF0aD48cGF0aCBkPSJNMTA2LjI2IDMyMEMxMzEuOTMgMjg3Ljk1IDEzNi41OSAyNjguODEgMTIwLjI2IDI2Mi41N0M4MC43NiAyMTIuMjEgMTE4LjI2IDE3NS4yMSAxMTUuMjYgMTc0LjU3QzUyLjU5IDIyMi44MSAzMi45MyAyNzEuMjkgNTYuMjYgMzIwIiBpZD0iYTlVQjZuQWFUIj48L3BhdGg+PHBhdGggZD0iTTUwMC45NiAzMjBDNTI2LjIzIDI2Ny40NiA1MjMuMiAyMzEuODYgNDkxLjg3IDIxMy4xOUM0NDQuODcgMTg1LjE5IDQ4Ny44NyAxMDkuOTkgNDgyLjc4IDEwNC44N0MzOTguOSAxMzAuMDYgMzE2Ljk2IDIyMi42NCAzNjYuOTYgMzIwIiBpZD0ia0tNQzE2Qnd5Ij48L3BhdGg+PHBhdGggZD0iTTQ0OS4yNyAzMjBDNDcyLjcgMjk2LjY2IDQ3Ni4yNCAyODEuODcgNDU5LjkxIDI3NS42M0M0MjAuNDEgMjI1LjI3IDQ0My4yMiAyMDIuNDcgNDM0LjggMTkyLjU5QzQwOC45OCAyMzMuNDcgMzk3LjE0IDI3NS45NCAzOTkuMjcgMzIwIiBpZD0iZTFlbHJ1TU5DWCI+PC9wYXRoPjxwYXRoIGQ9Ik00OTcuNjMgMzIwQzQ3MS41OCAyMzEuMTIgNTY5LjY2IDE3MS4yNSA1NDguOTkgNjQuNUM1MzcuMzUgNTMuNTcgNjE0LjQ0IDEyMy41MyA2MjguODUgMTg3LjQxQzY0My4yNiAyNTEuMjkgNjQ1LjA2IDI4Ni40NyA2MjYuNzcgMzIyLjA4IiBpZD0iY05aYzVmMlNmIj48L3BhdGg+PHBhdGggZD0iTTU0OC4zNiAzMjBDNTU2LjU2IDI4NC4yMSA0ODguMTcgMjQ3LjYzIDU4MS4xNiAxNzYuODJDNTY2Ljc2IDI2Ni43MSA2MTYuOTggMjM5Ljc2IDU5OC4zNiAzMjAiIGlkPSJhMklwTEZ0TXNtIj48L3BhdGg+PC9kZWZzPjxnPjxnPjxnPjx1c2UgeGxpbms6aHJlZj0iI2JiUUdBbmhIeiIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmNWUyYSIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNiYlFHQW5oSHoiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2MyMURNdG5vTFkiIG9wYWNpdHk9IjEiIGZpbGw9IiNjNjA1MDAiIGZpbGwtb3BhY2l0eT0iMSI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjYzIxRE10bm9MWSIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjaDJ4WDUzMENFOSIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmYjIwMCIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNoMnhYNTMwQ0U5IiBvcGFjaXR5PSIxIiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iI2ZmYTgwMCIgc3Ryb2tlLXdpZHRoPSIxIiBzdHJva2Utb3BhY2l0eT0iMCI+PC91c2U+PC9nPjwvZz48Zz48dXNlIHhsaW5rOmhyZWY9IiNlMTVzdllaSW1TIiBvcGFjaXR5PSIxIiBmaWxsPSIjZmY3ZDU0IiBmaWxsLW9wYWNpdHk9IjEiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2UxNXN2WVpJbVMiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2JsbnFjbVZDRCIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmYzMwMCIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNibG5xY21WQ0QiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjZmZhODAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2E5VUI2bkFhVCIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmZGUwMCIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNhOVVCNm5BYVQiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjZmZhODAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2tLTUMxNkJ3eSIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmYTk3ZCIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNrS01DMTZCd3kiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIwIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2UxZWxydU1OQ1giIG9wYWNpdHk9IjEiIGZpbGw9IiNmZmQ1MDAiIGZpbGwtb3BhY2l0eT0iMSI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjZTFlbHJ1TU5DWCIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiNmZmE4MDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjY05aYzVmMlNmIiBvcGFjaXR5PSIxIiBmaWxsPSIjZmY1ODM4IiBmaWxsLW9wYWNpdHk9IjEiPjwvdXNlPjxnPjx1c2UgeGxpbms6aHJlZj0iI2NOWmM1ZjJTZiIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjYTJJcExGdE1zbSIgb3BhY2l0eT0iMSIgZmlsbD0iI2ZmYzQwMCIgZmlsbC1vcGFjaXR5PSIxIj48L3VzZT48Zz48dXNlIHhsaW5rOmhyZWY9IiNhMklwTEZ0TXNtIiBvcGFjaXR5PSIxIiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iI2ZmYTgwMCIgc3Ryb2tlLXdpZHRoPSIxIiBzdHJva2Utb3BhY2l0eT0iMCI+PC91c2U+PC9nPjwvZz48L2c+PC9nPjwvc3ZnPg==");
      height: 80px;
      background-size: contain;
      background-origin: content-box;
    }

    .imgHeaderWater {
      background-image: url("data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+CjxzdmcgdmVyc2lvbj0iMS4xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCBtZWV0IiB2aWV3Qm94PSIwIDAgNjQwIDMyMCIgd2lkdGg9IjY0MCIgaGVpZ2h0PSIzMjAiPjxkZWZzPjxwYXRoIGQ9IiIgaWQ9ImExbkFhUFdLOXYiPjwvcGF0aD48cGF0aCBkPSJNLTMuNDYgMTI2LjUxQzcuNDYgMTI2Ljg4IDE2LjE0IDExOS44OCAyMi41OCAxMDUuNTFDMzEuOTQgMTE5LjUxIDQwLjY2IDEyNi41MSA0OC43NCAxMjYuNTFDNTYuODMgMTI2LjUxIDY0LjI3IDExOS41MSA3MS4wOCAxMDUuNTFDNzUuNDQgMTE4LjEzIDgzLjIyIDEyNS4xMyA5NC40MyAxMjYuNTFDMTA1LjYzIDEyNS41OSAxMTIuNzQgMTE4LjU5IDExNS43NCAxMDUuNTFDMTI0LjM3IDExOS41MSAxMzIuNDkgMTI2LjUxIDE0MC4xMSAxMjYuNTFDMTQ3LjcyIDEyNi41MSAxNTQuODMgMTE5LjUxIDE2MS40MyAxMDUuNTFDMTY4LjUzIDExOS41MSAxNzYuMzIgMTI2LjUxIDE4NC43OCAxMjYuNTFDMTkzLjIzIDEyNi41MSAyMDIuMzcgMTE5LjUxIDIxMi4xOCAxMDUuNTFDMjIwLjQ4IDExOS41MSAyMjguNiAxMjYuNTEgMjM2LjU1IDEyNi41MUMyNDQuNSAxMjYuNTEgMjUyLjI4IDExOS41MSAyNTkuOSAxMDUuNTFDMjY2LjE2IDExOS41MSAyNzIuNTkgMTI2LjUxIDI3OS4xOSAxMjYuNTFDMjg1Ljc4IDEyNi41MSAyOTIuNTUgMTE5LjUxIDI5OS40OSAxMDUuNTFDMzA2LjMgMTE5LjUxIDMxMy42IDEyNi41MSAzMjEuMzkgMTI2LjUxQzMyOS4xNyAxMjYuNTEgMzM3LjQ0IDExOS41MSAzNDYuMTkgMTA1LjUxQzM1Ni44NCAxMTkuNTEgMzY2LjMyIDEyNi41MSAzNzQuNjEgMTI2LjUxQzM4Mi45IDEyNi41MSAzOTAuMDEgMTE5LjUxIDM5NS45MyAxMDUuNTFDNDA0LjIyIDExOS41MSA0MTMuMDIgMTI2LjUxIDQyMi4zMiAxMjYuNTFDNDMxLjYzIDEyNi41MSA0NDEuNDQgMTE5LjUxIDQ1MS43NiAxMDUuNTFDNDYzLjk0IDExOS41MSA0NzQuNzcgMTI2LjUxIDQ4NC4yNSAxMjYuNTFDNDk4LjQ2IDEyNi41MSA1MDguNjEgMTA0LjUxIDUwOC42MSAxMDUuNTFDNTA4LjYxIDEwNi41MSA1MjAuODUgMTI2LjUxIDUzMy4wMyAxMjYuNTFDNTQxLjE1IDEyNi41MSA1NDkuMjYgMTE5LjUxIDU1Ny4zNCAxMDUuNTFDNTcxLjIxIDExOS41MSA1ODMuMzkgMTI2LjUxIDU5My44OCAxMjYuNTFDNjA0LjM3IDEyNi41MSA2MTMuMTcgMTE5LjUxIDYyMC4yOCAxMDUuNTFDNjI0LjggMTE4LjQ5IDYzMy40NSAxMjUuNDkgNjQ2LjI0IDEyNi41MUM2NDUuODYgMjUzLjkzIDY0NS44NiAzMTguNDIgNjQ2LjI0IDMyMEwtMy40NiAzMjBDLTMuNTcgMzE3LjUgLTMuNTcgMjUzIC0zLjQ2IDEyNi41MVoiIGlkPSJhM3VQeTE3aXJYIj48L3BhdGg+PHBhdGggZD0iTTI4OS43NCAyMDUuOEMyODIuNjggMjA1LjY4IDI3My4xOSAxOTcuMTIgMjYxLjI3IDE4MC4xQzI0OC43NyAxOTcuMjMgMjM3LjQzIDIwNS44IDIyNy4yNCAyMDUuOEMyMTcuMDYgMjA1LjggMjA4LjAzIDE5Ny4yMyAyMDAuMTYgMTgwLjFDMTg2LjYyIDE5Ny4yMyAxNzQuNTggMjA1LjggMTY0LjA1IDIwNS44QzE1My41MiAyMDUuOCAxNDQuNDkgMTk3LjIzIDEzNi45NiAxODAuMUMxMjQuMzUgMTk3LjIzIDExMy40NyAyMDUuOCAxMDQuMzMgMjA1LjhDOTUuMTggMjA1LjggODcuNzcgMTk3LjIzIDgyLjEgMTgwLjFDNjYuOTQgMTk3LjEyIDU1LjYgMjA1LjY4IDQ4LjA4IDIwNS44IiBpZD0iZTFWeU1icVlaYyI+PC9wYXRoPjxwYXRoIGQ9Ik02MTQuMzMgMTgzLjE2QzYwOS42IDE4My4wOCA2MDMuMjQgMTc3LjUzIDU5NS4yNiAxNjYuNDlDNTg2Ljg5IDE3Ny42IDU3OS4zIDE4My4xNiA1NzIuNDggMTgzLjE2QzU2NS42NiAxODMuMTYgNTU5LjYyIDE3Ny42IDU1NC4zNSAxNjYuNDlDNTQ1LjI4IDE3Ny42IDUzNy4yMiAxODMuMTYgNTMwLjE3IDE4My4xNkM1MjMuMTIgMTgzLjE2IDUxNy4wNyAxNzcuNiA1MTIuMDMgMTY2LjQ5QzUwMy41OSAxNzcuNiA0OTYuMyAxODMuMTYgNDkwLjE4IDE4My4xNkM0ODQuMDYgMTgzLjE2IDQ3OS4xIDE3Ny42IDQ3NS4zIDE2Ni40OUM0NjUuMTUgMTc3LjUzIDQ1Ny41NiAxODMuMDggNDUyLjUyIDE4My4xNiIgaWQ9ImQyaWU2U1d4d1UiPjwvcGF0aD48cGF0aCBkPSJNMjc1LjcxIDI5My4xNkMyODMuNTMgMjkzLjAxIDI5NC4wMyAyODIuMzcgMzA3LjIyIDI2MS4yMUMzMjEuMDUgMjgyLjUxIDMzMy42MSAyOTMuMTYgMzQ0Ljg4IDI5My4xNkMzNTYuMTUgMjkzLjE2IDM2Ni4xNCAyODIuNTEgMzc0Ljg1IDI2MS4yMUMzODkuODMgMjgyLjUxIDQwMy4xNSAyOTMuMTYgNDE0LjgxIDI5My4xNkM0MjYuNDYgMjkzLjE2IDQzNi40NSAyODIuNTEgNDQ0Ljc4IDI2MS4yMUM0NTguNzQgMjgyLjUxIDQ3MC43OCAyOTMuMTYgNDgwLjkgMjkzLjE2QzQ5MS4wMiAyOTMuMTYgNDk5LjIxIDI4Mi41MSA1MDUuNDkgMjYxLjIxQzUyMi4yNyAyODIuMzcgNTM0LjgyIDI5My4wMSA1NDMuMTQgMjkzLjE2IiBpZD0iYVZDRHVhb3dpIj48L3BhdGg+PC9kZWZzPjxnPjxnPjxnPjxnPjx1c2UgeGxpbms6aHJlZj0iI2ExbkFhUFdLOXYiIG9wYWNpdHk9IjEiIGZpbGwtb3BhY2l0eT0iMCIgc3Ryb2tlPSIjMDAwMDAwIiBzdHJva2Utd2lkdGg9IjEiIHN0cm9rZS1vcGFjaXR5PSIxIj48L3VzZT48L2c+PC9nPjxnPjx1c2UgeGxpbms6aHJlZj0iI2EzdVB5MTdpclgiIG9wYWNpdHk9IjEiIGZpbGw9IiM0ZWFiZTQiIGZpbGwtb3BhY2l0eT0iMC45OCI+PC91c2U+PGc+PHVzZSB4bGluazpocmVmPSIjYTN1UHkxN2lyWCIgb3BhY2l0eT0iMSIgZmlsbC1vcGFjaXR5PSIwIiBzdHJva2U9IiMwMDAwMDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlLW9wYWNpdHk9IjAiPjwvdXNlPjwvZz48L2c+PGc+PGc+PGZpbHRlciBpZD0ic2hhZG93MTM3MjgyMjkiIHg9IjM3LjA4IiB5PSIxNjkuMSIgd2lkdGg9IjI2NC42NyIgaGVpZ2h0PSI0OC42OSIgZmlsdGVyVW5pdHM9InVzZXJTcGFjZU9uVXNlIiBwcmltaXRpdmVVbml0cz0idXNlclNwYWNlT25Vc2UiPjxmZUZsb29kPjwvZmVGbG9vZD48ZmVDb21wb3NpdGUgaW4yPSJTb3VyY2VBbHBoYSIgb3BlcmF0b3I9ImluIj48L2ZlQ29tcG9zaXRlPjxmZUdhdXNzaWFuQmx1ciBzdGREZXZpYXRpb249IjEuNDEiPjwvZmVHYXVzc2lhbkJsdXI+PGZlT2Zmc2V0IGR4PSIxIiBkeT0iMSIgcmVzdWx0PSJhZnRlck9mZnNldCI+PC9mZU9mZnNldD48ZmVGbG9vZCBmbG9vZC1jb2xvcj0iIzAwNjlmZiIgZmxvb2Qtb3BhY2l0eT0iMSI+PC9mZUZsb29kPjxmZUNvbXBvc2l0ZSBpbjI9ImFmdGVyT2Zmc2V0IiBvcGVyYXRvcj0iaW4iPjwvZmVDb21wb3NpdGU+PGZlTW9ycGhvbG9neSBvcGVyYXRvcj0iZGlsYXRlIiByYWRpdXM9IjEiPjwvZmVNb3JwaG9sb2d5PjxmZUNvbXBvc2l0ZSBpbjI9IlNvdXJjZUFscGhhIiBvcGVyYXRvcj0ib3V0Ij48L2ZlQ29tcG9zaXRlPjwvZmlsdGVyPjxwYXRoIGQ9Ik0yODkuNzQgMjA1LjhDMjgyLjY4IDIwNS42OCAyNzMuMTkgMTk3LjEyIDI2MS4yNyAxODAuMUMyNDguNzcgMTk3LjIzIDIzNy40MyAyMDUuOCAyMjcuMjQgMjA1LjhDMjE3LjA2IDIwNS44IDIwOC4wMyAxOTcuMjMgMjAwLjE2IDE4MC4xQzE4Ni42MiAxOTcuMjMgMTc0LjU4IDIwNS44IDE2NC4wNSAyMDUuOEMxNTMuNTIgMjA1LjggMTQ0LjQ5IDE5Ny4yMyAxMzYuOTYgMTgwLjFDMTI0LjM1IDE5Ny4yMyAxMTMuNDcgMjA1LjggMTA0LjMzIDIwNS44Qzk1LjE4IDIwNS44IDg3Ljc3IDE5Ny4yMyA4Mi4xIDE4MC4xQzY2Ljk0IDE5Ny4xMiA1NS42IDIwNS42OCA0OC4wOCAyMDUuOCIgaWQ9ImRBanlhUWdkRSIgZmlsbD0ibm9uZSIgc3Ryb2tlPSJ3aGl0ZSIgZmlsdGVyPSJ1cmwoI3NoYWRvdzEzNzI4MjI5KSI+PC9wYXRoPjwvZz48Zz48dXNlIHhsaW5rOmhyZWY9IiNlMVZ5TWJxWVpjIiBvcGFjaXR5PSIwLjU2IiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iI2ZmZmZmZiIgc3Ryb2tlLXdpZHRoPSI0IiBzdHJva2Utb3BhY2l0eT0iMSI+PC91c2U+PC9nPjwvZz48Zz48Zz48ZmlsdGVyIGlkPSJzaGFkb3czMTk1ODc2IiB4PSI0NDEuNTIiIHk9IjE1NS40OSIgd2lkdGg9IjE4NC44MSIgaGVpZ2h0PSIzOS42NyIgZmlsdGVyVW5pdHM9InVzZXJTcGFjZU9uVXNlIiBwcmltaXRpdmVVbml0cz0idXNlclNwYWNlT25Vc2UiPjxmZUZsb29kPjwvZmVGbG9vZD48ZmVDb21wb3NpdGUgaW4yPSJTb3VyY2VBbHBoYSIgb3BlcmF0b3I9ImluIj48L2ZlQ29tcG9zaXRlPjxmZUdhdXNzaWFuQmx1ciBzdGREZXZpYXRpb249IjEuNDEiPjwvZmVHYXVzc2lhbkJsdXI+PGZlT2Zmc2V0IGR4PSIxIiBkeT0iMSIgcmVzdWx0PSJhZnRlck9mZnNldCI+PC9mZU9mZnNldD48ZmVGbG9vZCBmbG9vZC1jb2xvcj0iIzAwNjlmZiIgZmxvb2Qtb3BhY2l0eT0iMSI+PC9mZUZsb29kPjxmZUNvbXBvc2l0ZSBpbjI9ImFmdGVyT2Zmc2V0IiBvcGVyYXRvcj0iaW4iPjwvZmVDb21wb3NpdGU+PGZlTW9ycGhvbG9neSBvcGVyYXRvcj0iZGlsYXRlIiByYWRpdXM9IjEiPjwvZmVNb3JwaG9sb2d5PjxmZUNvbXBvc2l0ZSBpbjI9IlNvdXJjZUFscGhhIiBvcGVyYXRvcj0ib3V0Ij48L2ZlQ29tcG9zaXRlPjwvZmlsdGVyPjxwYXRoIGQ9Ik02MTQuMzMgMTgzLjE2QzYwOS42IDE4My4wOCA2MDMuMjQgMTc3LjUzIDU5NS4yNiAxNjYuNDlDNTg2Ljg5IDE3Ny42IDU3OS4zIDE4My4xNiA1NzIuNDggMTgzLjE2QzU2NS42NiAxODMuMTYgNTU5LjYyIDE3Ny42IDU1NC4zNSAxNjYuNDlDNTQ1LjI4IDE3Ny42IDUzNy4yMiAxODMuMTYgNTMwLjE3IDE4My4xNkM1MjMuMTIgMTgzLjE2IDUxNy4wNyAxNzcuNiA1MTIuMDMgMTY2LjQ5QzUwMy41OSAxNzcuNiA0OTYuMyAxODMuMTYgNDkwLjE4IDE4My4xNkM0ODQuMDYgMTgzLjE2IDQ3OS4xIDE3Ny42IDQ3NS4zIDE2Ni40OUM0NjUuMTUgMTc3LjUzIDQ1Ny41NiAxODMuMDggNDUyLjUyIDE4My4xNiIgaWQ9ImUzU050U1pKdkoiIGZpbGw9Im5vbmUiIHN0cm9rZT0id2hpdGUiIGZpbHRlcj0idXJsKCNzaGFkb3czMTk1ODc2KSI+PC9wYXRoPjwvZz48Zz48dXNlIHhsaW5rOmhyZWY9IiNkMmllNlNXeHdVIiBvcGFjaXR5PSIwLjU2IiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iI2ZmZmZmZiIgc3Ryb2tlLXdpZHRoPSI0IiBzdHJva2Utb3BhY2l0eT0iMSI+PC91c2U+PC9nPjwvZz48Zz48Zz48ZmlsdGVyIGlkPSJzaGFkb3c0NTkyNzQiIHg9IjI2NC43MSIgeT0iMjUwLjIxIiB3aWR0aD0iMjkwLjQzIiBoZWlnaHQ9IjU0Ljk0IiBmaWx0ZXJVbml0cz0idXNlclNwYWNlT25Vc2UiIHByaW1pdGl2ZVVuaXRzPSJ1c2VyU3BhY2VPblVzZSI+PGZlRmxvb2Q+PC9mZUZsb29kPjxmZUNvbXBvc2l0ZSBpbjI9IlNvdXJjZUFscGhhIiBvcGVyYXRvcj0iaW4iPjwvZmVDb21wb3NpdGU+PGZlR2F1c3NpYW5CbHVyIHN0ZERldmlhdGlvbj0iMS40MSI+PC9mZUdhdXNzaWFuQmx1cj48ZmVPZmZzZXQgZHg9IjEiIGR5PSIxIiByZXN1bHQ9ImFmdGVyT2Zmc2V0Ij48L2ZlT2Zmc2V0PjxmZUZsb29kIGZsb29kLWNvbG9yPSIjMDA2OWZmIiBmbG9vZC1vcGFjaXR5PSIxIj48L2ZlRmxvb2Q+PGZlQ29tcG9zaXRlIGluMj0iYWZ0ZXJPZmZzZXQiIG9wZXJhdG9yPSJpbiI+PC9mZUNvbXBvc2l0ZT48ZmVNb3JwaG9sb2d5IG9wZXJhdG9yPSJkaWxhdGUiIHJhZGl1cz0iMSI+PC9mZU1vcnBob2xvZ3k+PGZlQ29tcG9zaXRlIGluMj0iU291cmNlQWxwaGEiIG9wZXJhdG9yPSJvdXQiPjwvZmVDb21wb3NpdGU+PC9maWx0ZXI+PHBhdGggZD0iTTI3NS43MSAyOTMuMTZDMjgzLjUzIDI5My4wMSAyOTQuMDMgMjgyLjM3IDMwNy4yMiAyNjEuMjFDMzIxLjA1IDI4Mi41MSAzMzMuNjEgMjkzLjE2IDM0NC44OCAyOTMuMTZDMzU2LjE1IDI5My4xNiAzNjYuMTQgMjgyLjUxIDM3NC44NSAyNjEuMjFDMzg5LjgzIDI4Mi41MSA0MDMuMTUgMjkzLjE2IDQxNC44MSAyOTMuMTZDNDI2LjQ2IDI5My4xNiA0MzYuNDUgMjgyLjUxIDQ0NC43OCAyNjEuMjFDNDU4Ljc0IDI4Mi41MSA0NzAuNzggMjkzLjE2IDQ4MC45IDI5My4xNkM0OTEuMDIgMjkzLjE2IDQ5OS4yMSAyODIuNTEgNTA1LjQ5IDI2MS4yMUM1MjIuMjcgMjgyLjM3IDUzNC44MiAyOTMuMDEgNTQzLjE0IDI5My4xNiIgaWQ9ImNxUzV0RVU4QyIgZmlsbD0ibm9uZSIgc3Ryb2tlPSJ3aGl0ZSIgZmlsdGVyPSJ1cmwoI3NoYWRvdzQ1OTI3NCkiPjwvcGF0aD48L2c+PGc+PHVzZSB4bGluazpocmVmPSIjYVZDRHVhb3dpIiBvcGFjaXR5PSIwLjU2IiBmaWxsLW9wYWNpdHk9IjAiIHN0cm9rZT0iI2ZmZmZmZiIgc3Ryb2tlLXdpZHRoPSI0IiBzdHJva2Utb3BhY2l0eT0iMSI+PC91c2U+PC9nPjwvZz48L2c+PC9nPjwvc3ZnPg==");
      height: 80px;
      background-size: contain;
      background-origin: content-box;
    }
    /* Switch button styles */
    /* The switch - the box around the slider */
    .switch {
      position: relative;
      display: inline-block;
      width: 60px;
      height: 34px;
    }

    /* Hide default HTML checkbox */
    .switch input {
      opacity: 0;
      width: 0;
      height: 0;
    }

    /* The slider */
    .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: #ccc;
      -webkit-transition: 0.4s;
      transition: 0.4s;
    }

    .slider:before {
      position: absolute;
      content: "";
      height: 26px;
      width: 26px;
      left: 4px;
      bottom: 4px;
      background-color: white;
      -webkit-transition: 0.4s;
      transition: 0.4s;
    }

    input:checked + .slider {
      background-color: #2196f3;
    }

    input:focus + .slider {
      box-shadow: 0 0 1px #2196f3;
    }

    input:checked + .slider:before {
      -webkit-transform: translateX(26px);
      -ms-transform: translateX(26px);
      transform: translateX(26px);
    }

    /* Rounded sliders */
    .slider.round {
      border-radius: 34px;
    }

    .slider.round:before {
      border-radius: 50%;
    }
  </style>
</head>

<body>
  <div class="container">
    <div class="page-header mt-4">
      <div class="row">
        <div class="col-sm-6">
          <h1>Haloght</h1>
        </div>
        <div class="col-sm-6">
          <div class="row">
            <div class="col-2">
              <label class="switch float-sm-right mt-3">
                <input type="checkbox" id="onOffSwitch" />
                <span class="slider round"></span>
              </label>
            </div>
            <div class="col-10">
              <input
                type="range"
                class="custom-range float-sm-right ml-3 mt-4"
                min="0"
                max="100"
                step="1"
                id="brightnessRangeSlider"
              />
            </div>
          </div>
        </div>
      </div>
      <hr />
    </div>
    <div class="row">
      <div class="col-sm-6 pb-3">
        <div class="card">
          <div
            class="card-img-top pl-2 pr-2 pt-1"
            style="background-color: #F3F3F3;"
          >
            <div class="imgHeaderSolidColor"></div>
          </div>
          <div class="card-body">
            <h4>Solid color</h4>
            <form class="form-horizontal" action="javascript:void(0);">
              <div class="form-group">
                <div class="col-sm-12">
                  <input
                    type="color"
                    class="form-control"
                    id="solidColorInput"
                    name="solidColorInput"
                    style="height: 50px; width: 100%;"
                  />
                </div>
              </div>
              <div class="form-group">
                <div class="col-sm-12">
                  <button
                    class="btn btn-default"
                    style="width: 100%;"
                    id="sendSolidColorButton"
                  >
                    Send
                  </button>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
      <div class="col-sm-6 pb-3">
        <div class="card mb-3">
          <div
            class="card-img-top pl-2 pr-2 pt-1"
            style="background-color: #F3F3F3;"
          >
            <div class="imgHeaderFire"></div>
          </div>
          <div class="card-body">
            <h4>Fire</h4>
            <form class="form-horizontal" action="javascript:void(0);">
              <div class="form-group">
                <div class="col-sm-12">
                  <button
                    class="btn btn-default"
                    style="width: 100%;"
                    id="sendFireButton"
                  >
                    Send
                  </button>
                </div>
              </div>
            </form>
          </div>
        </div>
        <div class="card mb-3">
          <div
            class="card-img-top pl-2 pr-2 pt-1"
            style="background-color: #F3F3F3;"
          >
            <div class="imgHeaderWater"></div>
          </div>
          <div class="card-body">
            <h4>Water</h4>
            <form class="form-horizontal" action="javascript:void(0);">
              <div class="form-group">
                <div class="col-sm-12">
                  <button
                    class="btn btn-default"
                    style="width: 100%;"
                    id="sendWaterButton"
                  >
                    Send
                  </button>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
    </div>
  </div>
</body>

)=====";
