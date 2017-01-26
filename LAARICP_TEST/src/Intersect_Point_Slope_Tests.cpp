#include "stdafx.h"
#include "CppUnitTest.h"
#include "opencv2/imgproc.hpp"

#include "LAARICP_Lib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Intersect_Point_Slope_Test_Class ) {
public:

  TEST_METHOD( Intersect_Point_Slope__Basic_Test ) {
    std::vector< cv::Point > line { {2,1}, {3,2} };
    cv::Point pt { 2, 1 };
    float s = slope( line[ 0 ], line[ 1 ] );

    cv::Point2f result; 
    Assert::IsTrue( Intersect_Point_Slope( pt, line, result ) );
    
    Assert::AreEqual( 2.f, result.x );
    Assert::AreEqual( 1.f, result.y );

  }

  
  }; //TEST_CLASS( Intersect_Point_Slope_Test_Class ) {



}