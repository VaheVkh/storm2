#include "storm/simulator/PrismProgramSimulator.h"
#include "storm/simulator/JaniModelSimulator.h"
#include "storm-parsers/parser/JaniParser.h"
#include "storm-parsers/parser/PrismParser.h"
#include "storm-parsers/api/properties.h"
#include "storm/storage/jani/Property.h"
#include "storm/environment/Environment.h"
#include "test/storm_gtest.h"

TEST(PrismProgramSimulatorTest, KnuthYaoDieTest) {
    storm::Environment env;
    storm::prism::Program program = storm::parser::PrismParser::parse(STORM_TEST_RESOURCES_DIR "/mdp/die_c1.nm");
    std::cout << program <<std::endl;
    storm::builder::BuilderOptions options;
    options.setBuildAllRewardModels();
    options.setBuildAllLabels();

    storm::simulator::DiscreteTimePrismProgramSimulator<double> sim(program, options);
    sim.setSeed(42);
    EXPECT_EQ("coin_flips", sim.getRewardNames()[0]);
    auto rew = sim.getLastRewards();
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    auto labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    EXPECT_EQ(2ul, sim.getChoices().size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    EXPECT_EQ(1ul, sim.getChoices().size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(1.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(1.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(2ul, labels.size());
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "done") == 1);
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "five") == 1);
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "done") == 1);
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "five") == 1);
}

TEST(JaniModelSimulatorTest, KnuthYaoDieTest) {
    storm::Environment env;
    storm::prism::Program program = storm::parser::PrismParser::parse(STORM_TEST_RESOURCES_DIR "/mdp/die_c1.nm");
    storm::builder::BuilderOptions options;
    auto model = program.toJani(true);
    //    std::string propertyString= "\"done\"; \"five\"";
//    auto properties = storm::api::parsePropertiesForPrismProgram(propertyString, program);
//    auto modelProperties = program.toJani(properties);
//    std::cout << "modelProperties.first "<< modelProperties.first << std::endl;
//    std::vector<std::shared_ptr<storm::logic::Formula const>> formulas({modelProperties.second[0].getRawFormula(), modelProperties.second[1].getRawFormula()});
//    storm::builder::BuilderOptions options(formulas, modelProperties.first);


    options.setBuildAllRewardModels();
    options.setBuildAllLabels();


    storm::simulator::DiscreteTimeJaniModelSimulator<double> sim(model, options);
    sim.setSeed(42);
    EXPECT_EQ("coin_flips", sim.getRewardNames()[0]);
    auto rew = sim.getLastRewards();
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    auto labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    EXPECT_EQ(2ul, sim.getChoices().size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    EXPECT_EQ(1ul, sim.getChoices().size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(1.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(0ul, labels.size());
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(1.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_EQ(2ul, labels.size());
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "done") == 1);
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "five") == 1);
    sim.step(0);
    rew = sim.getLastRewards();
    EXPECT_EQ(1ul, rew.size());
    EXPECT_EQ(0.0, rew[0]);
    labels = sim.getCurrentStateLabelling();
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "done") == 1);
    EXPECT_TRUE(std::count(labels.begin(), labels.end(), "five") == 1);
}
