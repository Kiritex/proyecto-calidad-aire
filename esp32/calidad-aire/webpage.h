const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Monitor de Calidad de Aire</title>
  <style>
    * { box-sizing: border-box; }
    body {
      font-family: Arial, sans-serif;
      background: #111;
      color: #eee;
      text-align: center;
      margin: 0;
      padding: 20px 10px;
    }
    h1 { font-size: 1.4em; margin-bottom: 20px; }

    .contenedor {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      gap: 15px;
      max-width: 700px;
      margin: 0 auto;
    }

    .card {
      background: #222;
      flex: 1 1 250px;
      max-width: 300px;
      padding: 25px 20px;
      border-radius: 12px;
      border: 3px solid #444;
      transition: border-color 0.3s, background 0.3s;
    }

    .valor { font-size: 2.8em; font-weight: bold; }
    .label { font-size: 1.1em; color: #aaa; margin-bottom: 5px; }
    .unidad { font-size: 0.9em; color: #888; }
    .estado { font-size: 1em; margin-top: 8px; font-weight: bold; }

    .verde   { border-color: #4caf50; }
    .verde   .valor, .verde   .estado { color: #4caf50; }

    .amarillo { border-color: #ffc107; }
    .amarillo .valor, .amarillo .estado { color: #ffc107; }

    .rojo    { border-color: #f44336; }
    .rojo    .valor, .rojo    .estado { color: #f44336; }

    @media (max-width: 480px) {
      .card { flex: 1 1 100%; max-width: 100%; }
      .valor { font-size: 2.3em; }
    }
  </style>
</head>
<body>
  <h1>Calidad de Aire - PMS7003</h1>

  <div class="contenedor">
    <div class="card" id="card-pm1">
      <div class="label">PM1.0</div>
      <div class="valor" id="pm1">--</div>
      <div class="unidad">ug/m3</div>
      <div class="estado" id="estado-pm1">--</div>
    </div>

    <div class="card" id="card-pm25">
      <div class="label">PM2.5</div>
      <div class="valor" id="pm25">--</div>
      <div class="unidad">ug/m3</div>
      <div class="estado" id="estado-pm25">--</div>
    </div>

    <div class="card" id="card-pm10">
      <div class="label">PM10</div>
      <div class="valor" id="pm10">--</div>
      <div class="unidad">ug/m3</div>
      <div class="estado" id="estado-pm10">--</div>
    </div>
  </div>

  <script>
    // Umbrales por contaminante [limiteVerde, limiteAmarillo]
    // Arriba del limiteAmarillo = rojo
    const umbrales = {
      pm1:  { verde: 10,   amarillo: 30   }, // aproximado, sin estandar oficial
      pm25: { verde: 12,   amarillo: 35.4 }, // EPA
      pm10: { verde: 54,   amarillo: 154  }  // EPA
    };

    function clasificar(valor, limites) {
      if (valor <= limites.verde) return { clase: 'verde', texto: 'Bueno' };
      if (valor <= limites.amarillo) return { clase: 'amarillo', texto: 'Moderado' };
      return { clase: 'rojo', texto: 'Danino' };
    }

    function aplicarEstado(id, valor, limites) {
      const { clase, texto } = clasificar(valor, limites);
      const card = document.getElementById('card-' + id);
      card.classList.remove('verde', 'amarillo', 'rojo');
      card.classList.add(clase);
      document.getElementById('estado-' + id).innerText = texto;
    }

    function actualizarDatos() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          document.getElementById('pm1').innerText = data.pm1;
          document.getElementById('pm25').innerText = data.pm25;
          document.getElementById('pm10').innerText = data.pm10;

          aplicarEstado('pm1', data.pm1, umbrales.pm1);
          aplicarEstado('pm25', data.pm25, umbrales.pm25);
          aplicarEstado('pm10', data.pm10, umbrales.pm10);
        })
        .catch(error => console.error('Error obteniendo datos:', error));
    }

    setInterval(actualizarDatos, 5000);
    window.onload = actualizarDatos;
  </script>
</body>
</html>
)rawliteral";
