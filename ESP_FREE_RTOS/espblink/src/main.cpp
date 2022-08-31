# include <Arduino.h>

// making sure esp32 ony uses 1 core why? ,bcz we can
#if !CONFIG_FREERTOS_UNICORE

#define TASK_CPU APP_CPU_NUM // Core 1
#else
#define TASK_CPU PRO_CPU_NUM // Core 0
#endif

static const int led_pin = 2; 

void toggleLed (void *parm)   // void *parm should allways be passed
{
  while(true)
  {

  digitalWrite(led_pin,HIGH);
  vTaskDelay(300 / portTICK_PERIOD_MS);
  digitalWrite(led_pin,LOW);
  vTaskDelay(300 / portTICK_PERIOD_MS); // portTICK_PERIOD_MS = 1 
  
/*
  vtaskDelay() -> tells the scheduler to run other tasks
  untill the specified time is over.

  Tic period as 1ms

  Tick timmer is a mc hardware timmer that is alocated to interrupt 
  the processor at a specific interrupt
  
  The interrupt period is called a tick.
  The seheduler has an opprtunity to run each tick to figure out which 
  task needs to run for that tick
*/

  }
}

void toggleLedDif(void *parm)
{
  while(true)
  {
    digitalWrite(2,HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    digitalWrite(2,LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);

  }
}

void setup() 
{
  Serial.begin(115200);
  pinMode(2,OUTPUT);

  xTaskCreatePinnedToCore(
    toggleLed,    // function to be called
    "Toggle LED", // name of the task
    1024,         // stack size
    NULL,         // parameters to pass to the function
    1,            // task priority(0 to 24)
    NULL,         // Task handle
    APP_CPU_NUM
    );

  xTaskCreatePinnedToCore(
    toggleLedDif,
    "Toggle LED DIFF",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM
    );
    
}

void loop()
{
  // lol
}