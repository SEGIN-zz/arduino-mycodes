#include <Arduino.h>

#if !config_unicore
#define TASK_CPU APP_CPU_NUM
#else
#define TASK_CPU PRO_CPU_NUM
#endif

static const uint8_t queue_len = 3;
static QueueHandle_t msg_queu;


void printMsg(void *parm)
{
  int item;

  while (true)
  {
    if (xQueueReceive(msg_queu,(void*)&item,0) == pdTRUE)
    {
      Serial.println(item); 
    }
    vTaskDelay(500/portTICK_PERIOD_MS);

  }
}

void setup()
{
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.print("------Queue Demo------");
  msg_queu = xQueueCreate(queue_len,sizeof(int));

  xTaskCreatePinnedToCore(
    printMsg,
    "printMsg",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM
  );

}

void loop()
{
  static int num = 0;

  if (xQueueSend(msg_queu,(void*) &num,5) != pdTRUE)
  {
    Serial.println("Queue full");
  }
  num++;
  vTaskDelay(100/portTICK_PERIOD_MS);
}