#include "liushuideng.h"
#include "user_beep.h"
#include "led.h"
#include "buzzer.h"

void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
  uint16_t i = 0U; /* 循环计数变量 */
  uint16_t LED_COUNT = 4U;

  /* if 判断：LED 编号只允许 1~4 */
  if (led_num > LED_COUNT)
  {
    return;/* return 直接结束当前函数 */
  }

  /* for 循环：初始化; 判断条件; 每次循环后执行 */
  for (i = 0U; i < times; i++)
  {
    led_on(led_num);          /* 点亮指定 LED */
    HAL_Delay(delay_ms);      /* 延时一段时间 */
    led_off(led_num);         /* 熄灭指定 LED */
    HAL_Delay(delay_ms);
  }
}

void beep(uint32_t beep_ms)
{
  buzzer_on();          /* 打开蜂鸣器 */
  HAL_Delay(beep_ms);   /* 保持响一段时间 */
  buzzer_off();         /* 关闭蜂鸣器 */
}

void alarm_sys_func(void)
{
  static uint8_t mode = 0U;
  uint8_t led;
  uint8_t DELAY_MS;
  uint8_t delay_ms;
  uint8_t i;

  switch(mode)
	{
	  case 0U:
	  HAL_Delay(5000); //延时5秒
	  break;
	
	  case 1U:
	  for(i=0;i<5;i++)
	  {
	    for(led=1U;led<5U;led++) //LED1至4按顺序各闪烁一次
	  {
	    blink_led(led, 1U, 250U);
	  }
	   for(led=4U;led>0U;led--) //LED1至4按逆序各闪烁一次
	  {
	    blink_led(led, 1U, 250U);
	  }
	  }
	  HAL_Delay(5000); //延时5秒
	  break;
	
	  case 2U:
	  while(1)
	  {
	  beep(120U);
      for(i=0;i<5;i++)
	  {
	    for(led=1U;led<5U;led++)
	   {
	    blink_led(led, 1U, 250U);  //LED1至4按顺序各闪烁一次
        if (delay_ms > 50U)  //每闪烁一次，闪烁时间缩短10毫秒，直到闪烁时间为50毫秒重置
	    {
	      delay_ms -= 10U; 
	    }
	    else
	    {
	      delay_ms = DELAY_MS;
	    }
       }
	   for(led=4U;led>0U;led--) 
	   {
	    blink_led(led, 1U, 250U);  //LED1至4按逆序各闪烁一次
        if (delay_ms > 50U)  //每闪烁一次，闪烁时间缩短10毫秒，直到闪烁时间为50毫秒重置
	    {
	      delay_ms -= 10U; 
	    }
	    else
	    {
	      delay_ms = DELAY_MS;
	    }        
	   }
	  }

	  default:
	  break;
	 }
	  }
	 
	mode++;
}


 
