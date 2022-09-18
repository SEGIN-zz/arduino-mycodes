# include <Arduino.h>
# include <stdio.h>

# if !CONFIG_FREERTOS_UNICORE
# define TASK_CPU APP_CPU_NUM
# else
# define TASk_CPU PRO_CPU_NUM
# endif

static const uint8_t buf_len = 20;

int dy = 500;

void readCerial (void * parm)
{
  char c;
  char buf[buf_len];

  uint8_t idx = 0;
  
  memset(buf, 0, buf_len);
  while(true)
  {
    if (Serial.available() > 0)
    {
      c = Serial.read();
      
      if (c == '\n')
      {
        dy = atoi(buf);
        Serial.printf("delay is : %i",dy);
        memset(buf, 0, buf_len);
        idx = 0;
      }
      else
      {
        if (idx < buf_len - 1)
        {
          buf[idx] = c;
          idx++;
        }
      }
    }
  }
} 

void blinkmyLed(void *parm )
{
  while(true)
  {
    digitalWrite(2,HIGH);
    vTaskDelay(dy/portTICK_PERIOD_MS);
    digitalWrite(2,LOW);
    vTaskDelay(dy/portTICK_PERIOD_MS);
  }
}
void setup() 
{ 
  pinMode(2,OUTPUT); 
  Serial.begin(115200);
  vTaskDelay(1000/ portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(
    readCerial,
    "readCerial",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM
  );

  xTaskCreatePinnedToCore(
    blinkmyLed,
    "blinkmyLed",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM
  );

}

void loop() 
{
  //
} 


