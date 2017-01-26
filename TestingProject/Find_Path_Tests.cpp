#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Library/Library.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingProject {
  TEST_CLASS( Find_Path_Test_Class ) {
public:
  TEST_METHOD( Find_Path__Path_equals_0 ) {
    size_t A = 0, C = 0;
    unsigned path = Find_Path( A, C ); 

    Assert::AreEqual( static_cast<unsigned>( 0 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_1 ) {
    size_t A = 0, C = 2;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 1 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_2 ) {
    size_t A = 0, C = 3;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 2 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_4 ) {
    size_t A = 2, C = 0;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 4 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_5 ) {
    size_t A = 2, C = 2;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 5 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_6 ) {
    size_t A = 2, C = -5;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 6 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_8 ) {
    size_t A = -1, C = 0;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 8 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_9 ) {
    size_t A = 6, C = 2;
    unsigned path = Find_Path( A, C );

    Assert::AreEqual( static_cast<unsigned>( 9 ), path );
  }

  TEST_METHOD( Find_Path__Path_equals_10 ) {
    size_t A = 40, C = 1000;
    unsigned path = Find_Path( A, C );
    
    Assert::AreEqual( static_cast<unsigned>( 10 ), path );
  }  

  };

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