#ifndef STORM_MODELCHECKER_EXPLICITPARETOCURVECHECKRESULT_H_
#define STORM_MODELCHECKER_EXPLICITPARETOCURVECHECKRESULT_H_

#include <vector>

#include "storm/modelchecker/results/ParetoCurveCheckResult.h"
#include "storm/storage/sparse/StateType.h"

namespace storm {
    namespace modelchecker {
        template<typename ValueType>
        class ExplicitParetoCurveCheckResult : public ParetoCurveCheckResult<ValueType> {
        public:

            ExplicitParetoCurveCheckResult();
            ExplicitParetoCurveCheckResult(storm::storage::sparse::state_type const& state, std::vector<typename ParetoCurveCheckResult<ValueType>::point_type> const& points, typename ParetoCurveCheckResult<ValueType>::polytope_type const& underApproximation, typename ParetoCurveCheckResult<ValueType>::polytope_type const& overApproximation);
            ExplicitParetoCurveCheckResult(storm::storage::sparse::state_type const& state, std::vector<typename ParetoCurveCheckResult<ValueType>::point_type>&& points, typename ParetoCurveCheckResult<ValueType>::polytope_type&& underApproximation, typename ParetoCurveCheckResult<ValueType>::polytope_type&& overApproximation);
            
            ExplicitParetoCurveCheckResult(ExplicitParetoCurveCheckResult const& other) = default;
            ExplicitParetoCurveCheckResult& operator=(ExplicitParetoCurveCheckResult const& other) = default;
            ExplicitParetoCurveCheckResult(ExplicitParetoCurveCheckResult&& other) = default;
            ExplicitParetoCurveCheckResult& operator=(ExplicitParetoCurveCheckResult&& other) = default;
            virtual ~ExplicitParetoCurveCheckResult() = default;
            
            virtual bool isExplicitParetoCurveCheckResult() const override;
            virtual bool isExplicit() const override;

            virtual void filter(QualitativeCheckResult const& filter) override;
            
            storm::storage::sparse::state_type const& getState() const;

        private:
            // The state of the checked model to which the result applies
            storm::storage::sparse::state_type state;
        };
    }
}

#endif /* STORM_MODELCHECKER_EXPLICITPARETOCURVECHECKRESULT_H_ */
