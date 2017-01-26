#include "stdafx.h"
#include "CppUnitTest.h"
#include "opencv2/imgproc.hpp"

#include "../Library/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( LineLineIntersect_2D_Test_Class ) {
public:

  TEST_METHOD( LineLineIntersect_2D__Basic_Test ) {
    std::vector< cv::Point2i > points1 { { 1, 2 }, { 0, 3 } };
    std::vector< cv::Point2i > points2 { { 3, 2 }, { 2, 1 } };
    cv::Point2f intersect;
    int result = LineLineIntersect_2D( points1, points2, &intersect );

    Assert::AreEqual( 1, result );
    Assert::AreEqual( 2.f, intersect.x );
    Assert::AreEqual( 1.f, intersect.y );

    float slope1 = -1.f;
    float slope2 = 1.f;
    intersect = cv::Point2f( 0, 0 ); // reset intersect 
    result = -50;                    // reset result 

    result = LineLineIntersect_2D( points1[ 0 ], slope1, points2[ 0 ], slope2, &intersect );

    Assert::AreEqual( 1, result );
    Assert::AreEqual( 2.f, intersect.x );
    Assert::AreEqual( 1.f, intersect.y );

  }

  TEST_METHOD( LineLineIntersect_2D__Basic_Test2 ) {
    

  }

  TEST_METHOD( LineLineIntersect_2D__Parallel_Lines ) {
    
  }

  TEST_METHOD( LineLineIntersect_2D__Colinear_Lines ) {

  }

  TEST_METHOD( LineLineIntersect_2D__Undefined_Line ) {
    
  }
  }; //TEST_CLASS( LineLineIntersect_2D_Test_Class )



}