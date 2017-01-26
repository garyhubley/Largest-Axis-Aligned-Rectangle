
#include "Library.h"
#include "opencv2/core.hpp"
#include <iostream>
#include <opencv2/imgproc.hpp>

//enum MINMAX { MIN_X, MAX_Y, MAX_X, MIN_Y };
std::vector< int > Find_Extreme_Values( const std::vector< cv::Point2i > &points ) {
  if( points.size() < 3 ) {
    throw std::range_error( "Cannot be a polygon with less than 3 vertices" );
  }

  std::vector< int > extremes( 4 );

  // skip the first element, waste of time
  for( auto i = 1; i < points.size(); i++ ) {

    if( points[ i ].x < points[ extremes[ MIN_X ] ].x ) {  // check for new min x value
      extremes[ MIN_X ] = i;
    } 

    if( points[ i ].x > points[ extremes[ MAX_X ] ].x ) {  // check for new max x value
      extremes[ MAX_X ] = i;
    } 

    if( points[ i ].y <= points[ extremes[ MIN_Y ] ].y ) {  // check for new min y value
      extremes[ MIN_Y ] = i;
    }

    if( points[ i ].y >= points[ extremes[ MAX_Y ] ].y ) {  // check for new max y value
      extremes[ MAX_Y ] = i;
    }

  }  // end for( i < points.size() - 1; ){}
  
  if( points.front() != points.back() ) {
    if( points.front().x < points[ extremes[ MIN_X ] ].x ) {  // check for new min x value
      extremes[ MIN_X ] = 0;
    }

    if( points.front().x > points[ extremes[ MAX_X ] ].x ) {  // check for new max x value
      extremes[ MAX_X ] = 0;
    }

    if( points.front().y <= points[ extremes[ MIN_Y ] ].y ) {  // check for new min y value
      extremes[ MIN_Y ] = 0;
    }

    if( points.front().y >= points[ extremes[ MAX_Y ] ].y ) {  // check for new max y value
      extremes[ MAX_Y ] = 0;
    }
  }
  
  if( points[ extremes[ MIN_X ] ].y == points[ extremes[ MAX_Y ] ].y ) {
    extremes[ MAX_Y ] = extremes[ MIN_X ];
  } 
  if( points[ extremes[ MIN_Y ] ].x == points[ extremes[ MAX_X ] ].x ) {
    extremes[ MAX_X ] = extremes[ MIN_Y ];
  }
     
  if( points[ extremes[ MAX_X ] ].y == points[ extremes[ MAX_Y ] ].y ) {
    extremes[ MAX_Y ] = extremes[ MAX_X ];
  } 
  if( points[ extremes[ MIN_Y ] ].x == points[ extremes[ MIN_X ] ].x ) {
    extremes[ MIN_X ] = extremes[ MIN_Y ];
  }
  
  return extremes;

}

void Sectionalize_Polygon( std::vector< std::vector< cv::Point2i > > &sections, const std::vector< cv::Point2i > &polygon ) {
  if( sections.size() != 4 ) {
    throw std::range_error( "'sections' must be size 4" );
  }

  std::vector< int > section_idx = Find_Extreme_Values( polygon );    // determine where each section starts and ends

  std::sort( section_idx.begin(), section_idx.end() );                // sort the values into chronological order
  
  for( auto i = 0; i < NUM_SECTIONS - 1; i++ ) {                      // copy each section 
    sections[ i ] = std::vector< cv::Point2i >( polygon.begin() + section_idx[ i ], 
                                                polygon.begin() + section_idx[ i + 1 ] + 1 );
  } 
  
  // copy last section, (avoid out of range)
  sections[ 3 ] = std::vector< cv::Point2i >( polygon.begin() + section_idx[ 3 ], polygon.end() );

  if( section_idx[ 0 ] != 0 ) {                                       // check if a section overlaps the beginning of the polygon
    sections[ 3 ].insert( sections[ 3 ].end(), polygon.begin() + 1, polygon.begin() + section_idx[ 0 ] + 1 );
  }

}

int LineLineIntersect_2D( const std::vector< cv::Point2i > &line1, const std::vector< cv::Point2i > &line2, 
                          cv::Point2f* intersection ) {
  // this works
  if(line1.front() == line1.back() || line2.front() == line2.back() ) {  // points are the same. undefined vector
    return -1;
  }

  Vector2f dir_seg1 = line1.back() - line1.front();
  Vector2f dir_seg2 = line2.back() - line2.front();

  Vector2f dir_seg1_seg2 = line1.front() - line2.front();
  double D = PerpendicularProduct_2D( dir_seg1, dir_seg2 );

  // test if  they are parallel (includes either being a point)
  if( fabs( D ) < SMALL_NUMBER ) {           // seg1 and seg2 are parallel
    if( PerpendicularProduct_2D( dir_seg1, dir_seg1_seg2 ) != 0 ||
        PerpendicularProduct_2D( dir_seg2, dir_seg1_seg2 ) != 0 ) {
      return 0;                    // they are NOT collinear
    }
    return 2;
  }

  // the lines are skew and will intersect in a point
  // get the intersect parameter for seg1
  double     sI = PerpendicularProduct_2D( dir_seg2, dir_seg1_seg2 ) / D;
  // get the intersect parameter for seg2
  double     tI = PerpendicularProduct_2D( dir_seg1, dir_seg1_seg2 ) / D;

  *intersection = static_cast<cv::Point2f>( line1.front() ) + sI * dir_seg1;                // compute seg1 intersect point
  return 1;
}

int LineLineIntersect_2D( const cv::Point2i &point1, float slope1, const cv::Point2i &point2, float slope2, cv::Point2f *intersect ) {
  if( slope1 == slope2) { // lines are parallel
    if( -point1.x * slope1 + point1.y == -point2.x * slope2 + point2.y ) {  
      return 2;  // lines are colinear
    }
    return 0; // lines are not colinear
  } // lines arent parallel. they will intersect 

  float x = ( slope2 * static_cast<float>( point2.x ) - slope1 *static_cast<float>( point1.x ) + 
            static_cast<float>( point1.y - point2.y ) ) / ( slope2 - slope1 );

  float y = ( slope2 * static_cast<float>( point1.y ) - slope1 * static_cast<float>( point2.y ) + 
            static_cast<float>( point2.x - point1.x ) * slope1 * slope2 ) / ( slope2 - slope1 );
  *intersect = cv::Point2f( x, y );
  return 1;
}

float PerpendicularProduct_2D( const cv::Point2f &one, const cv::Point2f &two ) {
  return { one.x * two.y - one.y * two.x };                   // perp product  (2D)
}

std::vector< float > MagnitudeSection( std::vector< cv::Point2i > section ) {
  std::vector< float > mag;                                      // create return value
  int sz = static_cast<int>( section.size() ) - 1;               
  cv::Mat distances( sz, 1, CV_32F );
  cv::Mat x_values( sz, 1, CV_32F );
  cv::Mat y_values( sz, 1, CV_32F );

  for( auto j = 0; j < sz; j++ ) {                               // loop through all points in section
    cv::Point2i diff { section[ j ] - section[ j + 1 ] };        // calculate the difference of the x and y values
    x_values.at< float >( j ) = static_cast< float >( diff.x );  // separate x values 
    y_values.at< float >( j ) = static_cast< float >( diff.y );  // separate y values 
  }

  cv::magnitude( x_values, y_values, distances );                // get magnitude of each segment in section
  mag = distances;                                               // convert to vector
  return mag;
}


float slope( const cv::Point2i &point1, const cv::Point2i &point2 ) {
  return { static_cast<float>( point2.y - point1.y ) / static_cast<float>( point2.x - point1.x ) };
}


double PointOrientation( const cv::Point& P0, const cv::Point& P1, const cv::Point& P2 ) {
  return ( ( P1.x - P0.x ) * ( P2.y - P0.y ) - ( P2.x - P0.x ) * ( P1.y - P0.y ) );
}

unsigned Find_Path( size_t sizeA, size_t sizeC ) {
  unsigned pathA, pathC;
  switch( sizeA ) {
  case 0:// shouldnt be possible
  case 1: 
    pathA = 0;
    break;
  case 2:
    pathA = 1;
    break;
  default:
    pathA = 2;
    break;
  }

  switch( sizeC ) {
  case 0:// shouldnt be possible
  case 1: 
    pathC = 0;
    break;
  case 2:
    pathC = 1;
    break;
  default:
    pathC = 2;
    break;
  }

  // pathA -> 00 00 <- pathC
  // 9 possible options:
  //    0000  ( 0 )
  //    0001  ( 1 )
  //    0010  ( 2 )
  //    0100  ( 4 )
  //    0101  ( 5 )
  //    0110  ( 6 )
  //    1000  ( 8 )
  //    1001  ( 9 )
  //    1010  ( 10 )

  return { ( pathA << 2 ) | ( pathC & 0x03 ) };
}


// inSegment(): determine if a point is inside a segment
//    Input:  a point P, and a collinear segment S
//    Return: 1 = P is inside S
//            0 = P is  not inside S
int Is_In_Segment( const cv::Point &pt, const std::vector< cv::Point > &seg ) {

  if( seg[ 0 ].x != seg[ 1 ].x ) {    // seg is not  vertical
    
    if( seg[ 0 ].x <= pt.x && pt.x <= seg[ 1 ].x )  // seg goes left -> right
      return 1;
    
    if( seg[ 0 ].x >= pt.x && pt.x >= seg[ 1 ].x )  // seg goes right -> left
      return 1;

  } else {    // seg is vertical, so test y  coordinate
    
    if( seg[ 0 ].y <= pt.y && pt.y <= seg[ 1 ].y )  // bottom -> top
      return 1;

    if( seg[ 0 ].y >= pt.y && pt.y >= seg[ 1 ].y )  // top -> bottom
      return 1;

  }  // not in segment

  return 0;
}

// sizeA and sizeC = 2
//    -> todo: refactor this
std::vector< cv::Point2f > Max_Interior_Rect_Segment_Segment( const std::vector< cv::Point > &segA, 
  const std::vector< cv::Point > &segC, float &max_area, const std::vector< cv::Point > &polygon ) {
  
  if( segA.size() != 2 || segC.size()!=2) {
    throw std::range_error( "One or both segments are not the proper length" );
  }

  float slopeA = slope( segA[ 0 ], segA[ 1 ] );
  float slopeC = slope( segC[ 0 ], segC[ 1 ] );
  max_area = 0.f;                                  // sanity
  std::vector< cv::Point2f > result( 2 );

  for( auto i = 0; i < 2; i++ ) {
    float areaA = 0.f, areaC = 0.f;
    cv::Point2f A_cross_C;
    cv::Point2f C_cross_A;

    // find intersect of line from segA[i] to segC with slope of -slopeC
    if( Intersect_Point_Slope( segA[ i ], segC, A_cross_C ) ) {
      if( cv::pointPolygonTest( polygon, cv::Point2f( static_cast<float>( segA[ i ].x ), A_cross_C.y ), false ) >= 0 &&
          cv::pointPolygonTest( polygon, cv::Point2f( A_cross_C.y, static_cast<float>( segA[ i ].y ) ), false ) >= 0 ) {

        areaA = fabs( ( segA[ i ].x - A_cross_C.x )*( segA[ i ].y - A_cross_C.y ) );
      }
    }
    
    // find intersect of line from segC[i] to segA with slope of -slopeA
    if( Intersect_Point_Slope( segC[ i ], segA, C_cross_A ) ) {
      if( cv::pointPolygonTest( polygon, cv::Point2f( static_cast<float>( segC[ i ].x ), C_cross_A.y ), false ) >= 0 &&
          cv::pointPolygonTest( polygon, cv::Point2f( C_cross_A.x, static_cast<float>( segC[ i ].y ) ), false ) >= 0 ) {

        areaC = fabs( ( segC[ i ].x - C_cross_A.x )*( segC[ i ].y - C_cross_A.y ) );
      }
    }

    if( areaA > areaC && areaA > max_area ) {
      max_area = areaA;
      result[ 0 ] = segA[ i ];
      result[ 1 ] = A_cross_C;
    } else if ( areaC > areaA && areaC > max_area ) {
      max_area = areaC;
      result[ 0 ] = segC[ i ];
      result[ 1 ] = C_cross_A;
    }  
       
  }  // end for loop

  return result;
}

bool Intersect_Point_Slope( const cv::Point &pt, const std::vector<cv::Point> &line, cv::Point2f &intersect ) {
  if( line.size() != 2 ) {
    throw std::range_error( "A line consists of 2 points" );
  }

  float line_slope = slope( line[ 0 ], line[ 1 ] );
  intersect.x = 0.5f * ( pt.x + line[ 0 ].x + ( pt.y - line[ 0 ].y ) / line_slope );
  intersect.y = -line_slope * ( intersect.x - pt.x ) + pt.y;
  if( Is_In_Segment( intersect, line) ){
    return true;
  }
  intersect = cv::Point2f( 0, 0 );
  return false;
}

std::vector< cv::Point2f > Max_Interior_Rect_Polyline_Segment( std::vector< cv::Point > polyline, std::vector< cv::Point > seg,
                                                float &max_area, const std::vector< cv::Point > &polygon ) {
  if( seg.size() != 2 ) {
    throw std::range_error( "Segments consist of 2 points" );
  }
  if( polyline.size() <= 2 ) {
    throw std::range_error( "Polyline must have more than 2 vertices" );
  }
  
  float s = slope( seg[ 0 ], seg[ 1 ] );
  std::vector< cv::Point2f > result( 2 );
  max_area = 0.f;                                  // sanity

  // s lies between the slope of the first and last section of the polyline 
  if( s <= slope( polyline[ 0 ], polyline[ 1 ] ) && s >= slope( *( polyline.end() - 2 ), *( polyline.end() - 1 ) ) ) {
    // foreach vertex in rangeC calculate the intercept of 
    // the line crossing through the vertex with slope = -s
    for( auto pt : polyline ) {
      cv::Point2f intercept;
      if( Intersect_Point_Slope( pt, seg, intercept ) ) {
      // see if all vertices lie inside polygon
        if( cv::pointPolygonTest( polygon, cv::Point2f( static_cast<float>( pt.x ), intercept.y ), false ) >= 0 &&
            cv::pointPolygonTest( polygon, cv::Point2f( intercept.x, static_cast<float>( pt.y ) ), false ) >= 0 ) {
          float area = fabs( ( intercept.x - pt.x )*( intercept.y - pt.y ) );

          if( area > max_area ) {
            max_area = area;
            result[ 0 ] = pt;
            result[ 1 ] = intercept;
          }

        } // A vertex isnt inside polygon

      }

    } // end for() loop

  } // s outside range

  return result;
}

bool Rect_In_Polygon( const std::vector< cv::Point2f > &rect, const std::vector< cv::Point > &poly ) {
  if( rect.size() != 2 ) {
    throw std::range_error( "Rectangle consists of 2 points on opposite corners" );
  }

  return { cv::pointPolygonTest( poly, cv::Point2f( rect[ 0 ].x, rect[ 1 ].y ), false ) >= 0 &&
    cv::pointPolygonTest( poly, cv::Point2f( rect[ 1 ].x, rect[ 0 ].y ), false ) >= 0 &&
    cv::pointPolygonTest( poly, rect[ 0 ], false ) >= 0 &&
    cv::pointPolygonTest( poly, rect[ 1 ], false ) >= 0 };
  
}

std::vector<cv::Point2f> Max_Interior_Rect_Point_Polyline( const cv::Point2f &pt, const std::vector< cv::Point > &polyline, const std::vector< cv::Point> &polygon, float &max_area ) {
  max_area = 0.f;
  std::vector< cv::Point2f> result( 2 );

  for( auto i = 0; i < polyline.size() - 1; i++ ) {
    cv::Point2f intersect;
    std::vector< cv::Point2f > rect( 2, { 0, 0 } );

    if( Intersect_Point_Slope( pt, std::vector<cv::Point>( polyline.begin() + i, polyline.begin() + i + 2 ), intersect ) ) {
      rect[ 0 ] = pt;
      rect[ 1 ] = intersect;
      if( Rect_In_Polygon( rect, polygon ) ) {
        float area = fabs( ( rect[ 1 ].x - rect[ 0 ].x )*( rect[ 1 ].y - rect[ 0 ].y ) );

        if( area > max_area ) {
          max_area = area;
          result[ 0 ] = rect[ 0 ];
          result[ 1 ] = rect[ 1 ];
        }
      }

    }

    rect[ 0 ] = pt;
    rect[ 1 ] = polyline[ i ];
    if( Rect_In_Polygon( rect, polygon ) ) {
      float area = fabs( ( rect[ 1 ].x - rect[ 0 ].x )*( rect[ 1 ].y - rect[ 0 ].y ) );

      if( area > max_area ) {
        max_area = area;
        result[ 0 ] = rect[ 0 ];
        result[ 1 ] = rect[ 1 ];
      }

    }

  } // end for loop
  return result;
}

std::vector<cv::Point2f> Max_Interior_Rect_Polyline_Polyline( std::vector<cv::Point> &polyline1, std::vector<cv::Point> &polyline2, float &max_area, const std::vector<cv::Point> &polygon ) {
  if( polyline1.size() < 3 || polyline2.size() < 3 ) {
    throw std::range_error( "One or both polylines are too small" );
  }

  std::vector<cv::Point2f> result( 2 );
  
  // choose vertex near middle of sectionA and sectionC
  int idxA = static_cast<int>( polyline1.size() ) / 2;
  int idxC = static_cast<int>( polyline2.size() ) / 2;
  
  // choose a slope for A
  float mA = slope( polyline1[ idxA ], polyline1[ idxA - 1 ] );

  // choose a slope for C
  float mC = slope( polyline2[ idxC ], polyline2[ idxC - 1 ] );

  // calculate slope between 'a' and 'c'
  float mAC = slope( polyline1[ idxA ], polyline2[ idxC ] );


  while( polyline1.size() > 1 && polyline2.size() > 1 ) {
    int eliminate = 0;


    // test if f(a) is after or before 'c'
    if( mA < mC ) {      // after
      eliminate = 0;
    } else {             // before
      eliminate = 1;
    }

    // test if g(c) is after or before 'a'
    if( -mC <= mAC ) {    // after
      eliminate = eliminate << 1;
    } else {              // before
      eliminate = ( eliminate << 1 ) | ( 1 );
    }

    switch( eliminate ) {
    case 0:          // f(a) after c   &&  g(c) after a   eliminate everything  before c
      std::vector< cv::Point2i >( polyline2.begin() + idxC, polyline2.end() ).swap( polyline2 );
      
      // change rangeC so change mC
      idxC = 0;

      if( polyline2.size() > 1 ) {
        mC = slope( polyline2[ idxC ], polyline2[ idxC + 1 ] );
      }
      break;
    case 1:          // f(a) after c   &&  g(c) before a  eliminate everything  after a
      std::vector< cv::Point2i >( polyline1.begin(), polyline1.begin() + idxA + 1 ).swap( polyline1 );
      // change rangeA so change mA
      idxA = static_cast<int>( polyline1.size() ) - 1;

      if( polyline1.size() > 1 ) {
        mA = slope( polyline1[ idxA ], polyline1[ idxA - 1 ] );
      }
      break;
    case 2:          // f(a) before c  &&  g(c) after a   eliminate everything  before a
      std::vector< cv::Point2i >( polyline1.begin() + idxA, polyline1.end() ).swap( polyline1 );
      // change rangeC so change mC
      idxA = 0;

      if( polyline1.size() > 1 ) {
        mA = slope( polyline1[ idxA ], polyline1[ idxA + 1 ] );
      }
      break;
    case 3:          // f(a) before c  &&  g(c) before a  eliminate everything  after c
      std::vector< cv::Point2i >( polyline2.begin(), polyline2.begin() + idxC + 1 ).swap( polyline2 );
      // change rangeA so change mA
      idxC = static_cast<int>( polyline2.size() ) - 1;

      if( polyline2.size() > 1 ) {
        mC = slope( polyline2[ idxC ], polyline2[ idxC - 1 ] );
      }
      break;
    default:
      std::cout << "Something went wrong" << std::endl;
      break;
    }
    // recalculate mAC
    mAC = slope( polyline1[ idxA ], polyline2[ idxC ] );
  }
    
  if( polyline1.size() == 1 ) {
    result = Max_Interior_Rect_Point_Polyline( polyline1[ 0 ], polyline2, polygon, max_area );
  } else if( polyline2.size() == 1 ) {
    result = Max_Interior_Rect_Point_Polyline( polyline2[ 0 ], polyline1, polygon, max_area );
  }
  return result;
}

void PrintVector( const std::vector< float > &vec ) {
  for( auto j : vec ) {
    std::cout << "    " << j << std::endl;
  }
}

void PrintVector( const std::vector< int > &vec ) {
  for( auto j : vec ) {
    std::cout << "    " << j << std::endl;
  }
}

void PrintVector( const std::vector< cv::Point2i > &vec ) {
  for( auto j : vec ) {
    std::cout << "    " << j << std::endl;
  }
}

void PrintVector( const std::vector< cv::Point2f > &vec ) {
  for( auto j : vec ) {
    std::cout << "    " << j << std::endl;
  }
}

void PrintSections( const std::vector< std::vector< cv::Point2i>> sec ) {
  for( auto i = 0; i < sec.size(); i++ ) {
    std::cout << "sec " << i << ": " << std::endl;
    PrintVector( sec[ i ] );
  }
}