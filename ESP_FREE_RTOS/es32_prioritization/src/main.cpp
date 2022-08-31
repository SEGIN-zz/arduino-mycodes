# include<Arduino.h>

# if !CONFIG_FREERTOS_UNICORE
# define TASK_CPU APP_CPU_NUM
# else
# define TASK_CPU PRO_CPU_NUM
# endif

const char msg[] = "Hi my name is black";

static TaskHandle_t task_0 = NULL;
static TaskHandle_t task_1 = NULL;

void startTask0(void *parm)
{
  int mesg_len = strlen(msg);
  
  while(true)
  {
    for (int i = 0; i < mesg_len; i++)
    {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void startTask1(void *parm)
{
  while(true)
  {
    Serial.print("*");
    Serial.println();
    vTaskDelay(100/ portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(300);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("----Free-RTOS TASK----");
  Serial.printf("setup & loop are running on core %i with priority %i"
  ,xPortGetCoreID,uxTaskPriorityGet(NULL));

  xTaskCreatePinnedToCore(
    startTask0,
    "Start Task 0",
    1024,
    NULL,
    1,
    &task_0,
    APP_CPU_NUM
  );

  xTaskCreatePinnedToCore(
    startTask1,
    "Start Task 1",
    1024,
    NULL,
    2,
    &task_1,
    APP_CPU_NUM
  );

}
void loop()
{
  for (int i = 0; i < 3; i++ )
  {
    vTaskSuspend(task_1);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(task_1);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
  if(task_0 != NULL)
  {
    vTaskDelete(task_0);
    task_0 = NULL;
  }

}