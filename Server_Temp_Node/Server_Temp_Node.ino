//Include Libraries

#include "Arduino.h"

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
//#include <EEPROM.h>

#include <avr/io.h>
#include <avr/sleep.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#define OneWire_bus A3 //Data bus is connected to digital pin 6 of the arduino
OneWire oneWire(OneWire_bus); //Setup a OneWire instance to comm with any OneWire device
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

//Pin definitions for OLED connections
#define OLED_DC 6
#define OLED_CS 7
#define OLED_RST 8

#define MAX_RETRIES 60

int num_of_retries = MAX_RETRIES;

float get_temperature();
float temperature = 0;

#define DEBUG

#ifdef DEBUG
    #define DEBUG_BEGIN(x)    Serial.begin(x)
    #define DEBUG_PRINT(x)    Serial.print(x)
    #define DEBUG_PRINTLN(x)  Serial.println(x)
    #define OLED_CLR()        oled.clear()
    #define OLED_PRINT(x)     oled.print(x)
    #define OLED_PRINTLN(x)   oled.println(x)
    #define DEBUG_DELAY(x)    delay(x)
#else
    #define DEBUG_BEGIN(x)
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define OLED_CLR()
    #define OLED_PRINT(x)
    #define OLED_PRINTLN(x)
    #define DEBUG_DELAY(x)
#endif

SSD1306AsciiSpi oled;

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(10, 5);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/
#define node_ID 5				//Change this for every node (Unique number)
char send_packet[] = "005-23.34\n";	//Change this for every node (Unique number same as above)

struct payload_t
{
        unsigned long ms;
        unsigned long counter;
};	//; coz of structure

//Function prototype for sleep and wake up
void sleep();
void wake_up();
volatile char watchdog_interrupt_flag = 0;
int watchdog_count = 0;

//PIR sensor is connected on digital pin 3
int sensor_pin = 3;

int last_sensor_state = LOW;
int current_sensor_state = LOW;

//True if interrupt is received
bool sensor_interrupt_flag = false;

void sensor_ISR()
{
    sensor_interrupt_flag = true;
}

int transmit_to_master(char str[], char msg_type, int size_of_str) {

	//Write a message and if write fails renew addresses
    if (!mesh.write(str, msg_type, size_of_str))
    {
        // If a write fails, check connectivity to the mesh network
        if (!mesh.checkConnection()) {
            //refresh the network address
            //OLED_CLR();
            //OLED_PRINTLN("Renewing");
            //OLED_PRINTLN("Address");
            //DEBUG_PRINTLN("Renewing Address");
            mesh.renewAddress();				//Will try for one minute by default to renew addresses
        }
        else {
        	//Send fail, Test OK

            //OLED_CLR();
            //OLED_PRINTLN("Send fail");

            //DEBUG_PRINTLN("Send fail");
        }

        return 0;	//if send not ok
    }
    //If a write succeeds do this
    else
    {
        //OLED_CLR();
        //OLED_PRINTLN("Send OK: ");
        //OLED_PRINTLN(str);

        //DEBUG_PRINT("Send OK: ");
        //DEBUG_PRINTLN(str);

        return 1;	//if send ok
    }
}

void setup()
{
	//attachInterrupt(1, digitalInterrupt, CHANGE); //interrupt for waking up

    //SETUP WATCHDOG TIMER
    WDTCSR = (24);//change enable and WDE - also resets
    WDTCSR = (33);//prescalers only - get rid of the WDE and WDCE bit
    WDTCSR |= (1<<6);//enable interrupt mode

	//3.2xmA
	//#1
    ADCSRA &= ~(1<<7);  // disable ADC

    //3.2xmA
    //#2
	//Set not required pins to input (Output right??)
    DDRD = DDRD | 0b00010011;
    DDRC = DDRC | 0b00111111;
    DDRB = DDRB | 0b00000010;

    //delay(3000);	//2.5mA

    //17uA
    //#3
    //ENABLE SLEEP - this enables the sleep mode
    SMCR |= (1 << 2); //power down mode
    SMCR |= 1;//enable sleep

    //PIR Sensor is input
    pinMode(sensor_pin, INPUT);
    //attachInterrupt(digitalPinToInterrupt(sensor_pin), sensor_ISR, CHANGE);

    radio.begin();

    //Max power and minimum baud rate will increase the transmission range
	radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);

	//radio.setPALevel(RF24_PA_HIGH);
    //radio.setDataRate(RF24_1MBPS);

    #ifdef DEBUG
        oled.begin(&Adafruit128x64, OLED_CS, OLED_DC, OLED_RST);
        oled.setFont(System5x7);
        OLED_CLR();
        oled.set2X();

    #endif

    DEBUG_BEGIN(115200);
    //printf_begin();

    // Set the nodeID manually
    mesh.setNodeID(node_ID);
    // Connect to the mesh

    OLED_PRINTLN("Starting..");
    DEBUG_PRINTLN(F("Starting.."));

    mesh.begin();

    DEBUG_PRINTLN(F("Started"));

    /*
    //Get the current sensor state
    current_sensor_state = digitalRead(sensor_pin);

    if (current_sensor_state == HIGH)
        send_packet[4] = '1';
    else
        send_packet[4] = '0';
    //********************************************

    //Loop until package is not sent or num_of_retries is not over
    while(!transmit_to_master(send_packet, 'M', sizeof(send_packet)))
    {
    	delay(500);
    	num_of_retries--;

    	if (num_of_retries == 0) {
    		OLED_CLR();
    		OLED_PRINTLN("Max retries");
    		OLED_PRINTLN("exceeded!");

    		DEBUG_PRINTLN("Max retries exceeded!");

    		delay(10000);

    		break;
    	}
    }*/

    OLED_CLR();
    OLED_PRINTLN("Standing");
    OLED_PRINTLN("by...");

    DEBUG_PRINTLN(F("Standing by..."));

    pinMode(A4, OUTPUT);
    digitalWrite(A4, HIGH);

    sensors.begin(); //Initialize the sensor
}

void loop()
{
	//Very similar to network.update(), it needs to be called regularly to keep the network and the mesh going.
	//Call mesh.update to keep the network updated
    mesh.update();

    		//char test_packet[] = "005-30.12\n";

    		//Read sensor
    		Serial.println("Reading");
    		temperature = get_temperature();
    		Serial.print("Read: ");
    		Serial.println(temperature);

    		char charVal[10];               //temporarily holds data
    		dtostrf(temperature, 4, 4, charVal);

    		for(int i=0;i<5;i++)
    		{
    	    	send_packet[i+4] = charVal[i];
    		}

            num_of_retries = MAX_RETRIES;

            //DEBUG_PRINTLN(send_packet);

            Serial.print("Sending ");
            Serial.println(send_packet);

            while(!transmit_to_master(send_packet, 'M', sizeof(send_packet))){
                delay(500);
                num_of_retries--;

                if (num_of_retries == 0) {
                	//OLED_CLR();
                    //OLED_PRINTLN("Max retries");
                    //OLED_PRINTLN("exceeded!");

                    //DEBUG_PRINTLN("Max retries exceeded!");

                    break;
                }
            }
        sensor_interrupt_flag = false;

        DEBUG_DELAY(500);

        //OLED_CLR();
        //OLED_PRINTLN("Standing");
        //OLED_PRINTLN("by...");

    //Test whether there is a message available for this node.
    while (network.available()) {
        RF24NetworkHeader header;
        payload_t payload;
        network.read(header, &payload, sizeof(payload));

        OLED_CLR();
        OLED_PRINT("Received packet #");
        OLED_PRINT(payload.counter);
        OLED_PRINT(" at ");
        OLED_PRINTLN(payload.ms);

        DEBUG_PRINT("Received packet #");
        DEBUG_PRINT(payload.counter);
        DEBUG_PRINT(" at ");
        DEBUG_PRINTLN(payload.ms);
    }

    delay(500);
}

//Watchdog interrupt ISR
ISR(WDT_vect){
  //DON'T FORGET THIS!  Needed for the watch dog timer.  This is called after a watch dog timer timeout - this is the interrupt function called after waking up
	watchdog_interrupt_flag = 1;
}

void digitalInterrupt(){
}

//Function declaration for sleep
void sleep()
{
		//Make radio go to sleep
		mesh.releaseAddress();
		radio.powerDown();

		//BOD DISABLE - this must be called right before the __asm__ sleep instruction
		MCUCR |= (3 << 5); //set both BODS and BODSE at the same time
		MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time

		//uC goes to sleep
		__asm__  __volatile__("sleep");		//in line assembler to go to sleep
}

//Function declaration for waking up
void wake_up()
{
	radio.powerUp();
	mesh.renewAddress();	//Will try for one minute by default to renew addresses
	watchdog_count = 0;
}

float get_temperature()
{
	Serial.println("In fn");
	sensors.requestTemperatures(); //Request the temperature & store it in memory
	delay(1000);
	float Temp = sensors.getTempCByIndex(0); //Get the temp from the memory

	return Temp;
	//return 12.34;
}
