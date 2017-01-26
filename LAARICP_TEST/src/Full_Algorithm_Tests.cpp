#include "stdafx.h"
#include "CppUnitTest.h"
#include "opencv2/imgproc.hpp"

#include "LAARICP_Lib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Full_Algorithm_Test_Class ) {
public:
  TEST_METHOD( Algorithm_Speed_Test ) {
    std::vector< cv::Point2i > polygon { { 485, 505 }, { 545, 380 }, { 515, 255 }, { 375, 270 }, { 315, 300 },
 { 270, 345 }, { 250, 485 }, { 295, 525 }, { 335, 545 }, { 415, 535 }, { 485, 505 } };

    for( auto i = 0; i < 100; i++ ) {
      std::vector< std::vector< cv::Point2i > > sections( 4 );

      float max_area = 0.f;
      std::vector< cv::Point2f > result;
      Sectionalize_Polygon( sections, polygon );

      char path;
      // copy sections.
      for( auto i = 0; i < 2; i++ ) {
        std::vector< cv::Point2i > rangeA = sections[ i ];
        std::vector< cv::Point2i > rangeC = sections[ i + 2 ];

        path = Find_Path( rangeA.size(), rangeC.size() );

        switch( path ) {
        case 0:   // sizeA and sizeC < 2
        case 1:   // sizeA < 2 and sizeC = 2
        case 2:   // sizeA < 2 and sizeC > 2
        case 4:   // sizeC < 2 and sizeA = 2
        case 8:   // sizeC < 2 and sizeA > 2
          break;
        case 5:   // sizeA and sizeC = 2
          result = Max_Interior_Rect_Segment_Segment( rangeA, rangeC, max_area, polygon );
          break;
        case 6:   // sizeA = 2 and sizeC > 2
          result = Max_Interior_Rect_Polyline_Segment( rangeC, rangeA, max_area, polygon );
          break;
        case 9:   // sizeC = 2 and sizeA > 2
          result = Max_Interior_Rect_Polyline_Segment( rangeC, rangeA, max_area, polygon );
          break;
        case 10:  // sizeA and sizeC > 2
          result = Max_Interior_Rect_Polyline_Polyline( rangeA, rangeC, max_area, polygon );
          break;
        default:

          break;

        }
      }
    }

  }

  };

}




