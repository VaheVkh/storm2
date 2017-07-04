#pragma once

#include "storm-pars/utility/parametric.h"
#include "storm/logic/Formulas.h"
#include "storm/modelchecker/CheckTask.h"
#include "storm/modelchecker/results/CheckResult.h"
#include "storm/modelchecker/hints/ModelCheckerHint.h"

namespace storm {
    namespace modelchecker {
        
        /*!
         * Class to efficiently check a formula on a parametric model with different parameter instantiations
         */
        template <typename SparseModelType, typename ConstantType>
        class SparseInstantiationModelChecker {
        public:
            SparseInstantiationModelChecker(SparseModelType const& parametricModel);
            virtual ~SparseInstantiationModelChecker() = default;
            
            void specifyFormula(CheckTask<storm::logic::Formula, typename SparseModelType::ValueType> const& checkTask);
            
            virtual std::unique_ptr<CheckResult> check(storm::utility::parametric::Valuation<typename SparseModelType::ValueType> const& valuation) = 0;
            
            // If set, it is assumed that all considered model instantiations have the same underlying graph structure.
            // This bypasses the graph analysis for the different instantiations.
            void setInstantiationsAreGraphPreserving(bool value);
            bool getInstantiationsAreGraphPreserving() const;
            
        protected:
            
            SparseModelType const& parametricModel;
            std::unique_ptr<CheckTask<storm::logic::Formula, ConstantType>> currentCheckTask;
            
        private:
            // store the current formula. Note that currentCheckTask only stores a reference to the formula.
            std::shared_ptr<storm::logic::Formula const> currentFormula;

            bool instantiationsAreGraphPreserving;
        };
    }
}
