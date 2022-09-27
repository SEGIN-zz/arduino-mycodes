# include <Arduino.h>

#if !config_free_rtos_unicore
#define TASK_CPU APP_CPU_NUM
#else
#define TASK_CPU PRO_CPU_NUM
#endif

static const uint8_t buff_len = 255;
static char *msg_ptr = NULL;
static volatile uint8_t msg_flg = 0;


void readSerial(void *parm)
{
    char c;
    char buf[buff_len];
    uint8_t idx = 0;
    
    memset(buf, 0, buff_len);
    
  while(true)
  {
    if(Serial.available() > 0)
    {
      c = Serial.read();
 
      if (idx < buff_len -1)
      {
        buf[idx] = c;
        idx++;
      }

      if(c == '\n')
      {
        buf[idx - 1] = '\0';
        if (msg_flg == 0)
        {
          msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));
          configASSERT(msg_ptr);
          memcpy(msg_ptr,buf,idx);
          msg_flg = 1;  
        }
        memset(buf, 0, buff_len);
        idx = 0;
      } 
    }
  }
}


void printTask(void* parm)
{
  while(true)
  {
    if(msg_flg == 1)
    {
      Serial.println(msg_ptr);
      vPortFree(msg_ptr);
      msg_ptr = NULL;
      msg_flg = 0;
    }
  }
}


void setup()
{
  Serial.begin(115200);
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println("demo");

  xTaskCreatePinnedToCore(

    readSerial,
    "readSerial",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM

  );
  xTaskCreatePinnedToCore(
    
    printTask,
    "printTask",
    1024,
    NULL,
    1,
    NULL,
    APP_CPU_NUM

  );
  vTaskDelete(NULL);
}

  void loop()
  {
    //lol
  }