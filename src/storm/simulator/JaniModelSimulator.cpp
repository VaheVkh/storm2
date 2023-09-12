#include "JaniModelSimulator.h"
#include "storm/adapters/JsonAdapter.h"

using namespace storm::generator;

namespace storm::simulator {

template<typename ValueType>
DiscreteTimeJaniModelSimulator<ValueType>::DiscreteTimeJaniModelSimulator(storm::jani::Model const& model,
                                                                                storm::generator::NextStateGeneratorOptions const& options)
    : GeneralSimulator<ValueType>(stateGenerator->getNumberOfRewardModels(), storm::utility::zero<ValueType>()),
      model(model),
      stateGenerator(std::make_shared<storm::generator::PrismNextStateGenerator<ValueType, uint32_t>>(model, options))
{ }

template<typename ValueType>
storm::expressions::ExpressionManager& DiscreteTimeJaniModelSimulator<ValueType>::helperGetManager() const {
    return model.getManager();
}

} // namespace storm::simulator


