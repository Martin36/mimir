#if !defined(PLANNERS_PDB_BASE_HPP_)
#define PLANNERS_PDB_BASE_HPP_

#include "../../formalism/problem.hpp"
#include "../../formalism/state.hpp"
#include "../../generators/successor_generator.hpp"
#include "heuristic_base.hpp"

namespace planners
{
    class PDBBase : public HeuristicBase
    {
      private:
        formalism::ProblemDescription problem_;
        std::vector<formalism::ActionList> relevant_actions_;  // An action is in the list at index i if it affects the atom with rank i

      protected:
        PDBBase(const formalism::ProblemDescription& problem, const planners::SuccessorGenerator& successor_generator);

        std::vector<double> compute_table(const std::vector<int32_t>& pattern);

        std::size_t get_index(const formalism::State& state, const std::vector<int32_t>& pattern);
    };

}  // namespace planners

#endif  // PLANNERS_PDB_BASE_HPP_
