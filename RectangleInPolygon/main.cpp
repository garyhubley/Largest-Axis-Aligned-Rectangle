
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "main.h"
#include "time.h"
//#include "Library.h"
#include <filesystem>
#include <iostream>
#include "../Library/Library.h"

std::string elim_string[ 4 ] { "f(a) after c   &&  g(c) after a   eliminate everything  before c",
"f(a) after c   &&  g(c) before a  eliminate everything  after a",
"f(a) before c  &&  g(c) after a   eliminate everything  before a",
"f(a) before c  &&  g(c) before a  eliminate everything  after c" };
  



int main() {
  /*std::vector< cv::Point2i > polygon { { 320, 320 }, { 340, 500 }, { 500, 540 }, { 540, 480 },
  { 520, 340 }, { 440, 300 }, { 320, 320 } };*/

  /*std::vector< cv::Point2i > polygon { { 240, 460 }, { 295, 510 }, { 350, 540 }, { 455, 525 }, { 550, 490 },
  { 625, 330 }, { 585, 170 }, { 400, 190 }, { 325, 225 }, { 270, 285 },{ 240, 460 } };*/

  //std::vector< cv::Point2i > polygon {{ 550, 490 },{ 590, 410 },{ 625, 330 },{ 585, 170 },{ 400, 190 },
  //  { 325, 225 },{ 270, 285 },{ 240, 460 },{ 295, 510 },{ 350, 540 },{ 455, 525 },{ 550, 490 } };

  //std::vector< cv::Point2i > polygon {{ 380, 475 },{ 450, 500 },{ 550, 500 },{ 300, 150 },{ 300, 300 },
  //  { 325, 400 },{ 380, 475 } };
  
  //std::vector< cv::Point2i > polygon {{ 420, 475 },{ 475, 400 },{ 500, 300 },{ 500, 150 },{ 250, 500 },
  //  { 350, 500 },{ 420, 475 }};

  //std::vector< cv::Point2i > polygon {{ 380, 475 },450, 500 },550, 500 },300, 150 },300, 300 },
  //{ 325, 400 },380, 475 } };

  //std::vector< cv::Point2i > polygon {{ 365, 395 },{ 455, 420 },{ 480, 355 },{ 410, 275 },{ 335, 315 },
  //{ 365, 395 }};
  
  std::vector< cv::Point2i > polygon {{ 300, 305 },{ 310, 465 },{ 480, 505 },{ 535, 445 },{ 500, 315 },
  { 410, 280 },{ 300, 305 } };

  //std::vector< cv::Point2i > polygon { {485, 505 },{ 545, 380 },{ 515, 255 },{ 375, 270 },{ 315, 300 },
  //{ 270, 345 },{ 250, 485 },{ 295, 525 },{ 335, 545 },{ 415, 535 },{ 485, 505 } };

  std::vector< std::vector< float > > dist( 4 );
  std::vector< std::vector< cv::Point2i > > sections( 4 );
  std::vector< int > res( 4 );

  cv::Matx33f affine_matrix1, affine_matrix2;
  cv::Mat frame( FRAME_SZ, FRAME_SZ, CV_8UC3, BLACK );
  float max_area=0.f;
  std::vector< cv::Point2f > largest_rect;

  srand( static_cast<uint>( time( nullptr ) ) );   // Init random seed with current time

  Sectionalize_Polygon( sections, polygon );
  
  char path;
  // copy sections.
  for( auto i = 0; i < 2; i++ ) {
    std::vector< cv::Point2i > rangeA = sections[ i ];
    std::vector< cv::Point2i > rangeC = sections[ i + 2 ];
    float area = 0.f;
    std::vector< cv::Point2f > result;
    path = Find_Path( rangeA.size(), rangeC.size() );

    switch( path ) {
    case 0:   // sizeA and sizeC < 2
    case 1:   // sizeA < 2 and sizeC = 2
    case 2:   // sizeA < 2 and sizeC > 2
    case 4:   // sizeC < 2 and sizeA = 2
    case 8:   // sizeC < 2 and sizeA > 2
      break;
    case 5:   // sizeA and sizeC = 2
      result = Max_Interior_Rect_Segment_Segment( rangeA, rangeC, area, polygon );
      break;
    case 6:   // sizeA = 2 and sizeC > 2
      result = Max_Interior_Rect_Polyline_Segment( rangeC, rangeA, area, polygon );
      break;
    case 9:   // sizeC = 2 and sizeA > 2
      result = Max_Interior_Rect_Polyline_Segment( rangeC, rangeA, area, polygon );
      break;
    case 10:  // sizeA and sizeC > 2
      result = Max_Interior_Rect_Polyline_Polyline( rangeA, rangeC, area, polygon );
      break;
    default:
      std::cout << "Something went wrong" << std::endl;
      break;

    }
    if(area>max_area) {
      max_area = area;
      largest_rect = result;
    }
  }
  
    // sizeA and sizeC < 2
    //    -> move on
    // [ sizeA | sizeC ] < 2 and [ sizeC | sizeA ] = 2
    //    -> move on
    // [ sizeA | sizeC ] < 2 and [ sizeC | sizeA ] > 2
    //    -> move on
    // sizeA and sizeC = 2
    //    -> Max_Interior_Rect_Segment_Segment
    // [ sizeA | sizeC ] = 2 and [ sizeC | sizeA ] > 2
    //    -> Max_Interior_Rect_Polyline_Segment
    // sizeA and sizeC > 2
    //    -> Max_Interior_Rect_Polyline_Polyline

    // select vertex on A
    PrintSections( sections );
    system( "cls" );
  
  

  std::cout << "**********end************" << std::endl;
  std::cout << "Corners: " << std::endl;
  PrintVector( largest_rect );
  std::cout << "Area: " << max_area << std::endl;
  
 
  
  for( auto i = 0; i < polygon.size() - 1; i++ ) {
    if( i < static_cast<int>( polygon.size() ) - 1 )
      cv::line( frame, polygon[ i ], polygon[ i + 1 ], RED );
  }
  cv::rectangle( frame, largest_rect[ 0 ], largest_rect[ 1 ], BLUE );
  cv::imshow( "Polygon", frame );
  cv::waitKey( 0 );

return 0;
  
}


  //for( auto i = 0; i < sections.size(); i++ ) {
  //  dist[ i ] = MagnitudeSection( sections[ i ] );
  //}
  //
  ////percent length to point 
  //float percent = .500f;
  //float total_section_length = 0;
  //float dist_to_travel;

  //for( auto i : dist[ 1 ] ) {
  //  total_section_length += i;
  //}
  //dist_to_travel = percent * total_section_length;
  //
  //std::cout << dist_to_travel << std::endl;
