#include "stdafx.h"
#include "CppUnitTest.h"

#include "LAARICP_Lib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Max_Interior_Rect_Segment_Segment_Test_Class ) {
public:
  TEST_METHOD( Max_Interior_Rect_Segment_Segment__Basic_Test1 ) {
    std::vector< cv::Point > polygon {
      { 0, 0 },
      { -3, 0 },
      { -3, 1 },
      { 3, 4 },
      { 5, 4 },
      { 5, 1 } };

    std::vector< cv::Point > segA { { 0, 0 }, { 5, 1 } };
    std::vector< cv::Point > segC { {-3, 1 }, { 7, 6 } };
    std::vector< cv::Point2f > result;
    float max_area = 0.f;
    
    result = Max_Interior_Rect_Segment_Segment( segA, segC, max_area, polygon );
    
    // area
    Assert::AreEqual( 8.f, max_area );

    // first point
    Assert::AreEqual( 5.f, result[ 0 ].x );
    Assert::AreEqual( 1.f, result[ 0 ].y );

    // second point
    Assert::AreEqual( 1.f, result[ 1 ].x );
    Assert::AreEqual( 3.f, result[ 1 ].y );
  }

  TEST_METHOD( Max_Interior_Rect_Segment_Segment__Basic_Test2 ) {
    std::vector< cv::Point > polygon {
      { 0, 0 },
      { -3, 0 },
      { -3, 1 },
      { 3, 4 },
      { 5, 1 } };

    std::vector< cv::Point > segA { { 0, 0 }, { 5, 1 } };
    std::vector< cv::Point > segC { { -3, 1 }, { 7, 6 } };
    std::vector< cv::Point2f > result;
    float max_area = 0.f;

    result = Max_Interior_Rect_Segment_Segment( segA, segC, max_area, polygon );

    // area
    Assert::AreEqual( 3.2f, max_area, 0.1f );

    // first point
    Assert::AreEqual( -3.f, result[ 0 ].x, 0.1f );
    Assert::AreEqual( 1.f, result[ 0 ].y, 0.1f );

    // second point
    Assert::AreEqual( 1.f, result[ 1 ].x, 0.1f );
    Assert::AreEqual( 0.2f, result[ 1 ].y, 0.1f );
  }

  };

}

