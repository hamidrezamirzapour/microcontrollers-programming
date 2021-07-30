//8.000000 MHz
#include <mega8.h>
#include <delay.h>
#include <pinha.h>

eeprom  int count_min_on=2,count_hour_on=1,count_min_off=1,count_hour_off=1;
eeprom  int count_min_rest=1,count_hour_rest=1;
eeprom  int count_min_rest2=1,count_hour_rest2=1;
eeprom float count_sec_on=10.7,count_sec_rest=5.7,count_sec_rest2=5.2,count_sec_off=10.3;
eeprom int on_count=1,off_count=1,rest_count=1,rest2_count=1;
char onoff_display,timing=1,temp_seg,led_ind=0,temp_led=0,seq_count=0,setting=0,yekan=0,dahgan=0,set_mark,mark,onoff_count=0;
long int temp_timer=0,timer_count=1;
float temp=0,ashar=0;

int temp_count_min_on,temp_count_hour_on,temp_count_min_off,temp_count_hour_off;
int temp_count_min_rest,temp_count_hour_rest;
int temp_count_min_rest2,temp_count_hour_rest2;
float  temp_count_sec_on,temp_count_sec_off,temp_count_sec_rest,temp_count_sec_rest2;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
//#asm("cli")
seq_count+=1;
if(seq_count>=4)seq_count=1;

if(setting==0)
{ 
dahgan=timer_count/100;
temp=timer_count-(dahgan*100);
yekan=temp/10;
ashar=temp-(yekan*10);


if(seq_count==1)
{
 
 s1=1;s2=0;s3=0;dt=1;temp_seg=dahgan;
}

if(seq_count==2)
{
s1=0;s2=1;s3=0;
if((on_count==1 && timing==1) || (rest_count==1 && timing==2) || (off_count==1 && timing==3) || (rest2_count==1  && timing==4))dt=0;else dt=1;                                     
temp_seg=yekan;
}    

if(seq_count==3)
{
s1=0;s2=0;s3=1;dt=1;                                     
temp_seg=ashar;} 

}

 if(setting==1)
{
if(set_mark==1)//display lft
{
switch(seq_count)
{
case 1:{s1=1;s2=0;s3=0;a=1;b=1;c=1;d=0;e=0;f=0;g=1;dt=1;break;}//l
case 2:{s1=0;s2=1;s3=0;a=0;b=1;c=1;d=1;e=0;f=0;g=0;dt=1;break;}//f
case 3:{s1=0;s2=0;s3=1;a=1;b=1;c=1;d=0;e=0;f=0;g=0;dt=1;break;}//t
}

}


else if(set_mark==3)//display rt
{
switch(seq_count)
{
case 1:{s1=1;s2=0;s3=0;a=0;b=1;c=1;d=1;e=0;f=0;g=1;dt=1;break;}//r
case 2:{s1=0;s2=1;s3=0;a=1;b=1;c=1;d=1;e=0;f=0;g=1;dt=1;break;}//i
case 3:{s1=0;s2=0;s3=1;a=1;b=1;c=1;d=0;e=0;f=0;g=0;dt=1;break;}//t
}

}

else if(set_mark==5)//display of1
{
switch(seq_count)
{
case 1:{s1=1;s2=0;s3=0;a=0;b=0;c=0;d=0;e=0;f=0;g=1;dt=1;break;}//o
case 2:{s1=0;s2=1;s3=0;a=0;b=1;c=1;d=1;e=0;f=0;g=0;dt=1;break;}//f
case 3:{s1=0;s2=0;s3=1;a=1;b=0;c=0;d=1;e=1;f=1;g=1;dt=1;break;}//1
}
}


else if(set_mark==7)//display of2
{
switch(seq_count)
{
case 1:{s1=1;s2=0;s3=0;a=0;b=0;c=0;d=0;e=0;f=0;g=1;dt=1;break;}//o
case 2:{s1=0;s2=1;s3=0;a=0;b=1;c=1;d=1;e=0;f=0;g=0;dt=1;break;} //f
case 3:{s1=0;s2=0;s3=1;a=0;b=0;c=1;d=0;e=0;f=1;g=0;dt=1;break;}//2
}

}

else if(set_mark==2)//rt  value
{
if(seq_count==1){s1=1;s2=0;s3=0;dt=1;
temp_seg=dahgan;                
}

if(seq_count==2){s1=0;s2=1;s3=0;
if(on_count==1 && onoff_display==1)dt=0;else dt=1;                                     
                                    
temp_seg=yekan;}

if(seq_count==3){s1=0;s2=0;s3=1;dt=1;                                     

temp_seg=ashar;}

}

else if(set_mark==4) //lt value
{
if(seq_count==1){s1=1;s2=0;s3=0;dt=1;
temp_seg=dahgan;                
}

if(seq_count==2){s1=0;s2=1;s3=0;
if(off_count==1 && onoff_display==2)dt=0;else dt=1;                                     
                                    
temp_seg=yekan;

}

if(seq_count==3){s2=0;s1=0;s3=1;dt=1;                                    
temp_seg=ashar;

}
}


if(set_mark==6) //off1 value
{

if(seq_count==1){s1=1;s2=0;s3=0;dt=1;
temp_seg=dahgan;                
}

if(seq_count==2){s1=0;s2=1;s3=0;
if(rest_count==1 && onoff_display==3)dt=0;else dt=1;                                  
temp_seg=yekan;             
}

if(seq_count==3){s1=0;s2=0;s3=1;dt=1;                                    
temp_seg=ashar;             
}

}

if(set_mark==8) //off2 value
{

if(seq_count==1){s1=1;s2=0;s3=0;dt=1;
temp_seg=dahgan;                
}

if(seq_count==2){s1=0;s2=1;s3=0;
if(rest2_count==1 && onoff_display==4)dt=0;else dt=1;                                      
temp_seg=yekan;           
}

if(seq_count==3){s1=0;s2=0;s3=1;dt=1;                                    
temp_seg=ashar;                
}

}


}

if(setting==0 || set_mark==2 || set_mark==4 || set_mark==6 || set_mark==8) 
 switch(temp_seg)
{  
case 0:{a=0;b=0;c=0;d=0;e=0;f=0;g=1;break;} 
case 1:{a=1;b=0;c=0;d=1;e=1;f=1;g=1;break;}  
case 2:{a=0;b=0;c=1;d=0;e=0;f=1;g=0;break;}  
case 3:{a=0;b=0;c=0;d=0;e=1;f=1;g=0;break;}  
case 4:{a=1;b=0;c=0;d=1;e=1;f=0;g=0;break;}
case 5:{a=0;b=1;c=0;d=0;e=1;f=0;g=0;break;}  
case 6:{a=0;b=1;c=0;d=0;e=0;f=0;g=0;break;}  
case 7:{a=0;b=0;c=0;d=1;e=1;f=1;g=1;break;}  
case 8:{a=0;b=0;c=0;d=0;e=0;f=0;g=0;break;}  
case 9:{a=0;b=0;c=0;d=0;e=1;f=0;g=0;break;}  

}                



}


interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
TCNT2=0x94;//10ms
temp_timer+=1;
temp_led+=1;

if(temp_led==50)led_ind=0;else if(temp_led==100){led_ind=1;temp_led=0;}

if((mark==1 || mark==4 || mark==7 || mark==10) && temp_timer==10){temp_timer=0;timer_count+=1;}

else if(mark==2 || mark==5 || mark==8 || mark==11)
 {
  if(temp_timer==60*100)
   {   
    temp_timer=0;
   // m+=1;
    timer_count+=1; 
   }   
  }   
  
  if(mark==3 || mark==6 || mark==9 || mark==12)
 {
   if(temp_timer==3600*100)
   { 
    temp_timer=0; 
    timer_count+=1; 
   }   
 }
}


void main(void)
{

char count=1;

DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (1<<PORTB2) | (1<<PORTB1) | (1<<PORTB0);

DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
PORTC=(0<<PORTC6) | (1<<PORTC5) | (1<<PORTC4) | (1<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);


// Clock value: 31.250 kHz(~8ms)
TCCR0=(1<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x00;


TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);

  

#asm("sei")

//temp_timer+=1;

//PORTD.4=1;

//delay_ms(500);

 relay1=1;//left relay on
 relay2=0;//right relay oFF  
 
 // Timer Period: 10 ms
ASSR=0<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (1<<CS22) | (1<<CS21) | (1<<CS20);
TCNT2=0x94;
OCR2=0x00; 
  

           
while (1)
      {  

onoff_count=0;
set_button:if(set_key==0)//if press 'set' button
          {  
           s2=0;s1=0;s3=0;
           setting=1;
           onoff_display=1;
           timing=1;
            delay_ms(200);
           temp_count_min_on=count_min_on;temp_count_hour_on=count_hour_on;temp_count_sec_on=count_sec_on;
           temp_count_min_off=count_min_off;temp_count_hour_off=count_hour_off;temp_count_sec_off=count_sec_off;  
           temp_count_min_rest=count_min_rest;temp_count_hour_rest=count_hour_rest;temp_count_sec_rest=count_sec_rest;  
           temp_count_min_rest2=count_min_rest2;temp_count_hour_rest2=count_hour_rest2;temp_count_sec_rest2=count_sec_rest2;  
           
           while(onoff_display==1)
            {    
               set1:if(set_key==0){
               temp_count_min_on=count_min_on;temp_count_hour_on=count_hour_on;temp_count_sec_on=count_sec_on;
          
               onoff_count=0;delay_ms(110);if(count==2)on_count+=1;count=2;if(on_count>=4)on_count=1;}
               updown1:
               if(on_count==1){sec_led=1;min_led=0;hour_led=0;
               while(up_key==0){temp_count_sec_on+=0.1;
               if(temp_count_sec_on>=100)temp_count_sec_on=99.9;
               set_mark=2;dahgan=temp_count_sec_on/10;yekan=temp_count_sec_on-(dahgan*10);ashar=(temp_count_sec_on-(dahgan*10))-yekan;ashar=ashar*10;
               onoff_count=0;delay_ms(100);}
               
               while(down_key==0){temp_count_sec_on-=0.1;
               if(temp_count_sec_on<=0)temp_count_sec_on=0;
               set_mark=2;dahgan=temp_count_sec_on/10;yekan=temp_count_sec_on-(dahgan*10);ashar=(temp_count_sec_on-(dahgan*10))-yekan;ashar=ashar*10;
               set_mark=2;onoff_count=0;delay_ms(100);}
               dahgan=temp_count_sec_on/10;yekan=temp_count_sec_on-(dahgan*10);ashar=(temp_count_sec_on-(dahgan*10))-yekan;ashar=ashar*10;
               }//sec
               if(on_count==2){sec_led=0;min_led=1;hour_led=0;while(up_key==0){temp_count_min_on+=1;if(temp_count_min_on>=1000)temp_count_min_on=999;set_mark=2;dahgan=temp_count_min_on/100;temp=temp_count_min_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=2;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_min_on-=1;if(temp_count_min_on<=0)temp_count_min_on=0;set_mark=2;dahgan=temp_count_min_on/100;temp=temp_count_min_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=2;onoff_count=0;delay_ms(100);}dahgan=temp_count_min_on/100;temp=temp_count_min_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//min
               if(on_count==3){sec_led=0;min_led=0;hour_led=1;while(up_key==0){temp_count_hour_on+=1;if(temp_count_hour_on>=1000)temp_count_hour_on=999;set_mark=2;dahgan=temp_count_hour_on/100;temp=temp_count_hour_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=2;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_hour_on-=1;if(temp_count_hour_on<=0)temp_count_hour_on=0;set_mark=2;dahgan=temp_count_hour_on/100;temp=temp_count_hour_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=2;onoff_count=0;delay_ms(100);}dahgan=temp_count_hour_on/100;temp=temp_count_hour_on-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//hour

               onoff_count+=1;
               set_mark=1; 
              
               delay_ms(100);
               
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);                       
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);                      
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1; 
               
               delay_ms(100);                      
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);                      
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);                      
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);                     
                  
               set_mark=2;
              
               delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
               delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
                delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
                delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               
                delay_ms(100);
               if(set_key==0)goto set1;          
               if(up_key==0 || down_key==0)goto updown1;
               delay_ms(100);
              
               if(onoff_count==5){count_min_on=temp_count_min_on;count_hour_on=temp_count_hour_on;count_sec_on=temp_count_sec_on;onoff_count=0;onoff_display=3;goto rest;}  
            }
            
          rest: while(onoff_display==3)
            {    
            
               set3:if(set_key==0){
               temp_count_min_rest=count_min_rest;temp_count_hour_rest=count_hour_rest;temp_count_sec_rest=count_sec_rest;
               onoff_count=0;delay_ms(110);if(count==2)rest_count+=1;count=2;if(rest_count>=4)rest_count=1;}
               updown3:
               if(rest_count==1){sec_led=1;min_led=0;hour_led=0;while(up_key==0){temp_count_sec_rest+=0.1;if(temp_count_sec_rest>=100)temp_count_sec_rest=99;set_mark=6;dahgan=temp_count_sec_rest/10;yekan=temp_count_sec_rest-(dahgan*10);ashar=(temp_count_sec_rest-(dahgan*10))-yekan;ashar=ashar*10;onoff_count=0;delay_ms(100);}
               while(down_key==0){temp_count_sec_rest-=0.1;if(temp_count_sec_rest<=0)temp_count_sec_rest=0;set_mark=5;dahgan=temp_count_sec_rest/10;yekan=temp_count_sec_rest-(dahgan*10);ashar=(temp_count_sec_rest-(dahgan*10))-yekan;ashar=ashar*10;set_mark=6;onoff_count=0;delay_ms(100);}dahgan=temp_count_sec_rest/10;yekan=temp_count_sec_rest-(dahgan*10);ashar=(temp_count_sec_rest-(dahgan*10))-yekan;ashar=ashar*10;}//sec
               if(rest_count==2){sec_led=0;min_led=1;hour_led=0;while(up_key==0){temp_count_min_rest+=1;if(temp_count_min_rest>=1000)temp_count_min_rest=999;set_mark=6;dahgan=temp_count_min_rest/100;temp=temp_count_min_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=6;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_min_rest-=1;if(temp_count_min_rest<=0)temp_count_min_rest=0;set_mark=2;dahgan=temp_count_min_rest/100;temp=temp_count_min_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=6;onoff_count=0;delay_ms(100);}dahgan=temp_count_min_rest/100;temp=temp_count_min_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//min
               if(rest_count==3){sec_led=0;min_led=0;hour_led=1;while(up_key==0){temp_count_hour_rest+=1;if(temp_count_hour_rest>=1000)temp_count_hour_rest=999;set_mark=6;dahgan=temp_count_hour_rest/100;temp=temp_count_hour_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=6;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_hour_rest-=1;if(temp_count_hour_rest<=0)temp_count_hour_rest=0;set_mark=2;dahgan=temp_count_hour_rest/100;temp=temp_count_hour_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=6;onoff_count=0;delay_ms(100);}dahgan=temp_count_hour_rest/100;temp=temp_count_hour_rest-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//hour

               onoff_count+=1;
               set_mark=5; 
              
               delay_ms(100);
               
               if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               
               delay_ms(100);
               if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);                       
               if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);                      
              if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);                     
                
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);  
               
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);  
               
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);    
               set_mark=6;
              
               delay_ms(100);
               if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
               if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
             if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
              if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
               
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
               
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
               
                if(set_key==0)goto set3;          
               if(up_key==0 || down_key==0)goto updown3;
               delay_ms(100);
              
               if(onoff_count==5){count_min_rest=temp_count_min_rest;count_hour_rest=temp_count_hour_rest;count_sec_rest=temp_count_sec_rest;onoff_count=0;onoff_display=2;goto off;}  
            }
           
            
             rest2: while(onoff_display==4)
            {    
            
               set4:if(set_key==0){
               temp_count_min_rest2=count_min_rest2;temp_count_hour_rest2=count_hour_rest2;temp_count_sec_rest2=count_sec_rest2;
               onoff_count=0;delay_ms(110);if(count==2)rest2_count+=1;count=2;if(rest2_count>=4)rest2_count=1;}
               updown4:
               if(rest2_count==1){sec_led=1;min_led=0;hour_led=0;while(up_key==0){temp_count_sec_rest2+=0.1;if(temp_count_sec_rest2>=100)temp_count_sec_rest2=99.9;set_mark=8;dahgan=temp_count_sec_rest2/10;yekan=temp_count_sec_rest2-(dahgan*10);ashar=(temp_count_sec_rest2-(dahgan*10))-yekan;ashar=ashar*10;onoff_count=0;delay_ms(100);}
               while(down_key==0){temp_count_sec_rest2-=0.1;if(temp_count_sec_rest2<=0)temp_count_sec_rest2=0;set_mark=8;dahgan=temp_count_sec_rest2/10;yekan=temp_count_sec_rest2-(dahgan*10);ashar=(temp_count_sec_rest2-(dahgan*10))-yekan;ashar=ashar*10;set_mark=8;onoff_count=0;delay_ms(100);}dahgan=temp_count_sec_rest2/10;yekan=temp_count_sec_rest2-(dahgan*10);ashar=(temp_count_sec_rest2-(dahgan*10))-yekan;ashar=ashar*10;}//sec
               if(rest2_count==2){sec_led=0;min_led=1;hour_led=0;while(up_key==0){temp_count_min_rest2+=1;if(temp_count_min_rest2>=1000)temp_count_min_rest2=999;set_mark=8;dahgan=temp_count_min_rest2/100;temp=temp_count_min_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=8;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_min_rest2-=1;if(temp_count_min_rest2<=0)temp_count_min_rest2=0;set_mark=8;dahgan=temp_count_min_rest2/100;temp=temp_count_min_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=8;onoff_count=0;delay_ms(100);}dahgan=temp_count_min_rest2/100;temp=temp_count_min_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//min
               if(rest2_count==3){sec_led=0;min_led=0;hour_led=1;while(up_key==0){temp_count_hour_rest2+=1;if(temp_count_hour_rest2>=1000)temp_count_hour_rest2=999;set_mark=8;dahgan=temp_count_hour_rest2/100;temp=temp_count_hour_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=8;onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_hour_rest2-=1;if(temp_count_hour_rest2<=0)temp_count_hour_rest2=0;set_mark=8;dahgan=temp_count_hour_rest2/100;temp=temp_count_hour_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);set_mark=8;onoff_count=0;delay_ms(100);}dahgan=temp_count_hour_rest2/100;temp=temp_count_hour_rest2-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//hour

               onoff_count+=1;
               set_mark=7; 
              
               delay_ms(100);
               
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               
               delay_ms(100);
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);                       
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);                      
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);  
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);   
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);   
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);                      
                  
               set_mark=8;
              
               delay_ms(100);
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
              if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
               if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100); 
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
               
                if(set_key==0)goto set4;          
               if(up_key==0 || down_key==0)goto updown4;
               delay_ms(100);
              
               if(onoff_count==5){count_min_rest2=temp_count_min_rest2;count_hour_rest2=temp_count_hour_rest2;count_sec_rest2=temp_count_sec_rest2;onoff_count=0;onoff_display=1;temp_timer=0;timer_count=0;goto back;}  
            }
           
           
        off:while(onoff_display==2)
            { 
            
              set2:if(set_key==0){
              temp_count_min_off=count_min_off;temp_count_hour_off=count_hour_off;temp_count_sec_off=count_sec_off;  
          
              onoff_count=0;delay_ms(110);if(count==2)off_count+=1;count=2;if(off_count>=4)off_count=1;}
              updown2:
              if(off_count==1){sec_led=1;min_led=0;hour_led=0;while(up_key==0){temp_count_sec_off+=0.1;if(temp_count_sec_off>=100)temp_count_sec_off=99;set_mark=4;dahgan=temp_count_sec_off/10;yekan=temp_count_sec_off-(dahgan*10);ashar=(temp_count_sec_off-(dahgan*10))-yekan;ashar=ashar*10;onoff_count=0;delay_ms(100);}
              while(down_key==0){temp_count_sec_off-=0.1;if(temp_count_sec_off<=0)count_sec_off=0;set_mark=4;dahgan=temp_count_sec_off/10;yekan=temp_count_sec_off-(dahgan*10);ashar=(temp_count_sec_off-(dahgan*10))-yekan;ashar=ashar*10;set_mark=4;onoff_count=0;delay_ms(100);}dahgan=temp_count_sec_off/10;yekan=temp_count_sec_off-(dahgan*10);ashar=(temp_count_sec_off-(dahgan*10))-yekan;ashar=ashar*10;}//sec
              if(off_count==2){sec_led=0;min_led=1;hour_led=0;while(up_key==0){temp_count_min_off+=1;if(temp_count_min_off>=1000)temp_count_min_off=999;set_mark=4;dahgan=temp_count_min_off/100;temp=temp_count_min_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_min_off-=1;if(temp_count_min_off<=0)temp_count_min_off=0;set_mark=4;dahgan=temp_count_min_off/100;temp=temp_count_min_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);onoff_count=0;delay_ms(100);}dahgan=temp_count_min_off/100;temp=temp_count_min_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//min
              if(off_count==3){sec_led=0;min_led=0;hour_led=1;while(up_key==0){temp_count_hour_off+=1;if(temp_count_hour_off>=1000)temp_count_hour_off=999;set_mark=4;dahgan=temp_count_hour_off/100;temp=temp_count_hour_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);onoff_count=0;delay_ms(100);}while(down_key==0){temp_count_hour_off-=1;if(temp_count_hour_off<=0)temp_count_hour_off=0;set_mark=4;dahgan=temp_count_hour_off/100;temp=temp_count_hour_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);onoff_count=0;delay_ms(100);}dahgan=temp_count_hour_off/100;temp=temp_count_hour_off-(dahgan*100);yekan=temp/10;ashar=temp-(yekan*10);}//hour

              onoff_count+=1;
              set_mark=3;   
              delay_ms(100);
              if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
             
              delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
               delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
               delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
               delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              delay_ms(100);
              
              
              
              set_mark=4;
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
            if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
             if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100); 
              
               if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
               if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
               if(set_key==0)goto set2;          
              if(up_key==0 || down_key==0)goto updown2;
              
              delay_ms(100);
              
              if(onoff_count==5){count_min_off=temp_count_min_off;count_hour_off=temp_count_hour_off;count_sec_off=temp_count_sec_off;count=1;onoff_count=0;onoff_display=4;timing=1;goto rest2;}
            }
          
          }

back: while(timing==1)//on1
         {  
           setting=0;
          
           timer_count=0; 
           temp_timer=0;
            
           sec_led=0;min_led=0;hour_led=0;
           //count_sec_on=count_sec_on*10;
           
            
  while(on_count==1)//sec
          {   
               mark=1;
              
               relay1=1;//left relay on
               relay2=0;// right relay oFF  
              
               min_led=0;hour_led=0;
               if(led_ind==1)sec_led=1;
               else sec_led=0; 
              
               if(set_key==0)goto set_button;       
               if(timer_count>=count_sec_on*10)
               {
                 
                relay2=0;//left relay off
                relay1=0;// right relay off  
                timer_count=0;
                // m=0; 
                temp_timer=0;
                  
                timing=2;
                if(rest_count==1) {temp_timer=1;timer_count=1;goto rest1;}
                 else goto rest1;
               }
             
          }
         
  while(on_count==2)//min
          {   
             
              mark=2;  
              relay1=1;//left relay on
              relay2=0;// right relay off  
              sec_led=0;hour_led=0;
              if(led_ind==1)min_led=1;
              else min_led=0; 
              
              if(set_key==0)goto set_button;
                 /*
              if(temp_timer==60*m)
               { 
                m+=1;
                timer_count+=1; 
               }  
               */
            
           if(timer_count>=count_min_on)
               {
                 relay1=0;
                 timer_count=0;
                 // m=0;
                 temp_timer=0;
                 timing=2; 
                 if(rest_count==1) {temp_timer=1;timer_count=1;goto rest1;}
                 else goto rest1;
               }
               
          }
         
 while(on_count==3)//hour
          {    
               mark=3; 
               
               relay1=1;//left relay on
               relay2=0;// right relay off  
              
               sec_led=0;min_led=0;
               if(led_ind==1)hour_led=1;
              else hour_led=0; 
               
              if(set_key==0)goto set_button;
              if(timer_count>=count_hour_on)
               {
                
                 relay2=0;//left relay off
                 relay1=0;// right relay off  
                 timer_count=0;
                // m=0;
                 temp_timer=0;
                 timing=2; 
                 if(rest_count==1) {temp_timer=1;timer_count=1;goto rest1;}
                 else goto rest1;
               }
               
          }
         }
                  
rest1:while(timing==2)//takhir 1
         {  
            setting=0;
          
            timer_count=0; 
            temp_timer=0;
            
            //m=0;
           relay2=0;
           relay1=0; 
           sec_led=0;min_led=0;hour_led=0;
            
  while(rest_count==1)//sec
          {   
              mark=7;
              relay2=0;
              relay1=0; 
              
              min_led=0;hour_led=0;
              if(led_ind==1)sec_led=1;
              else sec_led=0; 
              
               if(set_key==0)goto set_button;       
             if(timer_count>=count_sec_rest*10)
               {
                 relay1=1; 
                 
                 timer_count=0;
                // m=0; 
                 temp_timer=0;
                  
                 timing=3;
                 if(off_count==1) {temp_timer=1;timer_count=1;goto on2;}
                 else goto on2;
               }
             
          }
         
  while(rest_count==2)//min
          {   
             
             mark=8;  
             
             relay2=0;
             relay1=0; 
           
              sec_led=0;hour_led=0;
              if(led_ind==1)min_led=1;
              else min_led=0; 
              
              if(set_key==0)goto set_button;
                 /*
              if(temp_timer==60*m)
               { 
                m+=1;
                timer_count+=1; 
               }  
               */
            
           if(timer_count>=count_min_rest)
               {
                 relay1=1;
                 timer_count=0;
                // m=0;
                 temp_timer=0;
                 timing=3; 
                if(off_count==1) {temp_timer=1;timer_count=1;goto on2;}
                 else goto on2;
               }
               
          }
         
  while(on_count==3)//hour
          {    
              mark=9; 
              
              relay2=0;
              relay1=0; 
           
              sec_led=0;min_led=0;
              if(led_ind==1)hour_led=1;
              else hour_led=0; 
               
              if(set_key==0)goto set_button;
              if(timer_count>=count_hour_rest)
               {
              relay1=1;
              timer_count=0;
              // m=0;
              temp_timer=0;
              timing=3; 
              if(off_count==1) {temp_timer=1;timer_count=1;goto on2;}
                 else goto on2;
               }
               
          }
         
         }
               
on2:while(timing==3)//on2
         {  
            setting=0;
          
            timer_count=0; 
            temp_timer=0;
           
            relay1=0;
            
            sec_led=0;min_led=0;hour_led=0;
             
 while(off_count==1)//sec
          {  
             
             relay1=0;
             relay2=1;
             
             mark=4;
             min_led=0;hour_led=0; 
             
              if(led_ind==1)sec_led=1;
              else sec_led=0; 
              
             if(set_key==0)goto set_button;
             if(timer_count>=count_sec_off*10)
               {  
                   
                  relay2=0;
                  relay1=0;
                  timer_count=0;
                 // m=0;
                  temp_timer=0;
                  timing=4;
                  if(rest2_count==1) {temp_timer=1;timer_count=1;goto rest22;}
                  else goto rest22;
               }
             
          }
         
 while(off_count==2)//min
          {  
          
             mark=5;  
              
              relay1=0;
              relay2=1;
             
              sec_led=0;hour_led=0;
              if(led_ind==1)min_led=1;
              else min_led=0; 
             
             if(PINC.4==0)goto set_button;
              if(timer_count>=count_min_off)
               {  
                  relay2=0;
                  relay1=0;
                  timer_count=0;
                 // m=0; 
                  temp_timer=0;
                  timing=4;
                if(rest2_count==1) {temp_timer=1;timer_count=1;goto rest22;}
                  else goto rest22;
               }
          }
         
 while(off_count==3)//hour
          {    
            
          
             relay1=0;
             relay2=1;
             mark=6;
              
             sec_led=0;min_led=0;
              if(led_ind==1)hour_led=1;
              else hour_led=0; 
              
             if(set_key==0)goto set_button;
              if(timer_count>=count_hour_off)
               {  
                  relay2=0;
                  relay1=0;
                  timer_count=0;
                //  m=0;
                  temp_timer=0;
                  timing=4;    
                if(rest2_count==1) {temp_timer=1;timer_count=1;goto rest22;}
                  else goto rest22;
               }
               
          }
         
         }

rest22:while(timing==4)//takhir 2(after right)
         {  
            setting=0;
          
            timer_count=0; 
            temp_timer=0;
          
            //m=0;
           relay2=0;
           relay1=0; 
           sec_led=0;min_led=0;hour_led=0;
            
  while(rest2_count==1)//sec
          {   
              mark=10;
              relay2=0;
              relay1=0; 
              
              min_led=0;hour_led=0;
              if(led_ind==1)sec_led=1;
              else sec_led=0; 
              
               if(set_key==0)goto set_button;       
             if(timer_count>=count_sec_rest2*10)
               {
                /// relay1=1; 
                 timer_count=0;
                // m=0; 
                 temp_timer=0;
                  
                 timing=1;
                 temp_timer=1;timer_count=1;goto back;
                  
               }
             
          }
         
 while(rest2_count==2)//min
          {   
             
             mark=11;  
             
             relay2=0;
             relay1=0; 
           
              sec_led=0;hour_led=0;
              if(led_ind==1)min_led=1;
              else min_led=0; 
              
              if(set_key==0)goto set_button;
                 /*
              if(temp_timer==60*m)
               { 
                m+=1;
                timer_count+=1; 
               }  
               */
            
           if(timer_count>=count_min_rest2)
               {
               //  relay1=1;
                 timer_count=0;
                // m=0;
                 temp_timer=0;
                 timing=1; 
                  if(on_count==1) {temp_timer=1;timer_count=1;goto back;}
                  else goto back;
               }
               
          }
         
 while(rest2_count==3)//hour
          {    
              mark=12; 
              
              relay1=0;
              relay2=0; 
           
              sec_led=0;min_led=0;
              if(led_ind==1)hour_led=1;
              else hour_led=0; 
               
              if(set_key==0)goto set_button;
              if(timer_count>=count_hour_rest2)
               {
              //relay1=1;
              timer_count=0;
              // m=0;
              temp_timer=0;
              timing=1; 
                if(on_count==1) {temp_timer=1;timer_count=1;goto back;}
                  else goto back;
               }
               
          }
          
         }       
      }
}
