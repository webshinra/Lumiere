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
{ torche(300.0, channel);}

  template <typename ChannelType>
void
torche(WallVariant,
       ChannelType* channel)
  { torche(75.0, channel); }
  
  template <typename ChannelType>
  void
         stromboscope(ChannelType* channel)
         {
           channel->setOutPower(1000);

           delay(30);

           channel->setOutPower(0);
    
           delay(100);
         }
}
