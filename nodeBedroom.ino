#include <ShutterButton.h>
#include <Relay.h>
#include <CnC.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char nodeName[] PROGMEM = "bedroom";
const char sepName[] PROGMEM = " ";
const char hkName[] PROGMEM = "val";
const char cmdGetName[] PROGMEM = "get";
const char cmdSetName[] PROGMEM = "set";

const char pingName[] PROGMEM = "ping";
const char parentsShutterButtonName[] PROGMEM = "parentsShutterButton";
const char parentsWindowContactName[] PROGMEM = "parentsWindowContact";
const char parentsShutterContactName[] PROGMEM = "parentsShutterContact";
const char ellisShutterButtonName[] PROGMEM = "ellisShutterButton";
const char ellisWindowContactName[] PROGMEM = "ellisWindowContact";
const char ellisShutterContactName[] PROGMEM = "ellisShutterContact";
const char desktopShutterButtonName[] PROGMEM = "desktopShutterButton";
const char desktopWindowContactName[] PROGMEM = "desktopWindowContact";
const char desktopShutterContactName[] PROGMEM = "desktopShutterContact";
const char basementWindowContactName[] PROGMEM = "basementWindowContact";
const char basementShutterContactName[] PROGMEM = "basementShutterContact";
const char lightRelayName[] PROGMEM = "lightRelay";
const char tempSensorsName[] PROGMEM = "tempSensors";

ShutterButton parentsShutterButton(parentsShutterButtonName, 11, 12);
Contact parentsWindowContact(parentsWindowContactName, 10);
Contact parentsShutterContact(parentsShutterContactName, 9);

ShutterButton ellisShutterButton(ellisShutterButtonName, A2, A3);
Contact ellisWindowContact(ellisWindowContactName, A1);
Contact ellisShutterContact(ellisShutterContactName, A0);

ShutterButton desktopShutterButton(desktopShutterButtonName, 7, 8);
Contact desktopWindowContact(desktopWindowContactName, A5);
Contact desktopShutterContact(desktopShutterContactName, A4);

Contact basementWindowContact(basementWindowContactName, 4);
Contact basementShutterContact(basementShutterContactName, 3);

Relay lightRelay(lightRelayName, 13);

OneWire oneWire(2);
DallasTemperature tempSensors(&oneWire);

uint32_t previousTime_1s = 0;
uint32_t previousTime_10s = 0;
uint32_t currentTime = 0;

void ping_cmdGet(int arg_cnt, char **args) { cnc_print_cmdGet_u32(pingName, currentTime); }
void parentsShutterButton_cmdGet(int arg_cnt, char **args) { parentsShutterButton.cmdGet(arg_cnt, args); }
void parentsWindowContact_cmdGet(int arg_cnt, char **args) { parentsWindowContact.cmdGet(arg_cnt, args); }
void parentsShutterContact_cmdGet(int arg_cnt, char **args) { parentsShutterContact.cmdGet(arg_cnt, args); }
void ellisShutterButton_cmdGet(int arg_cnt, char **args) { ellisShutterButton.cmdGet(arg_cnt, args); }
void ellisWindowContact_cmdGet(int arg_cnt, char **args) { ellisWindowContact.cmdGet(arg_cnt, args); }
void ellisShutterContact_cmdGet(int arg_cnt, char **args) { ellisShutterContact.cmdGet(arg_cnt, args); }
void desktopShutterButton_cmdGet(int arg_cnt, char **args) { desktopShutterButton.cmdGet(arg_cnt, args); }
void desktopWindowContact_cmdGet(int arg_cnt, char **args) { desktopWindowContact.cmdGet(arg_cnt, args); }
void desktopShutterContact_cmdGet(int arg_cnt, char **args) { desktopShutterContact.cmdGet(arg_cnt, args); }
void basementWindowContact_cmdGet(int arg_cnt, char **args) { basementWindowContact.cmdGet(arg_cnt, args); }
void basementShutterContact_cmdGet(int arg_cnt, char **args) { basementShutterContact.cmdGet(arg_cnt, args); }
void lightRelay_cmdGet(int arg_cnt, char **args) { lightRelay.cmdGet(arg_cnt, args); }
void lightRelay_cmdSet(int arg_cnt, char **args) { lightRelay.cmdSet(arg_cnt, args); }
uint8_t tempSensorsNb = 0;

void setup() {
  Serial.begin(115200);
  cncInit(nodeName);
  cnc_hkName_set(hkName);
  cnc_cmdGetName_set(cmdGetName);
  cnc_cmdSetName_set(cmdSetName);
  cnc_sepName_set(sepName);
  cnc_cmdGet_Add(pingName, ping_cmdGet);
  cnc_cmdGet_Add(parentsShutterButtonName , parentsShutterButton_cmdGet);
  cnc_cmdGet_Add(parentsWindowContactName , parentsWindowContact_cmdGet);
  cnc_cmdGet_Add(parentsShutterContactName, parentsShutterContact_cmdGet);
  cnc_cmdGet_Add(ellisShutterButtonName   , ellisShutterButton_cmdGet);
  cnc_cmdGet_Add(ellisWindowContactName   , ellisWindowContact_cmdGet);
  cnc_cmdGet_Add(ellisShutterContactName  , ellisShutterContact_cmdGet);
  cnc_cmdGet_Add(desktopShutterButtonName , desktopShutterButton_cmdGet);
  cnc_cmdGet_Add(desktopWindowContactName , desktopWindowContact_cmdGet);
  cnc_cmdGet_Add(desktopShutterContactName, desktopShutterContact_cmdGet);
  cnc_cmdGet_Add(basementWindowContactName , basementWindowContact_cmdGet);
  cnc_cmdGet_Add(basementShutterContactName, basementShutterContact_cmdGet);
  cnc_cmdGet_Add(lightRelayName, lightRelay_cmdGet);
  cnc_cmdSet_Add(lightRelayName, lightRelay_cmdSet);
  previousTime_1s = millis();
  previousTime_10s = previousTime_1s;
}

void loop() {
  currentTime = millis(); cncPoll();
  /* HK @ 2.0Hz */
  if((uint32_t)(currentTime - previousTime_1s) >= 500) {
    parentsWindowContact.run(true); cncPoll();
    parentsShutterContact.run(true); cncPoll();
    ellisWindowContact.run(true); cncPoll();
    ellisShutterContact.run(true); cncPoll();
    desktopWindowContact.run(true); cncPoll();
    desktopShutterContact.run(true); cncPoll();
    basementWindowContact.run(true); cncPoll();
    basementShutterContact.run(true); cncPoll();
    parentsShutterButton.run(true); cncPoll();
    ellisShutterButton.run(true); cncPoll();
    desktopShutterButton.run(true); cncPoll();
    lightRelay.run(true); cncPoll();
    previousTime_1s = currentTime;
  }
  /* HK @ 0.1Hz */
  if((uint32_t)(currentTime - previousTime_10s) >= 100000) {
    tempSensors.begin(); cncPoll();
    tempSensorsNb = tempSensors.getDeviceCount(); cncPoll();
    tempSensors.requestTemperatures(); cncPoll();
    for(uint8_t i=0; i<tempSensorsNb; i++)  {
      DeviceAddress sensorAddr;
      tempSensors.getAddress(sensorAddr, i); cncPoll();
      float temp_ = tempSensors.getTempCByIndex(i);
      if(DEVICE_DISCONNECTED_C != temp_) {
        cnc_print_hk_temp_sensor(tempSensorsName, sensorAddr, temp_); cncPoll();
      }
    }
    previousTime_10s = currentTime;
  }
}
