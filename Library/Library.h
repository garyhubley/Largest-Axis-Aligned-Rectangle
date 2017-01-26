#pragma once

#include "opencv2/core/mat.hpp"

typedef cv::Point2f Vector2f;
typedef cv::Point2i Vector2i;

const int NUM_SECTIONS = 4;
const double SMALL_NUMBER = 0.00000001;  // anything that avoids division overflow

enum MINMAX { MIN_X, MAX_Y, MAX_X, MIN_Y };

/// <summary> Finds the extrem X and Y values in a vector of points. </summary>
/// <param name='&points'> A const vector of points. </param>
/// <returns> A vector holding the indicies of the extrema. </returns>
std::vector< int > Find_Extreme_Values( const std::vector< cv::Point2i > &points );

/// <summary> Separate a polygon into 4 sections based on the extrema. </summary>
/// <param name='&sections'> A vector of polylines to be passed back. </param>
/// <param name='&polygon'> A const vector of points with the last point having the same value as the first. </param>
/// <returns> None. </returns>
void Sectionalize_Polygon( std::vector< std::vector< cv::Point2i > > &sections, const std::vector< cv::Point2i > &polygon );

/// <summary> Find the 2D intersection of 2 infinite lines. </summary>
/// <param name='line1'> A vector< cv::Point2i > containing two points. </param>
/// <param name='line2'> A vector< cv::Point2i > containing two points. </param>
/// <param name='intersection_point'> Intersection of two segments </param>
/// <returns> An int coressponding to the type of intersection. 
///           -1=invalid line
///           0=disjoint (no intersect)
///           1=intersect at unique point (intersection_point)
///           2=colinear lines (overlapping)
int LineLineIntersect_2D( const std::vector< cv::Point2i > &, const std::vector< cv::Point2i > &, cv::Point2f* );
int LineLineIntersect_2D( const cv::Point2i &, float, const cv::Point2i &, float, cv::Point2f * );

/// <summary> Modification of DotProduct in which 'one' is replaced by the perpendicular vector rotated 90 degrees to 
/// the left defined by Hill (1994). </summary>
/// <param name='one'> A vector/point. </param>
/// <param name='two'> A vector/point. </param>
/// <returns> The float perpendicular dot product. </returns>
float PerpendicularProduct_2D( const cv::Point2f &one, const cv::Point2f &two );

//todo: comments
std::vector< float > MagnitudeSection( std::vector< cv::Point2i > section );

float slope( const cv::Point2i &point1, const cv::Point2i &point2 );

// PointOrientation(): test if a point is Left|On|Right of an infinite 2D line.
//    Input:  three points P0, P1, and P2
//    Return: >0 for P2 left of the line through P0 to P1
//          =0 for P2 on the line
//          <0 for P2 right of the line
double PointOrientation( const cv::Point& P0, const cv::Point& P1, const cv::Point& P2 );


unsigned Find_Path( size_t sizeA, size_t sizeC );

// inSegment(): determine if a point is inside a segment
//    Input:  a point P, and a collinear segment S
//    Return: 1 = P is inside S
//            0 = P is  not inside S
int Is_In_Segment( const cv::Point &pt, const std::vector< cv::Point > &seg );

std::vector< cv::Point2f > Max_Interior_Rect_Segment_Segment( const std::vector< cv::Point > &segA, const std::vector< cv::Point > &segC, float &max_area, const std::vector< cv::Point > &polygon );
std::vector< cv::Point2f > Max_Interior_Rect_Polyline_Segment( std::vector< cv::Point > polyline, std::vector< cv::Point > seg, float &max_area, const std::vector< cv::Point > &polygon );
std::vector<cv::Point2f> Max_Interior_Rect_Point_Polyline( const cv::Point2f &pt, const std::vector< cv::Point > &polyline, const std::vector< cv::Point> &polygon, float &max_area );
std::vector<cv::Point2f> Max_Interior_Rect_Polyline_Polyline( std::vector< cv::Point > &polyline1, std::vector< cv::Point > &polyline2, float &max_area, const std::vector< cv::Point> &polygon );

bool Intersect_Point_Slope( const cv::Point &pt, const std::vector<cv::Point> &line, cv::Point2f &intersect );
bool Rect_In_Polygon( const std::vector< cv::Point2f > &rect, const std::vector< cv::Point > &poly );


























void PrintVector( const std::vector< float > &vec );
void PrintVector( const std::vector< int > &vec );
void PrintVector( const std::vector< cv::Point2i > &vec );
void PrintVector( const std::vector< cv::Point2f > &vec );
void PrintSections( const std::vector< std::vector< cv::Point2i>> sec );
