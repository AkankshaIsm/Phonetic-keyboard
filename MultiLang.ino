/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino:      2, 3
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy 2.0:   5, 6, 7, 8
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/

#include <ProTrinketKeyboard.h>

#include <PS2Keyboard.h>
#include <HashMap.h>

const byte HASH_SIZE = 60; 
//storage 
HashType<String,int> hashRawArray[HASH_SIZE]; 
//handles the storage [search,retrieve,insert]
HashMap<String,int> hashMap = HashMap<String,int>( hashRawArray , HASH_SIZE ); 


  
//define the max size of the hashtable



const int DataPin = 8;
int i=0;
const int IRQpin =  3;
 char *buff;
 char *pri; 
 char buffe[5]={0};
int a[4];
char prev='\0';
char prevprev='\0';
PS2Keyboard keyboard;
int lang=0x900;
void sendunic(int val)
{
   memset(buffe,0,5);
  itoa(val,buffe,16);
  
  /*Serial.print(buffe[0]);
  Serial.print(buffe[1]);
  Serial.print(buffe[2]);*/
  Serial.println("inside func");
  Serial.println(buffe);
  TrinketKeyboard.poll();
  TrinketKeyboard.pressKey(0,0);
  for(i=0;i<3;i++)
  {
    if(buffe[i]=='0')
    {
      a[i]=0x27;
    }
    else if(buffe[i]=='1')
    {
      a[i]=0x1E;
    }
     else if(buffe[i]=='2')
    {
      a[i]=0x1F;
    }
     else if(buffe[i]=='3')
    {
      a[i]=0x20;
    }
     else if(buffe[i]=='4')
    {
      a[i]=0x21;
    }
     else if(buffe[i]=='5')
    {
      a[i]=0x22;
    }
     else if(buffe[i]=='6')
    {
      a[i]=0x23;
    }
     else if(buffe[i]=='7')
    {
      a[i]=0x24;
    }
     else if(buffe[i]=='8')
    {
      a[i]=0x25;
    }
     else if(buffe[i]=='9')
    {
      a[i]=0x26;
    }
     else if((buffe[i]=='A') | (buffe[i]=='a'))
    {
      a[i]=0x04;
    }
     else if(buffe[i]=='B'| (buffe[i]=='b'))
    {
      a[i]=0x05;
    }
     else if(buffe[i]=='C'| (buffe[i]=='c'))
    {
      a[i]=0x06;
    }
     else if(buffe[i]=='D'| (buffe[i]=='d'))
    {
      a[i]=0x07;
    }
     else if(buffe[i]=='E'| (buffe[i]=='e'))
    {
      a[i]=0x08;
    }
     else if(buffe[i]=='F'| (buffe[i]=='f'))
    {
      a[i]=0x09;
    }
    
  }
  //Serial.print("Done");
  TrinketKeyboard.poll();
  TrinketKeyboard.pressKey((KEYCODE_MOD_LEFT_SHIFT|KEYCODE_MOD_LEFT_CONTROL),KEYCODE_U);
  //TrinketKeyboard.pressKey(0,0);
  
  TrinketKeyboard.pressKey(0,a[0]);
  //TrinketKeyboard.pressKey(0,0);
  
  TrinketKeyboard.pressKey(0,a[1]);
  //TrinketKeyboard.pressKey(0,0);
  
  TrinketKeyboard.pressKey(0,a[2]);
  TrinketKeyboard.pressKey(0,KEYCODE_SPACE);
  
  TrinketKeyboard.pressKey(0,0);
  
  //Serial.print("Done");
  return ;
}
void setup() {
  
  hashMap[0]("k",0x015);
  hashMap[1]("kh",0x016);
  hashMap[2]("g",0x017);
  hashMap[3]("gh",0x018);
  hashMap[4]("ch",0x01A);
  hashMap[5]("chh",0x01B);
  hashMap[6]("j",0x01C);
  hashMap[7]("jh",0x01D);
  hashMap[8]("t",0x024);
  hashMap[9]("th",0x025);
  hashMap[10]("d",0x026);
  hashMap[11]("dh",0x027);
  hashMap[12]("T",0x01F);
  hashMap[13]("Th",0x020);
  hashMap[14]("D",0x021);
  hashMap[15]("Dh",0x022);
  hashMap[16]("s",0x038);
  hashMap[17]("sh",0x036);
  hashMap[18]("h",0x039);
  hashMap[19]("y",0x02F);
  hashMap[20]("r",0x030);
  hashMap[21]("b",0x02C);
  
 
  hashMap[22]("A",0x005);
  hashMap[23]("Aa",0x006);
  hashMap[24]("I",0x007);
  hashMap[25]("EE",0x008);
  hashMap[26]("U",0x009);
  hashMap[27]("OO",0x00A);
  hashMap[28]("E",0x00F);
  hashMap[29]("AI",0x010);
  hashMap[30]("O",0x013);
  hashMap[31]("AU",0x014);
 // Matra of AM 
  hashMap[52]("AN",0x002);
  hashMap[53]("AM",0x002);
  
 
  
  hashMap[32]("ph",0x02B);
  hashMap[33]("v",0x035);
  hashMap[34]("n",0x028);
  hashMap[35]("l",0x032);
  hashMap[36]("m",0x02E);
  hashMap[37]("Sh",0x37);
  hashMap[38]("p",0x02A);
  hashMap[39]("bh",0x02D);
  
  hashMap[40]("aa",0x03E);
  hashMap[41]("i",0x03F);
  hashMap[42]("ee",0x040);
  hashMap[44]("u",0x041);
  hashMap[45]("oo",0x042);
  hashMap[46]("e",0x047);
  hashMap[47]("ai",0x048);
  hashMap[48]("o",0x04B);
  hashMap[49]("au",0x04C);
  hashMap[50]("w",0x035);
  hashMap[51]("f",0x02B);
  hashMap[54]("N",0x023);
  hashMap[55]("z",0x05B);
  
  
 //matra
  
  
 
 // hashMap[50]("an",0x0902);
 // hashMap[51]("am",0x0902);

  
  delay(1000);
 
  buff = (char *)malloc(15*sizeof(char));
  pri = (char *)malloc(15*sizeof(char));
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("KeyBoard Testing ");
  //Serial.println( hashMap.getValueOf("kha"),HEX );
  TrinketKeyboard.begin();
}

int j,l=0;
char com[3];
char com1[2];

void loop() {
   
  //Serial.print("came");
  TrinketKeyboard.poll();
  
  if (keyboard.available())
  {
     TrinketKeyboard.poll();   
    // read the next key
      char c = keyboard.read();
       if(c==PS2_BACKSPACE)
       { TrinketKeyboard.poll();
       Serial.print("Backspace");
  TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
  TrinketKeyboard.pressKey(0,0);
       }
       else 
       if(c==' ')
       { TrinketKeyboard.poll();
       Serial.print("space");
    TrinketKeyboard.pressKey(0,KEYCODE_SPACE);
    TrinketKeyboard.pressKey(0,0);
       }
        else 
       if(c==PS2_ENTER)
       { TrinketKeyboard.poll();
       Serial.print("Enter");
    TrinketKeyboard.pressKey(0,KEYCODE_ENTER);
    TrinketKeyboard.pressKey(0,0);
       }
      else if(c==PS2_F1)
       { Serial.print("F1 Hindi ");
         lang = 0x900;
       }
       else if(c==PS2_F2)
       { Serial.print("F2 Bengali");
         lang=0x980;
       }
       else if(c==PS2_F3)
       { Serial.print("F3 Punjabi");
         lang= 0xA00;
       }
       else if(c==PS2_F4)
       { Serial.print("F4 Gujrati");
         lang= 0xA80;
       }
       else if(c==PS2_F5)
       { Serial.print("F5 Oriya");
         lang=0xB00;
       }
       else if(c==PS2_F6)
       { Serial.print("F6 Tamil");
         lang=0xB80;
       }
       else if(c==PS2_F7)
       { Serial.print("F7 ");
         
       }
       else if(c==PS2_F8)
       { Serial.print("F8 Telugu");
          lang=0xC00;
       }
       else if(c==PS2_F9)
       { Serial.print("F9 Kannada");
         lang=0xC80;
       }
       else if(c==PS2_F10)
       { Serial.print("F10 Malyalam");
         lang=0xD00;
       }
       else if(c==PS2_F11)
       { Serial.print("F11 ");
      
       }
       else if(c==PS2_F12)
       { Serial.print("F12 ");
      
       }
       else 
       if(((prevprev=='k')&&(prev=='S')&&(c=='h'))||((prevprev=='c')&&(prev=='h')&&(c=='h'))||((prevprev=='p')&&(prev=='r')&&(c=='u'))||((prevprev=='s')&&(prev=='h')&&(c=='r'))||((prevprev=='S')&&(prev=='h')&&(c=='T')))
          {
            TrinketKeyboard.poll();
           Serial.print("Backspace");
           TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
           TrinketKeyboard.pressKey(0,0);
           TrinketKeyboard.poll();
           Serial.print("Backspace");
           TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
           TrinketKeyboard.pressKey(0,0);
           
             com1[0]=prevprev;
            String str=com1;
            sendunic(lang+hashMap.getValueOf(str));
           
            sendunic(lang+0x4D); 
             com[0]=prev;
             com[1]=c;
             str=com;
             sendunic(lang+hashMap.getValueOf(str)); 
             prevprev=prev;
             prev=c;

        }
       
       else
        if(((prev=='k')||(prev=='d')||(prev=='g')||(prev=='t')||(prev=='p')||(prev=='b')||(prev=='T')||(prev=='D')||(prev=='j')||(prev=='s')||(prev=='c')||(prev=='S'))&&(c=='h'))
          { com[0]=prev;
            com[1]=c;
            String str=com;
            TrinketKeyboard.poll();
         Serial.print("Backspace");
        TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
         prev=c;
          }
         else
         if((prev=='a')&&((c=='a')||(c=='i')||(c=='u')))
          { com[0]=prev;
            com[1]=c;
            String str=com;
           
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
         if((prev=='e')&&(c=='e'))
          { com[0]=prev;
            com[1]=c;
            String str=com;
           TrinketKeyboard.poll();
        Serial.print("Backspace");
        TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
         if((prev=='o')&&(c=='o'))
          { com[0]=prev;
            com[1]=c;
            String str=com;
            TrinketKeyboard.poll();
         Serial.print("Backspace");
        TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
         if((prev=='A')&&((c=='a')||(c=='I')||(c=='U')||(c=='M')||(c=='N')))
          { com[0]=prev;
            com[1]=c;
            String str=com;
            
          TrinketKeyboard.poll();
         Serial.print("Backspace");
        TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
         if((prev=='O')&&(c=='O'))
          { com[0]=prev;
            com[1]=c;
            String str=com;
            TrinketKeyboard.poll();
        Serial.print("Backspace");
       TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
         if((prev=='E')&&(c=='E'))
          { com[0]=prev;
            com[1]=c;
            String str=com;
            TrinketKeyboard.poll();
        Serial.print("Backspace");
        TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
        TrinketKeyboard.pressKey(0,0);
        sendunic(lang+hashMap.getValueOf(str));
         prevprev=prev;
        prev=c;
          }
          else
          if(((prev=='p')&&(c=='r'))||((prev=='t')&&(c=='r'))||((prev=='T')&&(c=='r'))||((prev=='k')&&(c=='r'))|| ((prev=='d')&&(c=='r'))||((prev=='D')&&(c=='r'))||((prev=='b')&&(c=='r'))||((prev=='r')&&(c=='y'))||((prev=='r')&&(c=='t'))||((prev=='m')&&(c=='r')))//for pra
          {
             TrinketKeyboard.poll();
           Serial.print("Backspace");
           TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
           TrinketKeyboard.pressKey(0,0);
           
             com1[0]=prev;
            String str=com1;
            sendunic(lang+hashMap.getValueOf(str));
           
            sendunic(lang+0x04D); 
             com1[0]=c;
             str=com1;
             sendunic(lang+hashMap.getValueOf(str)); 
               prevprev=prev;
               prev=c;


        }
        else
          if(((prev=='p')&&(c=='y'))|| ((prev=='k')&&(c=='t'))||((prev=='s')&&(c=='t'))||((prev=='s')&&(c=='w'))||((prev=='p')&&(c=='n'))||((prev=='t')&&(c=='n'))||((prev=='t')&&(c=='v'))||((prev=='l')&&(c=='t'))||((prev=='t')&&(c=='t'))||((prev=='l')&&(c=='l'))||((prev=='m')&&(c=='m'))||((prev=='n')&&(c=='n'))||((prev=='k')&&(c=='k'))||((prev=='T')&&(c=='T'))||((prev=='j')&&(c=='j'))||((prev=='d')&&(c=='d')))//for pra
          {
             TrinketKeyboard.poll();
           Serial.print("Backspace");
           TrinketKeyboard.pressKey(0,KEYCODE_BACKSPACE);
           TrinketKeyboard.pressKey(0,0);
           com1[0]=prev;
            String str=com1;
            sendunic(lang+hashMap.getValueOf(str));
           // unicode of p
           
            sendunic(lang+0x04D); 
             TrinketKeyboard.poll();
             TrinketKeyboard.pressKey((KEYCODE_MOD_LEFT_SHIFT|KEYCODE_MOD_LEFT_CONTROL),KEYCODE_U);
             TrinketKeyboard.pressKey(0,0);
  
             TrinketKeyboard.pressKey(0,KEYCODE_2);
             TrinketKeyboard.pressKey(0,0);
  
             TrinketKeyboard.pressKey(0,KEYCODE_0);
             TrinketKeyboard.pressKey(0,0);
  
             TrinketKeyboard.pressKey(0,KEYCODE_0);
             TrinketKeyboard.pressKey(0,0);
             TrinketKeyboard.pressKey(0,KEYCODE_D);
  
             TrinketKeyboard.pressKey(0,0);
             com1[0]=c;
             str=com1;
             sendunic(lang+hashMap.getValueOf(str)); 
             prevprev=prev;
             prev=c;
           // unicode of halant

        }
         else
        if((c=='a'))
         {  prevprev=prev;
           prev=c;

         }
         else
        { com1[0]=c;
         
         String m=com1;
         Serial.println( hashMap.getValueOf(m),HEX );
       //uSerial.println( hashMap.getValueOf("kha"),HEX );
         int r=hashMap.getValueOf(m);
         sendunic(lang+r);
          prevprev=prev;
         prev=c;
         com1[0]='\0';
       }
      
       
  
      
      memset(buff,0,15);
      i=0;
        //memset(pri,0,15);
      // }
       
      // otherwise, just print all normal characters
      Serial.print(c);
    
  }
}

