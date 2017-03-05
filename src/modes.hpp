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
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#undef abs
#include <map>

#include "Color.hpp"
namespace Lumiere
{
  enum class Mode
    {off,
     torche,
     bleu_rouge, moving_bleu_rouge,
     grow_cycle, daylight};


  struct CeilingVariant { };
  struct WallVariant { };

  enum class Daytime
    {twilight =  7 * 60,
     morning  =  8 * 60,
     midday   = 12 * 60,
     noon     = 18 * 60,
     night    = 21 * 60,
     midnight = 24 * 60};
  
  template <typename ChannelType>
  void
  torche(float greenDivisor,
         ChannelType* channel)
  {
    channel->setTarget
      (Lumiere::Color
       {static_cast<float>(random(7, 10))/10.0,
          static_cast<float>(random(1, 5))/greenDivisor,
          0,
          static_cast<float>(random(1, 5))/200.0},
       random(35,200));
      
    while(!channel->interpolationConverged())
      {
        delay(10); 
        channel->sync(10);
      }
  }
  
  template <typename ChannelType>
  void
  torche(CeilingVariant,
         ChannelType* channel)
  { torche(50.0, channel);}

  template <typename ChannelType>
  void
  torche(WallVariant,
         ChannelType* channel)
  { torche(50.0, channel); }
  
  template <typename ChannelType>
  void
  stromboscope(ChannelType* channel)
  {
    channel->setOutPower(1000);

    delay(30);

    channel->setOutPower(0);
    
    delay(100);
  }
  
  template <typename ChannelType>
  void
  bleu_rouge(CeilingVariant,
             ChannelType* channel)
  {
    channel->setColor({0,0,1,0});
  }
  
  template <typename ChannelType>
  void
  bleu_rouge(WallVariant,
             ChannelType* channel)
  {
    channel->setColor({1,0,0,0});
  }
  
  template <typename ChannelType>
  void
  moving_bleu_rouge(WallVariant,
                    ChannelType* channel)
  { moving_bleu_rouge(true, channel);}

  template <typename ChannelType>
  void
  moving_bleu_rouge(CeilingVariant,
                    ChannelType* channel)
  { moving_bleu_rouge(false, channel);}
  
  template <typename ChannelType>
  void
  moving_bleu_rouge(bool variant,
                    ChannelType* channel)
  {
    static bool even = false;
    if(channel->interpolationConverged())
      {
        constexpr int switchTime = 1000*10; 
        if(even xor variant) 
          {
            channel->setColor({1,0,0,0}); 
            channel->setTarget({1,0,0,0}, switchTime);
            even = !even;
          } 
        else
          {
            channel->setColor({0,0,1,0}); 
            channel->setTarget({0,0,1,0}, switchTime);
            even = !even; 
          } 
      } 
    channel->sync(10);
    delay(10); 
  }

  template <typename Variant,
            typename ChannelType>
  void
  grow_cycle(Variant, ChannelType* channel)
  {
    DateTime now = rtc.now();
    //auto t = now.unixtime();
    const int time
      = (now.hour() * 60)
      + now.minute();
    
    if((   now.hour() <= 12 and time < (long)Daytime::morning)
       or (now.hour() >  12 and time > (long)Daytime::night))
      { channel->setColor({0, 0.1, 0,0}); } 
    else
      { channel->setColor({0, 0, 0, 1}); }
  }

  template <typename Variant,
            typename ChannelType>
  void
  daylight(Variant, ChannelType* channel)
  {
    std::map<Daytime, Color> daymap;

    daymap[Daytime::twilight] = {0.847058823529,
                                 0.749019607843,
                                 0.721568627451,
                                 0}; 
    daymap[Daytime::morning] =  {0, 0, 0.1, 1};
    daymap[Daytime::midday] =   {0, 0, 0.3, 1};
    daymap[Daytime::noon] =     {1.000,
                                 0.517,
                                 0.0588,
                                 0};
    daymap[Daytime::night] =    {0,
                                 0,
                                 0.1,
                                 0};
    daymap[Daytime::midnight] = {0,0,0.1 ,0};
    
    DateTime now = rtc.now();

    const int time
      = (now.hour() * 60)
      + now.minute();

    delay(10); 
    channel->sync(10);
    
    if(channel->interpolationConverged())
              { 
        if(now.hour() <= 12)
          {
            if(time < (long)Daytime::twilight) 
              channel->setTarget(daymap[Daytime::twilight],
                                 ((long)Daytime::twilight-time)*1000*60);
            else if(time < (long)Daytime::morning) 
              channel->setTarget(daymap[Daytime::morning],
                                 ((long)Daytime::morning-time)*1000*60);
            else
              channel->setTarget(daymap[Daytime::midday],
                                 ((long)Daytime::midday-time)*1000*60);
          }
        else
          {
            if(time < (long)Daytime::noon) 
              channel->setTarget(daymap[Daytime::noon],
                                 ((long)Daytime::noon-time)*1000*60);
            else
              channel->setTarget(daymap[Daytime::night],
                                 ((long)Daytime::night-time)*1000*60);
          }
      }
    
  } 
}

