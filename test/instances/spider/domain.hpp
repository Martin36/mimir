#if !defined(TEST_INSTANCES_SPIDER_DOMAIN_HPP_)
#define TEST_INSTANCES_SPIDER_DOMAIN_HPP_

#include "../../expect_structures.hpp"

#include <string>

namespace test::spider
{
    static DomainParseResult domain_parse_result = { num_action_schemas : 16, num_predicates : 21, num_constants : 1, num_types : 6 };

    static std::string domain = R"(
(define (domain spider)
    (:requirements :typing :conditional-effects :action-costs :negative-preconditions)

    (:types cardposition - object
            card_or_tableau - cardposition
            card - card_or_tableau
            tableau - card_or_tableau
            deal - cardposition)

    (:constants discard - cardposition)

    (:predicates (on ?c1 - card ?c2 - cardposition)
                 (clear ?c - cardposition)
                 (in-play ?c - card)
                 (current-deal ?d - deal)
                 (can-continue-group ?c1 - card ?c2 - cardposition)
                 (can-be-placed-on ?c1 - card ?c2 - card)
                 (is-ace ?c - card)
                 (is-king ?c - card)
                 (next-deal ?d ?nd - deal)
                 (to-deal ?c - card ?p - tableau ?d - deal ?next - cardposition)
                 (currently-dealing)
                 (currently-collecting-deck)
                 (collect-card ?c - cardposition)
                 (part-of-tableau ?c - cardposition ?t - tableau)
                 (movable ?c - card)
                 (currently-updating-unmovable)
                 (make-unmovable ?c - card)
                 (currently-updating-movable)
                 (make-movable ?c - cardposition)
                 (currently-updating-part-of-tableau)
                 (make-part-of-tableau ?c - card ?t - tableau))

    (:functions (total-cost) - number)

    (:action start-dealing
        :parameters ()
        :precondition (and (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (not (currently-dealing)))
        :effect (and (currently-dealing)
                     (increase (total-cost) 1)))

    (:action deal-card
        :parameters (?c - card ?from - cardposition ?fromdeal - deal ?to - card ?totableau - tableau)
        :precondition (and (currently-dealing)
                           (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (current-deal ?fromdeal)
                           (to-deal ?c ?totableau ?fromdeal ?from)
                           (clear ?c)
                           (on ?c ?from)
                           (part-of-tableau ?to ?totableau)
                           (clear ?to))
        :effect (and (not (on ?c ?from))
                     (on ?c ?to)
                     (not (clear ?to))
                     (clear ?from)
                     (in-play ?c)
                     (part-of-tableau ?c ?totableau)
                     (movable ?c)
                     (when (not (can-continue-group ?c ?to))
                           (and (currently-updating-unmovable)
                                (make-unmovable ?to)))))

    (:action finish-dealing
        :parameters (?d ?nd - deal)
        :precondition (and (currently-dealing)
                           (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (current-deal ?d)
                           (clear ?d)
                           (next-deal ?d ?nd))
        :effect (and (not (currently-dealing))
                     (not (current-deal ?d))
                     (current-deal ?nd)))

    (:action move-to-card
        :parameters (?c - card ?from - card_or_tableau ?to - card ?totableau - tableau)
        :precondition (and (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-collecting-deck))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-dealing))
                           (movable ?c)
                           (in-play ?c)
                           (clear ?to)
                           (in-play ?to)
                           (part-of-tableau ?to ?totableau)
                           (can-be-placed-on ?c ?to)
                           (on ?c ?from))
        :effect (and (not (on ?c ?from))
                     (on ?c ?to)
                     (not (clear ?to))
                     (clear ?from)
                     (when (not (can-continue-group ?c ?from))
                           (and (currently-updating-movable)
                                (make-movable ?from)))
                     (when (not (can-continue-group ?c ?to))
                           (and (currently-updating-unmovable)
                                (make-unmovable ?to)))
                     (currently-updating-part-of-tableau)
                     (make-part-of-tableau ?c ?totableau)
                     (increase (total-cost) 1)))

    (:action move-to-tableau
        :parameters (?c - card ?from - card_or_tableau ?to - tableau)
        :precondition (and (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-collecting-deck))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-dealing))
                           (movable ?c)
                           (in-play ?c)
                           (clear ?to)
                           (on ?c ?from))
        :effect (and (not (on ?c ?from))
                     (on ?c ?to)
                     (not (clear ?to))
                     (clear ?from)
                     (when (not (can-continue-group ?c ?from))
                           (and (currently-updating-movable)
                                (make-movable ?from)))
                     (currently-updating-part-of-tableau)
                     (make-part-of-tableau ?c ?to)
                     (increase (total-cost) 1)))

    (:action change-tableau-and-continue
        :parameters (?c - card ?tbefore - tableau ?t - tableau ?next - card)
        :precondition (and (currently-updating-part-of-tableau)
                           (not (currently-collecting-deck))
                           (on ?next ?c)
                           (make-part-of-tableau ?c ?t)
                           (part-of-tableau ?c ?tbefore))
        :effect (and (not (part-of-tableau ?c ?tbefore))
                     (part-of-tableau ?c ?t)
                     (not (make-part-of-tableau ?c ?t))
                     (make-part-of-tableau ?next ?t)))

    (:action change-tableau-and-stop
        :parameters (?c - card ?tbefore - tableau ?t - tableau)
        :precondition (and (currently-updating-part-of-tableau)
                           (not (currently-collecting-deck))
                           (make-part-of-tableau ?c ?t)
                           (part-of-tableau ?c ?tbefore)
                           (clear ?c))
        :effect (and (not (part-of-tableau ?c ?tbefore))
                     (part-of-tableau ?c ?t)
                     (not (make-part-of-tableau ?c ?t))
                     (not (currently-updating-part-of-tableau))))

    (:action make-unmovable-and-continue
        :parameters (?c - card ?nextcard - card)
        :precondition (and (currently-updating-unmovable)
                           (not (currently-collecting-deck))
                           (not (currently-updating-part-of-tableau))
                           (on ?c ?nextcard)
                           (make-unmovable ?c)
                           (can-continue-group ?c ?nextcard)
                           (movable ?nextcard))
        :effect (and (not (movable ?c))
                     (make-unmovable ?nextcard)
                     (not (make-unmovable ?c))))

    (:action make-unmovable-and-stop-at-tableau
        :parameters (?c - card ?t - tableau)
        :precondition (and (currently-updating-unmovable)
                           (not (currently-collecting-deck))
                           (not (currently-updating-part-of-tableau))
                           (on ?c ?t)
                           (make-unmovable ?c))
        :effect (and (not (movable ?c))
                     (not (make-unmovable ?c))
                     (not (currently-updating-unmovable))))

    (:action make-unmovable-and-stop-at-unmovable
        :parameters (?c - card ?nextcard - card)
        :precondition (and (currently-updating-unmovable)
                           (not (currently-collecting-deck))
                           (not (currently-updating-part-of-tableau))
                           (on ?c ?nextcard)
                           (make-unmovable ?c)
                           (not (movable ?nextcard)))
        :effect (and (not (movable ?c))
                     (not (make-unmovable ?c))
                     (not (currently-updating-unmovable))
                     (not (currently-updating-part-of-tableau))))

    (:action make-movable-and-continue
        :parameters (?c - card ?nextcard - card)
        :precondition (and (currently-updating-movable)
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (on ?c ?nextcard)
                           (make-movable ?c)
                           (can-continue-group ?c ?nextcard))
        :effect (and (make-movable ?nextcard)
                     (not (make-movable ?c))
                     (movable ?c)))

    (:action make-movable-ignore-pile
        :parameters (?p - tableau)
        :precondition (and (currently-updating-movable)
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (make-movable ?p))
        :effect (and (not (make-movable ?p))
                     (not (currently-updating-movable))))

    (:action make-movable-and-stop
        :parameters (?c - card ?nextcard - cardposition)
        :precondition (and (currently-updating-movable)
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (on ?c ?nextcard)
                           (make-movable ?c)
                           (not (can-continue-group ?c ?nextcard)))
        :effect (and (not (make-movable ?c))
                     (not (currently-updating-movable))
                     (movable ?c)))

    (:action start-collecting-deck
        :parameters (?c - card)
        :precondition (and (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-collecting-deck))
                           (not (currently-dealing))
                           (clear ?c)
                           (is-ace ?c)
                           (in-play ?c))
        :effect (and (currently-collecting-deck)
                     (collect-card ?c)
                     (increase (total-cost) 1)))

    (:action collect-card
        :parameters (?c - card ?nextcard - cardposition ?p - tableau)
        :precondition (and (currently-collecting-deck)
                           (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-dealing))
                           (collect-card ?c)
                           (on ?c ?nextcard)
                           (in-play ?c)
                           (part-of-tableau ?c ?p)
                           (can-continue-group ?c ?nextcard))
        :effect (and (not (on ?c ?nextcard))
                     (on ?c discard)
                     (clear ?nextcard)
                     (not (in-play ?c))
                     (not (part-of-tableau ?c ?p))
                     (not (movable ?c))
                     (not (collect-card ?c))
                     (collect-card ?nextcard)))

    (:action finish-collecting-deck
        :parameters (?c - card ?nextcard - cardposition ?p - tableau)
        :precondition (and (currently-collecting-deck)
                           (not (currently-updating-movable))
                           (not (currently-updating-unmovable))
                           (not (currently-updating-part-of-tableau))
                           (not (currently-dealing))
                           (on ?c ?nextcard)
                           (collect-card ?c)
                           (is-king ?c)
                           (in-play ?c)
                           (part-of-tableau ?c ?p))
        :effect (and (not (on ?c ?nextcard))
                     (on ?c discard)
                     (clear ?nextcard)
                     (not (in-play ?c))
                     (not (part-of-tableau ?c ?p))
                     (not (movable ?c))
                     (not (collect-card ?c))
                     (not (currently-collecting-deck))
                     (make-movable ?nextcard)
                     (currently-updating-movable))))
)";
}  // namespace test

#endif  // TEST_INSTANCES_SPIDER_DOMAIN_HPP_
