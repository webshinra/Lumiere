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

namespace Lumiere
{
  enum class Mode
    {off,
     torche,
     bleu_rouge, moving_bleu_rouge,
     grow_cycle};
  
  struct CeilingVariant { };
  struct WallVariant { };

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
  { torche(25.0, channel); }
  
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
            channel->setTarget({1,0,0,0}, switchTime);
            even = !even;
          } 
        else
          {
            channel->setTarget({0,0,1,0}, switchTime);
            even = !even; 
          } 
      } 
    channel->sync(10);
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
    
    constexpr int nightBegining = 19 * 60;
    constexpr int nightEnd      = 07 * 60;

    bool night = ((time > nightBegining) and (time <= nightEnd));
    
    if(night)
      channel->setColor({0,0,0,0});
    else
      channel->setColor({0,0,0,1});
    
  }
  
}

