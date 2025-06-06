/*
 * Copyright (C) 2023 Dominik Drexler
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

#ifndef SRC_LANGUAGES_DESCRIPTION_LOGICS_GRAMMAR_PARSER_PARSER_HPP_
#define SRC_LANGUAGES_DESCRIPTION_LOGICS_GRAMMAR_PARSER_PARSER_HPP_

#include "../parser/ast.hpp"

#include <boost/spirit/home/x3.hpp>

namespace mimir::languages::dl
{
namespace x3 = boost::spirit::x3;
namespace ascii = boost::spirit::x3::ascii;

using x3::eoi;
using x3::eol;
using x3::lit;
using x3::no_skip;
using x3::string;

using ascii::char_;
using ascii::space;

///////////////////////////////////////////////////////////////////////////
// parser public interface for testing
///////////////////////////////////////////////////////////////////////////

namespace grammar_parser
{
template<IsConceptOrRoleOrBooleanOrNumericalTag D>
struct ConstructorClass;

template<IsConceptOrRoleOrBooleanOrNumericalTag D>
struct NonTerminalClass;

template<IsConceptOrRoleOrBooleanOrNumericalTag D>
struct ConstructorOrNonTerminalClass;

template<IsConceptOrRoleOrBooleanOrNumericalTag D>
struct DerivationRuleClass;

struct FeatureCategoryDerivationRuleClass;

struct ConceptBotClass;
struct ConceptTopClass;
struct ConceptAtomicStateClass;
struct ConceptAtomicGoalClass;
struct ConceptIntersectionClass;
struct ConceptUnionClass;
struct ConceptNegationClass;
struct ConceptValueRestrictionClass;
struct ConceptExistentialQuantificationClass;
struct ConceptRoleValueMapContainmentClass;
struct ConceptRoleValueMapEqualityClass;
struct ConceptNominalClass;

struct RoleUniversalClass;
struct RoleAtomicStateClass;
struct RoleAtomicGoalClass;
struct RoleIntersectionClass;
struct RoleUnionClass;
struct RoleComplementClass;
struct RoleInverseClass;
struct RoleCompositionClass;
struct RoleTransitiveClosureClass;
struct RoleReflexiveTransitiveClosureClass;
struct RoleRestrictionClass;
struct RoleIdentityClass;

struct ConceptOrRoleNonterminalClass;

struct BooleanAtomicStateClass;
struct BooleanNonemptyClass;

struct NumericalCountClass;
struct NumericalDistanceClass;

struct GrammarHeadClass;
struct GrammarBodyClass;

struct GrammarClass;

typedef x3::rule<ConstructorClass<ConceptTag>, ast::Constructor<ConceptTag>> concept_type;
typedef x3::rule<ConceptBotClass, ast::ConceptBot> concept_bot_type;
typedef x3::rule<ConceptTopClass, ast::ConceptTop> concept_top_type;
typedef x3::rule<ConceptAtomicStateClass, ast::ConceptAtomicState> concept_atomic_state_type;
typedef x3::rule<ConceptAtomicGoalClass, ast::ConceptAtomicGoal> concept_atomic_goal_type;
typedef x3::rule<ConceptIntersectionClass, ast::ConceptIntersection> concept_intersection_type;
typedef x3::rule<ConceptUnionClass, ast::ConceptUnion> concept_union_type;
typedef x3::rule<ConceptNegationClass, ast::ConceptNegation> concept_negation_type;
typedef x3::rule<ConceptValueRestrictionClass, ast::ConceptValueRestriction> concept_value_restriction_type;
typedef x3::rule<ConceptExistentialQuantificationClass, ast::ConceptExistentialQuantification> concept_existential_quantification_type;
typedef x3::rule<ConceptRoleValueMapContainmentClass, ast::ConceptRoleValueMapContainment> concept_role_value_map_containment_type;
typedef x3::rule<ConceptRoleValueMapEqualityClass, ast::ConceptRoleValueMapEquality> concept_role_value_map_equality_type;
typedef x3::rule<ConceptNominalClass, ast::ConceptNominal> concept_nominal_type;
typedef x3::rule<NonTerminalClass<ConceptTag>, ast::NonTerminal<ConceptTag>> concept_non_terminal_type;
typedef x3::rule<ConstructorOrNonTerminalClass<ConceptTag>, ast::ConstructorOrNonTerminal<ConceptTag>> concept_choice_type;
typedef x3::rule<DerivationRuleClass<ConceptTag>, ast::DerivationRule<ConceptTag>> concept_derivation_rule_type;

typedef x3::rule<ConstructorClass<RoleTag>, ast::Constructor<RoleTag>> role_type;
typedef x3::rule<RoleUniversalClass, ast::RoleUniversal> role_universal_type;
typedef x3::rule<RoleAtomicStateClass, ast::RoleAtomicState> role_atomic_state_type;
typedef x3::rule<RoleAtomicGoalClass, ast::RoleAtomicGoal> role_atomic_goal_type;
typedef x3::rule<RoleIntersectionClass, ast::RoleIntersection> role_intersection_type;
typedef x3::rule<RoleUnionClass, ast::RoleUnion> role_union_type;
typedef x3::rule<RoleComplementClass, ast::RoleComplement> role_complement_type;
typedef x3::rule<RoleInverseClass, ast::RoleInverse> role_inverse_type;
typedef x3::rule<RoleCompositionClass, ast::RoleComposition> role_composition_type;
typedef x3::rule<RoleTransitiveClosureClass, ast::RoleTransitiveClosure> role_transitive_closure_type;
typedef x3::rule<RoleReflexiveTransitiveClosureClass, ast::RoleReflexiveTransitiveClosure> role_reflexive_transitive_closure_type;
typedef x3::rule<RoleRestrictionClass, ast::RoleRestriction> role_restriction_type;
typedef x3::rule<RoleIdentityClass, ast::RoleIdentity> role_identity_type;
typedef x3::rule<NonTerminalClass<RoleTag>, ast::NonTerminal<RoleTag>> role_non_terminal_type;
typedef x3::rule<ConstructorOrNonTerminalClass<RoleTag>, ast::ConstructorOrNonTerminal<RoleTag>> role_choice_type;
typedef x3::rule<DerivationRuleClass<RoleTag>, ast::DerivationRule<RoleTag>> role_derivation_rule_type;

typedef x3::rule<ConceptOrRoleNonterminalClass, ast::ConceptOrRoleNonterminal> concept_or_role_nonterminal_type;

typedef x3::rule<ConstructorClass<BooleanTag>, ast::Constructor<BooleanTag>> boolean_type;
typedef x3::rule<BooleanAtomicStateClass, ast::BooleanAtomicState> boolean_atomic_state_type;
typedef x3::rule<BooleanNonemptyClass, ast::BooleanNonempty> boolean_nonempty_type;
typedef x3::rule<NonTerminalClass<BooleanTag>, ast::NonTerminal<BooleanTag>> boolean_non_terminal_type;
typedef x3::rule<ConstructorOrNonTerminalClass<BooleanTag>, ast::ConstructorOrNonTerminal<BooleanTag>> boolean_choice_type;
typedef x3::rule<DerivationRuleClass<BooleanTag>, ast::DerivationRule<BooleanTag>> boolean_derivation_rule_type;

typedef x3::rule<ConstructorClass<NumericalTag>, ast::Constructor<NumericalTag>> numerical_type;
typedef x3::rule<NumericalCountClass, ast::NumericalCount> numerical_count_type;
typedef x3::rule<NumericalDistanceClass, ast::NumericalDistance> numerical_distance_type;
typedef x3::rule<NonTerminalClass<NumericalTag>, ast::NonTerminal<NumericalTag>> numerical_non_terminal_type;
typedef x3::rule<ConstructorOrNonTerminalClass<NumericalTag>, ast::ConstructorOrNonTerminal<NumericalTag>> numerical_choice_type;
typedef x3::rule<DerivationRuleClass<NumericalTag>, ast::DerivationRule<NumericalTag>> numerical_derivation_rule_type;

typedef x3::rule<FeatureCategoryDerivationRuleClass, ast::FeatureCategoryDerivationRule> feature_category_derivation_rule_type;

typedef x3::rule<GrammarHeadClass, ast::GrammarHead> grammar_head_type;
typedef x3::rule<GrammarBodyClass, ast::GrammarBody> grammar_body_type;

typedef x3::rule<GrammarClass, ast::Grammar> grammar_type;

BOOST_SPIRIT_DECLARE(concept_type,
                     concept_bot_type,
                     concept_top_type,
                     concept_atomic_state_type,
                     concept_atomic_goal_type,
                     concept_intersection_type,
                     concept_union_type,
                     concept_negation_type,
                     concept_value_restriction_type,
                     concept_existential_quantification_type,
                     concept_role_value_map_containment_type,
                     concept_role_value_map_equality_type,
                     concept_nominal_type,
                     concept_non_terminal_type,
                     concept_choice_type,
                     concept_derivation_rule_type)

BOOST_SPIRIT_DECLARE(role_type,
                     role_universal_type,
                     role_atomic_state_type,
                     role_atomic_goal_type,
                     role_intersection_type,
                     role_union_type,
                     role_complement_type,
                     role_inverse_type,
                     role_composition_type,
                     role_transitive_closure_type,
                     role_reflexive_transitive_closure_type,
                     role_restriction_type,
                     role_identity_type,
                     role_non_terminal_type,
                     role_choice_type,
                     role_derivation_rule_type)

BOOST_SPIRIT_DECLARE(concept_or_role_nonterminal_type)

BOOST_SPIRIT_DECLARE(boolean_type,
                     boolean_atomic_state_type,
                     boolean_nonempty_type,
                     boolean_non_terminal_type,
                     boolean_choice_type,
                     boolean_derivation_rule_type)

BOOST_SPIRIT_DECLARE(numerical_type,
                     numerical_count_type,
                     numerical_distance_type,
                     numerical_non_terminal_type,
                     numerical_choice_type,
                     numerical_derivation_rule_type)

BOOST_SPIRIT_DECLARE(feature_category_derivation_rule_type, grammar_head_type, grammar_body_type)

BOOST_SPIRIT_DECLARE(grammar_type)
}

namespace grammar_parser
{
concept_type const& concept_parser();
concept_bot_type const& concept_bot_parser();
concept_top_type const& concept_top_parser();
concept_atomic_state_type const& concept_atomic_state_parser();
concept_atomic_goal_type const& concept_atomic_goal_parser();
concept_intersection_type const& concept_intersection_parser();
concept_union_type const& concept_union_parser();
concept_negation_type const& concept_negation_parser();
concept_value_restriction_type const& concept_value_restriction_parser();
concept_existential_quantification_type const& concept_existential_quantification_parser();
concept_role_value_map_containment_type const& concept_role_value_map_containment_parser();
concept_role_value_map_equality_type const& concept_role_value_map_equality_parser();
concept_nominal_type const& concept_nominal_parser();
concept_non_terminal_type const& concept_non_terminal_parser();
concept_choice_type const& concept_choice_parser();
concept_derivation_rule_type const& concept_derivation_rule_parser();

role_type const& role_parser();
role_universal_type const& role_universal_parser();
role_atomic_state_type const& role_atomic_state_parser();
role_atomic_goal_type const& role_atomic_goal_parser();
role_intersection_type const& role_intersection_parser();
role_union_type const& role_union_parser();
role_complement_type const& role_complement_parser();
role_inverse_type const& role_inverse_parser();
role_composition_type const& role_composition_parser();
role_transitive_closure_type const& role_transitive_closure_parser();
role_reflexive_transitive_closure_type const& role_reflexive_transitive_closure_parser();
role_restriction_type const& role_restriction_parser();
role_identity_type const& role_identity_parser();
role_non_terminal_type const& role_non_terminal_parser();
role_choice_type const& role_choice_parser();
role_derivation_rule_type const& role_derivation_rule_parser();

concept_or_role_nonterminal_type const& concept_or_role_nonterminal_parser();

boolean_type const& boolean_parser();
boolean_atomic_state_type const& boolean_atomic_state_parser();
boolean_nonempty_type const& boolean_nonempty_parser();
boolean_non_terminal_type const& boolean_non_terminal_parser();
boolean_choice_type const& boolean_choice_parser();
boolean_derivation_rule_type const& boolean_derivation_rule_parser();

numerical_type const& numerical_parser();
numerical_count_type const& numerical_count_parser();
numerical_distance_type const& numerical_distance_parser();
numerical_non_terminal_type const& numerical_non_terminal_parser();
numerical_choice_type const& numerical_choice_parser();
numerical_derivation_rule_type const& numerical_derivation_rule_parser();

feature_category_derivation_rule_type const& feature_category_derivation_rule_parser();

grammar_head_type const& grammar_head_parser();
grammar_body_type const& grammar_body_parser();

grammar_type const& grammar_parser_();
}
}

#endif
