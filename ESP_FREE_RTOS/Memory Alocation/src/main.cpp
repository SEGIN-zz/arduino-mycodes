# include <Arduino.h>

#if !config_free_rtos_unicore
#define TASK_CPU APP_CPU_NUM
#else
#define TASK_CPU PRO_CPU_NUM
#endif

void mundanetask(void *parm)
{
  for(;;)
  {

    int a = 1;
    int b[100];
    for(int i = 0; i < 100; i++)
    {
      b[i] = a + 1;
    }
    Serial.println(b[0]);
  }

}

void setup()
{
  Serial.begin(115200);
  // vTaskDelay(1000/portTICK_PERIOD_MS);
  xTaskCreatePinnedToCore(
    mundanetask,
    "mundanetask",
    1500,
    NULL,
    1,
    NULL,
    APP_CPU_NUM
  );
//  vTaskDelete(NULL);



}


void loop()
{
  //
}