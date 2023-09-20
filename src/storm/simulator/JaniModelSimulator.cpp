#include "JaniModelSimulator.h"
#include "storm/adapters/JsonAdapter.h"

using namespace storm::generator;

namespace storm::simulator {

template<typename ValueType>
DiscreteTimeJaniModelSimulator<ValueType>::DiscreteTimeJaniModelSimulator(storm::jani::Model const& model,
                                                                                storm::generator::NextStateGeneratorOptions const& options)
    : GeneralSimulator<ValueType>( std::make_shared<storm::generator::JaniNextStateGenerator<ValueType, uint32_t>>(model, options)),
      model(model)
{
}

template<typename ValueType>
storm::expressions::ExpressionManager& DiscreteTimeJaniModelSimulator<ValueType>::helperGetManager() const {
    return model.getManager();
}

template class DiscreteTimeJaniModelSimulator<double>;
template class DiscreteTimeJaniModelSimulator<storm::RationalNumber>;

} // namespace storm::simulator


