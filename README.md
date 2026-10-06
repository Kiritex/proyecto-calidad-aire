# Proyecto-calidad-aire
Sistema de monitoreo y filtración de calidad del aire con ESP32

## Descripción
En esto proyecto vamos a crear un filtro de aire con el cual vamos a detectar los niveles de pm y esos mismos datos los vamos a subir a una pàgina web

## Objetivo
El objetivo de este proyecto es crear un filtro de aire el cual tenga incorporado un sensor para detectar los niveles de pm2.5 y pm10 y que dichos datos se envien a una pagian weba para poder visualizarlos

## Materiales
- Esp-32
- PMS7003
- Ventilador
- Caja
- Filtro HEPA
- Carbón activado

## Funcionamiento del código
1. El Esp-32 activa el PMS7003 el cual se encarga de recibir el PM
2. El PMS lee esos valores y los pasa al Esp
3. Este los interpreta y los manda a la página web que se actializa cada 5 segundos
4. Usando un umbral previamente establecido podemos determinar si el aire se encuentra en buenas o malas condiciones (además de que cada nivel de PM cambia de color gracias al umbral)

## Posibles mejoras
- Que los registros de PM se guarden en una base de datos
- Una mejor estructura en los archivos para la página web (para no tener todo dentro de un solo HTMl)
- Que el ventilador pueda encenderse o apagarse automáticamente dependiendo de los niveles de PM registrados
- Acceso remoto a la página sin conectarse al mismo wWiFi
