# include <Arduino.h>

# if ! CONFIG_FREERTOS_UNICORE
# define TASK_CPU APP_CPU_NUM
# else
# define TASK_CPU PRO_CPU_NUM
# endif

int potVal = 0;


void readpot(void *parm)
{
  while(true)
  {
    potVal = analogRead(35);
    Serial.println(potVal);
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(35,INPUT);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  xTaskCreatePinnedToCore(
    readpot,
    "readPot",
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