#ifndef VR920_H_INCLUDED
#define VR920_H_INCLUDED

#include "windows.h" 
#include <math.h>
#include "Vector3.h"


class VR920
{
public:
            VR920             ( );
  void      setup             ( );
  void      shutdown          ( );

  void      update            ( );
  
  void      beginDraw         ( float screenWidth, float screenHeight );
  void      endDraw           ( );
  bool      shouldUpdate      ( );

  void      setTracking       ( bool enable )        { tracking = enable;      }
  void      enableTracking    ()                     { setTracking(true);      }
  void      disableTracking   ()                     { setTracking(false);     }

  void      setStereo         ( bool enable )        { stereoEnabled = enable; updateStereoMode(); }
  void      enableStereo      ()                     { stereoEnabled = true;   updateStereoMode(); }
  void      disableStereo     ()                     { stereoEnabled = false;  updateStereoMode(); }

  void      setFocalLength    ( float dist )         { focalLength = dist;     }
  float     getFocalLength    ()               const { return focalLength;     }

  void      setEyeSeperation  ( float dist )         { eyeSeparation = dist;   }
  float     getEyeSeperation  ()               const { return eyeSeparation;   }

  void      setLeftEye();
  void      setRightEye();
  void      waitLeftEye();
  void      waitRightEye();
  float     getPitch()    { return -orientation.x; }
  float     getYaw()      { return -orientation.y; }
  float     getRoll()     { return orientation.z; }
  void      applyOrientation();

private:
  void      setViewingFrustum ( int eye, float screenWidth, float screenHeight );
  void      updateStereoMode  ();

private:

  static int   loadCounter;
  static bool  driverLoaded;
  static bool  arbSupported;

  HANDLE       stereoHandle;

  float        eyeSeparation;
  float        focalLength;
  bool         tracking;
  bool         drawLeft;
  bool         stereoEnabled;
  int          frame;

  Vector3      orientation;
  Vector3      orientationRead;

  enum { LEFT_EYE=0, RIGHT_EYE, MONO_EYES };
};

#endif //VR920_H_INCLUDED