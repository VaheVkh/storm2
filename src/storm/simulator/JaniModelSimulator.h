#ifndef STORM_JANIMODELSIMULATOR_H
#define STORM_JANIMODELSIMULATOR_H

#include "storm/simulator/GeneralSimulator.h"
#include "storm/generator/JaniNextStateGenerator.h"
#include "storm/storage/expressions/SimpleValuation.h"
#include "storm/storage/jani/Model.h"
#include "storm/utility/random.h"

namespace storm::simulator {

/**
 * This class provides a simulator interface on the jani model,
 * and uses the next state generator. While the next state generator has been tuned,
 * it is not targeted for simulation purposes. In particular, we (as of now)
 * always extend all actions as soon as we arrive in a state.
 * This may cause significant overhead, especially with a larger branching factor.
 *
 * On the other hand, this simulator is convenient for stepping through the model
 * as it potentially allows considering the next states.
 * Thus, while a performant alternative would be great, this simulator has its own merits.
 *
 * @tparam ValueType
 */
template<typename ValueType>
class DiscreteTimeJaniModelSimulator : public GeneralSimulator<ValueType> {
   public:
    /**
     * Initialize the simulator for a given jani model.
     *
     * @param model The jani model. Should have a unique initial state.
     * @param options The generator options that are used to generate successor states.
     */
    DiscreteTimeJaniModelSimulator(storm::jani::Model const& model, storm::generator::NextStateGeneratorOptions const& options);

    storm::expressions::ExpressionManager& helperGetManager() const override;

   protected:
    /// The model that we are simulating.
    storm::jani::Model const& model;
    /// Generator for the next states
    std::shared_ptr<storm::generator::JaniNextStateGenerator<ValueType, uint32_t>> stateGenerator;

};
} // namespace storm::simulator

#endif  // STORM_JANIMODELSIMULATOR_H
