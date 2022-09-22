//Bibliotecas necessarias para a utilização das funções importantes à resolução
#include <SPI.h>
#include <MFRC522.h>
//Biblioteca TFT
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

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


//Cores
#define Preto 0x0000
#define Azul 0x001F
#define Vermelho 0xF800
#define Verde 0x07E0
#define Amarelo 0xFFE0
#define Branco 0xFFFF

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
int blockNum1 = 2;
int blockNum2 = 5;
int blockNum3 = 6;

/* Create an array of 16 Bytes and fill it with data */
/* This is the actual data which is going to be written into the card */

char blockData0 [16];
char blockData1 [16];
char blockData2 [16];

/* Create another array to read data from Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
byte bufferLen = 18;
byte readBlockData0[18];
byte readBlockData1[18];
byte readBlockData2[18];

int w = 0;
int count = 0;

bool flag1;
bool flag2;
bool flag3;
bool flag4;
bool flag5;
bool flag6;
bool flag7;
bool flag8;
bool flag9;
bool flag10;
bool flag11;
bool flag12;

char Objeto1[9] = "Objeto 1 ";
char Objeto2[9] = "Objeto 2 ";
char Objeto3[9] = "Objeto 3 ";
char Objeto4[9] = "Objeto 4 ";
char Objeto5[9] = "Objeto 5 ";
char Objeto6[9] = "Objeto 6 ";
char Objeto7[9] = "Objeto 7 ";
char Objeto8[9] = "Objeto 8 ";
char Objeto9[9] = "Objeto 9 ";
char Objeto10[9] = "Objeto 10";
char Objeto11[9] = "Objeto 11";
char Objeto12[9] = "Objeto 12";

int comp1;
int comp2;
int comp3;
int comp4;
int comp5;
int comp6;
int comp7;
int comp8;
int comp9;
int comp10;
int comp11;
int comp12;

char forma1[9]="RETANGULO";
char forma2[9]="TRIANGULO";
char forma3[7]="ESTRELA";
char forma4[7]="CIRCULO";

int verifica;

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
  Serial.println(F("Scan a MIFARE 1K Tag to write data..."));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);


 Objeto1[8] = 0;
 Objeto2[8] = 0;
 Objeto3[8] = 0;
 Objeto4[8] = 0;
 Objeto5[8] = 0;
 Objeto6[8] = 0;
 Objeto7[8] = 0;
 Objeto8[8] = 0;
 Objeto9[8] = 0;

 flag1 = 0;
 flag2 = 0;
 flag3 = 0;
 flag4 = 0;
 flag5 = 0;
 flag6 = 0;
 flag7 = 0;
 flag8 = 0;
 flag9 = 0;
 flag10 = 0;
 flag11 = 0;
 flag12 = 0;
}

void loop()
{
  /************************* CODIGO LIGACAO CAMARA ********************************/
   verifica=0;
   int32_t len = 0;
   int32_t TamanhoTotal = 0;
   char buff[BUF] = {1};
   digitalWrite(CS_PIN, LOW);
   delay(1); // Give the OpenMV Cam some time to setup to send data.

   i=SPI.transfer(1);
   delayMicroseconds(20);
   if(i == 85) { // saw sync char?
     SPI.transfer(&len, 4); // get length
     TamanhoTotal = len;
     if (len) {
       SPI.transfer(&buff, min(len,BUF));
       len -= min(len, BUF);
       
     }
     while (len) SPI.transfer(0); // eat any remaining bytes

   }
   else {
    Serial.print(F("Deu erro:"));
    }

   digitalWrite(CS_PIN, HIGH);

 
  //************************************************** CAMARA *****************************************************
 
   for(int j=0; j<tamanho;j++){
      blockData1[j] = buff[j];
     }
     
   for(int i=tamanho; i<2*tamanho;i++){
      blockData2[k] = buff[i];
      k++;
     }
     k=0;
   
   delay(1); // Don't loop to quickly.
   
  
  /* Prepare the ksy for authentication */
  /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }

  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  Serial.println(F("Scan a MIFARE 1K Tag to write data..."));
  
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
  Serial.println(F("**Card Detected**"));
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
   Serial.println(F("Reading from Data Block..."));
   ReadDataFromBlock0(blockNum0, readBlockData0);

   char compara[9];

    for(int z=0; z < 9; z++){
      compara[z] = readBlockData0[z];
    }
/*********************************** Testes **************************************************
    Serial.print(F("compara:"));
    for(int y=0; y < 9; y++){
      Serial.print(compara[y], DEC);
      Serial.print(" ");
    }
    Serial.println("");
    for(int b=0; b < 9; b++){
      Serial.print(Objeto1[b], DEC);
      Serial.print(" ");
    }
    Serial.println("");
    
    Serial.print(F("read:"));
    Serial.println(readBlockData0[18]);
    Serial.print(F("flag:"));
    Serial.println(flag1);
    
***********************************************************************************************
    Serial.println(z);
       Serial.print(F("C"));
       Serial.println(compara[z],DEC);
       Serial.print(F("O"));
       Serial.println(Objeto1[z],DEC);
    
*********************************************************************************************/
    
    comp1=1;
    
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto1[z]){
        comp1=0;
        break;
      }
    }
    comp2=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto2[z]){
        comp2=0;
        break;
      }
    }
    comp3=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto3[z]){
        comp3=0;
        break;
      }
    }
    comp4=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto4[z]){
        comp4=0;
        break;
      }
    }
    comp5=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto5[z]){
        comp5=0;
        break;
      }
    }
    comp6=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto6[z]){
        comp6=0;
        break;
      }
    }
    comp7=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto7[z]){
        comp7=0;
        break;
      }
    }
    comp8=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto8[z]){
        comp8=0;
        break;
      }
    }
    comp9=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto9[z]){
        comp9=0;
        break;
      }
    }
    comp10=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto10[z]){
        comp10=0;
        break;
      }
    }
    comp11=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto11[z]){
        comp11=0;
        break;
      }
    }
    comp12=1;
    for(int z=0;z<8;z++){
      if(compara[z]!=Objeto12[z]){
        comp12=0;
        break;
      }
    }

    for(int z=0;z<9;z++){
      if(blockData1[z]!=forma1[z]){
        verifica++;
        break;
      }
    }
    for(int z=0;z<9;z++){
      if(blockData1[z]!=forma2[z]){
        verifica++;
        break;
      }
    }
    for(int z=0;z<7;z++){
      if(blockData1[z]!=forma3[z]){
        verifica++;
        break;
      }
    }
    for(int z=0;z<7;z++){
      if(blockData1[z]!=forma4[z]){
        verifica++;
        break; 
      }
    }

    if(verifica==4)
    {
       Serial.println(F("não e importante"));
       return;
    }
    
   if(comp1){
    if(flag1 == 1){
      Serial.println(F("ENTROU"));
      return;
    }
   }
   else if(comp2){
    if(flag2 == 1){
      return;
    }
   }
   else if(comp3){
    if(flag3 == 1){
      return;
    }
   }
   else if(comp4){
    if(flag4 == 1){
      return;
    }
   }
   else if(comp5){
    if(flag5 == 1){
      return;
    }
   }
   else if(comp6){
    if(flag6 == 1){
      return;
    }
   }
   else if(comp7){
    if(flag7 == 1){
      return;
    }
   }
   else if(comp8){
    if(flag8 == 1){
      return;
    }
   }
   else if(comp9){
    if(flag9 == 1){
      return;
    }
   }
   else if(comp10){
    if(flag10 == 1){
      return;
    }
   }
   else if(comp11){
    if(flag11 == 1){
      return;
    }
   }
   else if(comp12){
    if(flag12 == 1){
      return;
    }
   }

  

   char string[6] = {"Objeto"};
   count = count + 1;
   char sCount[3];

   sCount[3] = itoa(count, sCount, 10);

   strcpy(blockData0, string);
   strcat(blockData0, " ");
   strcat(blockData0, sCount);
   blockData0[8] = '\0'; 

   /* Call 'WriteDataToBlock' function, which will write data to the block */
   Serial.print(F("\n"));
   Serial.println(F("Writing to Data Block..."));
   WriteDataToBlock0(blockNum0, blockData0);

   if(count == 1) flag1 = 1;
   else if (count == 2) flag2 = 1;
   else if (count == 3) flag3 = 1;
   else if (count == 4) flag4 = 1;
   else if (count == 5) flag5 = 1;
   else if (count == 6) flag6 = 1;
   else if (count == 7) flag7 = 1;
   else if (count == 8) flag8 = 1;
   else if (count == 9) flag9 = 1;
   else if (count == 10) flag10 = 1;
   else if (count == 11) flag11 = 1;
   else if (count == 12) flag12 = 1;
    
   Serial.print(F("\n"));
   Serial.println(F("Writing to Data Block..."));
   WriteDataToBlock1(blockNum1, blockData1);

   Serial.print(F("\n"));
   Serial.println(F("Writing to Data Block..."));
   WriteDataToBlock2(blockNum2, blockData2);

/* ***********************CODIGO DE READ *****************************/
   
   // Read data from the same block 
   Serial.print(F("\n"));
   Serial.println(F("Reading from Data Block..."));
   ReadDataFromBlock0(blockNum0, readBlockData0);

   Serial.print(F("\n"));
   Serial.println(F("Reading from Data Block..."));
   ReadDataFromBlock1(blockNum1, readBlockData1);

   Serial.print(F("\n"));
   Serial.println(F("Reading from Data Block..."));
   ReadDataFromBlock2(blockNum2, readBlockData2);
   
   // If you want to print the full memory dump, uncomment the next line 
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

   // Print the data read from block
  

   Serial.println(F("readBlockData0: ")); 
   for(int i=0; i < 8; i++){
      Serial.print(readBlockData0[i]);
      Serial.print(" ");  
   }
   Serial.println("");

   tft.setCursor(0, 0);
   tft.println(F("Numero da peca:"));
   Serial.print(F("Objeto:"));
   for (int j=0 ; j<16 ; j++)
   {
     tft.setCursor(j*5, 10);
     //tft.write(readBlockData0[j]);
     
    Serial.println(readBlockData0[j]);
     
     sprintf(str,"%c",readBlockData0[j]);
     tft.print(str);
     //Serial.print(readBlockData0[j]); */
   }

   tft.setCursor(0, 30);
   tft.println(F("Forma da peca:"));
   for (int h=0 ; h<16 ; h++)
   {
     tft.setCursor(h*5, 40);
     tft.write(readBlockData1[h]);
   }
      
   tft.setCursor(0, 60);
   tft.println(F("Cor da peca:"));
   for (int k=0 ; k<16 ; k++)
   {
     tft.setCursor(k*5, 70);
     tft.write(readBlockData2[k]);
   }


    String Forma = String((char *)readBlockData1);
    String Cor = String((char *)readBlockData2);
    Serial.print(F("Cor:"));
    Serial.println(Cor);

    
    Serial.print(F("Forma:"));
    Serial.println(Forma);
 

   if (Forma == "RETANGULO      \0"){
      if(Cor == "AMARELO"){
       tft.fillRect(30, 120, 70, 40, Amarelo); 
      }
      if(Cor == "VERDE          \0"){
       tft.fillRect(30, 120, 70, 40, Verde); 
      }
      if(Cor == "VERMELHO       \0"){
       tft.fillRect(30, 120, 70, 40, Vermelho);
      } 
      /*if(Cor == "AZUL           \0"){
       tft.fillRect(30, 120, 70, 40, Azul);
      }*/
      /*if(Cor == "PRETO"){
       tft.drawRect(30, 120, 70, 40, Branco); 
      }*/
   }

   if (Forma == "ESTRELA        \0"){
      if(Cor == "AMARELO"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Amarelo);
       tft.fillTriangle(60, 150, 40, 100, 80, 100, Amarelo);
       //tft.fillTriangle(60, 110, 40, 140, 80, 140, Amarelo);
      }
      if(Cor == "VERDE          \0"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Verde);
       tft.fillTriangle(60, 150, 40, 120, 80, 120, Verde);
      }
      if(Cor == "VERMELHO       \0"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Vermelho);
       tft.fillTriangle(60, 150, 40, 120, 80, 120, Vermelho); 
      } 
      /*if(Cor == "AZUL            \0"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Azul);
       tft.fillTriangle(60, 150, 40, 120, 80, 120, Azul);
      }*/
      /*if(Cor == "PRETO"){
       tft.drawTriangle(60, 110, 40, 140, 80, 140, Branco);
       tft.drawTriangle(60, 150, 40, 120, 80, 120, Branco);  
      }*/
   }

   if (Forma == "CIRCULO        \0"){
      if(Cor == "AMARELO"){
       tft.fillCircle(60, 130, 20, Amarelo); 
      }
      if(Cor == "VERDE          \0"){
       tft.fillCircle(60, 130, 20, Verde); 
      }
      if(Cor == "VERMELHO       \0"){
        tft.fillCircle(60, 130, 20, Vermelho);  
      } 
      /*if(Cor == "AZUL           \0"){
        tft.fillCircle(60, 130, 20, Azul);  
      }*/
      /*if(Cor == "PRETO"){
       tft.drawCircle(60, 130, 20, Branco); 
      }*/
   }
   if (Forma == "TRIANGULO      \0"){
      if(Cor == "AMARELO"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Amarelo);
      }
      if(Cor == "VERDE          \0"){
       tft.fillTriangle(60, 110, 40, 140, 80, 140, Verde); 
      }
      if(Cor == "VERMELHO       \0"){
        tft.fillTriangle(60, 110, 40, 140, 80, 140, Vermelho);  
      } 
      /*if(Cor == "AZUL           \0"){
        tft.fillTriangle(60, 110, 40, 140, 80, 140, Azul); 
      }*/
      /*if(Cor == "PRETO"){
       tft.drawRect(60, 110, 40, 140, 80, 140, Branco); 
      }*/
   }   

   //digitalWrite(SS_PIN, HIGH);
   delay(1000); //6000
}





/***************************************** FUNCOES DE ESCRITA EM CADA BLOCO *****************************************/

void WriteDataToBlock0(int blockNum0, byte blockData0[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum0, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed for Write: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Authentication success"));
  }

  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum0, blockData0, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Writing to Block failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Data was written into Block successfully");
  }
}

void WriteDataToBlock1(int blockNum1, byte blockData1[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum1, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed for Write: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum1, blockData1, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Writing to Block failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Data was written into Block successfully"));
  }
}

void WriteDataToBlock2(int blockNum2, byte blockData2[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum2, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Authentication failed for Write: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Authentication success"));
  }

  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum2, blockData2, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Writing to Block failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Data was written into Block successfully"));
  }
}







/* ***********************CODIGO DE READ *****************************/

void ReadDataFromBlock0(int blockNum0, byte readBlockData0[]) 
{
  // Authenticating the desired data block for Read access using Key A 
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum0, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print(F("Authentication failed for Read: "));
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
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Block was read successfully");  
  }
  
}

void ReadDataFromBlock1(int blockNum1, byte readBlockData1[]) 
{
  // Authenticating the desired data block for Read access using Key A 
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum1, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print(F("Authentication failed for Read: "));
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  // Reading data from the Block 
  status = mfrc522.MIFARE_Read(blockNum1, readBlockData1, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Block was read successfully"));  
  }
  
}

void ReadDataFromBlock2(int blockNum2, byte readBlockData2[]) 
{
  // Authenticating the desired data block for Read access using Key A 
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum2, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println(F("Authentication success"));
  }

  // Reading data from the Block 
  status = mfrc522.MIFARE_Read(blockNum2, readBlockData2, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println(F("Block was read successfully"));  
  }
  
}
