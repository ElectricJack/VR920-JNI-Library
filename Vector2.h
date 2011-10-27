#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED


#define DEFINE_VEC2_BASIC_OVERLOADS( RET_TYPE, FUNC, CONST )                                  \
RET_TYPE  FUNC  ( float      s    ) CONST  { return FUNC( s, s );                          }  \
RET_TYPE  FUNC  ( Vector2In  v    ) CONST  { return FUNC( v.x, v.y );                      }  \
RET_TYPE  FUNC  ( SVector2In v    ) CONST  { return FUNC( v.x, v.y );                      }  \
RET_TYPE  FUNC  ( float      v[2] ) CONST  { return FUNC( v[0], v[1] );                    }  \


#define DEFINE_VEC2_OPERATOR_OVERLOADS( SELF_MOD_OP_FUNC, OP_FUNC, SELF_MOD_OP, OP )                                          \
                                                                                                                              \
Vector2Out  SELF_MOD_OP_FUNC ( float      s )                                   { return SELF_MOD_OP_FUNC( s, s );         }  \
Vector2Out  SELF_MOD_OP_FUNC ( float      v[2] )                                { return SELF_MOD_OP_FUNC( v[0], v[1] );   }  \
Vector2Out  SELF_MOD_OP_FUNC ( Vector2In  v )                                   { return SELF_MOD_OP_FUNC( v.x, v.y );     }  \
Vector2Out  SELF_MOD_OP_FUNC ( SVector2In v )                                   { return SELF_MOD_OP_FUNC( v.x, v.y );     }  \
                                                                                                                              \
Vector2Out  SELF_MOD_OP      ( float      s    )                                { return SELF_MOD_OP_FUNC( s );    }          \
Vector2Out  SELF_MOD_OP      ( float      v[2] )                                { return SELF_MOD_OP_FUNC( v );    }          \
Vector2Out  SELF_MOD_OP      ( Vector2In  v    )                                { return SELF_MOD_OP_FUNC( v );    }          \
Vector2Out  SELF_MOD_OP      ( SVector2In v    )                                { return SELF_MOD_OP_FUNC( v );    }          \
                                                                                                                              \
Vector2     OP_FUNC          ( float      s )                            const  { return get().SELF_MOD_OP_FUNC( s );      }  \
Vector2     OP_FUNC          ( float      v[2] )                         const  { return get().SELF_MOD_OP_FUNC( v );      }  \
Vector2     OP_FUNC          ( float      x, float y )                   const  { return get().SELF_MOD_OP_FUNC( x, y );   }  \
Vector2     OP_FUNC          ( Vector2In  v )                            const  { return get().SELF_MOD_OP_FUNC( v );      }  \
Vector2     OP_FUNC          ( SVector2In v )                            const  { return get().SELF_MOD_OP_FUNC( v );      }  \
                                                                                                                              \
Vector2Out  OP_FUNC          ( float      s,            Vector2Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( s );    }  \
Vector2Out  OP_FUNC          ( float      v[2],         Vector2Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );    }  \
Vector2Out  OP_FUNC          ( float      x, float y,   Vector2Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( x, y ); }  \
Vector2Out  OP_FUNC          ( Vector2In  v,            Vector2Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );    }  \
Vector2Out  OP_FUNC          ( SVector2In v,            Vector2Out  v2 ) const  { return get(v2).SELF_MOD_OP_FUNC( v );    }  \
                                                                                                                              \
Vector2     OP               ( float      s    )                         const  { return OP_FUNC( s );                }       \
Vector2     OP               ( float      v[2] )                         const  { return OP_FUNC( v );                }       \
Vector2     OP               ( Vector2In  v    )                         const  { return OP_FUNC( v );                }       \
Vector2     OP               ( SVector2In v   )                          const  { return OP_FUNC( v );                }


#define EPSILON  0.0001f

class Vector2;

struct SVector2
{
  float x;
  float y;
};

typedef const Vector2&  Vector2In;
typedef Vector2&        Vector2Out;

typedef const SVector2& SVector2In;
typedef SVector2&       SVector2Out;


class Vector2
{
public:
  float x, y;


public:
              Vector2     ( )                                   { set( 0 );                                    }
              Vector2     ( float     x, float y )              { set( x, y );                                 }
              Vector2     ( float     xy         )              { set( xy   );                                 }
              Vector2     ( Vector2In v          )              { set( v    );                                 }
              Vector2     ( float     v[2]       )              { set( v    );                                 }

  // ------------------------------------------------------------------------------------------------------------ //
  // Setters
  Vector2Out  set         ( float x,     float y )              { this->x = x; this->y = y; return *this;                      }
  Vector2Out  set         ( int   xy )                          { return set( (float)xy, (float)xy );                          }

  DEFINE_VEC2_BASIC_OVERLOADS( Vector2Out, set, )

  // ------------------------------------------------------------------------------------------------------------ //
  // Getters
  float&      get         ( int        index )                  { return index == 0 ? x : y;                   }
  Vector2Out  get         ( Vector2Out v     )            const { return v.set( *this );                       }
  Vector2     get         ( )                             const { return *this;                                }

  // ------------------------------------------------------------------------------------------------------------ //
  Vector2Out  inc         ( float x, float y )                  { this->x += x; this->y += y; return *this;    }
  Vector2Out  dec         ( float x, float y )                  { this->x -= x; this->y -= y; return *this;    }
  Vector2Out  muleq       ( float x, float y )                  { this->x *= x; this->y *= y; return *this;    }
  Vector2Out  diveq       ( float x, float y )                  { return muleq( 1.0f / x, 1.0f / y );          }
  Vector2Out  modeq       ( float x, float y )                  { this->x = fmodf( this->x, x ); this->y = fmodf( this->y, y ); return *this; }


  DEFINE_VEC2_OPERATOR_OVERLOADS( inc,   add, operator+=, operator+ )
  DEFINE_VEC2_OPERATOR_OVERLOADS( dec,   sub, operator-=, operator- )
  DEFINE_VEC2_OPERATOR_OVERLOADS( muleq, mul, operator*=, operator* )
  DEFINE_VEC2_OPERATOR_OVERLOADS( diveq, div, operator/=, operator/ )
  DEFINE_VEC2_OPERATOR_OVERLOADS( modeq, mod, operator%=, operator% )

  // ------------------------------------------------------------------------------------------------------------ //
  float       dot         ( float x, float y )            const { return this->x * x + this->y * y;            }
  // ------------------------------------------------------------------------------------------------------------ //
  float       ang         ( )                             const { return atan2( y, x );                        }

  // ------------------------------------------------------------------------------------------------------------ //
  // Midpoint
  Vector2Out  mideq       ( )                                   { return muleq( 0.5f );                        }
  Vector2     mid         ( )                             const { return get().mideq();                        }
  Vector2Out  mid         ( Vector2Out v2 )               const { return get(v2).mideq();                    }

  // ------------------------------------------------------------------------------------------------------------ //
  // Inverse
  Vector2Out  inveq       ( )                                   { return set( 1.0f / x, 1.0f / y );            }
  Vector2     inv         ( )                             const { return get().inveq();                        }
  Vector2Out  inv         ( Vector2Out v2 )               const { return get( v2 ).inveq();                    }

  // ------------------------------------------------------------------------------------------------------------ //
  // Rotate
  Vector2Out  roteq       ( float a )                           { return set( (float)( x * cos(a) - y * sin(a) )
                                                                            , (float)( x * sin(a) + y * cos(a) ) ); }
  Vector2     rot         ( float a )                     const { return get().roteq( a );                     }

  // ------------------------------------------------------------------------------------------------------------ //
  // Length
  float       lenlen      ( )                             const { return dot( *this );                         }  /// Returns length of the vector squared
  float       len         ( )                             const { return (float)sqrt( lenlen() );              }

  // ------------------------------------------------------------------------------------------------------------ //
  // Normalization ( to unit vector )
  Vector2Out  nrmeq       ( )                                   { return diveq( len() );                       }
  Vector2     nrm         ( )                             const { return get().nrmeq();                        }
  Vector2     nrm         ( Vector2 vOut )                const { return get(vOut).nrmeq();                    }

  // ------------------------------------------------------------------------------------------------------------ //
  // Projection & Reflection
  Vector2Out  prjeq       ( float x, float y )                  { float d = dot(x,y); return set(x,y).muleq( d / Vector2(x,y).lenlen() ); } /// Projects this vector onto v and stores result in this
  Vector2Out  refeq       ( float x, float y )                  { return inc( prj( -y,x ).dec( *this ).muleq( 2.0f ) );                    } /// Reflects this vector along the surface normal vector v


  DEFINE_VEC2_BASIC_OVERLOADS( float, dot, const )
  DEFINE_VEC2_OPERATOR_OVERLOADS( prjeq, prj, operator|=,  operator|  )
  DEFINE_VEC2_OPERATOR_OVERLOADS( refeq, ref, operator>>=, operator>> )

  // ------------------------------------------------------------------------------------------------------------ //
  // Linear interpolation
  static Vector2Out lerp( Vector2In v0, Vector2In v1, float t, Vector2Out v2 )
  {
    v2.set( lerp( v0.x, v1.x, t )
          , lerp( v0.y, v1.y, t ) );

    return v2;
  }

  // ------------------------------------------------------------------------------------------------------------ //
  bool operator== ( Vector2In v ) const { return fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON; }
  bool operator!= ( Vector2In v ) const { return !(*this == v); }
  bool operator<  ( Vector2In v ) const { return x < v.x && y < v.y; }
  bool operator>  ( Vector2In v ) const { return x > v.x && y > v.y; }

  void print( const char* name ) { printf( "%s = {%f, %f}\n", name, x, y ); }
  void print()                   { printf( "{%f, %f}",              x, y ); }

protected:
  static float lerp( float a, float b, float t ) { return a * (1.f - t) + b * t; }
};


#endif // VECTOR2_H_INCLUDED