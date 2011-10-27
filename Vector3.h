#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include "Vector2.h"


#define DEFINE_VEC3_BASIC_OVERLOADS( RET_TYPE, FUNC, CONST )                    \
RET_TYPE  FUNC  ( float     s    ) CONST  { return FUNC( s, s, s );          }  \
RET_TYPE  FUNC  ( Vector3In v    ) CONST  { return FUNC( v.x, v.y, v.z );    }  \
RET_TYPE  FUNC  ( float     v[3] ) CONST  { return FUNC( v[0], v[1], v[2] ); }  \


#define DEFINE_VEC3_OPERATOR_OVERLOADS( SELF_MOD_OP_FUNC, OP_FUNC, SELF_MOD_OP, OP )                                                      \
                                                                                                                                          \
Vector3Out  SELF_MOD_OP_FUNC ( float      s )                                          { return SELF_MOD_OP_FUNC( s, s, s   );        }   \
Vector3Out  SELF_MOD_OP_FUNC ( float      v[3] )                                       { return SELF_MOD_OP_FUNC( v[0], v[1], v[2] ); }   \
Vector3Out  SELF_MOD_OP_FUNC ( Vector3In  v )                                          { return SELF_MOD_OP_FUNC( v.x, v.y, v.z );    }   \
Vector3Out  SELF_MOD_OP_FUNC ( SVector3In v )                                          { return SELF_MOD_OP_FUNC( v.x, v.y, v.z );    }   \
                                                                                                                                          \
Vector3Out  SELF_MOD_OP      ( float      s    )                                       { return SELF_MOD_OP_FUNC( s ); }                  \
Vector3Out  SELF_MOD_OP      ( float      v[3] )                                       { return SELF_MOD_OP_FUNC( v ); }                  \
Vector3Out  SELF_MOD_OP      ( Vector3In  v    )                                       { return SELF_MOD_OP_FUNC( v ); }                  \
Vector3Out  SELF_MOD_OP      ( SVector3In v    )                                       { return SELF_MOD_OP_FUNC( v ); }                  \
                                                                                                                                          \
Vector3     OP_FUNC          ( float      s )                                   const  { return get().SELF_MOD_OP_FUNC( s );       }      \
Vector3     OP_FUNC          ( float      v[3] )                                const  { return get().SELF_MOD_OP_FUNC( v );       }      \
Vector3     OP_FUNC          ( float      x, float y, float z )                 const  { return get().SELF_MOD_OP_FUNC( x, y, z ); }      \
Vector3     OP_FUNC          ( Vector3In  v )                                   const  { return get().SELF_MOD_OP_FUNC( v );       }      \
Vector3     OP_FUNC          ( SVector3In v )                                   const  { return get().SELF_MOD_OP_FUNC( v );       }      \
                                                                                                                                          \
Vector3Out  OP_FUNC          ( float      s,                   Vector3Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( s );       }    \
Vector3Out  OP_FUNC          ( float      v[3],                Vector3Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );       }    \
Vector3Out  OP_FUNC          ( float      x, float y, float z, Vector3Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( x, y, z ); }    \
Vector3Out  OP_FUNC          ( Vector3In  v,                   Vector3Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );       }    \
Vector3Out  OP_FUNC          ( SVector3In v,                   Vector3Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );       }    \
                                                                                                                                          \
Vector3     OP               ( float      s    )                                const  { return OP_FUNC( s ); }                           \
Vector3     OP               ( float      v[3] )                                const  { return OP_FUNC( v ); }                           \
Vector3     OP               ( Vector3In  v    )                                const  { return OP_FUNC( v ); }                           \
Vector3     OP               ( SVector3In v    )                                const  { return OP_FUNC( v ); }


class   Vector3; // Vector 3

struct SVector3
{
  float x;
  float y;
  float z;
};


typedef   const Vector3&  Vector3In;
typedef         Vector3&  Vector3Out;

typedef   const SVector3& SVector3In;
typedef         SVector3& SVector3Out;


class Vector3 : public Vector2
{
public:
  float z;

public:
  // -------------------------------------------------------------------------------------------------------- //
  // Constructors
              Vector3     ( )                                           { set( 0 );                }
              Vector3     ( float           xyz )                       { set( xyz );              }
              Vector3     ( float           x, float y, float z )       { set( x, y, z );          }
              Vector3     ( Vector3In       v )                         { set( v.x, v.y, v.z );    }
              Vector3     ( float           v[3] )                      { set( v[0], v[1], v[2] ); }
              Vector3     ( const SVector3& v )                         { set( v.x, v.y, v.z );    }

  // -------------------------------------------------------------------------------------------------------- //
  // Getters
  Vector3     get         ( )                               const { return Vector3( *this );                         }
  float&      get         ( int        index )                    { return index == 2 ? z : Vector2::get( index );   }
  Vector3Out  get         ( Vector3Out v     )              const { return v.set( *this );                           }
  Vector2     getXY       ( )                               const { return Vector2( x, y );                          }
  Vector2     getYX       ( )                               const { return Vector2( y, x );                          }
  Vector2     getYZ       ( )                               const { return Vector2( y, z );                          }
  Vector2     getZY       ( )                               const { return Vector2( z, y );                          }
  Vector2     getXZ       ( )                               const { return Vector2( x, z );                          }
  Vector2     getZX       ( )                               const { return Vector2( z, x );                          }
  // -------------------------------------------------------------------------------------------------------- //
  // Setters
  Vector3Out  set         ( int     xyz )                         { Vector2::set(xyz); this->z = (float)xyz; return *this; }
  Vector3Out  set         ( float     x, float y, float z )       { Vector2::set(x,y); this->z = z;          return *this; }
  Vector3Out  setYZ       ( float     y, float z )                { this->y = y;       this->z = z;          return *this; }
  Vector3Out  setXZ       ( float     x, float z )                { this->x = x;       this->z = z;          return *this; }
  // ------------------------------------------------------------------------------------------------------------ //
  float       lenlen      ( )                               const { return dot( *this );            }
  float       len         ( )                               const { return (float)sqrt( lenlen() ); }
  // ------------------------------------------------------------------------------------------------------------ //
  float       dot         ( float x, float y, float z )     const { return this->x*x + this->y*y + this->z*z; }
  // ------------------------------------------------------------------------------------------------------------ //
  // Normalizers
  Vector3Out  nrmeq       ( )                                     { return diveq( len() );                            }
  Vector3     nrm         ( )                               const { return get().nrmeq();                             }
  Vector3     nrm         ( Vector3Out v )                  const { return get(v).nrmeq();                            }
  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  inc         ( float x, float y, float z )           { this->x += x; this->y += y; this->z += z; return *this; }
  Vector3Out  dec         ( float x, float y, float z )           { this->x -= x; this->y -= y; this->z -= z; return *this; }
  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  muleq       ( float x, float y, float z )           { this->x *= x; this->y *= y; this->z *= z; return *this; }
  Vector3Out  diveq       ( float x, float y, float z )           { return muleq( 1.0f / x, 1.0f / y, 1.0f / z );  }
  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  modeq       ( float x, float y, float z )           { Vector2::modeq(x,y); this->z = fmod( this->z, z); return *this;  }
  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  crosseq     ( float x, float y, float z )
  {
    return set( this->y * z - this->z * y
              , this->z * x - this->x * z
              , this->x * y - this->y * x );
  }
  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  prjeq       ( float   x, float y, float z )         { float d = dot(x,y,z); return set(x,y,z).muleq( d / Vector3(x,y,z).lenlen() );  } /// Projects this vector onto v and stores result in this
  Vector3Out  refeq       ( float   x, float y, float z )         { return inc( prj( -y,x,z ).dec( *this ).muleq( 2.0f ) );                        } /// Reflects this vector along the surface normal vector v

  // -------------------------------------------------------------------------------------------------------- //
  Vector3Out  mideq       ( )                                     { return muleq( 0.5f );                                }
  Vector3Out  inveq       ( )                                     { return set( 1.0f / x, 1.0f / y, 1.0f / z );          }
  Vector3     inv         ( )                               const { return get().inveq();                                }
  Vector3Out  inv         ( Vector3Out v2 )                 const { return get( v2 ).inveq();                            }

  // -------------------------------------------------------------------------------------------------------- //
  bool        operator==  ( Vector3In v )                   const { return fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON; }
  bool        operator!=  ( Vector3In v )                   const { return !(*this == v); }
  bool        operator<   ( Vector3In v )                   const { return x < v.x && y < v.y && z < v.z; }
  bool        operator>   ( Vector3In v )                   const { return x > v.x && y > v.y && z > v.z; }


  DEFINE_VEC2_BASIC_OVERLOADS     ( Vector3, setYZ,       )
  DEFINE_VEC2_BASIC_OVERLOADS     ( Vector3, setXZ,       )

  DEFINE_VEC3_BASIC_OVERLOADS     ( float,   dot,   const )

  DEFINE_VEC3_OPERATOR_OVERLOADS  ( set,     set,   operator=,   operator=  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( inc,     add,   operator+=,  operator+  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( dec,     sub,   operator-=,  operator-  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( muleq,   mul,   operator*=,  operator*  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( diveq,   div,   operator/=,  operator/  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( modeq,   mod,   operator%=,  operator%  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( crosseq, cross, operator^=,  operator^  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( prjeq,   prj,   operator|=,  operator|  )
  DEFINE_VEC3_OPERATOR_OVERLOADS  ( refeq,   ref,   operator>>=, operator>> )


  // ------------------------------------------------------------------------------------------------------------ //
  // Linear interpolation
  static Vector3Out lerp( Vector3In v0, Vector3In v1, float t, Vector3Out v2 )
  {
    v2.set( Vector2::lerp( v0.x, v1.x, t )
          , Vector2::lerp( v0.y, v1.y, t )
          , Vector2::lerp( v0.z, v1.z, t ) );

    return v2;
  }

  // ------------------------------------------------------------------------------------------------------------ //
  void print( const char* name ) { printf( "%s = {%f, %f, %f}\n", name, x, y, z ); }
  void print()                   { printf( "{%f, %f, %f}",              x, y, z ); }


};

#endif // VECTOR3_H_INCLUDED