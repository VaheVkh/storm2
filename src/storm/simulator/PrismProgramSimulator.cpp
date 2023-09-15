#include "storm/simulator/PrismProgramSimulator.h"
#include "storm/adapters/JsonAdapter.h"


using namespace storm::generator;

namespace storm::simulator {

template<typename ValueType>
DiscreteTimePrismProgramSimulator<ValueType>::DiscreteTimePrismProgramSimulator(storm::prism::Program const& program,
                                                                                storm::generator::NextStateGeneratorOptions const& options)
    : program(program),
      stateGenerator(std::make_shared<storm::generator::PrismNextStateGenerator<ValueType, uint32_t>>(program, options))
{
    this->zeroRewards.assign(stateGenerator->getNumberOfRewardModels(), storm::utility::zero<ValueType>());
    this->lastActionRewards = this->zeroRewards;
}


template<typename ValueType>
storm::expressions::ExpressionManager& DiscreteTimePrismProgramSimulator<ValueType>::helperGetManager() const {
    return program.getManager();
}

template class DiscreteTimePrismProgramSimulator<double>;
template class DiscreteTimePrismProgramSimulator<storm::RationalNumber>;

} // namespace storm::simulator

