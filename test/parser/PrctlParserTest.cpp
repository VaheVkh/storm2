/*
 * PrctlParserTest.cpp
 *
 *  Created on: 01.02.2013
 *      Author: Thomas Heinemann
 */


#include "gtest/gtest.h"
#include "storm-config.h"
#include "src/parser/PrctlParser.h"

TEST(PrctlParserTest, parseApOnlyTest) {
	std::string ap = "ap";
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser(ap);
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);


	ASSERT_EQ(ap, prctlParser->getFormula()->toString());

	delete prctlParser->getFormula();
	delete prctlParser;

}

TEST(PrctlParserTest, parsePropositionalFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("!(a & b) | a & ! c")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);


	ASSERT_EQ(prctlParser->getFormula()->toString(), "(!(a & b) | (a & !c))");

	delete prctlParser->getFormula();
	delete prctlParser;

}

TEST(PrctlParserTest, parseProbabilisticFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("P > 0.5 [ F a ]")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);

	storm::formula::ProbabilisticBoundOperator<double>* op = static_cast<storm::formula::ProbabilisticBoundOperator<double>*>(prctlParser->getFormula());

	ASSERT_EQ(storm::formula::PathBoundOperator<double>::GREATER, op->getComparisonOperator());
	ASSERT_EQ(0.5, op->getBound());

	ASSERT_EQ(prctlParser->getFormula()->toString(), "P > 0.500000 [F a]");

	delete prctlParser->getFormula();
	delete prctlParser;

}

TEST(PrctlParserTest, parseRewardFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("R >= 15 [ a U !b ]")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);

	storm::formula::RewardBoundOperator<double>* op = static_cast<storm::formula::RewardBoundOperator<double>*>(prctlParser->getFormula());

	ASSERT_EQ(storm::formula::PathBoundOperator<double>::GREATER_EQUAL, op->getComparisonOperator());
	ASSERT_EQ(15.0, op->getBound());

	ASSERT_EQ(prctlParser->getFormula()->toString(), "R >= 15.000000 [a U !b]");

	delete prctlParser->getFormula();
	delete prctlParser;
}

TEST(PrctlParserTest, parseRewardNoBoundFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("R = ? [ a U <= 4 b & (!c) ]")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);


	ASSERT_EQ(prctlParser->getFormula()->toString(), "R = ? [a U<=4 (b & !c)]");

	delete prctlParser->getFormula();
	delete prctlParser;

}

TEST(PrctlParserTest, parseProbabilisticNoBoundFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("P = ? [ F <= 42 !a ]")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);


	ASSERT_EQ(prctlParser->getFormula()->toString(), "P = ? [F<=42 !a]");

	delete prctlParser->getFormula();
	delete prctlParser;

}

TEST(PrctlParserTest, parseComplexFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_NO_THROW(
			prctlParser = new storm::parser::PrctlParser("P<=0.5 [ F a ] & (R > 15 [ G P>0.9 [F<=7 a & b] ] | !P < 0.4 [ G !b ])")
	);

	ASSERT_NE(prctlParser->getFormula(), nullptr);


	ASSERT_EQ(prctlParser->getFormula()->toString(), "(P <= 0.500000 [F a] & (R > 15.000000 [G P > 0.900000 [F<=7 (a & b)]] | !P < 0.400000 [G !b]))");
	delete prctlParser->getFormula();
	delete prctlParser;

}


TEST(PrctlParserTest, wrongProbabilisticFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_THROW(
			prctlParser = new storm::parser::PrctlParser("P > 0.5 [ a ]"),
			storm::exceptions::WrongFormatException
	);

	delete prctlParser;
}

TEST(PrctlParserTest, wrongFormulaTest) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_THROW(
			prctlParser = new storm::parser::PrctlParser("(a | b) & +"),
			storm::exceptions::WrongFormatException
	);
	delete prctlParser;
}

TEST(PrctlParserTest, wrongFormulaTest2) {
	storm::parser::PrctlParser* prctlParser = nullptr;
	ASSERT_THROW(
			prctlParser = new storm::parser::PrctlParser("P>0 [ F & a ]"),
			storm::exceptions::WrongFormatException
	);
	delete prctlParser;
}
