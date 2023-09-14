#include "storm/simulator/PrismProgramSimulator.h"
#include "storm/adapters/JsonAdapter.h"


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
    storm::expressions::ExpressionManager& DiscreteTimePrismProgramSimulator<ValueType>::helperGetManager() const {
        return program.getManager();
    }

} // namespace storm::simulator

