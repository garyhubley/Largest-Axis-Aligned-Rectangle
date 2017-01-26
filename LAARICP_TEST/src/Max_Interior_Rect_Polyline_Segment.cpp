#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Library/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Max_Interior_Rect_Polyline_Segment_Test_Class ) {
public:
  TEST_METHOD( Max_Interior_Rect_Polyline_Segment__Basic_Test1 ) {
    std::vector< cv::Point > polygon {
      { 380, 475 },
      { 450, 500 },
      { 550, 500 },
      { 300, 150 },
      { 300, 300 },
      { 325, 400 },
      { 380, 475 } };

    std::vector< std::vector< cv::Point >> sections( 4 );
    Sectionalize_Polygon( sections, polygon );
    
    
    std::vector< cv::Point2f > result;
    float max_area = 0.f;

    result = Max_Interior_Rect_Polyline_Segment( sections[3], sections[ 1 ], max_area, polygon );

    // area
    Assert::AreEqual( 8254.4643f, max_area, 0.1f );

    // first point
    Assert::AreEqual( 325.f, result[ 0 ].x, 0.1f );
    Assert::AreEqual( 400.f, result[ 0 ].y, 0.1f );

    // second point
    Assert::AreEqual( 401.7857f, result[ 1 ].x, 0.1f );
    Assert::AreEqual( 292.5f, result[ 1 ].y, 0.1f );
  }
  
  TEST_METHOD( Max_Interior_Rect_Polyline_Segment__Basic_Test2 ) {
    std::vector< cv::Point > polygon {
      { 365, 395 },
      { 455, 420 },
      { 480, 355 },
      { 410, 275 },
      { 335, 315 },
      { 365, 395 } };

    std::vector< std::vector< cv::Point >> sections( 4 );
    Sectionalize_Polygon( sections, polygon );

    std::vector< cv::Point2f > result;
    float max_area = 0.f;

    result = Max_Interior_Rect_Polyline_Segment( sections[ 3 ], sections[ 1 ], max_area, polygon );

    // area
    Assert::AreEqual( 6428.57f, max_area, 0.1f );

    // first point
    Assert::AreEqual( 365.f, result[ 0 ].x, 0.1f );
    Assert::AreEqual( 395.f, result[ 0 ].y, 0.1f );

    // second point
    Assert::AreEqual( 440.f, result[ 1 ].x, 0.1f );
    Assert::AreEqual( 309.29f, result[ 1 ].y, 0.1f );
  }

  };

}

