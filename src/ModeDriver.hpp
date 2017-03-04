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

#include "modes.hpp"

#include <functional>

namespace Lumiere
{
  // should be metaprogrammed to allow arbitrary channels variant.
  template <typename CeilingChannelType,
            typename WallChannelType>
  struct ModeDriver
  { 
    
    ModeDriver(CeilingChannelType *ceilingChannel,
               WallChannelType *wallChannel):
      ceiling(Mode::off),
      wall(Mode::off),
      mCeilingChannel(ceilingChannel),
      mWallChannel(wallChannel)
    { }

    template <typename Variant,
              typename ChannelType>
    void
    dispatch(Mode mode, ChannelType *channel)
    {
      switch(mode)
        {
        case Mode::off:
          channel->setColor({0,0,0,0});
          
          break;
          
        case Mode::torche:
          torche(Variant{}, channel);
          break;
        case Mode::bleu_rouge:
          bleu_rouge(Variant{}, channel); 
          break;

        case Mode::moving_bleu_rouge:
          moving_bleu_rouge(Variant{}, channel);
          delay(10);
          break;

        case Mode::grow_cycle:
          grow_cycle(Variant{}, channel);
          break; 
        }
    }
    
    void
    sync()
    {
      dispatch<CeilingVariant>(ceiling, mCeilingChannel);
      dispatch<WallVariant>(wall, mWallChannel); 
    }
    
    Mode ceiling;
    Mode wall; 
    
  private:
    CeilingChannelType* mCeilingChannel;
    WallChannelType* mWallChannel; 
  }; 
}

