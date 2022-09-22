#include <SPI.h>
#include <MFRC522.h>

int mystr; //String data
char mystr1[10]="Hello!";

/*Using Hardware SPI of Arduino */
/*MOSI (11), MISO (12) and SCK (13) are fixed */
/*You can configure SS and RST Pins*/
#define SS_PIN 8  /* Slave Select Pin */
#define RST_PIN 7  /* Reset Pin */

/* Create an instance of MFRC522 */
MFRC522 mfrc522(SS_PIN, RST_PIN);
/* Create an instance of MIFARE_Key */
MFRC522::MIFARE_Key key;          

/* Set the block to which we want to write data */
/* Be aware of Sector Trailer Blocks */

int blockNum0 = 1;  
int blockNum1 = 2;
int blockNum2 = 5;

/* Create another array to read data from Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */

byte bufferLen = 18;
byte readBlockData0[18];
byte readBlockData1[18];
byte readBlockData2[18];

MFRC522::StatusCode status;

void setup() 
{
  /* Initialize serial communications with the PC */
  Serial.begin(9600);
  /* Initialize SPI bus */
  SPI.begin();
  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  //Serial.println("Scan a MIFARE 1K Tag to write data...");
}

void loop()
{
  /* Prepare the ksy for authentication */
  /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  
  mfrc522.PCD_Init();
  //Serial.println("Scan a MIFARE 1K Tag to write data...");
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
  /*_____Serial.print("\n");
  Serial.println("**Card Detected**");
  /* Print UID of the Card */
  /*_____Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.print("\n");
  /* Print type of card (for example, MIFARE 1K) */
  /*___Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));*/


   
   
   /* Read data from the same block */
   //Serial.print("\n");
   //Serial.println("Reading from Data Block...");
   ReadDataFromBlock0(blockNum0, readBlockData0);

   //Serial.print("\n");
   //Serial.println("Reading from Data Block...");
   ReadDataFromBlock1(blockNum1, readBlockData1);

   //Serial.print("\n");
   //Serial.println("Reading from Data Block...");
   ReadDataFromBlock2(blockNum2, readBlockData2);
   
   String forma= String((char *)readBlockData1);
   String cor= String((char *)readBlockData2);
  
   if(forma=="TRIANGULO      \0"){
      if(cor=="AMARELO        \0"){
      mystr=31;
    }
      else if(cor=="VERDE          \0"){
      mystr=32;
    }
      else if(cor=="VERMELHO       \0"){
      mystr=33;
    }
   }

   
    else if(forma=="RETANGULO      \0"){
       if(cor=="AMARELO        \0"){
      mystr=41;
    }
      else if(cor=="VERDE          \0"){
      mystr=42;
    }
      else if(cor=="VERMELHO       \0"){
      mystr=43;
    }
   }


   
    else if(forma=="CIRCULO        \0"){
      if(cor=="AMARELO        \0"){
      mystr=21;
    }
      else if(cor=="VERDE          \0"){
      mystr=22;
    }
      else if(cor=="VERMELHO       \0"){
      mystr=23;
    }
   }

    else if(forma=="ESTRELA        \0"){
       if(cor=="AMARELO        \0"){
      mystr=11;
    }
      else if(cor=="VERDE          \0"){
      mystr=12;
    }
      else if(cor=="VERMELHO       \0"){
      mystr=13;
    }
   }
  
   //___________________

  Serial.write(mystr); //Write the serial data
  Serial.println(mystr);
  delay(1000);

  //___________________
  /*Serial.println("__________");
  //Serial.println(readBlockData1);
  //Serial.println(readBlockData2);
  delay(2000);
  Serial.println("__________");
  Serial.println(forma);
  Serial.println(cor);*/
   /* Print the data read from block */
   /* ******************* TESTE ************/
  /* Serial.print("\n");
   Serial.print("Número da peça:");
   Serial.print(blockNum0);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.write(readBlockData0[j]);
   }
   Serial.print("\n");
   
   Serial.print("Forma:");
   //Serial.print(blockNum1);
   Serial.print(" --> ");
   for (int h=0 ; h<16 ; h++)
   {
     Serial.write(readBlockData1[h]);
   }
   Serial.print("\n");

   Serial.print("Cor:");
   //Serial.print(blockNum2);
   Serial.print(" --> ");
   for (int k=0 ; k<16 ; k++)
   {
     Serial.write(readBlockData2[k]);
   }
   Serial.print("\n");

   Serial.print("Área:");
   //Serial.print(blockNum3);
   Serial.print(" --> ");
   for (int l=0 ; l<16 ; l++)
   {
     Serial.write(readBlockData3[l]);
   }
   Serial.print("\n");
   /********************************************/
  //Serial.print(mystr1);
   //delay(2000);
}


void ReadDataFromBlock0(int blockNum0, byte readBlockData0[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum0, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     //Serial.print("Authentication failed for Read: ");
     //Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    //Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum0, readBlockData0, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    //Serial.print("Reading failed: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    //Serial.println("Block was read successfully");  
  }
  
}

void ReadDataFromBlock1(int blockNum1, byte readBlockData1[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum1, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     //Serial.print("Authentication failed for Read: ");
     //Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    //Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum1, readBlockData1, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    //Serial.print("Reading failed: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    //Serial.println("Block was read successfully");  
  }
  
}

void ReadDataFromBlock2(int blockNum2, byte readBlockData2[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum2, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     //Serial.print("Authentication failed for Read: ");
     //Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    //Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum2, readBlockData2, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    //Serial.print("Reading failed: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    //Serial.println("Block was read successfully");  
  }
  
}
