# Dispensador de ração automático para animais doméstiscos
Projeto desenvolvido para a disciplina de Objetos Inteligentes Conectados; O projeto consiste em um dispensador de ração automático em horários fixos com monitoramento remoto via IoT.

<img width="300" height="400" alt="image" src="https://github.com/user-attachments/assets/4a468086-3a4b-4a72-9c2d-e990c85bed79" />

## Alunos ##
- João Pedro Lopes Mendes RA: 10400793
- Yan Correa Santos RA: 10426549

## Funcionalidades

- Medição e liberação automática de ração em horários preestabelecidos;
- Notificação sobre quantidade de ração e se a ração foi liberada nos horários preestabelecidos via WhatsApp;
- Dashboard de monitoramento com Grafana;

## Materiais e ferramentas Utilizadas
- Recipiente onde a ração será armazenada (ex: Garrafa PET);
- Recipiente onde a ração será despejada (ex: Tigela);
- Microcontrolador ESP32 (É possível utilizar outros microcontroladores como o Arduino porém funções que dependem de Wi-Fi não funcionarão, sendo necessário o uso de Shields e/ou versão do Arduino com Wi-Fi embutido);
- Sensor de Peso HX711 com célula de carga de 10kg; (É possivel utilizar uma célula carga até 2kg);
- Servo Motor MG90s com torque de 2,2 kg; (É possível utilizar servo motores mais fracos como o SG90);
- Node-RED (para integração e automação);
- WhatsApp (para envio de notificações);
- InfluxDB (para armazenamento dos dados);
- Grafana (para visualização e criação de dashboards);
  
## Fluxo Node-RED
<img width="1313" height="333" alt="image" src="https://github.com/user-attachments/assets/4689dc5c-b50b-4ed0-bfc4-2e69ab61bdd7" />

## Notificação WhatsApp
<img width="721" height="361" alt="image" src="https://github.com/user-attachments/assets/3eb6c649-4ac4-48ea-9266-da1b20c1fc4d" />

## Dashboards Grafana
<img width="811" height="394" alt="image" src="https://github.com/user-attachments/assets/d148efc6-83bd-42fe-8637-357f8a8d0ecc" />


