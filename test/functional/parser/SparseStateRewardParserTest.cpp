/*
 * SparseStateRewardParserTest.cpp
 *
 *  Created on: 26.02.2014
 *      Author: Manuel Sascha Weiand
 */

#include "gtest/gtest.h"
#include "storm-config.h"

#include <cmath>

#include "src/parser/SparseStateRewardParser.h"
#include "src/exceptions/FileIoException.h"
#include "src/exceptions/WrongFormatException.h"
#include "src/exceptions/OutOfRangeException.h"

TEST(SparseStateRewardParserTest, NonExistingFile) {

	// No matter what happens, please do NOT create a file with the name "nonExistingFile.not"!
	ASSERT_THROW(storm::parser::SparseStateRewardParser::parseSparseStateReward(42, STORM_CPP_TESTS_BASE_PATH "/nonExistingFile.not"), storm::exceptions::FileIoException);
}

double round(double val, int precision)
{
    std::stringstream s;
    s << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
    s >> val;
    return val;
}

TEST(SparseStateRewardParserTest, BasicParsing) {

	// Get the parsing result.
	std::vector<double> result = storm::parser::SparseStateRewardParser::parseSparseStateReward(100, STORM_CPP_TESTS_BASE_PATH "/functional/parser/rew_files/state_reward_parser_basic.state.rew");

	// Now test if the correct value were parsed.
	for(int i = 0; i < 100; i++) {
		ASSERT_EQ(std::round(2*i + 15/13*i*i - 1.5/(i+0.1) + 15.7), std::round(result[i]));
	}
}

TEST(SparseStateRewardParserTest, Whitespaces) {

	// Get the parsing result.
	std::vector<double> result = storm::parser::SparseStateRewardParser::parseSparseStateReward(100, STORM_CPP_TESTS_BASE_PATH "/functional/parser/rew_files/state_reward_parser_whitespaces.state.rew");

	// Now test if the correct value were parsed.
	for(int i = 0; i < 100; i++) {
		ASSERT_EQ(std::round(2*i + 15/13*i*i - 1.5/(i+0.1) + 15.7), std::round(result[i]));
	}
}

TEST(SparseStateRewardParserTest, DoubledLines) {
	// There are multiple lines attributing a reward to the same state.
	ASSERT_THROW(storm::parser::SparseStateRewardParser::parseSparseStateReward(11, STORM_CPP_TESTS_BASE_PATH "/functional/parser/rew_files/state_reward_parser_doubledLines.state.rew"), storm::exceptions::WrongFormatException);

	// There is a line for a state that has been skipped.
	ASSERT_THROW(storm::parser::SparseStateRewardParser::parseSparseStateReward(11, STORM_CPP_TESTS_BASE_PATH "/functional/parser/rew_files/state_reward_parser_doubledLinesSkipped.state.rew"), storm::exceptions::WrongFormatException);
}

TEST(SparseStateRewardParserTest, RewardForNonExistentState) {
	// The index of one of the state that are to be given rewards is higher than the number of states in the model.
	ASSERT_THROW(storm::parser::SparseStateRewardParser::parseSparseStateReward(99, STORM_CPP_TESTS_BASE_PATH "/functional/parser/rew_files/state_reward_parser_basic.state.rew"), storm::exceptions::OutOfRangeException);
}
