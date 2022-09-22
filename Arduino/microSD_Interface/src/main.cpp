/* Main library */
#include "Arduino.h"
#include <Arduino_FreeRTOS.h>
#include "timers.h"
#include <semphr.h>

/* Communication library */
#include <SPI.h>

/* Sensor & Device library */
#include <SD.h>

const int chipSelect = 53;

#define Finename "log.txt"

SemaphoreHandle_t xSerialSemaphore;

File myFile;

void TaskWriteSD(void *pvParameters);

void setup() {
    Serial.begin(115200);

    Serial.println(myFile);
    myFile = SD.open("log.txt", FILE_WRITE); 
    Serial.println(myFile);

    if(SD.begin(chipSelect)){
        Serial.println("SD Card is ready");
        if(myFile){
            Serial.println("SD File is ready");
            myFile.println("Date, Time, Latitude, Longitude, Altitude\n");
            myFile.close();
        }
        else{
            Serial.println("SD File is not ready");
            while(1);
        }
    }

    /* Semaphire Setting */
    if((xSerialSemaphore = xSemaphoreCreateMutex()) != NULL)
        xSemaphoreGive((xSerialSemaphore));

    xTaskCreate(TaskWriteSD, "TaskWriteSD", 1024, NULL, 1, NULL);

    Serial.println("Start");
}

void loop() {}

void TaskWriteSD(void *pvParameters) {

    myFile = SD.open("log.txt");

    String dataString = "";

    for(;;) {
        if(xSemaphoreTake(xSerialSemaphore, (TickType_t)10) == pdTRUE) {
            if(myFile){
                dataString = "2022, 10:34:22, 34.22241, 128.42334, 1\n";
                myFile.println(dataString);
                myFile.close();
                Serial.println("Write SD");
            }
            xSemaphoreGive(xSerialSemaphore);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// #include <Arduino.h>

// #include <SD.h>
// #include <SPI.h>

// const int chipSelect = 53;

// void setup() {
//     // Open serial communications and wait for port to open:
//     Serial.begin(115200);
//     // wait for Serial Monitor to connect. Needed for native USB port boards
//     // only:
//     while(!Serial)
//         ;

//     Serial.print("Initializing SD card...");

//     if(!SD.begin(chipSelect)) {
//         Serial.println("initialization failed. Things to check:");
//         Serial.println("1. is a card inserted?");
//         Serial.println("2. is your wiring correct?");
//         Serial.println("3. did you change the chipSelect pin to match your "
//         "shield or module?"); Serial.println("Note: press reset button on the
//         board and reopen this " "Serial Monitor after fixing your issue!");
//         while(true) ;
//     }

//     Serial.println("initialization done.");
// }

// void loop() {
//     // make a string for assembling the data to log:
//     String dataString = "";

//     // read three sensors and append to the string:
//     for(int analogPin = 0; analogPin < 3; analogPin++) {
//         int sensor = analogRead(analogPin);
//         dataString += String(sensor);
//         if(analogPin < 2) {
//             dataString += ",";
//         }
//     }

//     // open the file. note that only one file can be open at a time,
//     // so you have to close this one before opening another.
//     File dataFile = SD.open("datalog.txt", FILE_WRITE);

//     // if the file is available, write to it:
//     if(dataFile) {
//         dataFile.println(dataString);
//         dataFile.close();
//         // print to the serial port too:
//         Serial.println(dataString);
//     }
//     // if the file isn't open, pop up an error:
//     else {
//         Serial.println("error opening datalog.txt");
//     }
// }

// #include <SD.h>
// #include <SPI.h>

// // set up variables using the SD utility library functions:
// Sd2Card card;
// SdVolume volume;
// SdFile root;

// // change this to match your SD shield or module;
// // Default SPI on Uno and Nano: pin 10
// // Arduino Ethernet shield: pin 4
// // Adafruit SD shields and modules: pin 10
// // Sparkfun SD shield: pin 8
// // MKR Zero SD: SDCARD_SS_PIN
// const int chipSelect = 53;

// void setup() {
//     // Open serial communications and wait for port to open:
//     Serial.begin(115200);
//     while(!Serial) {
//         ; // wait for serial port to connect. Needed for native USB port only
//     }

//     Serial.print("\nInitializing SD card...");

//     // we'll use the initialization code from the utility libraries
//     // since we're just testing if the card is working!
//     if(!card.init(SPI_HALF_SPEED, chipSelect)) {
//         Serial.println("initialization failed. Things to check:");
//         Serial.println("* is a card inserted?");
//         Serial.println("* is your wiring correct?");
//         Serial.println("* did you change the chipSelect pin to match your shield or module?");
//         Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
//         while(1)
//             ;
//     } else {
//         Serial.println("Wiring is correct and a card is present.");
//     }

//     // print the type of card
//     Serial.println();
//     Serial.print("Card type:         ");
//     switch(card.type()) {
//     case SD_CARD_TYPE_SD1:
//         Serial.println("SD1");
//         break;
//     case SD_CARD_TYPE_SD2:
//         Serial.println("SD2");
//         break;
//     case SD_CARD_TYPE_SDHC:
//         Serial.println("SDHC");
//         break;
//     default:
//         Serial.println("Unknown");
//     }

//     // Now we will try to open the 'volume'/'partition' - it should be FAT16 or
//     // FAT32
//     if(!volume.init(card)) {
//         Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
//         while(1);
//     }

//     Serial.print("Clusters:          ");
//     Serial.println(volume.clusterCount());
//     Serial.print("Blocks x Cluster:  ");
//     Serial.println(volume.blocksPerCluster());

//     Serial.print("Total Blocks:      ");
//     Serial.println(volume.blocksPerCluster() * volume.clusterCount());
//     Serial.println();

//     // print the type and size of the first FAT-type volume
//     uint32_t volumesize;
//     Serial.print("Volume type is:    FAT");
//     Serial.println(volume.fatType(), DEC);

//     volumesize = volume.blocksPerCluster();       // clusters are collections of blocks
//     volumesize *= volume.clusterCount(); // we'll have a lot of clusters
//     volumesize /= 2; // SD card blocks are always 512 bytes (2 blocks are 1 KB)
//     Serial.print("Volume size (KB):  ");
//     Serial.println(volumesize);
//     Serial.print("Volume size (MB):  ");
//     volumesize /= 1024;
//     Serial.println(volumesize);
//     Serial.print("Volume size (GB):  ");
//     Serial.println((float)volumesize / 1024.0);

//     Serial.println("\nFiles found on the card (name, date and size in bytes): ");
//     root.openRoot(volume);

//     // list all files in the card with date and size
//     root.ls(LS_R | LS_DATE | LS_SIZE);
//     root.close();
// }

// void loop(void) {}


// #include <SPI.h>
// #include <SD.h>

// const int chipSelect = 53;
// File myFile;

// void setup() {
//   // Open serial communications and wait for port to open:
//   Serial.begin(115200);
//   // wait for Serial Monitor to connect. Needed for native USB port boards only:
//   while (!Serial);

//   Serial.print("Initializing SD card...");

//   if (!SD.begin(chipSelect)) {
//     Serial.println("initialization failed. Things to check:");
//     Serial.println("1. is a card inserted?");
//     Serial.println("2. is your wiring correct?");
//     Serial.println("3. did you change the chipSelect pin to match your shield or module?");
//     Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
//     while (true);
//   }

//   Serial.println("initialization done.");

//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   myFile = SD.open("conc.txt", FILE_WRITE);
//     Serial.println(myFile);

//   // if the file opened okay, write to it:
//   if (myFile) {
//     Serial.print("Writing to conc.txt...");
//     myFile.println("testing 1, 2, 3.");
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening conc.txt");
//   }

//   // re-open the file for reading:
//   myFile = SD.open("conc.txt");
//   if (myFile) {
//     Serial.println("conc.txt:");

//     // read from the file until there's nothing else in it:
//     while (myFile.available()) {
//       Serial.write(myFile.read());
//     }
//     // close the file:
//     myFile.close();
//   } else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening conc.txt");
//   }
// }

// void loop() {
//   // nothing happens after setup
// }