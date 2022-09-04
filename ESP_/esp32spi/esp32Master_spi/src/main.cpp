# include <Arduino.h>
# include <SPI.h>


SPIClass *vspi = NULL;

void spiCommand(SPIClass *spi, byte data);
void sendString(SPIClass *spi);

//seting up spi clock as 1 MHz;
static const int spiCLK = 1000000; // 1 MHz

void setup()
{
/* 
    vspi->begin() init vspi by using std pins, if want to use
    coustum pins use vspi -> begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS)
*/
  vspi->begin();
  pinMode(vspi->pinSS(), OUTPUT);

  // snd string through spi fro 3 times
  for (int i = 0; i < 3; i++)
  {
    sendString(vspi);
    delay(1);
  }

}
void loop()
{
  // lul

}

void spiCommand(SPIClass *spi, byte data)
{
  spi->beginTransaction(SPISettings(spiCLK, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW); 
  spi->transfer(data);
  digitalWrite(spi->pinSS(), HIGH); 
  spi->endTransaction();
}

void sendString(SPIClass *spi)
{
  spi->beginTransaction(SPISettings(spiCLK, MSBFIRST, SPI_MODE0));
  digitalWrite(spi->pinSS(), LOW);
  char array [] = {'H','I','!'};
  for(int i = 0; i < 3; i++)
  {
    spi->transfer(array[i]);
  }
  digitalWrite(spi->pinSS(), HIGH);
  spi->endTransaction();

}
