

#include "stdio.h"
#include <gl/gl.h>
#include "vr920.h"
#include "IWRsdk.h"




 int   VR920::loadCounter   = 0;
 bool  VR920::driverLoaded  = false;
 bool  VR920::arbSupported  = false;

#define EXIT_IF_NOT_ENABLED()   if( stereoHandle == INVALID_HANDLE_VALUE || !stereoEnabled )

VR920::VR920( )
  : stereoHandle  ( INVALID_HANDLE_VALUE )
  , eyeSeparation ( 0.3f  )
  , focalLength   ( 3.0f  )
  , tracking      ( false )
  , drawLeft      ( true  )
  , stereoEnabled ( false  )
{
}

// -------------------------------------------------------------------------------------------- //
void VR920::setup( )
{
  //ofSetVerticalSync    ( true );  // We need vertical sync on to avoid tearing between eyes
  //ofSetFrameRate       ( 60 );    // Also framerate must be set to 60fps
  //ofDisableSetupScreen ( );       // We will do our own screen setup including perspective and model-view matrices

  if( !driverLoaded )
  {
    driverLoaded = (IWRLoadDll() == IWR_OK);

    //if( driverLoaded ) cs.print( "VR920 - IWRDriver loaded successfully!" );
    //else               cs.print( "VR920 - NO VR920 IWRDriver support." );
  }

  if( driverLoaded )
  {
    // Increment the loaded counter so that we know when to unload the DLL
    ++loadCounter;

        stereoHandle = IWRSTEREO_Open();
    //if( stereoHandle == INVALID_HANDLE_VALUE ) cs.print( "VR920 - Stereoscopy not supported!" );


    char * ext          = (char*)glGetString( GL_EXTENSIONS );
           arbSupported = (strstr( ext, "GL_ARB_occlusion_query" ) == NULL);

    //if( arbSupported ) cs.print( "VR920 - GL_ARB_occlusion_query supported!" );
    //else               cs.print( "VR920 - GL_ARB_occlusion_query is not supported!" );

    IWRSTEREO_SetStereo( stereoHandle, IWR_STEREO_MODE );

    stereoEnabled = true;
  }
}

// -------------------------------------------------------------------------------------------- //
void VR920::updateStereoMode()
{
  if( stereoHandle != INVALID_HANDLE_VALUE )
    IWRSTEREO_SetStereo ( stereoHandle, stereoEnabled ? IWR_STEREO_MODE : IWR_MONO_MODE );
}

// -------------------------------------------------------------------------------------------- //
void VR920::shutdown( )
{
  if( loadCounter > 0 )
  {
    updateStereoMode();

    if( stereoHandle != INVALID_HANDLE_VALUE )
      IWRSTEREO_Close( stereoHandle );

    // Decrement the load counter, and free the DLL if there are no more VR920's loaded
    --loadCounter;
    if( loadCounter == 0 ) IWRFreeDll();
  }
}

// -------------------------------------------------------------------------------------------- //
void VR920::update()
{
  if( stereoHandle == INVALID_HANDLE_VALUE ) return;

  if( tracking )
  {
    long	 Roll = 0, Yaw = 0, Pitch = 0;
    IWRGetTracking( &Yaw, &Pitch, &Roll );

    orientationRead.set( Pitch * IWR_RAWTODEG
                       , Yaw   * IWR_RAWTODEG
                       , Roll  * IWR_RAWTODEG );

    Vector3::lerp( orientation, orientationRead, 0.8, orientation );
  }
}

// -------------------------------------------------------------------------------------------- //
void VR920::beginDraw( float screenWidth, float screenHeight )
{
  ++frame;

  if( stereoEnabled && stereoHandle != INVALID_HANDLE_VALUE )
  {
    if( drawLeft ) IWRSTEREO_SetLR( stereoHandle, LEFT_EYE );
    else           IWRSTEREO_SetLR( stereoHandle, RIGHT_EYE );

    drawLeft = !drawLeft;   //toggle after check and before usage?

    if( drawLeft ) setViewingFrustum( LEFT_EYE,  screenWidth, screenHeight );
    else           setViewingFrustum( RIGHT_EYE, screenWidth, screenHeight );
  }
  else
  {
    setViewingFrustum( MONO_EYES, screenWidth, screenHeight );
  }

  if( stereoHandle == INVALID_HANDLE_VALUE ) return;

  // Add headtracking from VR920 tracker.
  if( tracking )
    applyOrientation();
}


// -------------------------------------------------------------------------------------------- //
void VR920::endDraw()
{
  EXIT_IF_NOT_ENABLED() return;

  //Wait for the VR920 to acknowldege previous right eye frame is scanning into frame buffer.
  if( drawLeft ) IWRSTEREO_WaitForAck( stereoHandle, LEFT_EYE );
  else           IWRSTEREO_WaitForAck( stereoHandle, RIGHT_EYE );

  glFinish();
}

// -------------------------------------------------------------------------------------------- //
void VR920::setLeftEye()   { IWRSTEREO_SetLR( stereoHandle, LEFT_EYE );       }
// -------------------------------------------------------------------------------------------- //
void VR920::setRightEye()  { IWRSTEREO_SetLR( stereoHandle, RIGHT_EYE );      }
// -------------------------------------------------------------------------------------------- //
void VR920::waitLeftEye()  { IWRSTEREO_WaitForAck( stereoHandle, LEFT_EYE );  }
// -------------------------------------------------------------------------------------------- //
void VR920::waitRightEye() { IWRSTEREO_WaitForAck( stereoHandle, RIGHT_EYE ); }
// -------------------------------------------------------------------------------------------- //
void VR920::applyOrientation() {
  glRotated( -orientation.x, 1.0, 0.0, 0.0 );
  glRotated(  orientation.z, 0.0, 0.0, 1.0 );
  glRotated( -orientation.y, 0.0, 1.0, 0.0 );
}


// -------------------------------------------------------------------------------------------- //
bool VR920::shouldUpdate()
{
  return stereoEnabled && stereoHandle != INVALID_HANDLE_VALUE ? ( frame % 2 == 0 ) : true;
}
// -------------------------------------------------------------------------------------------- //
static float degToRad( float deg ) {
  return deg * 0.0174532925f;
}
// -------------------------------------------------------------------------------------------- //
void VR920::setViewingFrustum( int eye, float screenWidth, float screenHeight )
{
  GLfloat   fovy         = 45.0;                                      //field of view in y-axis
  GLfloat   aspect       = screenWidth / screenHeight;                //screen aspect ratio
  GLfloat   nearZ        = 1.0;                                       //near clipping plane
  GLfloat   farZ         = 1000.0;                                    //far clipping plane
  GLfloat   top          = nearZ  * tan( degToRad( fovy / 2 ) );
  GLdouble  right        = aspect * top;
  GLdouble  frustumshift = (eyeSeparation / 2) * nearZ / focalLength;
  GLdouble  leftfrustum, rightfrustum, bottomfrustum, topfrustum;
  GLfloat   modeltranslation;

  switch( eye )
  {
    case LEFT_EYE:    // Setup left viewing frustum.
      topfrustum        =  top;
      bottomfrustum     = -top;
      leftfrustum       = -right + frustumshift;
      rightfrustum      =  right + frustumshift;
      modeltranslation  =  eyeSeparation / 2;
    break;

    case RIGHT_EYE:   // Setup right viewing frustum.

      topfrustum       =  top;
      bottomfrustum    = -top;
      leftfrustum      = -right - frustumshift;
      rightfrustum     =  right - frustumshift;
      modeltranslation = -eyeSeparation / 2;
    break;

    case MONO_EYES:   // Setup mono viewing frustum.
      topfrustum       =  top;
      bottomfrustum    = -top;
      leftfrustum      = -right;
      rightfrustum     =  right;
      modeltranslation =  0.0f;
    break;
  }

  // Initialize off-axis projection if in stereoscopy mode.
  glMatrixMode   ( GL_PROJECTION );
  glLoadIdentity ();
  glFrustum      ( leftfrustum, rightfrustum, bottomfrustum, topfrustum, nearZ, farZ );


  glMatrixMode   ( GL_MODELVIEW );
  glLoadIdentity ();
  glTranslated   ( modeltranslation , 0.0f, 0.0f ); // Translate Camera to cancel parallax.

  // Add headtracking from VR920 tracker.
  if( tracking )
  {
    glRotated( -orientation.x, 1.0, 0.0, 0.0 );
    glRotated(  orientation.z, 0.0, 0.0, 1.0 );
    glRotated( -orientation.y, 0.0, 1.0, 0.0 );
  }

  // Translate camera to global viewing position.
  //glTranslated( vr920_CameraPosition.x, vr920_CameraPosition.y, vr920_CameraPosition.z );
}