const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <title>Monitor de Calidad de Aire</title>
  <style>
    body { font-family: Arial, sans-serif; background: #111; color: #eee; text-align: center; padding-top: 40px; }
    .card { background: #222; display: inline-block; padding: 30px 50px; border-radius: 12px; margin: 10px; }
    .valor { font-size: 3em; font-weight: bold; color: #4fc3f7; }
    .label { font-size: 1.2em; color: #aaa; }
  </style>
</head>
<body>
  <h1>Calidad de Aire - PMS7003</h1>
  <div class="card">
    <div class="label">PM1.0</div>
    <div class="valor" id="pm1">--</div>
    <div class="label">ug/m3</div>
  </div>
  <div class="card">
    <div class="label">PM2.5</div>
    <div class="valor" id="pm25">--</div>
    <div class="label">ug/m3</div>
  </div>
  <div class="card">
    <div class="label">PM10</div>
    <div class="valor" id="pm10">--</div>
    <div class="label">ug/m3</div>
  </div>

  <script>
    function actualizarDatos() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          document.getElementById('pm1').innerText = data.pm1;
          document.getElementById('pm25').innerText = data.pm25;
          document.getElementById('pm10').innerText = data.pm10;
        })
        .catch(error => console.error('Error obteniendo datos:', error));
    }

    setInterval(actualizarDatos, 5000);
    window.onload = actualizarDatos;
  </script>
</body>
</html>
)rawliteral";
