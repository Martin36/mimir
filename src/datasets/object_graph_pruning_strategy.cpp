/*
 * Copyright (C) 2023 Dominik Drexler and Simon Stahlberg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "mimir/datasets/object_graph_pruning_strategy.hpp"

#include "mimir/common/concepts.hpp"
#include "mimir/common/types_cista.hpp"
#include "mimir/datasets/object_graph.hpp"
#include "mimir/formalism/ground_action.hpp"
#include "mimir/formalism/repositories.hpp"
#include "mimir/formalism/utils.hpp"
#include "mimir/graphs/static_graph.hpp"
#include "mimir/graphs/static_graph_boost_adapter.hpp"
#include "mimir/search/applicable_action_generators/grounded.hpp"

#include <loki/details/utils/hash.hpp>
#include <optional>
#include <stack>

namespace mimir
{

}
