///////////////////////////////////////////////////////////////////////////////
// UnitTest.hpp - UnitTest Framework
///////////////////////////////////////////////////////////////////////////////
// Created by Ilan Gavriel 
///////////////////////////////////////////////////////////////////////////////
// History:
// 02/03/2008 - Creating the first version based on NUnit 2.4.6 API
// 20/07/2010 - Add some NUnit 2.5.5 modification
//
///////////////////////////////////////////////////////////////////////////////
// This UnitTest Framework implements most of the NUnit functionality.
// The framework could be used in two different ways:
//	1) Assert - Each assertion failure will raise std::runtime_error, which 
//				means you have to use try and catch for every test separately.
//	2) Test - Each test prints to the tcout all PASS/FAIL statuses separately
//				(there is no need to use try/catch scope).
//
// The assert methods accepts several input parameters as follows:
//	1) expected, actual -	two input parameters
//	2) message -			free text message which can be used as a description
//	3) throws -				boolean parameters which distinguish between the
//							Assert and Test methodology (true=Assert, false=Test)
//	4) file, line -			source code location from where the test was called
//
// There are several macro that simplify the usage of the testing.
// Each macro has 4 different declarations:
//  1) ASSERT_XXX0 - use assertion methodology without a free text message
//  2) ASSERT_XXX  - use assertion methodology including a free text message
//  3) TEST_XXX0   - use testing methodology without a free text message
//  4) TEST_XXX    - use assertion methodology including a free text message
//
//	Example of usage:
//	//-------------------------------------------------------------------------
//	//  Equality
//	//-------------------------------------------------------------------------
//	UnitTest::Assert::AreEqual(1,1,			false, __FILE__, __LINE__)	// test that 1=1
//	UnitTest::Assert::AreEqual(1,1, "1=1",	false, __FILE__, __LINE__)	// test that 1=1 and print "1=1"
//	TEST_EQUAL0(1,1);													// test that 1=1
//	TEST_EQUAL(1,1,"1=1");												// test that 1=1 and print "1=1"
//
//	UnitTest::Assert::AreEqual(1,1,			true, __FILE__, __LINE__)	// assert that 1=1
//	UnitTest::Assert::AreEqual(1,1, "1=1",	true ,__FILE__, __LINE__)	// assert that 1=1
//	ASSERT_EQUAL0(1,1);													// assert that 1=1
//	ASSERT_EQUAL(1,1,"1=1");											// assert that 1=1
//
//	TEST_NOT_EQUAL0("test", "TEST");		// test that "test" != "TEST"
//
//	TEST_EQUAL(1,2, "1 is not equal to 2");	// test that 1=2 and print the fail message "1 is not equal to 2"
//	TEST_EQUAL(1,1, "1 is equal to 1");		// test that 1=1 and print the pass message "1 is equal to 1"
//
//	//-------------------------------------------------------------------------
//	// Condition
//	//-------------------------------------------------------------------------
//	TEST_IS_TRUE(1==1,					"[IsTrue]");	// make sure the given condition is true
//	TEST_TRUE(1==1,						"[True]");		// make sure the given condition is true
//
//	TEST_IS_FALSE(1==2,					"[IsFalse]");	// make sure the given condition is false
//	TEST_FALSE(1==2,					"[False]");		// make sure the given condition is false
//
//	int* p=NULL;	TEST_IS_NULL(p,		"[IsNull]");	// make sure the given pointer is null
//					TEST_NULL(p,		"[Null]");		// make sure the given pointer is null
//
//	int  n=0;	 	TEST_IS_NOT_NULL(&n,"[IsNotNull]");	// make sure the given pointer is not null
//					TEST_NOT_NULL(&n,	"[NotNull]");	// make sure the given pointer is not null
//
//	TEST_IS_EMPTY_STRING("",			"[IsEmpty]");	// make sure the input is an empty string
//	TEST_IS_NOT_EMPTY_STRING("Hello",	"[IsNotEmpty]");// make sure the input is a non-empty string
//
//	//-------------------------------------------------------------------------
//	// Comparisons
//	//-------------------------------------------------------------------------
//	TEST_GREATER(2, 1,			"[Greater]");			// 2 > 1
//	TEST_GREATER_OR_EQUAL(2, 2, "[GreaterOrEqual]");	// 2 >= 2
//	TEST_LESS(2, 3,				"[Less]");				// 2 < 3
//	TEST_LESS_OR_EQUAL(3, 3,	"[LessOrEqual]");		// 3 <= 3
//
//	//-------------------------------------------------------------------------
//	// StringAssert
//	//-------------------------------------------------------------------------
//	ASSERT_CONTAINS("World", "Hello World",		"[Contains]");		// "World" is a substring of "Hello World"
//	ASSERT_STARTS_WITH("Hello", "Hello World",	"[StartsWith]");	// "Hello" is the start of "Hello World"
//	ASSERT_EQUAL_IGNORING_CASE("test", "TEST",	"[AreEqualIgnoringCase]");	// "test" is the same as "TEST"
//	ASSERT_IS_MATCH("Hello", "Hello", "Hello is Hello");
//
//	//-------------------------------------------------------------------------
//	// Utility Methods
//	//-------------------------------------------------------------------------
//	TEST_PASS("This line will always pass");
//	TEST_FAIL("This line will always fail");
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <sstream>		// std::ostringstream
#include <iostream>		// cout, cerr
#include <tchar.h>		// _T("...")
#include <windows.h>

#pragma warning(disable:4267) // converting X to Y, possible loss of data

///////////////////////////////////////////////////////////////////////////////
// Equality Asserts
///////////////////////////////////////////////////////////////////////////////
#define ASSERT_EQUAL0(a,b)						UnitTest::Assert::AreEqual(a,b,		true,__FILE__,__LINE__)
#define ASSERT_EQUAL(a,b,msg)					UnitTest::Assert::AreEqual(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_EQUAL0(a,b)						UnitTest::Assert::AreEqual(a,b,		false,__FILE__,__LINE__)
#define TEST_EQUAL(a,b,msg)						UnitTest::Assert::AreEqual(a,b,msg,	false,__FILE__,__LINE__)

#define ASSERT_NOT_EQUAL0(a,b)					UnitTest::Assert::AreNotEqual(a,b,		true,__FILE__,__LINE__)
#define ASSERT_NOT_EQUAL(a,b,msg)				UnitTest::Assert::AreNotEqual(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_NOT_EQUAL0(a,b)					UnitTest::Assert::AreNotEqual(a,b,		false,__FILE__,__LINE__)
#define TEST_NOT_EQUAL(a,b,msg)					UnitTest::Assert::AreNotEqual(a,b,msg,	false,__FILE__,__LINE__)

///////////////////////////////////////////////////////////////////////////////
// Condition Tests
///////////////////////////////////////////////////////////////////////////////
#define ASSERT_IS_TRUE0(condition)				UnitTest::Assert::IsTrue(condition,		true,__FILE__,__LINE__)
#define ASSERT_IS_TRUE(condition,msg)			UnitTest::Assert::IsTrue(condition,msg,	true,__FILE__,__LINE__)
#define TEST_IS_TRUE0(condition)				UnitTest::Assert::IsTrue(condition,		false,__FILE__,__LINE__)
#define TEST_IS_TRUE(condition,msg)				UnitTest::Assert::IsTrue(condition,msg,	false,__FILE__,__LINE__)

#define ASSERT_TRUE0(condition)					UnitTest::Assert::True(condition,		true,__FILE__,__LINE__)
#define ASSERT_TRUE(condition,msg)				UnitTest::Assert::True(condition,msg,	true,__FILE__,__LINE__)
#define TEST_TRUE0(condition)					UnitTest::Assert::True(condition,		false,__FILE__,__LINE__)
#define TEST_TRUE(condition,msg)				UnitTest::Assert::True(condition,msg,	false,__FILE__,__LINE__)

#define ASSERT_IS_FALSE0(condition)				UnitTest::Assert::IsFalse(condition,		true,__FILE__,__LINE__)
#define ASSERT_IS_FALSE(condition,msg)			UnitTest::Assert::IsFalse(condition,msg,	true,__FILE__,__LINE__)
#define TEST_IS_FALSE0(condition)				UnitTest::Assert::IsFalse(condition,		false,__FILE__,__LINE__)
#define TEST_IS_FALSE(condition,msg)			UnitTest::Assert::IsFalse(condition,msg,	false,__FILE__,__LINE__)

#define ASSERT_FALSE0(condition)				UnitTest::Assert::False(condition,		true,__FILE__,__LINE__)
#define ASSERT_FALSE(condition,msg)				UnitTest::Assert::False(condition,msg,	true,__FILE__,__LINE__)
#define TEST_FALSE0(condition)					UnitTest::Assert::False(condition,		false,__FILE__,__LINE__)
#define TEST_FALSE(condition,msg)				UnitTest::Assert::False(condition,msg,	false,__FILE__,__LINE__)

#define ASSERT_IS_NULL0(p)						UnitTest::Assert::IsNull(p,		true,__FILE__,__LINE__)
#define ASSERT_IS_NULL(p,msg)					UnitTest::Assert::IsNull(p,msg,	true,__FILE__,__LINE__)
#define TEST_IS_NULL0(p)						UnitTest::Assert::IsNull(p,		false,__FILE__,__LINE__)
#define TEST_IS_NULL(p,msg)						UnitTest::Assert::IsNull(p,msg,	false,__FILE__,__LINE__)

#define ASSERT_NULL0(p)							UnitTest::Assert::Null(p,		true,__FILE__,__LINE__)
#define ASSERT_NULL(p,msg)						UnitTest::Assert::Null(p,msg,	true,__FILE__,__LINE__)
#define TEST_NULL0(p)							UnitTest::Assert::Null(p,		false,__FILE__,__LINE__)
#define TEST_NULL(p,msg)						UnitTest::Assert::Null(p,msg,	false,__FILE__,__LINE__)

#define ASSERT_IS_NOT_NULL0(p)					UnitTest::Assert::IsNotNull(p,		true,__FILE__,__LINE__)
#define ASSERT_IS_NOT_NULL(p,msg)				UnitTest::Assert::IsNotNull(p,msg,	true,__FILE__,__LINE__)
#define TEST_IS_NOT_NULL0(p)					UnitTest::Assert::IsNotNull(p,		false,__FILE__,__LINE__)
#define TEST_IS_NOT_NULL(p,msg)					UnitTest::Assert::IsNotNull(p,msg,	false,__FILE__,__LINE__)

#define ASSERT_NOT_NULL0(p)						UnitTest::Assert::NotNull(p,		true,__FILE__,__LINE__)
#define ASSERT_NOT_NULL(p,msg)					UnitTest::Assert::NotNull(p,msg,	true,__FILE__,__LINE__)
#define TEST_NOT_NULL0(p)						UnitTest::Assert::NotNull(p,		false,__FILE__,__LINE__)
#define TEST_NOT_NULL(p,msg)					UnitTest::Assert::NotNull(p,msg,	false,__FILE__,__LINE__)

#define ASSERT_IS_EMPTY_STRING0(str)			UnitTest::Assert::IsEmpty(str,		true,__FILE__,__LINE__)
#define ASSERT_IS_EMPTY_STRING(str,msg)			UnitTest::Assert::IsEmpty(str,msg,	true,__FILE__,__LINE__)
#define TEST_IS_EMPTY_STRING0(str)				UnitTest::Assert::IsEmpty(str,		false,__FILE__,__LINE__)
#define TEST_IS_EMPTY_STRING(str,msg)			UnitTest::Assert::IsEmpty(str,msg,	false,__FILE__,__LINE__)

#define ASSERT_IS_NOT_EMPTY_STRING0(str)		UnitTest::Assert::IsNotEmpty(str,		true,__FILE__,__LINE__)
#define ASSERT_IS_NOT_EMPTY_STRING(str,msg)		UnitTest::Assert::IsNotEmpty(str,msg,	true,__FILE__,__LINE__)
#define TEST_IS_NOT_EMPTY_STRING0(str)			UnitTest::Assert::IsNotEmpty(str,		false,__FILE__,__LINE__)
#define TEST_IS_NOT_EMPTY_STRING(str,msg)		UnitTest::Assert::IsNotEmpty(str,msg,	false,__FILE__,__LINE__)

///////////////////////////////////////////////////////////////////////////////
// Comparisons
///////////////////////////////////////////////////////////////////////////////
#define ASSERT_GREATER0(a,b)					UnitTest::Assert::Greater(a,b,		true,__FILE__,__LINE__)
#define ASSERT_GREATER(a,b,msg)					UnitTest::Assert::Greater(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_GREATER0(a,b)						UnitTest::Assert::Greater(a,b,		false,__FILE__,__LINE__)
#define TEST_GREATER(a,b,msg)					UnitTest::Assert::Greater(a,b,msg,	false,__FILE__,__LINE__)

#define ASSERT_GREATER_OR_EQUAL0(a,b)			UnitTest::Assert::GreaterOrEqual(a,b,		true,__FILE__,__LINE__)
#define ASSERT_GREATER_OR_EQUAL(a,b,msg)		UnitTest::Assert::GreaterOrEqual(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_GREATER_OR_EQUAL0(a,b)				UnitTest::Assert::GreaterOrEqual(a,b,		false,__FILE__,__LINE__)
#define TEST_GREATER_OR_EQUAL(a,b,msg)			UnitTest::Assert::GreaterOrEqual(a,b,msg,	false,__FILE__,__LINE__)

#define ASSERT_LESS0(a,b)						UnitTest::Assert::Less(a,b,		true,__FILE__,__LINE__)
#define ASSERT_LESS(a,b,msg)					UnitTest::Assert::Less(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_LESS0(a,b)							UnitTest::Assert::Less(a,b,		false,__FILE__,__LINE__)
#define TEST_LESS(a,b,msg)						UnitTest::Assert::Less(a,b,msg,	false,__FILE__,__LINE__)

#define ASSERT_LESS_OR_EQUAL0(a,b)				UnitTest::Assert::LessOrEqual(a,b,		true,__FILE__,__LINE__)
#define ASSERT_LESS_OR_EQUAL(a,b,msg)			UnitTest::Assert::LessOrEqual(a,b,msg,	true,__FILE__,__LINE__)
#define TEST_LESS_OR_EQUAL0(a,b)				UnitTest::Assert::LessOrEqual(a,b,		false,__FILE__,__LINE__)
#define TEST_LESS_OR_EQUAL(a,b,msg)				UnitTest::Assert::LessOrEqual(a,b,msg,	false,__FILE__,__LINE__)

///////////////////////////////////////////////////////////////////////////////
// StringAssert
///////////////////////////////////////////////////////////////////////////////
#define ASSERT_CONTAINS0(substr,str)			UnitTest::Assert::Contains(substr,str,		true,__FILE__,__LINE__)
#define ASSERT_CONTAINS(substr,str,msg)			UnitTest::Assert::Contains(substr,str,msg,	true,__FILE__,__LINE__)
//[DISABLE] - TEST_CONTAINS - is disabled because it use more than one assertion in the test

#define ASSERT_STARTS_WITH0(substr,str)			UnitTest::Assert::StartsWith(substr,str,		true,__FILE__,__LINE__)
#define ASSERT_STARTS_WITH(substr,str,msg)		UnitTest::Assert::StartsWith(substr,str,msg,	true,__FILE__,__LINE__)
//[DISABLE] - TEST_STARTS_WITH - is disabled because it use more than one assertion in the test

#define ASSERT_EQUAL_IGNORING_CASE0(str1,str2)		UnitTest::Assert::AreEqualIgnoringCase(str1,str2,		true,__FILE__,__LINE__)
#define ASSERT_EQUAL_IGNORING_CASE(str1,str2,msg)	UnitTest::Assert::AreEqualIgnoringCase(str1,str2,msg,	true,__FILE__,__LINE__)
//[DISABLE] - TEST_EQUAL_IGNORING_CASE - is disabled because it use more than one assertion in the test

#define ASSERT_IS_MATCH0(str1,str2)				UnitTest::Assert::IsMatch(str1,str2,		true,__FILE__,__LINE__)
#define ASSERT_IS_MATCH(str1,str2,msg)			UnitTest::Assert::IsMatch(str1,str2,msg,	true,__FILE__,__LINE__)
//[DISABLE] - TEST_IS_MATCH - is disabled because it use more than one assertion in the test

///////////////////////////////////////////////////////////////////////////////
// Utility Methods
///////////////////////////////////////////////////////////////////////////////
#define ASSERT_PASS(msg)						UnitTest::Assert::Pass(msg, true,__FILE__,__LINE__)
#define TEST_PASS(msg)							UnitTest::Assert::Pass(msg, false,__FILE__,__LINE__)

#define ASSERT_FAIL(msg)						UnitTest::Assert::Fail(msg, true,__FILE__,__LINE__)
#define TEST_FAIL(msg)							UnitTest::Assert::Fail(msg, false,__FILE__,__LINE__)

///////////////////////////////////////////////////////////////////////////////
// Wrapper for assert functions - for example: ASSERT_WRAPPER( ASSERT_IS_TRUE(1==1) );
#define ASSERT_WRAPPER(pFunction) try{ pFunction; } catch(const std::runtime_error& e) { std::cout << e.what() << std::endl; }

///////////////////////////////////////////////////////////////////////////////
// Console color
#define SET_CONSOLE_COLOR(color) SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), color)

///////////////////////////////////////////////////////////////////////////////
// namespace for UnitTest Framework - implementation for most of the NUnit functionality
///////////////////////////////////////////////////////////////////////////////
namespace UnitTest
{

///////////////////////////////////////////////////////////////////////////////
// class Assert implements all compare methods
///////////////////////////////////////////////////////////////////////////////
class Assert
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Equality Asserts - These methods test whether the two arguments are equal.
	// Overloaded methods are provided for null terminated strings
	///////////////////////////////////////////////////////////////////////////
	template <class T1, class T2>
	static void AreEqual(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqual(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void AreEqual(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected == actual), message, 
			/*[PASS]*/ _T("AreEqual: Expression was equal"),
			/*[FAIL]*/ _T("AreEqual: Expression was not equal"),
						expected, actual, throws, file, line);
	}

	template <class T1, class T2>
	static void AreNotEqual(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreNotEqual(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void AreNotEqual(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected != actual), message,
			/*[PASS]*/ _T("AreNotEqual: Expression was not equal"),
			/*[FAIL]*/ _T("AreNotEqual: Expression was equal"),
						expected, actual, throws, file, line);
	}

	// AreEqual for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void AreEqual(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqual(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void AreEqual(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqual(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void AreEqual(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqual(expected, actual, NULL, throws, file, line);
	}
	static void AreEqual(LPTSTR expected, LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// test _tcscmp only if the expected and actual buffers points to a string
		if(expected && actual)
		{
			Assert::Test( (_tcscmp(expected, actual) == 0 ), message,
				/*[PASS]*/ _T("AreEqual: Expression was equal"),
				/*[FAIL]*/ _T("AreEqual: Expression was not equal"),
							expected, actual, throws, file, line);
		}
		else
		{	// otherwise fail
			Assert::Fail( message, _T("AreEqual: Expected a non-NULL pointers"), throws, file, line);
		}
	}

	// AreNotEqual for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void AreNotEqual(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreNotEqual(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void AreNotEqual(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::AreNotEqual(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void AreNotEqual(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreNotEqual(expected, actual, NULL, throws, file, line);
	}
	static void AreNotEqual(LPTSTR expected, LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// test _tcscmp only if the expected and actual buffers points to a string
		if(expected && actual)
		{
			Assert::Test( (_tcscmp(expected, actual) != 0 ), message, 
				/*[PASS]*/ _T("AreNotEqual: Expression was not equal"),
				/*[FAIL]*/ _T("AreNotEqual: Expression was equal"),
							expected, actual, throws, file, line);
		}
		else
		{	// otherwise fail
			Assert::Fail( message, _T("AreEqual: Expected a non-NULL pointers"), throws, file, line);
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// Identity Asserts - test whether the same objects are referenced by the two arguments.
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////
	// static void AreSame(T1 const& expected, T2 const& actual, bool throws, LPCSTR file, int line);
	//
	// static void AreNotSame(T1 const& expected, T2 const& actual, bool throws, LPCSTR file, int line);
 	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Condition Tests - Methods that test a specific condition are named for the condition
	// they test and take the value tested as their first argument and, optionally a message
	// as the second.
	// Two forms are provided for the True, False, Null and NotNull conditions.
	// With or without the "Is" prefix.
	///////////////////////////////////////////////////////////////////////////
	static void IsTrue (int condition, bool throws, LPCSTR file, int line)
	{
	    Assert::IsTrue(condition, NULL, throws, file, line);
	}
	static void IsTrue (int condition, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::Test( (condition == 1), message, 
			/*[PASS]*/ _T("IsTrue: Condition was true"),
			/*[FAIL]*/ _T("IsTrue: Condition was not true"),
						throws, file, line);
	}
	static void True (int condition, bool throws, LPCSTR file, int line)
	{
	    Assert::True(condition, NULL, throws, file, line);
	}
	static void True (int condition, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::Test( (condition == 1), message, 
			/*[PASS]*/ _T("True: Condition was true"),
			/*[FAIL]*/ _T("True: Condition was not true"),
						throws, file, line);
	}

	static void IsFalse(int condition, bool throws, LPCSTR file, int line)
	{
	    Assert::IsFalse(condition, NULL, throws, file, line);
	}
	static void IsFalse(int condition, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::Test( (condition == 0), message, 
			/*[PASS]*/ _T("IsFalse: Condition was false"),
			/*[FAIL]*/ _T("IsFalse: Condition was not false"),
						throws, file, line);
	}
	static void False(int condition, bool throws, LPCSTR file, int line)
	{
	    Assert::False(condition, NULL, throws, file, line);
	}
	static void False(int condition, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::Test( (condition == 0), message, 
			/*[PASS]*/ _T("False: Condition was false"),
			/*[FAIL]*/ _T("False: Condition was not false"),
						throws, file, line);
	}

	template <class T>
	static void IsNull(T* pointer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsNull(pointer, NULL, throws, file, line);
	}
	template <class T>
	static void IsNull(T* pointer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (pointer == 0), message,
			/*[PASS]*/ _T("IsNull: Actual pointer was a NULL pointer"),
			/*[FAIL]*/ _T("IsNull: Expected a NULL pointer"),
						throws, file, line );
	}
	template <class T>
	static void Null(T* pointer, bool throws, LPCSTR file, int line)
	{
	    Assert::Null(pointer, NULL, throws, file, line);
	}
	template <class T>
	static void Null(T* pointer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (pointer == 0), message,
			/*[PASS]*/ _T("Null: Actual pointer was a NULL pointer"),
			/*[FAIL]*/ _T("Null: Expected a NULL pointer"),
						throws, file, line );
	}

	template <class T>
	static void IsNotNull(T* pointer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsNotNull(pointer, NULL, throws, file, line);
	}
 	template <class T>
	static void IsNotNull(T* pointer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (pointer != 0), message,
			/*[PASS]*/ _T("IsNotNull: Actual pointer was a non-NULL pointer"),
			/*[FAIL]*/ _T("IsNotNull: Expected a non-NULL pointer"),
						throws, file, line);
	}
	template <class T>
	static void NotNull(T* pointer, bool throws, LPCSTR file, int line)
	{
	    Assert::NotNull(pointer, NULL, throws, file, line);
	}
	template <class T>
	static void NotNull(T* pointer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (pointer != 0), message,
			/*[PASS]*/ _T("NotNull: Actual pointer was a non-NULL pointer"),
			/*[FAIL]*/ _T("NotNull: Expected a non-NULL pointer"),
						throws, file, line);
	}

	// IsEmpty for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void IsEmpty(LPCTSTR buffer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsEmpty(const_cast<LPTSTR>(buffer), NULL, throws, file, line);
	}
	static void IsEmpty(LPCTSTR buffer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::IsEmpty(const_cast<LPTSTR>(buffer), message, throws, file, line);
	}
	static void IsEmpty(LPTSTR buffer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsEmpty(buffer, NULL, throws, file, line);
	}
	static void IsEmpty(LPTSTR buffer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// test _tcsclen only if the buffer points to a string
		if(buffer)
		{
			Assert::Test( (_tcsclen(buffer) == 0), message, 
				/*[PASS]*/ _T("IsEmpty: Actual string was empty"),
				/*[FAIL]*/ _T("IsEmpty: Expected an empty string"),
							throws, file, line);
		}
		else
		{	// otherwise pass
			Assert::Pass( message, _T("IsEmpty: Actual string was empty"), throws, file, line);
		}
	}

	// IsNotEmpty for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void IsNotEmpty(LPCTSTR buffer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsNotEmpty(const_cast<LPTSTR>(buffer), NULL, throws, file, line);
	}
	static void IsNotEmpty(LPCTSTR buffer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
	    Assert::IsNotEmpty(const_cast<LPTSTR>(buffer), message, throws, file, line);
	}
	static void IsNotEmpty(LPTSTR buffer, bool throws, LPCSTR file, int line)
	{
	    Assert::IsNotEmpty(buffer, NULL, throws, file, line);
	}
	static void IsNotEmpty(LPTSTR buffer, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// test _tcsclen only if the buffer points to a string
		if(buffer)
		{
			Assert::Test( (_tcsclen(buffer) > 0), message, 
				/*[PASS]*/ _T("IsNotEmpty: Actual string was not empty"),
				/*[FAIL]*/ _T("IsNotEmpty: Expected a non-empty string"),
							throws, file, line);
		}
		else
		{	// otherwise fail
			Assert::Fail( message, _T("IsEmpty: Expected an empty string"), throws, file, line);
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// Comparisons (NUnit 2.2.4) - The following methods test whether one object is:
	// Greater(>) / GreaterOrEqual(>=) / Less(<) / LessOrEqual(<=) than another
	template <class T1, class T2>
	static void Greater(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::Greater(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void Greater(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected > actual), message,
			/*[PASS]*/ _T("Greater: Condition was Greater"),
			/*[FAIL]*/ _T("Greater: Condition was not Greater"),
						expected, actual, throws, file, line);
	}

	template <class T1, class T2>
	static void GreaterOrEqual(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::GreaterOrEqual(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void GreaterOrEqual(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected >= actual), message,
			/*[PASS]*/ _T("GreaterOrEqual: Condition was Greater or equal"),
			/*[FAIL]*/ _T("GreaterOrEqual: Condition was not Greater or equal"),
						expected, actual, throws, file, line);
	}

	template <class T1, class T2>
	static void Less(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::Less(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void Less(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected < actual), message,
			/*[PASS]*/ _T("Less: Condition was Less"),
			/*[FAIL]*/ _T("Less: Condition was not Less"),
						expected, actual, throws, file, line);
	}

	template <class T1, class T2>
	static void LessOrEqual(const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::LessOrEqual(expected, actual, NULL, throws, file, line);
	}

	template <class T1, class T2>
	static void LessOrEqual(const T1& expected, const T2& actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Test( (expected <= actual), message,
			/*[PASS]*/ _T("Less: Condition was Less or equal"),
			/*[FAIL]*/ _T("Less: Condition was not Less or equal"),
						expected, actual, throws, file, line);
	}

 	///////////////////////////////////////////////////////////////////////////
	// Type Asserts (NUnit 2.2.3 / 2.5) - These methods allow us to make assertions 
	// about the type of an object.
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because the compilation should support RTTI 
	//							#include <typeinfo.h> // compile with: /GR /EHsc
	///////////////////////////////////////////////////////////////////////////
	//static void IsInstanceOfType(const type_info& expected, const T& actual, bool throws, LPCSTR file, int line);
	//
	//static void IsNotInstanceOfType(const type_info& expected, const T& actual, bool throws, LPCSTR file, int line);
	//
	//static void IsAssignableFrom(const type_info& expected, const T& actual, bool throws, LPCSTR file, int line);
	//
	//static void IsNotAssignableFrom(const type_info& expected, const T& actual, bool throws, LPCSTR file, int line);
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Exception Asserts (NUnit 2.5) - When used with a Type argument, Assert::Throws requires
	// that exact type to be thrown. If you want to test for any derived Type, use one of the
	// forms that allows specifying a constraint.
	// Alternatively, you may use Assert::Catch, which differs from Assert::Throws in allowing
	// derived types
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////
	//static Exception Throws( Type expectedExceptionType, TestDelegate code, string message, params object[] parms);
	//
	//static Exception Throws( IResolveConstraint constraint, TestDelegate code, string message, params object[] parms);
	//
	//static T Throws<T>( TestDelegate code, string message, params object[] parms);
	//
	//static void DoesNotThrow( TestDelegate code, string message, params object[] parms);
	//
	//static Exception Catch( TestDelegate code, string message, params object[] parms);
	//
	//static Exception Catch( Type expectedExceptionType, TestDelegate code,  string message, params object[] parms);
	//
	//static T Catch<T>( TestDelegate code, string message,  params object[] parms);
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Utility Methods - Two utility methods, Pass(), Fail(),
	// are provided in order to allow more direct control of the test process
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////
	//static void Ignore(LPCTSTR message, bool throws, LPCSTR file, int line)
	//
	//static void Inconclusive(LPCTSTR message, bool throws, LPCSTR file, int line)
	///////////////////////////////////////////////////////////////////////////
	static void Pass(LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Pass(message, NULL, throws, file, line);
	}

 	static void Fail(LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Fail(message, NULL, throws, file, line);
	}

	///////////////////////////////////////////////////////////////////////////
	// StringAssert (NUnit 2.2.3) - The StringAssert class provides a number of methods that are
	// useful when examining string values
	///////////////////////////////////////////////////////////////////////////

	// Contains for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void Contains(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::Contains(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void Contains(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::Contains(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void Contains(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::Contains(expected, actual, NULL, throws, file, line);
	}
	static void Contains(LPTSTR expected, LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// check if the 'actual' buffer (=string) contains the 'expected' buffer (=substring)
		Assert::IsNotEmpty(expected, _T("Contains: expected substring is empty"), throws, file, line);
		Assert::IsNotEmpty(actual,   _T("Contains: actual string is empty"),      throws, file, line);
		Assert::LessOrEqual( _tcsclen(expected), _tcsclen(actual),
									_T("Contains: expected substring is greater than the actual string"), throws, file, line);

		Assert::Test( ( _tcsstr(actual, expected) != NULL ), message,
			/*[PASS]*/ _T("Contains: Expected substring was contains in the actual string"),
			/*[FAIL]*/ _T("Contains: Expected substring was not contains in the actual string"),
						expected, actual, throws, file, line);
	}

	// StartsWith for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void StartsWith(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::StartsWith(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void StartsWith(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::StartsWith(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void StartsWith(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::StartsWith(expected, actual, NULL, throws, file, line);
	}
	static void StartsWith(LPTSTR expected,LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// check if the 'actual' buffer (=string) starts with the 'expected' buffer (=substring)
		Assert::IsNotEmpty(expected, _T("StartsWith: expected substring is empty"), throws, file, line);
		Assert::IsNotEmpty(actual,   _T("StartsWith: actual string is empty"),      throws, file, line);
		Assert::LessOrEqual( _tcsclen(expected), _tcsclen(actual),
									_T("StartsWith: expected substring is greater than the actual string"), throws, file, line);
		LPCTSTR start = _tcsstr(actual, expected);
		Assert::Test( ( _tcsstr(actual, expected) == actual), message,
			/*[PASS]*/ _T("StartsWith: Expected substring was started at the actual string"),
			/*[FAIL]*/ _T("StartsWith: Expected substring was not started at the actual string"),
						expected, actual, throws, file, line);
	}

	///////////////////////////////////////////////////////////////////////////
	//[TODO] static void EndsWith(LPCTSTR expected,LPCTSTR actual, bool throws, LPCSTR file, int line);
 	///////////////////////////////////////////////////////////////////////////

	// AreEqualIgnoringCase for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void AreEqualIgnoringCase(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqualIgnoringCase(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void AreEqualIgnoringCase(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqualIgnoringCase(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void AreEqualIgnoringCase(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::AreEqualIgnoringCase(expected, actual, NULL, throws, file, line);
	}
	static void AreEqualIgnoringCase(LPTSTR expected,LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// check if the 'actual' buffer is like the 'expected' buffer
		Assert::IsNotEmpty(expected, _T("AreEqualIgnoringCase: expected substring is empty"), throws, file, line);
		Assert::IsNotEmpty(actual,   _T("AreEqualIgnoringCase: actual string is empty"),      throws, file, line);
		Assert::Test( (_tcsicmp(expected, actual) == 0), message,
			/*[PASS]*/ _T("AreEqualIgnoringCase: Expression was equal"),
			/*[FAIL]*/ _T("AreEqualIgnoringCase: Expression was not equal"),
						expected, actual, throws, file, line);
	}

	// IsMatch for null terminated strings: (LPCTSTR)x2 and (LPTSTR)x2 - with and without a message
	static void IsMatch(LPCTSTR expected, LPCTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::IsMatch(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), NULL, throws, file, line);
	}
	static void IsMatch(LPCTSTR expected, LPCTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{
		Assert::IsMatch(const_cast<LPTSTR>(expected), const_cast<LPTSTR>(actual), message, throws, file, line);
	}
	static void IsMatch(LPTSTR expected, LPTSTR actual, bool throws, LPCSTR file, int line)
	{
		Assert::IsMatch(expected, actual, NULL, throws, file, line);
	}
	static void IsMatch(LPTSTR expected, LPTSTR actual, LPCTSTR message, bool throws, LPCSTR file, int line)
	{	// check if the 'actual' buffer is like the 'expected' buffer
		Assert::IsNotEmpty(expected, _T("IsMatch: expected substring is empty"), throws, file, line);
		Assert::IsNotEmpty(actual,   _T("IsMatch: actual string is empty"),      throws, file, line);
		Assert::Test( (_tcscmp(expected, actual) == 0), message,
			/*[PASS]*/ _T("IsMatch: Expression was match"),
			/*[FAIL]*/ _T("IsMatch: Expression was not match"),
						expected, actual, throws, file, line);
	}

	///////////////////////////////////////////////////////////////////////////
	// CollectionAssert (NUnit 2.4 / 2.5) - The CollectionAssert class provides a number 
	// of methods that are useful when examining collections and their contents or for
	// comparing two collections
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// FileAssert (NUnit 2.4) -  The FileAssert class provides methods for comparing two files,
	// which may be provided as Streams, as FileInfos or as strings giving the path to each file
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// DirectoryAssert (NUnit 2.5) - The DirectoryAssert class provides methods for making asserts
	// about file system directories, which may be provided as DirectoryInfos or as strings giving
	// the path to each directory.
	///////////////////////////////////////////////////////////////////////////
	// [TODO] Not implemented - because its not relevant for C++
	///////////////////////////////////////////////////////////////////////////

private:
	// private Utility Methods
	template <class T1, class T2>
	static void Fail(LPCTSTR message, const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::Fail(message, NULL, expected, actual, throws, file, line);
	}

	template <class T1, class T2>
	static void Pass(LPCTSTR message, const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::Pass(message, NULL, expected, actual, throws, file, line);
	}

	static void Test(bool condition, LPCTSTR message_pass, LPCTSTR message_fail,
					 bool throws, LPCSTR file, int line)
	{
		Assert::Test(condition, NULL, message_pass, message_fail, throws, file, line);
	}

	template <class T1, class T2>
	static void Test(bool condition, LPCTSTR message_pass, LPCTSTR message_fail,
					 const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		Assert::Test(condition, NULL, message_pass, message_fail, expected, actual, throws, file, line);
	}

	static void Test(bool condition, LPCTSTR message, LPCTSTR message_pass, LPCTSTR message_fail,
					 bool throws, LPCSTR file, int line)
	{
		if(message)
		{
			(condition) ?
				Assert::Pass(message, message_pass, throws, file, line) :
				Assert::Fail(message, message_fail, throws, file, line);
		}
		else
		{
			(condition) ?
				Assert::Pass(message_pass, throws, file, line) :
				Assert::Fail(message_fail, throws, file, line);
		}
	}

	template <class T1, class T2>
	static void Test(bool condition, LPCTSTR message, LPCTSTR message_pass, LPCTSTR message_fail,
					 const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		if(message)
		{
			(condition) ?
				Assert::Pass(message, message_pass, expected, actual, throws, file, line) :
				Assert::Fail(message, message_fail, expected, actual, throws, file, line);
		}
		else
		{
			(condition) ?
				Assert::Pass(message_pass, expected, actual, throws, file, line) :
				Assert::Fail(message_fail, expected, actual, throws, file, line);
		}
	}

	static void FormatMessage(std::ostringstream& ostr, LPCTSTR message1, LPCTSTR message2, LPCSTR file, int line, bool newline)
	{
		if(newline)
		{
			ostr << message1 << std::endl;
			if(message2)
			{
				ostr << message2 << std::endl;
			}
			ostr << _T("at ") << file << _T(" (") << line << _T(")");
		}
		else
		{
			ostr << message1 << _T(" ");
			if(message2)
			{
				ostr << message2 << _T(" ");
			}
			ostr << _T("at ") << file << _T(" (") << line << _T(")");
		}
	}

	template <class T1, class T2>
	static void FormatMessage(std::ostringstream& ostr, LPCTSTR message1, LPCTSTR message2, const T1& expected, const T2& actual, LPCSTR file, int line)
	{
		ostr << message1 << std::endl;
		if(message2)
		{
			ostr << message2 << std::endl;
		}
		ostr << _T("Expected: '") << expected << _T("'") << std::endl
			 << _T("Actual:   '") << actual   << _T("'") << std::endl 
			 << _T("at ") << file << _T(" (") << line << _T(")"); // this generates warning C4267 for size_t
	}

	static void FormatMessage(std::ostringstream& ostr, LPCTSTR message1, LPCTSTR message2, const ULONGLONG& expected, const ULONGLONG& actual, LPCSTR file, int line)
	{	// convert ULONGLONG to __int64 (used in DECIMAL values)
		FormatMessage(ostr, message1, message2, static_cast<const __int64&>(expected), static_cast<const __int64&>(actual), file, line);
	}

	static void FormatMessage(std::ostringstream& ostr, LPCTSTR message1, LPCTSTR message2, const __int64& expected, const __int64& actual, LPCSTR file, int line)
	{	// convert __int64 to string
		ostr << message1 << std::endl;
		if(message2)
		{
			ostr << message2 << std::endl;
		}
		TCHAR szExpected[256];
		TCHAR szActual[256];
		_stprintf_s(szExpected, sizeof(szExpected), _T("%I64d"), expected);
		_stprintf_s(szActual, sizeof(szActual), _T("%I64d"), actual);
		ostr << _T("Expected: '") << szExpected << _T("'") << std::endl
			 << _T("Actual:   '") << szActual   << _T("'") << std::endl 
			 << _T("at ") << file << _T(" (") << line << _T(")"); // this generates warning C4267 for size_t
	}

	static void Fail(LPCTSTR message1, LPCTSTR message2, bool throws, LPCSTR file, int line)
	{
		std::ostringstream ostr;
		FormatMessage(ostr, message1, message2, file, line, true);	// new line is needed in fail method 
		if(throws)
		{
			throw std::runtime_error(ostr.str());
		}
		else
		{
			SET_CONSOLE_COLOR(0x0C);	// RED
			std::cerr << _T("[FAIL]") << ostr.str() << std::endl;
			SET_CONSOLE_COLOR(0x0F);	// WHITE
		}
	}

	static void Pass(LPCTSTR message1, LPCTSTR message2, bool throws, LPCSTR file, int line)
	{
		if(throws)
		{	// do not print pass messages in case of assertion mode
			return;
		}
		SET_CONSOLE_COLOR(0x0A);	// GREEN
		std::cout << _T("[PASS] ");
		SET_CONSOLE_COLOR(0x0F);	// WHITE

		std::ostringstream ostr;
		FormatMessage(ostr, message1, message2, file, line, false);	// new line is not needed in pass method 
		std::cout << ostr.str() << std::endl;
	}

	template <class T1, class T2>
	static void Fail(LPCTSTR message1, LPCTSTR message2, const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		std::ostringstream ostr;
		FormatMessage(ostr, message1, message2, expected, actual, file, line); 
		if(throws)
		{
			throw std::runtime_error(ostr.str());
		}
		else
		{
			SET_CONSOLE_COLOR(0x0C);	// RED
			std::cerr << ostr.str() << std::endl;
			SET_CONSOLE_COLOR(0x0F);	// WHITE
		}
	}

	template <class T1, class T2>
	static void Pass(LPCTSTR message1, LPCTSTR message2, const T1& expected, const T2& actual, bool throws, LPCSTR file, int line)
	{
		if(throws)
		{	// do not print pass messages in case of assertion mode
			return;
		}
		SET_CONSOLE_COLOR(0x0A);	// GREEN
		std::cout << _T("[PASS] ");
		SET_CONSOLE_COLOR(0x0F);	// WHITE

		std::ostringstream ostr;
		FormatMessage(ostr, message1, message2, file, line, false); 	// new line is not needed in pass method
		std::cout << ostr.str() << std::endl;
	}

};	// Assert

};	// UnitTest

///////////////////////////////////////////////////////////////////////////////
#undef SET_CONSOLE_COLOR
