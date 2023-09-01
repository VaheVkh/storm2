#pragma once

#include "storm/simulator/GeneralSimulator.h"
#include "storm/generator/PrismNextStateGenerator.h"
#include "storm/storage/expressions/SimpleValuation.h"
#include "storm/storage/prism/Program.h"
#include "storm/utility/random.h"

namespace storm::simulator {

/**
 * This class provides a simulator interface on the prism program,
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
class DiscreteTimePrismProgramSimulator : public GeneralSimulator<ValueType> {
   public:
    /**
     * Initialize the simulator for a given prism program.
     *
     * @param program The prism program. Should have a unique initial state.
     * @param options The generator options that are used to generate successor states.
     */
    DiscreteTimePrismProgramSimulator(storm::prism::Program const& program, storm::generator::NextStateGeneratorOptions const& options);

    std::vector<prism::Label> helperGetLabels() const override;

    storm::expressions::ExpressionManager& helperGetManager() const override;

   protected:
    /// The program that we are simulating.
    storm::prism::Program const& program;
   /// Generator for the next states
    std::shared_ptr<storm::generator::PrismNextStateGenerator<ValueType, uint32_t>> stateGenerator;

};
} // namespace storm::simulator

