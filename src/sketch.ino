/*
  this file is part of Lumière Copyright (C) 2017 Yann Asset

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU  General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <Wire.h>
#include <RTClib.h>
//#include <BigNumber.h>


#include "LightChannel.hpp"
#include "RVBWChannelDriver.hpp"

#include "Color.hpp"

//#include "solar.hpp"

#include "modes.hpp"

RTC_DS3231 rtc;

void
setup()
{
  Serial.begin(9600);
  delay(3000); // wait for console opening
  
  // Should probably be avoided, as most effects will work without
  // rtc.
  if (! rtc.begin())
    {
      Serial.println("Couldn't find RTC");
      while (true);
    }

  if (rtc.lostPower())
    {
      Serial.println("RTC lost power, lets set the time!");
      // Set the RTC to the date & time this program was compiled.  As
      // platformio compile & update in the same «move», it allow to
      // set it with a suffisant precision for our usecase. 
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  
  // BigNumber::begin(50);
}

 
void
loop()
{

  //night
  //  greenWallChannel.setOutPower(100);
  // blueCeilingChannel.setOutPower(10);


  //blueCeilingChannel.setOutPower(10);
  //redCeilingChannel.setOutPower(10);
  //greenCeilingChannel.setOutPower(10);
  Lumiere::RVBWChannelDriver<Lumiere::LightChannel<2,  1000>,
                             Lumiere::LightChannel<3,  1000>,
                             Lumiere::LightChannel<4,  1000>,
                             Lumiere::LightChannel<5,  1000>> wall;
  
  Lumiere::RVBWChannelDriver<Lumiere::LightChannel<10, 1000>,
                             Lumiere::LightChannel<8,  1000>,
                             Lumiere::LightChannel<9,  1000>,
                             Lumiere::LightChannel<6,  1000>> ceiling; 
  
  //growWallChannel.setOutPower(1000);
  //whiteCeilingChannel.setOutPower(1000);
  randomSeed(43);
      
  while(true)
    {
      torche(Lumiere::CeilingVariant{}, &ceiling);
      torche(Lumiere::WallVariant{}, &wall);
    }
  
  /*DateTime now = rtc.now();
    auto t = now.unixtime();
          Serial.print(static_cast<double>(t));
          Serial.print(" ");*/
        //Serial.println(solar_elevation(static_cast<double>(t),
        //48.564396,
        //2.6063036))
}
