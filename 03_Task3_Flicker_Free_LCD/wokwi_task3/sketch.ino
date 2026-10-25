/*
 MODULAR BMS — Wokwi integrated demonstration (Task 3)
 Circuit: diagram.json in same folder.
 Pots: cell channels GPIO32/33/34/35, SoC GPIO36, discharge GPIO39.
 Buttons: GPIO16 frozen fault, GPIO17 jump fault, GPIO18 range fault.
 LCD I2C: SDA21/SCL22; relay GPIO23; green LED26; red LED27; buzzer14.
 NOTE: simulation example, not safety-certified firmware.
*/
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define NUM_CELLS 4
const int CELL_PINS[NUM_CELLS]={32,33,34,35};
const int SOC_PIN=36, DISCHARGE_PIN=39;
const int RELAY_PIN=23, GREEN_LED=26, RED_LED=27, BUZZER=14;
const int BTN_FROZEN=16, BTN_JUMP=17, BTN_RANGE=18;
LiquidCrystal_I2C lcd(0x27,16,2);
enum State { NORMAL, DEGRADED, FAILSAFE, SHUTDOWN };
enum Fault { NONE, CELL_IMBALANCE, ADC_FROZEN, ADC_JUMP, ADC_RANGE, RELAY_MISMATCH, COMM_LOSS, RECOVERY_VERIFY };
State state=NORMAL; Fault fault=NONE;
float cells[NUM_CELLS], prevCells[NUM_CELLS], prevImbalance=0;
unsigned long sampleAt=0,pageAt=0,recoveryAt=0,debounceAt[3]={0,0,0};
bool frozenFault=false,jumpFault=false,rangeFault=false,recovering=false;
int page=0; String lastLine1="",lastLine2="";
const unsigned long SAMPLE_MS=250, PAGE_MS=5000, DEBOUNCE_MS=300, RECOVERY_MS=3000;
const char* stateName(State s){switch(s){case NORMAL:return "NORMAL";case DEGRADED:return "DEGRADED";case FAILSAFE:return "FAILSAFE";case SHUTDOWN:return "SHUTDOWN";}return "?";}
const char* faultName(Fault f){switch(f){case NONE:return "NONE";case CELL_IMBALANCE:return "CELL_IMBALANCE";case ADC_FROZEN:return "ADC_FROZEN";case ADC_JUMP:return "ADC_JUMP";case ADC_RANGE:return "ADC_RANGE";case RELAY_MISMATCH:return "RELAY_MISMATCH";case COMM_LOSS:return "COMM_LOSS";case RECOVERY_VERIFY:return "RECOVERY_VERIFY";}return "?";}
float readV(int pin){return 3.0f+analogRead(pin)*(1.2f/4095.0f);}
void logTransition(State next, Fault why){
 if(next==state && why==fault)return;
 State old=state;state=next;fault=why;
 Serial.printf("{\"t_ms\":%lu,\"previous\":\"%s\",\"new\":\"%s\",\"fault_id\":\"%s\"}\n",millis(),stateName(old),stateName(state),faultName(fault));
}
void lcdDiff(String a,String b){
 while(a.length()<16)a+=' '; while(b.length()<16)b+=' ';
 if(a!=lastLine1){lcd.setCursor(0,0);lcd.print(a.substring(0,16));lastLine1=a;}
 if(b!=lastLine2){lcd.setCursor(0,1);lcd.print(b.substring(0,16));lastLine2=b;}
}
void updateDisplay(float pack,float imb,float soc){
 if(state==FAILSAFE||state==SHUTDOWN){lcdDiff("!! "+String(stateName(state)),String(faultName(fault))+" RELAY OFF");return;}
 if(millis()-pageAt>=PAGE_MS){page=(page+1)%3;pageAt=millis();}
 if(page==0)lcdDiff("BATTERY "+String(pack,2)+"V","SOC "+String((int)soc)+"% dV "+String(imb,3));
 else if(page==1)lcdDiff("STATE "+String(stateName(state)),"FAULT "+String(faultName(fault)));
 else lcdDiff("TELEMETRY","Q:0 RSSI:SIM");
}
void setup(){
 Serial.begin(115200);analogReadResolution(12);
 pinMode(RELAY_PIN,OUTPUT);pinMode(GREEN_LED,OUTPUT);pinMode(RED_LED,OUTPUT);pinMode(BUZZER,OUTPUT);
 pinMode(BTN_FROZEN,INPUT_PULLUP);pinMode(BTN_JUMP,INPUT_PULLUP);pinMode(BTN_RANGE,INPUT_PULLUP);
 lcd.init();lcd.backlight();lcdDiff("MODULAR BMS","TASK 3 DEMO START");
 for(int i=0;i<NUM_CELLS;i++)prevCells[i]=-1;
 Serial.println("MODULAR BMS | TASK 3 DEMO | Serial 115200");
}
void loop(){
 unsigned long now=millis();
 // Debounced button press handling without delay()
 int btnPins[3]={BTN_FROZEN,BTN_JUMP,BTN_RANGE};
 bool* flags[3]={&frozenFault,&jumpFault,&rangeFault};
 for(int i=0;i<3;i++){if(digitalRead(btnPins[i])==LOW && now-debounceAt[i]>=DEBOUNCE_MS){*flags[i]=!*flags[i];debounceAt[i]=now;Serial.printf("Fault toggle %d = %s\n",i+1,*flags[i]?"ON":"OFF");}}
 if(now-sampleAt<SAMPLE_MS)return;sampleAt=now;
 float pack=0,minV=99,maxV=-1;int weak=0,strong=0;
 for(int i=0;i<NUM_CELLS;i++){cells[i]=readV(CELL_PINS[i]);pack+=cells[i];if(cells[i]<minV){minV=cells[i];weak=i;}if(cells[i]>maxV){maxV=cells[i];strong=i;}}
 float imb=maxV-minV,soc=analogRead(SOC_PIN)*100.0f/4095.0f,dis=analogRead(DISCHARGE_PIN)*3.0f/4095.0f;
 float limit=0.08f+(soc<20?.025f:0)-dis*.008f;if(limit<.04f)limit=.04f;
 Fault detected=NONE;
 if(frozenFault)detected=ADC_FROZEN;else if(jumpFault)detected=ADC_JUMP;else if(rangeFault)detected=ADC_RANGE;else if(imb>limit*1.7f)detected=CELL_IMBALANCE;
 // Statistical sanity: compare each sample to previous, tolerate modest change; injected jump button explicitly tests jump path.
 if(detected==NONE){for(int i=0;i<NUM_CELLS;i++){if(prevCells[i]>=0 && fabs(cells[i]-prevCells[i])>.35f){detected=ADC_JUMP;break;}}}
 for(int i=0;i<NUM_CELLS;i++)prevCells[i]=cells[i];
 if(detected!=NONE){digitalWrite(RELAY_PIN,LOW);digitalWrite(RED_LED,HIGH);digitalWrite(GREEN_LED,LOW);tone(BUZZER,1800,80);recovering=false;logTransition(FAILSAFE,detected);}
 else if(imb>limit){digitalWrite(RELAY_PIN,HIGH);digitalWrite(RED_LED,HIGH);digitalWrite(GREEN_LED,LOW);logTransition(DEGRADED,CELL_IMBALANCE);}
 else if(state==FAILSAFE){if(!recovering){recovering=true;recoveryAt=now;logTransition(FAILSAFE,RECOVERY_VERIFY);}if(now-recoveryAt>=RECOVERY_MS){recovering=false;digitalWrite(RELAY_PIN,HIGH);digitalWrite(RED_LED,LOW);digitalWrite(GREEN_LED,HIGH);logTransition(NORMAL,NONE);}}
 else{digitalWrite(RELAY_PIN,HIGH);digitalWrite(RED_LED,LOW);digitalWrite(GREEN_LED,HIGH);logTransition(NORMAL,NONE);}
 Serial.printf("{\"task\":\"2-6\",\"pack_v\":%.3f,\"soc\":%.1f,\"imbalance\":%.3f,\"weakest\":%d,\"strongest\":%d,\"limit\":%.3f,\"state\":\"%s\",\"fault\":\"%s\"}\n",pack,soc,imb,weak+1,strong+1,limit,stateName(state),faultName(fault));
 updateDisplay(pack,imb,soc);
}
