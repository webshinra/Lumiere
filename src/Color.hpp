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
  struct Color
  {
    float red;
    float green;
    float blue;
    float white;

    bool
    operator==(Color const otherColor) const
    {
      return ((red   == otherColor.red)   and
              (green == otherColor.green) and
              (blue  == otherColor.blue)  and
              (white == otherColor.white));
    }
  }; 
}
