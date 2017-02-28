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

#include "LightChannel.hpp"

// Useless crap.
void
setup()
{ }

 
void
loop()
{
  Lumiere::LightChannel<2,  1000> redWallChannel;
  Lumiere::LightChannel<3,  1000> greenWallChannel;
  Lumiere::LightChannel<4,  1000> blueWallChannel;
  Lumiere::LightChannel<5,  1000> growWallChannel;
    
  Lumiere::LightChannel<10, 1000> redCeilingChannel;
  Lumiere::LightChannel<8,  1000> greenCeilingChannel;
  Lumiere::LightChannel<9,  1000> blueCeilingChannel;
  Lumiere::LightChannel<6,  1000> whiteCeilingChannel;

  redWallChannel.setOutPower(100); 
  redWallChannel.sync();

  while(true)
    { } 
}
