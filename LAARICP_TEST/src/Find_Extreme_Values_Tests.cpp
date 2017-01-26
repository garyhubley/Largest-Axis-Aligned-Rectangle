#include "stdafx.h"
#include "CppUnitTest.h"
#include "opencv2/imgproc.hpp"

#include "../Library/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject
{		
	TEST_CLASS( Find_Extreme_Values_Test_Class ) {
	public:
		
		TEST_METHOD( Find_Extreme_Values__Basic_Test ) {
      std::vector< cv::Point2i > polygon { { 320, 320 }, { 340, 500 }, { 500, 540 }, { 540, 480 },
                                           { 520, 340 }, { 440, 300 }, { 320, 320 } };

      std::vector< int > result = Find_Extreme_Values( polygon );

      Assert::AreEqual( 0, result[ MIN_X ] );
      Assert::AreEqual( 3, result[ MAX_X ] );
      Assert::AreEqual( 5, result[ MIN_Y ] );
      Assert::AreEqual( 2, result[ MAX_Y ] );

		}

    TEST_METHOD( Find_Extreme_Values__Basic_Test2 ) {
      std::vector< cv::Point2i > polygon { { 240, 460 }, { 295, 510 }, { 350, 540 }, { 455, 525 }, { 550, 490 },
                                           { 625, 330 }, { 585, 170 }, { 400, 190 }, { 325, 225 }, { 270, 285 },
                                           { 240, 460 } };

      std::vector< int > result = Find_Extreme_Values( polygon );

      Assert::AreEqual( 0, result[ MIN_X ] );
      Assert::AreEqual( 5, result[ MAX_X ] );
      Assert::AreEqual( 6, result[ MIN_Y ] );
      Assert::AreEqual( 2, result[ MAX_Y ] );

    }

    TEST_METHOD( Find_Extreme_Values__Perfect_Square ) {
      std::vector< cv::Point2i > polygon { { 100, 100 }, { 100, 200 }, { 200, 200 }, { 200, 100 } };

      std::vector< int > result = Find_Extreme_Values( polygon );

      Assert::AreEqual( 0, result[ MIN_X ] );
      Assert::AreEqual( 2, result[ MAX_X ] );
      Assert::AreEqual( 0, result[ MIN_Y ] );
      Assert::AreEqual( 2, result[ MAX_Y ] );

    }

    TEST_METHOD( Find_Extreme_Values__Triangle ) {
      std::vector< cv::Point2i > polygon { { 550, 490 }, { 585, 170 }, { 200, 190 }, { 550, 490 } };

      std::vector< int > result = Find_Extreme_Values( polygon );

      Assert::AreEqual( 2, result[ MIN_X ] );
      Assert::AreEqual( 1, result[ MAX_X ] );
      Assert::AreEqual( 1, result[ MIN_Y ] );
      Assert::AreEqual( 3, result[ MAX_Y ] );

    }

    TEST_METHOD( Find_Extreme_Values__Triangle2 ) {
      std::vector< cv::Point2i > polygon { { 550, 490 }, { 500, 170 }, { 200, 190 }, { 550, 490 } };

      std::vector< int > result = Find_Extreme_Values( polygon );

      Assert::AreEqual( 2, result[ MIN_X ] );
      Assert::AreEqual( 0, result[ MAX_X ] );
      Assert::AreEqual( 1, result[ MIN_Y ] );
      Assert::AreEqual( 0, result[ MAX_Y ] );

    }



	}; //TEST_CLASS( Find_Extreme_Values_Test_Class )
  
  

}