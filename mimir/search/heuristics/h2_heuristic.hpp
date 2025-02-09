#if !defined(PLANNERS_HEURISTIC_H2_HPP_)
#define PLANNERS_HEURISTIC_H2_HPP_

#include "../../formalism/atom.hpp"
#include "../../formalism/problem.hpp"
#include "../../formalism/state.hpp"
#include "../../generators/successor_generator.hpp"
#include "heuristic_base.hpp"

#include <limits>
#include <unordered_map>
#include <vector>

namespace planners
{
    class H2Heuristic : public HeuristicBase
    {
      private:
        using InternalAction = std::tuple<std::vector<int32_t>, std::vector<int32_t>, std::vector<int32_t>, double>;

        formalism::ProblemDescription problem_;
        std::vector<InternalAction> actions_;
        std::vector<int32_t> goal_;
        mutable std::vector<double> h1_table_;
        mutable std::vector<std::vector<double>> h2_table_;

        double evaluate(const std::vector<int32_t>& ranks) const;
        double evaluate(const std::vector<int32_t>& ranks, int32_t rank) const;
        void update(int32_t rank, double value, bool& changed) const;
        void update(int32_t rank1, int32_t rank2, double value, bool& changed) const;
        void fill_tables(const formalism::State& state) const;

      public:
        H2Heuristic(const formalism::ProblemDescription& problem, const planners::SuccessorGenerator& successor_generator);

        double evaluate(const formalism::State& state) const override;
    };

    std::shared_ptr<H2Heuristic> create_h2_heuristic(const formalism::ProblemDescription& problem, const planners::SuccessorGenerator& successor_generator);
}  // namespace planners

#endif  // PLANNERS_HEURISTIC_H2_HPP_
