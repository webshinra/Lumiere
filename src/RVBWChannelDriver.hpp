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

#include "Color.hpp"

namespace Lumiere
{
  enum class
  InterpolationMode
    {
     LINEAR_OVER_TIME,
     LOG_OVER_TIME,
     CONSTANT
    };

  template <typename RedChannel,
            typename GreenChannel,
            typename BlueChannel,
            typename WhiteChannel>
  struct RVBWChannelDriver
  {
    RVBWChannelDriver(Color initialColor={0,0,0,0}):
      mOriginColor (initialColor),
      mTargetColor (initialColor),
      mActualColor (initialColor),
      mMode(InterpolationMode::LINEAR_OVER_TIME)
    { }
    
    void
    sync(long delaySinceLastFrame)
    {
      if (mConvergenceCursor < mConvergenceDelay)
        mConvergenceCursor += delaySinceLastFrame;

      if(mConvergenceDelay > 0)
        {
          
          float progress
          = (float)mConvergenceCursor
          / (float)mConvergenceDelay;

          
          setColor(Color{mOriginColor.red +
                         ((mTargetColor.red - mOriginColor.red) *progress),
                         mOriginColor.green
                         + ((mTargetColor.green - mOriginColor.green) *progress),
                         mOriginColor.blue
                         + ((mTargetColor.blue - mOriginColor.blue) *progress),
                         mOriginColor.white
                         + ((mTargetColor.white - mOriginColor.white) *progress)});
        }
      else
        setColor(mTargetColor);
      
    }
    

    bool
    interpolationConverged()
    {
      return (mConvergenceCursor >= mConvergenceDelay); 
    } 

    void
    setTarget(Color newTarget,
              long interpolationConvergenceDelay)
    {
      mTargetColor = newTarget;
      mOriginColor = mActualColor; 
      mConvergenceDelay = interpolationConvergenceDelay; 
      mConvergenceCursor = 0; 
    }

    // should not be called from outside before interpolation convergence
    void
    setColor(Color newActual)
    {
      r.setOutPower(1000*newActual.red);
      g.setOutPower(1000*newActual.green); 
      b.setOutPower(1000*newActual.blue); 
      w.setOutPower(1000*newActual.white);
      mActualColor=newActual; 
    }
    
    RedChannel   r;
    GreenChannel g;
    BlueChannel  b;
    WhiteChannel w;
    
  private:
    Color mOriginColor;
    Color mTargetColor;
    Color mActualColor;
    
    long mConvergenceDelay;
    long mConvergenceCursor; 
    
    InterpolationMode mMode; 
  };
}
