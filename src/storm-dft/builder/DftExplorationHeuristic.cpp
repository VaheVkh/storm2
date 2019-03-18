#include "DftExplorationHeuristic.h"

#include "storm/adapters/RationalFunctionAdapter.h"
#include "storm/exceptions/NotImplementedException.h"

namespace storm {
    namespace builder {

        template<>
        double DFTExplorationHeuristicProbability<double>::getPriority() const {
            return probability;
        }

        template<typename ValueType>
        double DFTExplorationHeuristicProbability<ValueType>::getPriority() const {
            STORM_LOG_THROW(false, storm::exceptions::NotImplementedException, "Heuristic 'probability' does not work for this data type.");
        }

        template<>
        double DFTExplorationHeuristicBoundDifference<double>::getPriority() const {
            double difference = (storm::utility::one<double>() / upperBound) - (storm::utility::one<double>() / lowerBound);
            return probability * difference;
        }

        template<typename ValueType>
        double DFTExplorationHeuristicBoundDifference<ValueType>::getPriority() const {
            STORM_LOG_THROW(false, storm::exceptions::NotImplementedException, "Heuristic 'bound difference' does not work for this data type.");
        }

        // Instantiate templates.
        template class DFTExplorationHeuristic<double>;
        template class DFTExplorationHeuristicNone<double>;
        template class DFTExplorationHeuristicDepth<double>;
        template class DFTExplorationHeuristicProbability<double>;
        template class DFTExplorationHeuristicBoundDifference<double>;

#ifdef STORM_HAVE_CARL
        template class DFTExplorationHeuristic<storm::RationalFunction>;
        template class DFTExplorationHeuristicNone<storm::RationalFunction>;
        template class DFTExplorationHeuristicDepth<storm::RationalFunction>;
        template class DFTExplorationHeuristicProbability<storm::RationalFunction>;
        template class DFTExplorationHeuristicBoundDifference<storm::RationalFunction>;
#endif
    }
}
