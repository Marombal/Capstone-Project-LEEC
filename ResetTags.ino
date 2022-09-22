//Bibliotecas necessarias para a utilização das funções importantes à resolução
#include <SPI.h>
#include <MFRC522.h>
//Biblioteca TFT
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

//LiquidCrystal_I2C lcd(0x27,16,2);

/*Using Hardware SPI of Arduino */
/*MOSI (11), MISO (12) and SCK (13) are fixed */
/*You can configure SS and RST Pins*/
#define SS_PIN 10  /* Slave Select Pin */
#define RST_PIN 9  /* Reset Pin */

// enunciacao das entradas do display
#define cs 3
#define dc 5
#define rst 4
// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_MOSI 6  // Data out
#define TFT_SCLK 7  // Clock out

char str[8];

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, TFT_MOSI, TFT_SCLK, rst);

/* Create an instance of MFRC522 */
MFRC522 mfrc522(SS_PIN, RST_PIN);
/* Create an instance of MIFARE_Key */
MFRC522::MIFARE_Key key;          

/* Set the block to which we want to write data */
/* Be aware of Sector Trailer Blocks */

int blockNum0 = 1;  

/* Create an array of 16 Bytes and fill it with data */
/* This is the actual data which is going to be written into the card */

char blockData0 [16] = {"0000000000000000"};


/* Create another array to read data rom Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
byte bufferLen = 18;
byte readBlockData0[18];

MFRC522::StatusCode status;



/*********************** Codigo ligacao *******************************/

#define CS_PIN 8
#define BAUD_RATE 9600
#define BUF 128
#define tamanho 16
byte i=0;
int k=0;
int X=0;


void setup() 
{
   pinMode(CS_PIN, OUTPUT);
   SPI.setBitOrder(MSBFIRST);
   SPI.setClockDivider(SPI_CLOCK_DIV16);
   SPI.setDataMode(SPI_MODE0);
   delay(1000);
  /* Initialize serial communications with the PC */
  Serial.begin(9600);
  /* Initialize SPI bus */
  SPI.begin();

  // OR use this initializer if using a 1.8" TFT screen with offset such as WaveShare:
   tft.initR(INITR_GREENTAB);      // Init ST7735S chip, green tab
  
  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  Serial.println("Scan a MIFARE 1K Tag to write data...");

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);


}

void loop()
{   
  /* Prepare the ksy for authentication */
  /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  Serial.println("Scan a MIFARE 1K Tag to write data...");
  
  tft.fillScreen(ST77XX_BLACK);
  
  /* Look for new cards */
  /* Reset the loop if no new card is present on RC522 Reader */
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  
  /* Select one of the cards */
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("\n");
  Serial.println("**Card Detected**");
  /* Print UID of the Card */
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("\n");
  /* Print type of card (for example, MIFARE 1K) */
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));


   Serial.print("\n");
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock0(blockNum0, readBlockData0);

   /* Call 'WriteDataToBlock' function, which will write data to the block */
   Serial.print("\n");
   Serial.println("Writing to Data Block...");
   WriteDataToBlock0(blockNum0, blockData0);

    
   /* ***********************CODIGO DE READ *****************************/
   
   // Read data from the same block 
   Serial.print("\n");
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock0(blockNum0, readBlockData0);

   delay(1000); //6000
}





/***************************************** FUNCOES DE ESCRITA EM CADA BLOCO *****************************************/

void WriteDataToBlock0(int blockNum0, byte blockData0[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum0, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Authentication failed for Write: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum0, blockData0, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Writing to Block failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Data was written into Block successfully");
  }
}


/* ***********************CODIGO DE READ *****************************/

void ReadDataFromBlock0(int blockNum0, byte readBlockData0[]) 
{
  // Authenticating the desired data block for Read access using Key A 
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum0, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  // Reading data from the Block 
  status = mfrc522.MIFARE_Read(blockNum0, readBlockData0, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Block was read successfully");  
  }
  
}
