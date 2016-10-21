#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/filesystem.hpp>

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavTupleList.hpp"
#include "trihlavLib/trihlavRec2StrVisitor.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;

namespace attrs = boost::log::attributes;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace src = boost::log::sources;

using TestTupLst=TupleList<int, std::string, std::string, std::string, int, int>;
/**
 * Test the yubico-c library text to string calls.
 */

void fillTupLst(TestTupLst& myTupLst) {
	for (size_t myV = 0; myV < 77; ++myV) {
		myTupLst.addRow(
				TestTupLst::Row_t(myV, lexical_cast<string>(myV + 10),
						lexical_cast<string>(myV + 100),
						lexical_cast<string>(myV + 200), myV + 300, myV + 400));
	}
}

TEST( trihlavTestTupleList, testAccess ) {
	BOOST_LOG_NAMED_SCOPE("testAccess");
	TestTupLst myTupLst;
	fillTupLst(myTupLst);
	for (size_t myV = 0; myV < 77; ++myV) {
		EXPECT_EQ(myV,get<int>(myTupLst.get(myV,0)));

		EXPECT_EQ(lexical_cast<string>(myV+10) ,get<string>(myTupLst.get(myV,1)));
		EXPECT_EQ(lexical_cast<string>(myV+100),get<string>(myTupLst.get(myV,2)));
		EXPECT_EQ(lexical_cast<string>(myV+200),get<string>(myTupLst.get(myV,3)));

		EXPECT_EQ(300+myV,get<int>(myTupLst.get(myV,4)));
		EXPECT_EQ(400+myV,get<int>(myTupLst.get(myV,5)));
	}
}


TEST( trihlavTestTupleList, testVisitor ) {
	BOOST_LOG_NAMED_SCOPE("testVisitor");
	TestTupLst myTupLst;
	fillTupLst(myTupLst);
	for (size_t myV = 0; myV < 77; ++myV) {
		EXPECT_EQ(lexical_cast<string>(myV),boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,0)));

		EXPECT_EQ(lexical_cast<string>(myV+10) ,boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,1)));
		EXPECT_EQ(lexical_cast<string>(myV+100),boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,2)));
		EXPECT_EQ(lexical_cast<string>(myV+200),boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,3)));

		EXPECT_EQ(lexical_cast<string>(300+myV),boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,4)));
		EXPECT_EQ(lexical_cast<string>(400+myV),boost::apply_visitor(Rec2StrVisitor(),
				myTupLst.get(myV,5)));
	}
}

int main(int argc, char **argv) {
	trihlav::initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

