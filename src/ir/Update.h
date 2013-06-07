/*
 * Update.h
 *
 *  Created on: 06.01.2013
 *      Author: Christian Dehnert
 */

#ifndef STORM_IR_UPDATE_H_
#define STORM_IR_UPDATE_H_

#include <map>
#include <memory>

#include "expressions/BaseExpression.h"
#include "Assignment.h"

namespace storm {

namespace ir {

/*!
 * A class representing an update of a command.
 */
class Update {
public:
	/*!
	 * Default constructor. Creates an empty update.
	 */
	Update();

	/*!
	 * Creates an update with the given expression specifying the likelihood and the mapping of
	 * variable to their assignments.
     *
	 * @param likelihoodExpression An expression specifying the likelihood of this update.
	 * @param assignments A map of variable names to their assignments.
	 */
	Update(std::shared_ptr<storm::ir::expressions::BaseExpression> likelihoodExpression, std::map<std::string, storm::ir::Assignment> booleanAssignments, std::map<std::string, storm::ir::Assignment> integerAssignments);

    /*!
     * Creates a copy of the given update and performs the provided renaming.
     *
     * update The update that is to be copied.
     * renaming A mapping from names that are to be renamed to the names they are to be
     * replaced with.
     * @param booleanVariableToIndexMap A mapping from boolean variable names to their global indices.
     * @param integerVariableToIndexMap A mapping from integer variable names to their global indices.
     */
	Update(Update const& update, std::map<std::string, std::string> const& renaming, std::map<std::string, uint_fast64_t> const& booleanVariableToIndexMap, std::map<std::string, uint_fast64_t> const& integerVariableToIndexMap);

	/*!
	 * Retrieves the expression for the likelihood of this update.
     *
	 * @return The expression for the likelihood of this update.
	 */
	std::shared_ptr<storm::ir::expressions::BaseExpression> const& getLikelihoodExpression() const;

	/*!
	 * Retrieves the number of boolean assignments associated with this update.
     *
	 * @return The number of boolean assignments associated with this update.
	 */
	uint_fast64_t getNumberOfBooleanAssignments() const;

	/*!
	 * Retrieves the number of integer assignments associated with this update.
     *
	 * @return The number of integer assignments associated with this update.
	 */
	uint_fast64_t getNumberOfIntegerAssignments() const;

	/*!
	 * Retrieves a reference to the map of boolean variable names to their respective assignments.
     *
	 * @return A reference to the map of boolean variable names to their respective assignments.
	 */
	std::map<std::string, storm::ir::Assignment> const& getBooleanAssignments() const;

	/*!
	 * Retrieves a reference to the map of integer variable names to their respective assignments.
     *
	 * @return A reference to the map of integer variable names to their respective assignments.
	 */
	std::map<std::string, storm::ir::Assignment> const& getIntegerAssignments() const;

	/*!
	 * Retrieves a reference to the assignment for the boolean variable with the given name.
     *
	 * @return A reference to the assignment for the boolean variable with the given name.
	 */
	storm::ir::Assignment const& getBooleanAssignment(std::string variableName) const;

	/*!
	 * Retrieves a reference to the assignment for the integer variable with the given name.
     *
	 * @return A reference to the assignment for the integer variable with the given name.
	 */
	storm::ir::Assignment const& getIntegerAssignment(std::string variableName) const;

	/*!
	 * Retrieves a string representation of this update.
     *
	 * @return A string representation of this update.
	 */
	std::string toString() const;

private:
	// An expression specifying the likelihood of taking this update.
	std::shared_ptr<storm::ir::expressions::BaseExpression> likelihoodExpression;

	// A mapping of boolean variable names to their assignments in this update.
	std::map<std::string, storm::ir::Assignment> booleanAssignments;

	// A mapping of integer variable names to their assignments in this update.
	std::map<std::string, storm::ir::Assignment> integerAssignments;
};

} // namespace ir

} // namespace storm

#endif /* STORM_IR_UPDATE_H_ */
