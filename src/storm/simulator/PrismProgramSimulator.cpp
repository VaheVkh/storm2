#include "storm/simulator/PrismProgramSimulator.h"
#include "storm/adapters/JsonAdapter.h"
#include "storm/exceptions/NotSupportedException.h"
#include "storm/storage/expressions/ExpressionEvaluator.h"

using namespace storm::generator;

namespace storm::simulator {

template<typename ValueType>
DiscreteTimePrismProgramSimulator<ValueType>::DiscreteTimePrismProgramSimulator(storm::prism::Program const& program,
                                                                                storm::generator::NextStateGeneratorOptions const& options)
    : GeneralSimulator<ValueType>(stateGenerator->getNumberOfRewardModels(), storm::utility::zero<ValueType>()),
      program(program),
      stateGenerator(std::make_shared<storm::generator::PrismNextStateGenerator<ValueType, uint32_t>>(program, options))
    {

    }

    template<typename ValueType>
    std::vector<prism::Label> DiscreteTimePrismProgramSimulator<ValueType>::helperGetLabels() const {
        return program.getLabels();
    }

    template<typename ValueType>
    storm::expressions::ExpressionManager& DiscreteTimePrismProgramSimulator<ValueType>::helperGetManager() const {
        return program.getManager();
    }




//    : program(program),
//      stateGenerator(std::make_shared<storm::generator::PrismNextStateGenerator<ValueType, uint32_t>>(program, options)),
//      zeroRewards(stateGenerator->getNumberOfRewardModels(), storm::utility::zero<ValueType>()),
//      lastActionRewards(zeroRewards) {
//    // Current state needs to be overwritten to actual initial state.
//    // But first, let us create a state generator.
//
//    clearStateCaches();
//    resetToInitial();
//}

//template<typename ValueType>
//bool DiscreteTimePrismProgramSimulator<ValueType>::step(uint64_t actionNumber) {
//    uint32_t nextState = DiscreteTimePrismProgramSimulator<ValueType>::behavior.getChoices()[actionNumber].sampleFromDistribution(DiscreteTimePrismProgramSimulator<ValueType>::generator.random());
//    GeneralSimulator<ValueType>:: lastActionRewards = DiscreteTimePrismProgramSimulator<ValueType>::behavior.getChoices()[actionNumber].getRewards();
//    STORM_LOG_ASSERT(GeneralSimulator<ValueType>:: lastActionRewards.size() == stateGenerator->getNumberOfRewardModels(), "Reward vector should have as many rewards as model.");
//    GeneralSimulator<ValueType>::currentState = GeneralSimulator<ValueType>::idToState[nextState];
//    // TODO we do not need to do this in every step!
//    clearStateCaches();
//    explore();
//    return true;
//}
//
//template<typename ValueType>
//bool DiscreteTimePrismProgramSimulator<ValueType>::explore() {
//    // Load the current state into the next state generator.
//    stateGenerator->load(GeneralSimulator<ValueType>::currentState);
//    // TODO: This low-level code currently expands all actions, while this is not necessary.
//    // However, using the next state generator ensures compatibliity with the model generator.
//    DiscreteTimePrismProgramSimulator<ValueType>::behavior = stateGenerator->expand(GeneralSimulator<ValueType>::stateToIdCallback);
//    STORM_LOG_ASSERT(DiscreteTimePrismProgramSimulator<ValueType>::behavior.getStateRewards().size() == GeneralSimulator<ValueType>::lastActionRewards.size(), "Reward vectors should have same length.");
//    for (uint64_t i = 0; i < DiscreteTimePrismProgramSimulator<ValueType>::behavior.getStateRewards().size(); i++) {
//        GeneralSimulator<ValueType>::lastActionRewards[i] += DiscreteTimePrismProgramSimulator<ValueType>::behavior.getStateRewards()[i];
//    }
//    return true;
//}
//
//template<typename ValueType>
//std::vector<std::string> DiscreteTimePrismProgramSimulator<ValueType>::getCurrentStateLabelling() const {
//    std::vector<std::string> labels;
//    for (auto const& label : program.getLabels()) {
//        if (stateGenerator->evaluateBooleanExpressionInCurrentState(label.getStatePredicateExpression())) {
//            labels.push_back(label.getName());
//        }
//    }
//    return labels;
//}
//
//template<typename ValueType>
//std::string DiscreteTimePrismProgramSimulator<ValueType>::getCurrentStateString() const {
//    return stateGenerator->stateToString(GeneralSimulator<ValueType>::currentState);
//}
//
//
//template<typename ValueType>
//expressions::SimpleValuation DiscreteTimePrismProgramSimulator<ValueType>::getCurrentStateAsValuation() const {
//    return unpackStateIntoValuation(GeneralSimulator<ValueType>::currentState, stateGenerator->getVariableInformation(), program.getManager());
//}
//
//template<typename ValueType>
//storm::json<ValueType> DiscreteTimePrismProgramSimulator<ValueType>::getStateAsJson() const {
//    return stateGenerator->currentStateToJson(false);
//}
//
//template<typename ValueType>
//storm::json<ValueType> GeneralSimulator<ValueType>::getObservationAsJson() const {
//    return stateGenerator->currentStateToJson(true);
//}
//
//template<typename ValueType>
//bool DiscreteTimePrismProgramSimulator<ValueType>::resetToInitial() {
//    GeneralSimulator<ValueType>::lastActionRewards = GeneralSimulator<ValueType>::zeroRewards;
//    auto indices = stateGenerator->getInitialStates(GeneralSimulator<ValueType>::stateToIdCallback);
//    STORM_LOG_THROW(indices.size() == 1, storm::exceptions::NotSupportedException, "Program must have a unique initial state");
//    GeneralSimulator<ValueType>::currentState = GeneralSimulator<ValueType>::idToState[indices[0]];
//    return explore();
//}
//
//template<typename ValueType>
//bool DiscreteTimePrismProgramSimulator<ValueType>::resetToState(expressions::SimpleValuation const& valuation) {
//    GeneralSimulator<ValueType>::lastActionRewards = GeneralSimulator<ValueType>::zeroRewards;
//    GeneralSimulator<ValueType>::currentState = generator::packStateFromValuation(valuation, stateGenerator->getVariableInformation(), true);
//    return explore();
//}
//
//template<typename ValueType>
//std::vector<std::string> DiscreteTimePrismProgramSimulator<ValueType>::getRewardNames() const {
//    std::vector<std::string> names;
//    for (uint64_t i = 0; i < stateGenerator->getNumberOfRewardModels(); ++i) {
//        names.push_back(stateGenerator->getRewardModelInformation(i).getName());
//    }
//    return names;
//}
//
//template<typename ValueType>
//void DiscreteTimePrismProgramSimulator<ValueType>::clearStateCaches() {
//    GeneralSimulator<ValueType>::idToState.clear();
//    GeneralSimulator<ValueType>::stateToId = storm::storage::BitVectorHashMap<uint32_t>(stateGenerator->getStateSize());
//}


} // namespace storm::simulator

