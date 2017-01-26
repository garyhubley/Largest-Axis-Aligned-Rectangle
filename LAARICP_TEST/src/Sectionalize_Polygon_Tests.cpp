#include "stdafx.h"
#include "CppUnitTest.h"
#include "opencv2/imgproc.hpp"

#include "../Library/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Sectionalize_Polygon_Test_Class ) {
public:
  TEST_METHOD( Sectionalize_Polygon__Basic_Test ) {
    std::vector< cv::Point2i > polygon { { 240, 460 }, { 295, 510 }, { 350, 540 }, { 455, 525 }, { 550, 490 },
    { 625, 330 }, { 585, 170 }, { 400, 190 }, { 325, 225 }, { 270, 285 },
    { 240, 460 } };

    std::vector< std::vector< cv::Point2i > > sections( 4 );
    Sectionalize_Polygon( sections, polygon );

    // check section A
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 0 ].size() );
    Assert::AreEqual( polygon[ 0 ].x, sections[ 0 ].front().x );
    Assert::AreEqual( polygon[ 0 ].y, sections[ 0 ].front().y );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 0 ].back().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 0 ].back().y );

    // check section B
    Assert::AreEqual( static_cast<size_t>( 4 ), sections[ 1 ].size() );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 1 ].front().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 1 ].front().y );
    Assert::AreEqual( polygon[ 5 ].x, sections[ 1 ].back().x );
    Assert::AreEqual( polygon[ 5 ].y, sections[ 1 ].back().y );

    // check section C
    Assert::AreEqual( static_cast<size_t>( 2 ), sections[ 2 ].size() );
    Assert::AreEqual( polygon[ 5 ].x, sections[ 2 ].front().x );
    Assert::AreEqual( polygon[ 5 ].y, sections[ 2 ].front().y );
    Assert::AreEqual( polygon[ 6 ].x, sections[ 2 ].back().x );
    Assert::AreEqual( polygon[ 6 ].y, sections[ 2 ].back().y );

    // check section D
    Assert::AreEqual( static_cast<size_t>( 5 ), sections[ 3 ].size() );
    Assert::AreEqual( polygon[ 6 ].x, sections[ 3 ].front().x );
    Assert::AreEqual( polygon[ 6 ].y, sections[ 3 ].front().y );
    Assert::AreEqual( polygon[ 10 ].x, sections[ 3 ].back().x );
    Assert::AreEqual( polygon[ 10 ].y, sections[ 3 ].back().y );

  }

  TEST_METHOD( Sectionalize_Polygon__Basic_Test2 ) {
    std::vector< cv::Point2i > polygon { { 300, 305 }, { 310, 465 }, { 480, 505 }, { 535, 445 },
    { 500, 315 }, { 410, 280 }, { 300, 305 } };

    std::vector< std::vector< cv::Point2i > > sections( 4 );
    Sectionalize_Polygon( sections, polygon );

    // check section A
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 0 ].size() );
    Assert::AreEqual( polygon[ 0 ].x, sections[ 0 ].front().x );
    Assert::AreEqual( polygon[ 0 ].y, sections[ 0 ].front().y );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 0 ].back().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 0 ].back().y );

    // check section B
    Assert::AreEqual( static_cast<size_t>( 2 ), sections[ 1 ].size() );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 1 ].front().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 1 ].front().y );
    Assert::AreEqual( polygon[ 3 ].x, sections[ 1 ].back().x );
    Assert::AreEqual( polygon[ 3 ].y, sections[ 1 ].back().y );

    // check section C
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 2 ].size() );
    Assert::AreEqual( polygon[ 3 ].x, sections[ 2 ].front().x );
    Assert::AreEqual( polygon[ 3 ].y, sections[ 2 ].front().y );
    Assert::AreEqual( polygon[ 5 ].x, sections[ 2 ].back().x );
    Assert::AreEqual( polygon[ 5 ].y, sections[ 2 ].back().y );

    // check section D
    Assert::AreEqual( static_cast<size_t>( 2 ), sections[ 3 ].size() );
    Assert::AreEqual( polygon[ 5 ].x, sections[ 3 ].front().x );
    Assert::AreEqual( polygon[ 5 ].y, sections[ 3 ].front().y );
    Assert::AreEqual( polygon[ 6 ].x, sections[ 3 ].back().x );
    Assert::AreEqual( polygon[ 6 ].y, sections[ 3 ].back().y );

  }

  TEST_METHOD( Sectionalize_Polygon__Origin_Overlap ) {
    std::vector< cv::Point2i > polygon { { 550, 490 }, { 625, 330 }, { 585, 170 }, { 400, 190 }, { 325, 225 },
    { 270, 285 }, { 240, 460 }, { 295, 510 }, { 350, 540 }, { 455, 525 },
    { 550, 490 } };

    std::vector< std::vector< cv::Point2i > > sections( 4 );
    Sectionalize_Polygon( sections, polygon );

    // check section A
    Assert::AreEqual( static_cast<size_t>( 2 ), sections[ 0 ].size() );
    Assert::AreEqual( polygon[ 1 ].x, sections[ 0 ].front().x );
    Assert::AreEqual( polygon[ 1 ].y, sections[ 0 ].front().y );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 0 ].back().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 0 ].back().y );

    // check section B
    Assert::AreEqual( static_cast<size_t>( 5 ), sections[ 1 ].size() );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 1 ].front().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 1 ].front().y );
    Assert::AreEqual( polygon[ 6 ].x, sections[ 1 ].back().x );
    Assert::AreEqual( polygon[ 6 ].y, sections[ 1 ].back().y );

    // check section C
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 2 ].size() );
    Assert::AreEqual( polygon[ 6 ].x, sections[ 2 ].front().x );
    Assert::AreEqual( polygon[ 6 ].y, sections[ 2 ].front().y );
    Assert::AreEqual( polygon[ 8 ].x, sections[ 2 ].back().x );
    Assert::AreEqual( polygon[ 8 ].y, sections[ 2 ].back().y );

    // check section D
    Assert::AreEqual( static_cast<size_t>( 4 ), sections[ 3 ].size() );
    Assert::AreEqual( polygon[ 8 ].x, sections[ 3 ].front().x );
    Assert::AreEqual( polygon[ 8 ].y, sections[ 3 ].front().y );
    Assert::AreEqual( polygon[ 1 ].x, sections[ 3 ].back().x );
    Assert::AreEqual( polygon[ 1 ].y, sections[ 3 ].back().y );

  }

  TEST_METHOD( Sectionalize_Polygon__Perfect_Square ) {
    std::vector< cv::Point2i > polygon { { 100, 100 }, { 100, 200 }, { 200, 200 }, { 200, 100 }, { 100, 100 } };
    std::vector< std::vector< cv::Point2i > > sections( 4 );

    Sectionalize_Polygon( sections, polygon );

    // check section A
    Assert::AreEqual( static_cast<size_t>( 1 ), sections[ 0 ].size() );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 0 ].front().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 0 ].front().y );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 0 ].back().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 0 ].back().y );

    // check section B
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 1 ].size() );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 1 ].front().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 1 ].front().y );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 1 ].back().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 1 ].back().y );

    // check section C
    Assert::AreEqual( static_cast<size_t>( 1 ), sections[ 2 ].size() );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 2 ].front().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 2 ].front().y );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 2 ].back().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 2 ].back().y );

    // check section D
    Assert::AreEqual( static_cast<size_t>( 3 ), sections[ 3 ].size() );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 3 ].front().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 3 ].front().y );
    Assert::AreEqual( polygon[ 2 ].x, sections[ 3 ].back().x );
    Assert::AreEqual( polygon[ 2 ].y, sections[ 3 ].back().y );

  }

  TEST_METHOD( Sectionalize_Polygon__Single_Section_On_Corners ) {
    std::vector< cv::Point2i > polygon {
      { 420, 475 },  //0
      { 475, 400 },  //1
      { 500, 300 },  //2
      { 500, 150 },  //3
      { 250, 500 },  //4
      { 350, 500 },  //5
      { 420, 475 }   //6
    };

    std::vector< std::vector< cv::Point2i > > sections( 4 );

    Sectionalize_Polygon( sections, polygon );

    // check section A
    Assert::AreEqual( static_cast<size_t>( 1 ), sections[ 0 ].size() );
    Assert::AreEqual( polygon[ 3 ].x, sections[ 0 ].front().x );
    Assert::AreEqual( polygon[ 3 ].y, sections[ 0 ].front().y );
    
    // check section B
    Assert::AreEqual( static_cast<size_t>( 2 ), sections[ 1 ].size() );
    Assert::AreEqual( polygon[ 3 ].x, sections[ 1 ].front().x );
    Assert::AreEqual( polygon[ 3 ].y, sections[ 1 ].front().y );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 1 ].back().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 1 ].back().y );

    // check section C
    Assert::AreEqual( static_cast<size_t>( 1 ), sections[ 2 ].size() );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 2 ].front().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 2 ].front().y );
    
    // check section D
    Assert::AreEqual( static_cast<size_t>( 6 ), sections[ 3 ].size() );
    Assert::AreEqual( polygon[ 4 ].x, sections[ 3 ].front().x );
    Assert::AreEqual( polygon[ 4 ].y, sections[ 3 ].front().y );
    Assert::AreEqual( polygon[ 3 ].x, sections[ 3 ].back().x );
    Assert::AreEqual( polygon[ 3 ].y, sections[ 3 ].back().y );

  }

  
  };

}